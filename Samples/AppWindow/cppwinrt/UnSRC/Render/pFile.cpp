#include "pch.h"
#include "paralelo3d.h"

pFile::pFile() :
	pos(0),len(0),flag(0),buf(0),table(0)
{
}

pFile::~pFile()
{ 	
	if (table!=0)
	{
		clear_table();
		delete table;
	}
	this->close();	
}

bool pFile::open(const char *filename)
{
	close();

	if (filename[0]==0)
		return false;

	FILE *fp=fopen(filename, "rb");
	if(fp)
	{
		fseek(fp, 0, SEEK_END);
		len=ftell(fp);
		alloc_buf(len+1);
		fseek(fp, 0, SEEK_SET);
		fread(buf, len, 1, fp);
		fclose(fp);
		buf[len]=0;
		pos=0;
		name=filename;
		return true;
	}
	return false;
}

void pFile::alloc_buf(int size)
{
	buf=new unsigned char[size];
}

void pFile::close()
{
	if (buf != 0)
		delete[] buf;
	buf=0;
	pos=0;
	len=0;
}

int pFile::read(void *dest, int size)
{
	if(pos+size>=len) size=len-pos;
	memcpy(dest, &buf[pos], size);
	pos+=size;
	return size;
}

void pFile::get_string(pString& dest)
{
	int i=pos;
	while(i<len && buf[i]!='\r' && buf[i]!='\n') 
		i++;

	dest.copy((char *)buf,pos,i-pos);
	
	pos=i;
	if(pos<len && buf[pos]=='\r') pos++;
	if(pos<len && buf[pos]=='\n') pos++;
}

int pFile::get_profile_int(const char *section,const char *key,int& dest)
{
	pString s;
	if (get_profile_string(section,key,s)==0)
		return 0;

	if (sscanf((const char *)s,"%d",&dest)==0)
		return 0;

	return 1;
}


int pFile::get_profile_float(const char *section,const char *key,float& dest)
{
	pString s;
	if (get_profile_string(section,key,s)==0)
		return 0;

	if (sscanf((const char *)s,"%f",&dest)==0)
		return 0;

	return 1;
}

int pFile::get_profile_string(const char *section,const char *key,pString& dest)
{
	int i=0,j=0,k=0;

	static int last=0;
	if(table==0)
	{
		last=0;
		dest="";
		return 0;
	}

	k=strlen(key);
	
	for(i=0;i<table->num;i++)
	{
		j=(last+i)%table->num;
		if(_stricmp((*table)[j][0],section)==0)
			break;
	}

	if (i<table->num)
	{
		i=j;
		for(j=1;j<(*table)[i].num;j++)
			if (strchr((*table)[i][j],'=')-(*table)[i][j]==k && 
				_strnicmp((*table)[i][j],key,k)==0)
				{
					dest=(*table)[i][j].right((*table)[i][j].length()-k-1);
					last=i;
					return 1;
				}
	}

	last=0;
	dest="";
	return 0;
}

int pFile::find_group(const char *groupname) const
{
	if(table==0)
		return 0;

	for(int i=0;i<table->num;i++)
		if(_stricmp((*table)[i][0],groupname)==0)
			return 1;

	return 0;
}

void pFile::append_table()
{
	if (table==0){
		table=new pStringArray2;
	}

	char *c1,*c2;
	pString s;
	pArray<pString> section;
	int ok=0;

	c1=(char *)buf;
	while((c1-(char *)buf)<len) 
	{ 
		while( *c1==10 || *c1==13) 
			c1++; 
		if ((c1-(char *)buf)>=len) 
			break; 

		c2=strchr(c1,13);
		if (c2==0)
			c2=strchr(c1,10);

		if(c2==0) 
			c2=&c1[strlen(c1)]; 
		*c2=0; 

		if(*c1=='[' && *(c2-1)==']')
		{
			ok=1;

			*(c2-1)=0;
			if(find_group(c1+1))
			{
				ok=0;
				// print error
			}
			else
			{
				if(section.num>0)
					table->add(section);

				section.clear();
				section.add(pString(c1+1));
			}
		}
		else
			if(ok&&strchr(c1,'='))
				section.add(pString(c1,0,c2-c1));

		c1=c2+1;
	}

	if(section.num>0)
		table->add(section);
}

void pFile::clear_table()
{
	if (!table)
		return;

	for (int i = 0; i < table->num; i++)
		table->buf[i].free();
	table->free();
}

float pFile::get_float()
{
	while(pos<len && !((buf[pos]>=48 && buf[pos]<=57) || buf[pos]=='.' || buf[pos]=='-'))
		pos++;

	if(pos==len) return 0;

	int i=pos;
	do i++;
	while(i<len && ((buf[i]>=48 && buf[i]<=57) || buf[i]=='.'));

	pString str((char *)buf,pos,i-pos);
	pos=i;

	return (float)atof(str);
}

int pFile::get_int()
{
	while(pos<len && !((buf[pos]>=48 && buf[pos]<=57) || buf[pos]=='-'))
		pos++;

	if(pos==len) return 0;

	int i=pos;
	do i++;
	while(i<len && buf[i]>=48 && buf[i]<=57);
		
	pString str((char *)buf,pos,i-pos);
	pos=i;

	return atoi(str);
}

void pFile::seek(int offset)
{
	pos=pos+offset;
	if (pos<0)
		pos=0;
	if (pos>=len)
		pos=len-1;
}


