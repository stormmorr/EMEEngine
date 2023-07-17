/*

	icMySQL - MySQL Database Layer
	Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retains
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

#include "icMySQL.h"

/**************************************
 * Implementation of icMySQLResultSet *
 **************************************/
 
/// Constructor.
icMySQLResultSet::icMySQLResultSet ()
{
}

icMySQLResultSet::icMySQLResultSet (st_mysql_res* resultSet)
{
  recordset = resultSet;
}

/// Destructor.
icMySQLResultSet::~icMySQLResultSet ()
{
  mysql_free_result (recordset);
}

size_t icMySQLResultSet::GetRecordCount ()
{
  return recordset->row_count;
}
void icMySQLResultSet::ClearRecord (icDatabaseRecord* Record)
{
  Record->Clear ();
}
icDatabaseRecord icMySQLResultSet::NextRecord ()
{
  icDatabaseRecord rec;

  char** row = mysql_fetch_row (recordset);
  if (!row)
  {
    return rec;
  }

  unsigned int fieldcount = mysql_num_fields (recordset);
  MYSQL_FIELD* fields = mysql_fetch_fields (recordset);

  std::vector<std::string> fieldnames;
  std::vector<std::string> fieldvalues;

  // (fieldcount)

  for (unsigned int index = 0; index < fieldcount; index++)
  {
    fieldnames.push_back (fields[index].name);
    fieldvalues.push_back (row[index]);
  }

  rec.AddData(fieldvalues, fieldnames);
  return rec;
}

bool icMySQLResultSet::NextRecord (icDatabaseRecord* Record)
{
  if(!Record)
  {
    return false;
  }

  char** row = mysql_fetch_row (recordset);
  if (!row)
  {
    return false;
  }

  unsigned int fieldcount = mysql_num_fields (recordset);
  MYSQL_FIELD* fields = mysql_fetch_fields (recordset);

  std::vector<std::string> fieldnames (fieldcount);
  std::vector<std::string> fieldvalues (fieldcount);

  Record->Clear ();

  for (unsigned int index = 0; index < fieldcount; index++)
  {
    fieldnames.push_back (fields[index].name);
    fieldvalues.push_back (row[index]);
  }

  Record->AddData(fieldvalues, fieldnames);

  return true;
}

void icMySQLResultSet::NextRecord (char** rowBuffer, unsigned int* fieldcount, unsigned long* lengths)
{
  MYSQL_ROW row = mysql_fetch_row (recordset);
  *fieldcount = mysql_num_fields (recordset);

  //rowBuffer = (char**)realloc(rowBuffer, *fieldcount * sizeof(char*));
  if(!rowBuffer)
  {
    printf("Error allocating rowBuffer\n");
    return;
  }
  memcpy(lengths, mysql_fetch_lengths(recordset), *fieldcount * sizeof(unsigned long));
  for(size_t i = 0; i < *fieldcount; i++)
  {
    rowBuffer[i] = (char*)malloc((lengths[i] + 1) * sizeof(char));
    if(!rowBuffer[i])
    {
      printf("Error allocating rowBuffer[%d]\n", i);
      return;
    }
    memcpy(rowBuffer[i], row[i], lengths[i]);
    rowBuffer[i][lengths[i]] = 0;
  }
}

void icMySQLResultSet::ResetSet (void)
{
	//cursor.Reset();
}

/*******************************
 * Implementation of icMySQL *
 *******************************/

/// Constructor.
icMySQL::icMySQL (void)
{
  connection = 0;
  if (mysql_library_init (0, NULL, NULL))
  {
    printf("Error initialising MySQL Library!\n");
    exit (1);
  }
}

/// Destructor.
icMySQL::~icMySQL ()
{
  Disconnect ();
  mysql_library_end ();
  connection = 0;
}

void icMySQL::Disconnect ()
{
  mysql_close (connection);
}

bool icMySQL::Initialize (void)
{
  connection = mysql_init (NULL);

  return true;
}

bool icMySQL::Connect (const char* host, const char* username, const char* password, const char* database, unsigned short port)
{
  my_bool my_true = true;
  if (mysql_real_connect (connection, host, username, password, NULL, port, NULL, 0))
  {
    if (mysql_options (connection, MYSQL_OPT_RECONNECT, &my_true))
      printf("Failed to set option!\n");

    if (mysql_select_db (connection, database))
    { /* Select the database we want to use */
      printf("Failed to select the database\n");
      return false;
    }
  }
  else
  {
    printf("Failed to connect to database\n");
    return false;
  }
  printf("Connected to database\n");
  return true;
}

long icMySQL::acCommand (const char *cmd)
{
  //printf ("\nReceived DB Command: %s\n", cmd);
  fflush (stdout);

  if (mysql_real_query (connection, cmd, strlen (cmd)))
  {
   printf("Query Failed. Retrying...\n");
   fflush (stdout);
   //if it fails once try again as it should re-connect
  if (mysql_real_query (connection, cmd, strlen (cmd)))
    {
      printf("Failed database query\n");
      return -1;
    }
  }
  return (unsigned long) mysql_affected_rows (connection);
}

icMySQLResultSet* icMySQL::acSelectCommand (const char* cmd)
{
  MYSQL_RES* result = IssueSelectCommand (cmd);

  if (!result)
    return NULL;

  return new icMySQLResultSet(result);
}

MYSQL_RES* icMySQL::IssueSelectCommand (const char* cmd)
{
  if (mysql_real_query (connection, cmd, strlen (cmd)))
  {
    //if command fails first time, try again - it should re-connect
    if (mysql_real_query (connection, cmd, strlen (cmd)))
    {
      printf("Failed database query\n");
      return NULL;
    }
  }
  //mysql_store_result () fetches all results from the server
  //mysql_use_result () would not fetch the data immediately
  return mysql_store_result (connection);
}

int icMySQL::GetScalar (const char* cmd)
{
  MYSQL_RES* result = IssueSelectCommand (cmd);

  if (!result)
    return 0;

  char** row = mysql_fetch_row (result);
  if (row)
  {
    // might need some checks for a number returned
    return atoi (row[0]);
  }
  else
  {
    printf("ERROR mysql No Scalar found using\n");
    return 0;
  }

  mysql_free_result (result);
}

int icMySQL::GetLastInsertID ()
{
  return (int)mysql_insert_id (connection);
}

unsigned int icMySQL::Insert (const char *table, const char **fields, const char **values, int fieldcount)
{
	char cmd[1000];
    int i;

	sprintf (cmd, "INSERT INTO %s (", table);
    for (i = 0; i < fieldcount; i++)
    {
        if (i>0) strcat (cmd, ", ");
        strcat (cmd, fields[i]);
    }

    strcat (cmd, ") VALUES (");
    for (i = 0; i < fieldcount; i++)
    {
        if (i > 0) strcat (cmd, ",");
        if (values[i] != NULL)
        {
			strcat (cmd, "'");
            strcat (cmd, values[i]);
            strcat (cmd, "'");
        }
        else
        {
            strcat (cmd, "NULL");
        }
    }
    strcat (cmd, ")");

	//Do the SQL
    if (acCommand (cmd) == -1)
        return 0;

    return GetLastInsertID ();
}

bool icMySQL::Update (const char *table, const char **fields, const char **values, int fieldcount, const char *whereclause)
{
  char cmd[1000];
  int i;

  sprintf (cmd, "UPDATE %s SET ", table);

  for (i = 0; i < fieldcount; i++)
    {
        if (i > 0) strcat (cmd, ",");
        strcat (cmd, fields[i]);
        if (values[i] != "")
        {
            strcat (cmd, "='");
            strcat (cmd, values[i]); 
            strcat (cmd, "'");
        }
        else
        {
            strcat (cmd, "=NULL");
        }
    }

    strcat (cmd, " WHERE ");
	strcat (cmd, whereclause);

    if (acCommand (cmd) == -1)
    {
        return false;
    }
    return true;
}

void icMySQL::EscapeString(std::string& string, const char * data, unsigned long datalength)
{
  char* temp = (char*)malloc((datalength * 2) + 1);
  long templen = mysql_real_escape_string(connection, temp, data, datalength);
  string.empty();
  string.append(temp, templen);
  free(temp);
}

bool icMySQL::ExecutePreparedStatement(const char* SQL, unsigned char inParamCount, char** inBuffer, unsigned long* inLengths, unsigned char* ourParamCount, char** outBuffer, unsigned long* outLengths)
{
  MYSQL_STMT* statement = mysql_stmt_init(connection);
  if (!statement)
  {
    printf("mysql_stmt_init(), out of memory\n");
    return false;
  }

  if(mysql_stmt_prepare(statement, SQL, strlen(SQL)))
  {
    printf("mysql_stmt_prepare() failed\n");
    printf("%s\n", mysql_stmt_error(statement));
    return false;
  }

  unsigned long param_count= mysql_stmt_param_count(statement);

  if (param_count != inParamCount) /* validate parameter count */
  {
    printf("Invalid parameter count returned by MySQL\n");
    return false;
  }

  MYSQL_BIND* bind = (MYSQL_BIND*)calloc(inParamCount, sizeof(MYSQL_BIND));
  //memset(bind, 0, sizeof(bind));  //Not required because of calloc
  if (!bind)
  {
    printf("Out of memory while creating bind array\n");
    return false;
  }

  /* BLOB PARAMS */
  for(int i = 0; i < inParamCount; i++)
  {
    bind[i].buffer_type = MYSQL_TYPE_BLOB;
    bind[i].buffer= (char *)inBuffer[i];
    //bind[i].buffer_length = STRING_SIZE;
    bind[i].is_null= 0;
    bind[i].length = &inLengths[i];
  }

  /* Bind the buffers */
  if (mysql_stmt_bind_param(statement, bind))
  {
    printf("mysql_stmt_bind_param() failed\n");
    printf("%s\n", mysql_stmt_error(statement));
    free(bind);
    return false;
  }

  /* Execute the statement */
  if (mysql_stmt_execute(statement))
  {
    printf("mysql_stmt_execute() failed\n");
    printf("%s\n", mysql_stmt_error(statement));
    free(bind);
    return false;
  }

  my_ulonglong affected_rows = mysql_stmt_affected_rows(statement);
#ifdef _DEBUG
  printf("Total affected rows: %lu\n", (unsigned long) affected_rows);
#endif

  MYSQL_RES* meta = mysql_stmt_result_metadata(statement);

  /* Close the statement */
  if (mysql_stmt_close(statement))
  {
    printf("Failed while closing the statement\n");
    printf("%s\n", mysql_stmt_error(statement));
    free(bind);
    return false;
  }

  free(bind);
  return true;
}