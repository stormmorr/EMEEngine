#include "pch.h"
#include "pTeapot.h"
#include <math.h>

int pTeapot::patchmirror[P_TEAPOT_NUMPATCHES]=
	{ 4,4,4,4,4,2,2,2,2,4 };

int pTeapot::patchfaces[P_TEAPOT_NUMPATCHES][16]={
    { 102, 103, 104, 105,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15 },
    {  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27 },
    {  24,  25,  26,  27,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40 },
    {  96,  96,  96,  96,  97,  98,  99, 100, 101, 101, 101, 101,   0,   1,   2,   3 },
    {   0,   1,   2,   3, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117 },
    {  41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,  52,  53,  54,  55,  56 },
    {  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,  64,  28,  65,  66,  67 },
    {  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,  78,  79,  80,  81,  82,  83 },
    {  80,  81,  82,  83,  84,  85,  86,  87,  88,  89,  90,  91,  92,  93,  94,  95 },
    { 118, 118, 118, 118, 124, 122, 119, 121, 123, 126, 125, 120,  40,  39,  38,  37 } };

float pTeapot::patchverts[P_TEAPOT_NUMVERTS][3]={
    {  0.2000f,  0.0000f, 2.70000f }, {  0.2000f, -0.1120f, 2.70000f }, {  0.1120f, -0.2000f, 2.70000f },
    {  0.0000f, -0.2000f, 2.70000f }, {  1.3375f,  0.0000f, 2.53125f }, {  1.3375f, -0.7490f, 2.53125f },
    {  0.7490f, -1.3375f, 2.53125f }, {  0.0000f, -1.3375f, 2.53125f }, {  1.4375f,  0.0000f, 2.53125f },
    {  1.4375f, -0.8050f, 2.53125f }, {  0.8050f, -1.4375f, 2.53125f }, {  0.0000f, -1.4375f, 2.53125f },
    {  1.5000f,  0.0000f, 2.40000f }, {  1.5000f, -0.8400f, 2.40000f }, {  0.8400f, -1.5000f, 2.40000f },
    {  0.0000f, -1.5000f, 2.40000f }, {  1.7500f,  0.0000f, 1.87500f }, {  1.7500f, -0.9800f, 1.87500f },
    {  0.9800f, -1.7500f, 1.87500f }, {  0.0000f, -1.7500f, 1.87500f }, {  2.0000f,  0.0000f, 1.35000f },
    {  2.0000f, -1.1200f, 1.35000f }, {  1.1200f, -2.0000f, 1.35000f }, {  0.0000f, -2.0000f, 1.35000f },
    {  2.0000f,  0.0000f, 0.90000f }, {  2.0000f, -1.1200f, 0.90000f }, {  1.1200f, -2.0000f, 0.90000f },
    {  0.0000f, -2.0000f, 0.90000f }, { -2.0000f,  0.0000f, 0.90000f }, {  2.0000f,  0.0000f, 0.45000f },
    {  2.0000f, -1.1200f, 0.45000f }, {  1.1200f, -2.0000f, 0.45000f }, {  0.0000f, -2.0000f, 0.45000f },
    {  1.5000f,  0.0000f, 0.22500f }, {  1.5000f, -0.8400f, 0.22500f }, {  0.8400f, -1.5000f, 0.22500f },
    {  0.0000f, -1.5000f, 0.22500f }, {  1.5000f,  0.0000f, 0.15000f }, {  1.5000f, -0.8400f, 0.15000f },
    {  0.8400f, -1.5000f, 0.15000f }, {  0.0000f, -1.5000f, 0.15000f }, { -1.6000f,  0.0000f, 2.02500f },
    { -1.6000f, -0.3000f, 2.02500f }, { -1.5000f, -0.3000f, 2.25000f }, { -1.5000f,  0.0000f, 2.25000f },
    { -2.3000f,  0.0000f, 2.02500f }, { -2.3000f, -0.3000f, 2.02500f }, { -2.5000f, -0.3000f, 2.25000f },
    { -2.5000f,  0.0000f, 2.25000f }, { -2.7000f,  0.0000f, 2.02500f }, { -2.7000f, -0.3000f, 2.02500f },
    { -3.0000f, -0.3000f, 2.25000f }, { -3.0000f,  0.0000f, 2.25000f }, { -2.7000f,  0.0000f, 1.80000f },
    { -2.7000f, -0.3000f, 1.80000f }, { -3.0000f, -0.3000f, 1.80000f }, { -3.0000f,  0.0000f, 1.80000f },
    { -2.7000f,  0.0000f, 1.57500f }, { -2.7000f, -0.3000f, 1.57500f }, { -3.0000f, -0.3000f, 1.35000f },
    { -3.0000f,  0.0000f, 1.35000f }, { -2.5000f,  0.0000f, 1.12500f }, { -2.5000f, -0.3000f, 1.12500f },
    { -2.6500f, -0.3000f, 0.93750f }, { -2.6500f,  0.0000f, 0.93750f }, { -2.0000f, -0.3000f, 0.90000f },
    { -1.9000f, -0.3000f, 0.60000f }, { -1.9000f,  0.0000f, 0.60000f }, {  1.7000f,  0.0000f, 1.42500f },
    {  1.7000f, -0.6600f, 1.42500f }, {  1.7000f, -0.6600f, 0.60000f }, {  1.7000f,  0.0000f, 0.60000f },
    {  2.6000f,  0.0000f, 1.42500f }, {  2.6000f, -0.6600f, 1.42500f }, {  3.1000f, -0.6600f, 0.82500f },
    {  3.1000f,  0.0000f, 0.82500f }, {  2.3000f,  0.0000f, 2.10000f }, {  2.3000f, -0.2500f, 2.10000f },
    {  2.4000f, -0.2500f, 2.02500f }, {  2.4000f,  0.0000f, 2.02500f }, {  2.7000f,  0.0000f, 2.40000f },
    {  2.7000f, -0.2500f, 2.40000f }, {  3.3000f, -0.2500f, 2.40000f }, {  3.3000f,  0.0000f, 2.40000f },
    {  2.8000f,  0.0000f, 2.47500f }, {  2.8000f, -0.2500f, 2.47500f }, {  3.5250f, -0.2500f, 2.49375f },
    {  3.5250f,  0.0000f, 2.49375f }, {  2.9000f,  0.0000f, 2.47500f }, {  2.9000f, -0.1500f, 2.47500f },
    {  3.4500f, -0.1500f, 2.51250f }, {  3.4500f,  0.0000f, 2.51250f }, {  2.8000f,  0.0000f, 2.40000f },
    {  2.8000f, -0.1500f, 2.40000f }, {  3.2000f, -0.1500f, 2.40000f }, {  3.2000f,  0.0000f, 2.40000f },
    {  0.0000f,  0.0000f, 3.15000f }, {  0.8000f,  0.0000f, 3.15000f }, {  0.8000f, -0.4500f, 3.15000f },
    {  0.4500f, -0.8000f, 3.15000f }, {  0.0000f, -0.8000f, 3.15000f }, {  0.0000f,  0.0000f, 2.85000f },
    {  1.4000f,  0.0000f, 2.40000f }, {  1.4000f, -0.7840f, 2.40000f }, {  0.7840f, -1.4000f, 2.40000f },
    {  0.0000f, -1.4000f, 2.40000f }, {  0.4000f,  0.0000f, 2.55000f }, {  0.4000f, -0.2240f, 2.55000f },
    {  0.2240f, -0.4000f, 2.55000f }, {  0.0000f, -0.4000f, 2.55000f }, {  1.3000f,  0.0000f, 2.55000f },
    {  1.3000f, -0.7280f, 2.55000f }, {  0.7280f, -1.3000f, 2.55000f }, {  0.0000f, -1.3000f, 2.55000f },
    {  1.3000f,  0.0000f, 2.40000f }, {  1.3000f, -0.7280f, 2.40000f }, {  0.7280f, -1.3000f, 2.40000f },
    {  0.0000f, -1.3000f, 2.40000f },
    {  0.0000f,  0.0000f, 0.00000f }, {  1.4250f, -0.7980f, 0.00000f }, {  1.5000f,  0.0000f, 0.07500f },
    {  1.4250f,  0.0000f, 0.00000f }, {  0.7980f, -1.4250f, 0.00000f }, {  0.0000f, -1.5000f, 0.07500f },
    {  0.0000f, -1.4250f, 0.00000f }, {  1.5000f, -0.8400f, 0.07500f }, {  0.8400f, -1.5000f, 0.07500f } };

pTeapot::pTeapot()
{
	verts=0;
	numverts=0;
	faces=0;
	numfaces=0;
}

pTeapot::~pTeapot()
{
	reset();
}

void pTeapot::reset()
{
	delete[] verts;
	verts=0;
	numverts=0;

	delete[] faces;
	faces=0;
	numfaces=0;
}

void pTeapot::build(int tesselation,float scale,pTeapotMode mode)
{
	reset();

	if (tesselation<1)
		tesselation=1;

	for( int i=0;i<P_TEAPOT_NUMPATCHES;i++ )
	{
		numverts+=patchmirror[i]*(2+tesselation)*(2+tesselation);
		numfaces+=patchmirror[i]*2*(1+tesselation)*(1+tesselation);
	}

	verts=new pTeapotVertex[numverts];
	faces=new int[numfaces*3];

	build_verts(tesselation,scale,mode);
	build_faces(tesselation,mode);
}

void pTeapot::build_verts(int tesselation,float scale,pTeapotMode mode)
{
	float df=1.0f/(1+tesselation);
	int i,j,n,v,bv;

	v=0;
	for( n=0;n<P_TEAPOT_NUMPATCHES;n++ )
	{
		bv=v;
		for( j=0;j<2+tesselation;j++ )
		{
			for( i=0;i<2+tesselation;i++ )
			{
				evaluate_patch(n,i*df,j*df,&verts[v]);
				verts[v].pos[0]*=scale;
				verts[v].pos[1]*=scale;
				verts[v].pos[2]*=scale;
				if (mode==P_TEAPOT_OPENGL)
				{
					verts[v].texcoord[0]=1.0f-i*df;
					verts[v].texcoord[1]=1.0f-j*df;
				}
				else
				{
					verts[v].texcoord[0]=i*df;
					verts[v].texcoord[1]=j*df;
					verts[v].tangent[0]=-verts[v].tangent[0];
					verts[v].tangent[1]=-verts[v].tangent[1];
					verts[v].tangent[2]=-verts[v].tangent[2];
				}
				if (n>=5 && n<=8)
					if (n>=7)
						verts[v].texcoord[1]*=2;
					else
						verts[v].texcoord[1]*=4;

				v++;
			}
		}

		if (patchmirror[n]>0)
		{
			j=v-bv;
			for( i=0;i<j;i++ )
			{
				verts[v].pos[0]=verts[bv+i].pos[0];
				verts[v].pos[1]=-verts[bv+i].pos[1];
				verts[v].pos[2]=verts[bv+i].pos[2];
				verts[v].normal[0]=verts[bv+i].normal[0];
				verts[v].normal[1]=-verts[bv+i].normal[1];
				verts[v].normal[2]=verts[bv+i].normal[2];
				verts[v].tangent[0]=-verts[bv+i].tangent[0];
				verts[v].tangent[1]=verts[bv+i].tangent[1];
				verts[v].tangent[2]=-verts[bv+i].tangent[2];
				verts[v].binormal[0]=verts[bv+i].binormal[0];
				verts[v].binormal[1]=-verts[bv+i].binormal[1];
				verts[v].binormal[2]=verts[bv+i].binormal[2];
				verts[v].texcoord[0]=1.0f-verts[bv+i].texcoord[0];
				verts[v].texcoord[1]=verts[bv+i].texcoord[1];
				v++;
			}
		}

		if (patchmirror[n]==4)
		{
			j=v-bv;
			for( i=0;i<j;i++ )
			{
				verts[v].pos[0]=-verts[bv+i].pos[0];
				verts[v].pos[1]=verts[bv+i].pos[1];
				verts[v].pos[2]=verts[bv+i].pos[2];
				verts[v].normal[0]=-verts[bv+i].normal[0];
				verts[v].normal[1]=verts[bv+i].normal[1];
				verts[v].normal[2]=verts[bv+i].normal[2];
				verts[v].tangent[0]=verts[bv+i].tangent[0];
				verts[v].tangent[1]=-verts[bv+i].tangent[1];
				verts[v].tangent[2]=-verts[bv+i].tangent[2];
				verts[v].binormal[0]=-verts[bv+i].binormal[0];
				verts[v].binormal[1]=verts[bv+i].binormal[1];
				verts[v].binormal[2]=verts[bv+i].binormal[2];
				verts[v].texcoord[0]=1.0f-verts[bv+i].texcoord[0];
				verts[v].texcoord[1]=verts[bv+i].texcoord[1];
				v++;
			}
		}
	}
}

void pTeapot::build_faces(int tesselation,pTeapotMode mode)
{
	int i,j,n,f,v,bf,bv;

	f=0;
	v=0;
	for( n=0;n<P_TEAPOT_NUMPATCHES;n++ )
	{
		bf=f;
		bv=v;

		for( j=0;j<1+tesselation;j++ )
		{
			for( i=0;i<1+tesselation;i++ )
			{
				faces[f]=v+i;
				faces[f+1]=v+i+1;
				faces[f+2]=v+i+(2+tesselation);

				faces[f+3]=v+i+1;
				faces[f+4]=v+i+(2+tesselation)+1;
				faces[f+5]=v+i+(2+tesselation);
				
				f+=6;
			}
			v+=(2+tesselation);
		}
		v+=(2+tesselation);

		if (patchmirror[n]>0)
		{
			j=f-bf;
			for( i=0;i<j;i+=3 )
			{
				faces[f]=faces[bf+i+2]-bv+v;
				faces[f+1]=faces[bf+i+1]-bv+v;
				faces[f+2]=faces[bf+i]-bv+v;
				f+=3;
			}
			v+=v-bv;
		}

		if (patchmirror[n]==4)
		{
			j=f-bf;
			for( i=0;i<j;i+=3 )
			{
				faces[f]=faces[bf+i+2]-bv+v;
				faces[f+1]=faces[bf+i+1]-bv+v;
				faces[f+2]=faces[bf+i]-bv+v;
				f+=3;
			}
			v+=v-bv;
		}
	}
}

void pTeapot::evaluate_patch(int patch,float u,float v,pTeapotVertex *vertex)
{
	float u2,v2;
	float Bu[4],Bv[4];
	float Bdu[4],Bdv[4];

	u2=1.0f-u;
	Bu[0]=u2*u2*u2;
	Bu[1]=3.0f*u*u2*u2;
	Bu[2]=3.0f*u*u*u2;
	Bu[3]=u*u*u;

	v2=1.0f-v;
	Bv[0]=v2*v2*v2;
	Bv[1]=3.0f*v*v2*v2;
	Bv[2]=3.0f*v*v*v2;
	Bv[3]=v*v*v;

	u2=u*u;
	Bdu[0]=-3.0f +  6.0f*u - 3.0f*u2;
	Bdu[1]= 3.0f - 12.0f*u + 9.0f*u2;
	Bdu[2]= 6.0f*u - 9.0f*u2;
	Bdu[3]= 3.0f*u2;

	v2=v*v;
	Bdv[0]=-3.0f +  6.0f*v - 3.0f*v2;
	Bdv[1]= 3.0f - 12.0f*v + 9.0f*v2;
	Bdv[2]= 6.0f*v - 9.0f*v2;
	Bdv[3]= 3.0f*v2;

	int i,j,k;
	float f;

	vertex->pos[0]=vertex->pos[1]=vertex->pos[2]=0.0f;
	vertex->tangent[0]=vertex->tangent[1]=vertex->tangent[2]=0.0f;
	vertex->binormal[0]=vertex->binormal[1]=vertex->binormal[2]=0.0f;
	
	for( j=0;j<4;j++ )
	for( i=0;i<4;i++ )
	{
		k=patchfaces[patch][i+j*4];
		f=Bu[i]*Bv[j];
		
		vertex->pos[0]+=f*patchverts[k][0];
		vertex->pos[1]+=f*patchverts[k][1];
		vertex->pos[2]+=f*patchverts[k][2];

		vertex->tangent[0]-=patchverts[k][0]*(Bdu[i]*Bv[j]);
		vertex->tangent[1]-=patchverts[k][1]*(Bdu[i]*Bv[j]);
		vertex->tangent[2]-=patchverts[k][2]*(Bdu[i]*Bv[j]);

		vertex->binormal[0]+=patchverts[k][0]*(Bu[i]*Bdv[j]);
		vertex->binormal[1]+=patchverts[k][1]*(Bu[i]*Bdv[j]);
		vertex->binormal[2]+=patchverts[k][2]*(Bu[i]*Bdv[j]);
	}

	f = vertex->binormal[0]*vertex->binormal[0]+
		vertex->binormal[1]*vertex->binormal[1]+
		vertex->binormal[2]*vertex->binormal[2];
	if (f>0.01f)
	{
		f=1.0f/sqrtf(f);
		vertex->binormal[0]*=f;
		vertex->binormal[1]*=f;
		vertex->binormal[2]*=f;
	}

	f = vertex->tangent[0]*vertex->tangent[0]+
		vertex->tangent[1]*vertex->tangent[1]+
		vertex->tangent[2]*vertex->tangent[2];
	if (f>0.01f)
	{
		f=1.0f/sqrtf(f);
		vertex->tangent[0]*=f;
		vertex->tangent[1]*=f;
		vertex->tangent[2]*=f;

		vertex->normal[0]=vertex->binormal[1]*vertex->tangent[2]-vertex->binormal[2]*vertex->tangent[1];
		vertex->normal[1]=vertex->binormal[2]*vertex->tangent[0]-vertex->binormal[0]*vertex->tangent[2];
		vertex->normal[2]=vertex->binormal[0]*vertex->tangent[1]-vertex->binormal[1]*vertex->tangent[0];
	}
	else
	{
		if (vertex->pos[2]<1)
		{
			vertex->normal[0]=0;
			vertex->normal[1]=0;
			vertex->normal[2]=-1;
		}
		else
		{
			vertex->normal[0]=0;
			vertex->normal[1]=0;
			vertex->normal[2]=1;
		}

		vertex->tangent[0]=vertex->binormal[1]*vertex->normal[2]-vertex->binormal[2]*vertex->normal[1];
		vertex->tangent[1]=vertex->binormal[2]*vertex->normal[0]-vertex->binormal[0]*vertex->normal[2];
		vertex->tangent[2]=vertex->binormal[0]*vertex->normal[1]-vertex->binormal[1]*vertex->normal[0];
	}

	f = vertex->normal[0]*vertex->normal[0]+
		vertex->normal[1]*vertex->normal[1]+
		vertex->normal[2]*vertex->normal[2];
	if (f>0)
	{
		f=1.0f/sqrtf(f);
		vertex->normal[0]*=f;
		vertex->normal[1]*=f;
		vertex->normal[2]*=f;
	}
}
