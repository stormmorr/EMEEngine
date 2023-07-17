#include "pch.h"
#include "paralelo3d.h"

pLogReport::~pLogReport()
{
	if(m_logfile)
	{
		fclose(m_logfile);
		m_logfile=NULL;
	}
}

bool pLogReport::create_logfile(const char* path)
{
	pString filename(pString(path)+"paralelo3d.log");
	m_logfile=fopen((const char *)filename,"wt");
	if(m_logfile)
	{
		fprintf(m_logfile,"Paralelo3D Log File\n");
		fprintf(m_logfile,"lib version: %s\n\n",P_P3DVERSIONSTR);
		fflush(m_logfile);
		return true;
	}
	return false;
}

void pLogReport::print_log(int flag,const char *fmt, ...)
{
	static char ach[1024];

	if(m_logfile)
	{
		va_list va;
		va_start(va,fmt);
		vsprintf(ach,fmt,va);
		va_end(va);

		if(m_offset>0)
		{
			fseek(m_logfile,-m_offset,SEEK_CUR);
			m_offset=0;
		}

		if(flag==P_LOG_LAST_DRAWN_OBJ || flag==P_LOG_LAST_UPDATED_OBJ)
		{
			m_offset=fprintf(m_logfile,"%s",ach)+1;
			fflush(m_logfile);
		}
		else
		{
			fprintf(m_logfile,"%s",ach);
			fflush(m_logfile);
		}
	}
}