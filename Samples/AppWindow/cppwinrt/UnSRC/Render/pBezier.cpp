#include "pch.h"
#include "paralelo3d.h"

pBezierCurve::pBezierCurve() : 
	np(0), ns(0), nd(0), p(0), pivot(0,0,0) 
{ 
}

pBezierCurve::pBezierCurve(const pBezierCurve& in) : 
	p(new float[in.np*in.nd]),
	np(in.np),
	ns(in.ns),
	nd(in.nd),
	pivot(in.pivot) 
{ 
	for(int i=0; i<np*nd; i++) 
		p[i] = in.p[i];
}

pBezierCurve::~pBezierCurve() 
{ 
	reset(); 
}

void pBezierCurve::operator=(const pBezierCurve& in) 
{
	delete[] p;

	np = in.np;
	ns = in.ns;
	nd = in.nd;
	pivot = in.pivot;

	p = new float[np*nd];
	for(int i=0; i<np*nd; i++)  
		p[i] = in.p[i];
}

float pBezierCurve::distance(const float *pb,const float *p1,const float *p2) const
{
	// returns distance from point p to line defined by p1,p2

	float dot=0,len1=0,len2=0;
	int i;

	// alloc two vectors
	float *v1=new float [nd];
	float *v2=new float [nd];
	
	// compute length from (p1,p) and (p1,p2)
	for( i=0;i<nd;i++ )
	{
		v1[i]= pb[i]-p1[i];
		v2[i]=p2[i]-p1[i];
		len1+=v1[i]*v1[i];
		len2+=v2[i]*v2[i];
	}
	len1=sqrtf(len1);
	len2=sqrtf(len2);
	
	// normalize 
	if (len1>0)
		for( i=0;i<nd;i++ )
			v1[i]/=len1;
	if (len2>0)
		for( i=0;i<nd;i++ )
			v2[i]/=len2;
	
	// compute dot product
	for( i=0;i<nd;i++ )
		dot+=v1[i]*v2[i];

	// free vectors
	delete[] v1; 
	delete[] v2;

	// return distance
	return sqrtf(len1*len1*(1.0f-dot*dot));
}

int pBezierCurve::adaptative_subdiv(float maxerror,float *points,int maxpoints) const
{
	if (maxpoints<2) return 0;

	int npoints,i,j;
	float tmp;

	// start points list with two points (the curve edges)
	points[0]=0.0f;
	points[1]=1.0f;
	npoints=2;

	// subdiv curve recursevily
	subdiv(0,1,&p[0],&p[nd*(np-1)],points,npoints,maxerror,maxpoints);

	// sort points
	for( i=1;i<npoints;i++ )
		for( j=i+1;j<npoints;j++ )
			if (points[j]<points[i])
			{
				tmp=points[i];
				points[i]=points[j];
				points[j]=tmp;
			}

	// sort number of points
	return npoints;
}

void pBezierCurve::subdiv(float u1,float u2,const float *p1,const float *p2,float *points,int& npoints,float maxerror,int maxpoints) const
{
	// if points list is not full
	if (npoints<maxpoints)
	{
	// alloc a new point
	float *pb=new float[nd];
	
	// compute segment midpoint coordinate
	float u=(u1+u2)*0.5f;

	// evaluate curve at the segment midpoint
	evaluate(u,pb);

	// if error is bigger then maxerror
	if (distance(pb,p1,p2)>maxerror)
		{
		// add point to points list
		points[npoints++]=u;
		// subdiv each segment recursevily
		subdiv(u1,u,p1,pb,points,npoints,maxerror,maxpoints);
		subdiv(u,u2,pb,p2,points,npoints,maxerror,maxpoints);
		}
	
	// delete allocated point
	delete[] pb;
	}
}

void pBezierCurve::reset()
{
	delete[] p;
	p=0;
	ns=0;
	np=0;
}

void pBezierCurve::set_dim(int ndim)
{
	reset();
	nd=ndim;
}

void pBezierCurve::add_point(const float *f)
{
	// adds a new point to the curve
	// f must point to nd floats

	if (nd==0) return;
    float *t=new float[(np+1)*nd];
    if (p!=0)
        {
         memcpy(t,p,sizeof(float)*np*nd);
		 delete[] p;
        }
    p=t;
	memcpy(&p[np*nd],f,sizeof(float)*nd);
	np++;
    if (((np-4)%3)==0 && np>1)
       ns++;
}

void pBezierCurve::evaluate_tangent(float u,float *f) const 
{	
	// evaluate the curve tangent at position u
	// f must point to nd floats

	if (p==0) return;

	static float B[4];
	float u1,u2;
	int s,a,b,c;

	if (u>1.0f) u=1.0f;
	if (u<0.0f) u=0.0f;

	if (u==1.0f)
		s=np-4;
	else s=(int)(u*(np-1))/3*3;
	u1=(u-(float)s/(np-1))*ns;

	u2=u1*u1;
	B[0] =-3.0f +  6.0f*u1 - 3.0f*u2;
	B[1] = 3.0f - 12.0f*u1 + 9.0f*u2;
	B[2] = 6.0f*u1 - 9.0f*u2;
	B[3] = 3.0f*u2;

	memset(f,0,sizeof(float)*nd);

	c=s*nd;
	for( a=0;a<4;a++ )
		for( b=0;b<nd;b++ )
			f[b]+=p[c++]*B[a];
}

void pBezierCurve::evaluate(float u,float *f) const 
{
	// evaluate the curve point at position u
	// f must point to nd floats

	if (p==0) return;

	if (u>1.0f) u=1.0f;
	if (u<0.0f) u=0.0f;

	static float B[4];
	float u1,u2;
	int s,a,b,c;

	if (u==1.0f)
		s=np-4;
	else s=(int)(u*(np-1))/3*3;
	u1=(u-(float)s/(np-1))*ns;

	u2=1.0f-u1;
	B[0]=u2*u2*u2;
	B[1]=3.0f*u1*u2*u2;
	B[2]=3.0f*u1*u1*u2;
	B[3]=u1*u1*u1;

	memset(f,0,sizeof(float)*nd);

	c=s*nd;
	for( a=0;a<4;a++ )
		for( b=0;b<nd;b++ )
			f[b]+=p[c++]*B[a];
}

int pBezierCurve::load_bez(const char *file)
{
	// loads the curve from a .bez text file

	pFile fp;
	if (!fp.open(file))
		return 0;

	reset();
	int i,j,n,d;
	float *f;
	
	pivot.x=fp.get_float();
	pivot.y=fp.get_float();
	pivot.z=fp.get_float();
	d=fp.get_int();
	n=fp.get_int();
	set_dim(d);
	f=new float[d];
	for( i=0;i<n;i++ )
		{
		for( j=0;j<d;j++ )
			f[j]=fp.get_float();
		add_point(f);
		}
	delete[] f;
	fp.close();
	return 1;
}

float pBezierCurve::length() const 
{
	if (ns==0 || nd==0) return 0;

	int i,j=ns*8,k,vv=1;
	float *v[2],len=0.0f,f;
	v[0]=new float[nd];
	v[1]=new float[nd];
	evaluate(0.0f,v[0]);
	for( i=1;i<j;i++ )
	{
		evaluate((float)i/(j-1),v[vv]);
		f=0.0f;
		for( k=0;k<nd;k++ )
			f+=(v[0][k]-v[1][k])*(v[0][k]-v[1][k]);
		len+=sqrtf(f);
		vv=!vv;
	}

	delete[] v[0];
	delete[] v[1];

	return len;
}

