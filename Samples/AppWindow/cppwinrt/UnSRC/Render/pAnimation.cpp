#include "pch.h"
#include "paralelo3d.h"

int pAnimation::typesize[6] = { 1,3,3,9,4,4 };
int pAnimation::typevaluesize[6] = { 1,1,3,3,4,4 };

pAnimation::pAnimation() :
	type(-1),
	keysize(0),
	valuesize(0),
	numkey(0),
	keytime(0),
	keyvalue(0),
	curtime(0),
	curtimekey(0)
{
	lastvalue[0]=lastvalue[1]=
	lastvalue[2]=lastvalue[3]=0.0;
}

pAnimation::pAnimation(const pAnimation& in)
{
	type=in.type;
	keysize=in.keysize;
	valuesize=in.valuesize;
	numkey=in.numkey;
	curtime=in.curtime;
	curtimekey=in.curtimekey;
	if (numkey==0)
	{
		keytime=0;
		keyvalue=0;
	}
	else
	{
		keytime=new float[numkey];
		keyvalue=new float[numkey*keysize];
		int i;
		for( i=0;i<numkey;i++ )
			keytime[i]=in.keytime[i];
		for( i=0;i<numkey*keysize;i++ )
			keyvalue[i]=in.keyvalue[i];
	}
}

void pAnimation::operator=(const pAnimation& in)
{
	reset();
	type=in.type;
	keysize=in.keysize;
	valuesize=in.valuesize;
	numkey=in.numkey;
	curtime=in.curtime;
	curtimekey=in.curtimekey;
	if (numkey==0)
	{
		keytime=0;
		keyvalue=0;
	}
	else
	{
		keytime=new float[numkey];
		keyvalue=new float[numkey*keysize];
		int i;
		for( i=0;i<numkey;i++ )
			keytime[i]=in.keytime[i];
		for( i=0;i<numkey*keysize;i++ )
			keyvalue[i]=in.keyvalue[i];
	}
}

pAnimation::~pAnimation()
{
	reset();
}

void pAnimation::reset()
{
	type=-1;
	keysize=0;
	valuesize=0;
	numkey=0;
	delete[] keytime;
	delete[] keyvalue;
	keytime=0;
	keyvalue=0;
	curtime=0;
	curtimekey=0;
}

void pAnimation::set_type(int t)
{
	reset();

	if (t<0) t=0;
	if (t>5) t=5;
	type=t;

	keysize=typesize[t];
	valuesize=typevaluesize[t];
}

void pAnimation::set_numkeys(int nk,int zero_mem,int keep_old)
{
	if (nk<=0)
	{
		reset();
		return;
	}

	int i;
	float* tmp1;
	float* tmp2;

	tmp1=new float[nk];
	tmp2=new float[nk*keysize];

	if (zero_mem)
	{
		for( i=0;i<numkey;i++ )
			tmp1[i]=0;
		for( i=0;i<numkey*keysize;i++ )
			tmp2[i]=0;
	}

	if (keep_old)
	{
		for( i=0;i<numkey;i++ )
			tmp1[i]=keytime[i];
		for( i=0;i<numkey*keysize;i++ )
			tmp2[i]=keyvalue[i];
	}

	delete[] keytime;
	delete[] keyvalue;

	numkey=nk;
	keytime=tmp1;
	keyvalue=tmp2;

	curtime=0;
	curtimekey=0;
}

void pAnimation::read(pFile& fp,int ver)
{
	int t,nk;
	
	fp.read(&nk,sizeof(int));
	if (nk)
	{
		fp.read(&t,sizeof(int));
		set_type(t);
		set_numkeys(nk);
		fp.read(keytime,nk*sizeof(float));
		fp.read(keyvalue,nk*keysize*sizeof(float));
	}
}

void pAnimation::write(FILE *fp) const
{
	fwrite(&numkey,1,sizeof(int),fp);
	if (numkey)
	{
		fwrite(&type,1,sizeof(int),fp);
		fwrite(keytime,numkey,sizeof(float),fp);
		fwrite(keyvalue,numkey*keysize,sizeof(float),fp);
	}
}

void pAnimation::evaluate_bezier(const float *p,int n,float f,float *o) const
{
	float u1,u2;
	u1=f;
	u2=1.0f-u1;

	float B[4];
	B[0]=u2*u2*u2;
	B[1]=3.0f*u1*u2*u2;
	B[2]=3.0f*u1*u1*u2;
	B[3]=u1*u1*u1;

	int a,b,c;
	for( a=0;a<n;a++ )
		o[a]=0;
	
	c=0;
	for( a=0;a<4;a++ )
		for( b=0;b<n;b++ )
			o[b]+=p[c++]*B[a];
}

void pAnimation::update_loop(float time,float* value)
{
	if (numkey==0) 
		return;

	time=fmodf(time,keytime[numkey-1]);

	update(time,value);
}

void pAnimation::update(float time,float* value)
{
	if (numkey==0) 
		return;

	int i,j,k;

	if (time<0)
		time=0;
	else
	if (time>keytime[numkey-1])
		time=keytime[numkey-1];
	
	i=curtime<time?curtimekey:0;
	for( ;i<numkey;i++ )
		if (keytime[i]>time)
			break;
	
	curtime=time;
	curtimekey=i;

	k=i*keysize;
	if (i==0)
		for( j=0;j<valuesize;j++ )
			value[j]=keyvalue[j];
	else
	if (i==numkey)
		for( j=0;j<valuesize;j++ )
			value[j]=keyvalue[k+j-keysize];
	else
	if (type>3)
	{
		float f=(time-keytime[i-1])/(keytime[i]-keytime[i-1]);
		pQuaternion *q1=(pQuaternion *)value;
		q1->slerp(*((pQuaternion *)&keyvalue[k-keysize]),
			*((pQuaternion *)&keyvalue[k]),f);
	}
	else
	{
		float f=(time-keytime[i-1])/(keytime[i]-keytime[i-1]);
		if ((type&1)==0)
			for( j=0;j<valuesize;j++ )
				value[j]=(1.0f-f)*keyvalue[k+j-keysize]+f*keyvalue[k+j];
		else
			evaluate_bezier(&keyvalue[k-keysize+keysize/3],valuesize,f,value);
	}
	
	for( i=0;i<valuesize;i++ )
		lastvalue[i]=value[i];
}

float pAnimation::get_maxtime()
{
	if (numkey==0)
		return 0;
	return keytime[numkey-1];
}
