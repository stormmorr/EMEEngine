#include "paralelo3d.h"

pString::~pString()
{ 
	delete[] buf;
}

pString::pString() : 
	size(STR_MINSIZE),len(0)
{ 
	buf=new char[size];
	buf[0]=0; 
}

pString::pString(const char* in) :
	len(strlen(in))
{
	size=STR_MINSIZE; 
	while( size<len+1 ) size+=size>>1;

	buf=new char[size];
	strcpy(buf,in);
}

pString::pString(const pString& in) :
	len(in.len),size(in.size)
{
	buf=new char[size];
	strcpy(buf,(const char *)in);
}

pString::pString(const char* in,int p,int n) :
	len(n)
{
	size=STR_MINSIZE; 
	while( size<len+1 ) size+=size>>1;

	buf=new char[size];
	memcpy(buf,&in[p],len);
	buf[len]=0;
}

void pString::operator=(const pString& in)
{ 
	operator=((const char *)in); 
}

void pString::operator=(const char* in)
{
	len=strlen(in);
	if(size<len+1)
	{
		while( size<len+1 ) size<<=1;

		delete[] buf;
		buf=new char[size];
	}
	strcpy(buf,in);
}

void pString::operator+=(const pString& in)
{ 
	operator+=((const char *)in); 
}

void pString::operator+=(const char* in)
{
	len+=strlen(in);
	if(size<len+1)
	{
		while( size<len+1 ) size<<=1;

		char* temp=new char[size];
		strcpy(temp,buf);
		strcat(temp,in);
		delete[] buf;
		buf=temp;
	}
	else
		strcat(buf,in);
}

pString pString::operator+(const char* in) const
{ 
	pString str(buf);
	str+=in;
	return str;
}

pString pString::operator+(const pString& in) const
{ 
	return operator+((const char *)in); 
}

void pString::copy(const char* in,int p,int n)
{
	len=n;
	if (size<len+1)
	{
		while( size<len+1 ) size<<=1;

		char* temp=new char[size];
		strncpy(temp,&in[p],len);
		delete[] buf;
		buf=temp;
	}
	else
		strncpy(buf,&in[p],len);
	buf[len]=0;
}

void pString::reserve(int s)
{
	if (size<s)
	{
		char* temp=new char[s];
		memcpy(temp,buf,size);
		delete[] buf;
		buf=temp;
		size=s;
	}
}

int pString::find(const char *str) const
{ 
	char *pos=strstr(buf,str);
	if (pos==0)
		return -1;
	return (int)(pos-buf); 
}

int pString::find(char c) const
{ 
	char *pos=strchr(buf,c);
	if (pos==0)
		return -1;
	return (int)(pos-buf); 
}

int pString::find_reverse(char c) const
{
	char *pos=strrchr(buf,c);
	if (pos==0)
		return -1;
	return (int)(pos-buf); 
}

void pString::set_char(int i,char c)
{ 
	if (i<len) 
		buf[i]=c;
	if (c==0)
		if (len>i)
			len=i;
}

void pString::crop_begin(int n)
{ 
	if (n<len)
	{
		len-=n;
		strcpy(buf,&buf[n]);
	}
}

pString pString::left(int n) const
{ 
	return pString(buf,0,n); 
}

pString pString::right(int n) const
{ 
	return pString(n<=len?&buf[len-n]:&buf[0]); 
}

pString pString::mid(int p,int n) const
{ 
	return pString(buf,p,n); 
}

void pString::format(const char *fmt, ...)
{
	static char ach[32760];
	
	va_list va;
	va_start( va, fmt );
	vsprintf( ach, fmt, va );
	va_end( va );

	operator=(ach);
}

int pString::write(FILE *fp) const
{ 
	int i=0;
	do fwrite(&buf[i],1,1,fp);
	while(buf[i++]!=0);
	return i;
}

int pString::read(pFile& fp)
{ 
	len=-1;
	do 
	{
		len++;
		if (size<=len)
			reserve(size+(size>>1));
		fp.read(&buf[len],1);
	} while(buf[len]!=0);
	return len;
}
