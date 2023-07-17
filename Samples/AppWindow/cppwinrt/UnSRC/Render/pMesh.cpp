#include "pch.h"
#include "paralelo3d.h"

pMesh::pMesh()
{
	flags=0;
	vert=0;
	facevert=0;
	facemat=0;
	face=0;
	mat=0;
	cam=0;
	light=0;
	dummy=0;
	obb=0;
	nvert=0;
	nface=0;
	nfacemat=0;
	nmat=0;
	ncam=0;
	nlight=0;
	ndummy=0;
	nobb=0;
	vertbuffer=0;
	facebuffer=0;

	edge=0;
	nedge=0;
}

pMesh::~pMesh()
{
	reset();
}

void pMesh::reset()
{
	octree.reset();

	delete[] vert;
	delete[] facevert;
	delete[] facemat;
	delete[] face;
	delete[] cam;
	delete[] mat;
	delete[] light;
	delete[] dummy;
	delete[] obb;
	flags=0;
	vert=0;
	facevert=0;
	facemat=0;
	face=0;
	mat=0;
	cam=0;
	light=0;
	dummy=0;
	obb=0;
	nvert=0;
	nface=0;
	nfacemat=0;
	nmat=0;
	ncam=0;
	nlight=0;
	ndummy=0;
	nobb=0;
	ambient.vec(0.25f);
	bgcolor.null();
	bgpic="";
	bgmode=1;

#ifndef P_DISABLE_3D
	if (GLEW_ARB_vertex_buffer_object)
	{
		if (vertbuffer)
			glDeleteBuffersARB(1,&vertbuffer);
		if (facebuffer)
			glDeleteBuffersARB(1,&facebuffer);
	}
#endif
	vertbuffer=0;
	facebuffer=0;

	name.set_char(0,0);

	delete edge;
	edge=0;
	nedge=0;
}

void pMesh::set_numface(int nf,int keepold)
{
	pFace *tmp=0;
	if (nf)
		tmp=new pFace[nf];
	if (keepold && face)
		for( int i=0;i<nface&&i<nf;i++ )
			tmp[i]=face[i];
	delete[] face;
	face=tmp;

	for( int i=0;i<nf;i++ )
		face[i].vertindx=i*3;

#ifdef P_MESH_SHORT_FACE
	unsigned short *tmp2=0;
	if (nf)
		tmp2=new unsigned short[nf*3];
#else
	unsigned int *tmp2=0;
	if (nf)
		tmp2=new unsigned int[nf*3];
#endif
	if (keepold && facevert)
		for( int i=0;i<nface*3&&i<nf*3;i++ )
			tmp2[i]=facevert[i];
	delete[] facevert;
	facevert=tmp2;
	
	nface=nf;
}

void pMesh::set_numvert(int nv,int keepold)
{
	pVertex *tmp=0;
	if (nv)
		tmp=new pVertex[nv];
	if (keepold && vert)
		for( int i=0;i<nvert&&i<nv;i++ )
			tmp[i]=vert[i];
	delete[] vert;
	vert=tmp;

	nvert=nv;
}

void pMesh::set_nummat(int nm,int keepold)
{
	pMaterial *tmp=0;
	if (nm)
		tmp=new pMaterial[nm];
	if (keepold && mat)
		for( int i=0;i<nmat&&i<nm;i++ )
			tmp[i]=mat[i];
	delete[] mat;
	mat=tmp;
	nmat=nm;
}

void pMesh::set_numfacemat(int nfm,int keepold)
{
	int *tmp=0;
	if (nfm)
		tmp=new int[nfm];
	if (keepold && facemat)
		for( int i=0;i<nfacemat&&i<nfm;i++ )
			tmp[i]=facemat[i];
	delete[] facemat;
	facemat=tmp;
	nfacemat=nfm;
}

void pMesh::set_numcam(int nc,int keepold)
{
	pCamera *tmp=0;
	if (nc)
		tmp=new pCamera[nc];
	if (keepold && cam)
		for( int i=0;i<ncam&&i<nc;i++ )
			tmp[i]=cam[i];
	delete[] cam;
	cam=tmp;
	ncam=nc;
}

void pMesh::set_numlight(int nl,int keepold)
{
	pLight *tmp=0;
	if (nl)
		tmp=new pLight[nl];
	if (keepold && light)
		for( int i=0;i<nlight&&i<nl;i++ )
			tmp[i]=light[i];
	delete[] light;
	light=tmp;
	nlight=nl;
}

void pMesh::set_numdummy(int nd,int keepold)
{
	pDummy *tmp=0;
	if (nd)
		tmp=new pDummy[nd];
	if (keepold && dummy)
		for( int i=0;i<ndummy&&i<nd;i++ )
			tmp[i]=dummy[i];
	delete[] dummy;
	dummy=tmp;
	ndummy=nd;
}

void pMesh::set_numobb(int no,int keepold)
{
	pOrientedBoundBox *tmp=0;
	if (no)
		tmp=new pOrientedBoundBox[no];
	if (keepold && obb)
		for( int i=0;i<nobb&&i<no;i++ )
			tmp[i]=obb[i];
	delete[] obb;
	obb=tmp;
	nobb=no;
}

void pMesh::compute_normals(float f_UVFactor, int mode)
{
	int i,j,k;
	pVector v0,v1,v2;
	pVertex *vv0,*vv1,*vv2;

	if (mode&P_COMPUTE_FACENORM)
	{
		k=0;
		for( i=0;i<nface;i++,k+=3 )
		{
			vv0=&vert[facevert[k]];
			vv1=&vert[facevert[k+1]];
			vv2=&vert[facevert[k+2]];
			v0.vec(vv0->pos[0],vv0->pos[1],vv0->pos[2]);
			v1.vec(vv1->pos[0],vv1->pos[1],vv1->pos[2]);
			v2.vec(vv2->pos[0],vv2->pos[1],vv2->pos[2]);

			v1=v1-v0;
			v2=v2-v0;

			face[i].face_normal.cross(v1,v2);
			face[i].face_normal.normalize();
			face[i].face_normal.w=VECDOT(face[i].face_normal,v0);
		}
	}

	if (mode&P_COMPUTE_VERTNORM)
	{
		pVector d1,d2;
		float f;

		for( i=0;i<nvert;i++ )
			vert[i].norm[0]=vert[i].norm[1]=vert[i].norm[2]=0;

		k=0;
		for( i=0;i<nface;i++,k+=3 )
			for( j=0;j<3;j++ )
			{
				vv0=&vert[facevert[k+j]];
				vv1=&vert[facevert[k+((j+1)%3)]];
				vv2=&vert[facevert[k+((j+2)%3)]];
				v0.vec(vv0->pos[0],vv0->pos[1],vv0->pos[2]);
				v1.vec(vv1->pos[0],vv1->pos[1],vv1->pos[2]);
				v2.vec(vv2->pos[0],vv2->pos[1],vv2->pos[2]);

				d1=v1-v0;
				d2=v2-v0;
				d1.normalize();
				d2.normalize();
				
				f=VECDOT(d1,d2);
				f=acosf(f);
				vv0->norm[0]+=f*face[i].face_normal.x;
				vv0->norm[1]+=f*face[i].face_normal.y;
				vv0->norm[2]+=f*face[i].face_normal.z;
			}
		
		for( i=0;i<nvert;i++ )
		{
			f=sqrtf(
					vert[i].norm[0]*vert[i].norm[0]+
					vert[i].norm[1]*vert[i].norm[1]+
					vert[i].norm[2]*vert[i].norm[2]);
			if (f>0.01f)
			{
				f=1.0f/f;
				vert[i].norm[0]*=f;
				vert[i].norm[1]*=f;
				vert[i].norm[2]*=f;
			}
		}
	}

	if (mode&P_COMPUTE_TANGENTS)
		compute_tangents();

	if (mode&P_COMPUTE_CURVATURE)
		compute_curvature();

	if (mode&P_COMPUTE_BBOX)
	{
		bbox.reset();
		for( i=0;i<nvert;i++ )
			bbox.add_point(vert[i].pos);
	}

	update_buffers(f_UVFactor);
}

void pMesh::compute_tangents()
{
	pVector v0,v1,v2;
	pVector p0,p1,p2;
	pVector d1,d2;
	float uv[3][2],det,u,v,l1,l2;
	int i,j,k;

#ifndef P_MESH_SHORT_VERT
	int *count=new int[nvert];
#endif

	for( i=0;i<nvert;i++ )
	{
		vert[i].tanu[0]=vert[i].tanu[1]=vert[i].tanu[2]=0;
		vert[i].tanv[0]=vert[i].tanv[1]=vert[i].tanv[2]=0;
#ifndef P_MESH_SHORT_VERT
		vert[i].tanv[3]=vert[i].tanu[3]=0;
		count[i]=0;
#endif
	}

	k=0;
	for( i=0;i<nface;i++,k+=3 )
	{
		v0=*((pVector *)&vert[facevert[k]]);
		v1=*((pVector *)&vert[facevert[k+1]])-v0;
		v2=*((pVector *)&vert[facevert[k+2]])-v0;

		uv[0][0]=vert[facevert[k]].tx[0];
		uv[0][1]=vert[facevert[k]].tx[1];
		uv[1][0]=vert[facevert[k+1]].tx[0]-uv[0][0];
		uv[1][1]=vert[facevert[k+1]].tx[1]-uv[0][1];
		uv[2][0]=vert[facevert[k+2]].tx[0]-uv[0][0];
		uv[2][1]=vert[facevert[k+2]].tx[1]-uv[0][1];
		det=uv[1][0]*uv[2][1]-uv[2][0]*uv[1][1];

		if (fabsf(det)<0.000001f) 
			continue;

		u=0; v=0;
		u-=uv[0][0]; v-=uv[0][1];
		p0=v0+v1*((u*uv[2][1]-uv[2][0]*v)/det)+v2*((uv[1][0]*v-u*uv[1][1])/det);
		
		u=1; v=0;
		u-=uv[0][0]; v-=uv[0][1];
		p1=v0+v1*((u*uv[2][1]-uv[2][0]*v)/det)+v2*((uv[1][0]*v-u*uv[1][1])/det);

		u=0; v=1;
		u-=uv[0][0]; v-=uv[0][1];
		p2=v0+v1*((u*uv[2][1]-uv[2][0]*v)/det)+v2*((uv[1][0]*v-u*uv[1][1])/det);

		d1=p1-p0;
		d2=p2-p0;
		l1=d1.length();
		l2=d2.length();
		d1*=1.0f/l1;
		d2*=1.0f/l2;

		j=facevert[k];
		vert[j].tanu[0]+=d1.x;	vert[j].tanu[1]+=d1.y;	vert[j].tanu[2]+=d1.z;
		vert[j].tanv[0]+=d2.x;	vert[j].tanv[1]+=d2.y;	vert[j].tanv[2]+=d2.z;
#ifndef P_MESH_SHORT_VERT
		vert[j].tanu[3]+=l1;
		vert[j].tanv[3]+=l2;
		count[j]++;
#endif

		j=facevert[k+1];
		vert[j].tanu[0]+=d1.x;	vert[j].tanu[1]+=d1.y;	vert[j].tanu[2]+=d1.z;
		vert[j].tanv[0]+=d2.x;	vert[j].tanv[1]+=d2.y;	vert[j].tanv[2]+=d2.z;
#ifndef P_MESH_SHORT_VERT
		vert[j].tanu[3]+=l1;
		vert[j].tanv[3]+=l2;
		count[j]++;
#endif

		j=facevert[k+2];
		vert[j].tanu[0]+=d1.x;	vert[j].tanu[1]+=d1.y;	vert[j].tanu[2]+=d1.z;
		vert[j].tanv[0]+=d2.x;	vert[j].tanv[1]+=d2.y;	vert[j].tanv[2]+=d2.z;
#ifndef P_MESH_SHORT_VERT
		vert[j].tanu[3]+=l1;
		vert[j].tanv[3]+=l2;
		count[j]++;
#endif
	}

	for( i=0;i<nvert;i++ )
	{
		v0.vec(vert[i].tanu[0],vert[i].tanu[1],vert[i].tanu[2]);
		v0.normalize();
		v1.vec(vert[i].tanv[0],vert[i].tanv[1],vert[i].tanv[2]);
		if (v1.length2()<0.01f)
		{
			pVector n(vert[i].norm[0],vert[i].norm[1],vert[i].norm[2]);
			v1.cross(v0,n);
		}
		v1.normalize();

		vert[i].tanu[0]=v0.x;
		vert[i].tanu[1]=v0.y;
		vert[i].tanu[2]=v0.z;
		vert[i].tanv[0]=v1.x;
		vert[i].tanv[1]=v1.y;
		vert[i].tanv[2]=v1.z;
#ifndef P_MESH_SHORT_VERT		
		vert[i].tanu[3]/=count[i];
		vert[i].tanv[3]/=count[i];
#endif
	}

#ifndef P_MESH_SHORT_VERT
	delete[] count;
#endif
}

void pMesh::update_buffers(float f_UVFactor, int flagsb)
{
#ifndef P_DISABLE_3D
	if (GLEW_ARB_vertex_buffer_object==0 || g_render->vertbuffer==0)
		return;

	if (flagsb==-1)
	{
		if (vertbuffer)
			glDeleteBuffersARB(1,&vertbuffer);
		vertbuffer=0;
		if (facebuffer)
			glDeleteBuffersARB(1,&facebuffer);
		facebuffer=0;
		
		return;
	}

	if(f_UVFactor != 1 && f_UVFactor != 0)
		{
		for(int f_flag = 0; f_flag < nvert; f_flag++)
			{
			vert[f_flag].tx[0] *= f_UVFactor;
			vert[f_flag].tx[1] *= f_UVFactor;
			}
		}

	if (vert && (flagsb&1))
	{
		if (vertbuffer==0)
			glGenBuffersARB(1,&vertbuffer);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB,vertbuffer);
		glBufferDataARB(GL_ARRAY_BUFFER_ARB,sizeof(pVertex)*nvert,vert,(flagsb&4)?GL_DYNAMIC_DRAW_ARB:GL_STATIC_DRAW_ARB);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB,0);
	}
	if (facevert && (flagsb&2))
	{
		if (facebuffer==0)
			glGenBuffersARB(1,&facebuffer);
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB,facebuffer);
#ifdef P_MESH_SHORT_FACE
		glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB,sizeof(unsigned short)*nface*3,facevert,(flagsb&4)?GL_DYNAMIC_DRAW_ARB:GL_STATIC_DRAW_ARB);
#else
		glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB,sizeof(unsigned int)*nface*3,facevert,(flagsb&4)?GL_DYNAMIC_DRAW_ARB:GL_STATIC_DRAW_ARB);
#endif
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB,0);
	}
#endif
}

int pMesh::save_p3d(const char *file)
{
	FILE *fp;
	fp=fopen(file,"wb");
	if (fp==0)
		return 0;

	int i,ver;

	i=P3D_FILEID;
	fwrite(&i,1,sizeof(int),fp);
	ver=P3D_FILEVER+8;
	fwrite(&ver,1,sizeof(int),fp);

	fwrite(&nvert,1,sizeof(int),fp);
	fwrite(&nface,1,sizeof(int),fp);
	fwrite(&nmat,1,sizeof(int),fp);
	fwrite(&ncam,1,sizeof(int),fp);
	fwrite(&nlight,1,sizeof(int),fp);
	fwrite(&ndummy,1,sizeof(int),fp);
	fwrite(&nobb,1,sizeof(int),fp);

	fwrite(&ambient.x,4,sizeof(float),fp);
	fwrite(&bgmode,1,sizeof(int),fp);
	fwrite(&bgcolor.x,4,sizeof(float),fp);
	bgpic.write(fp);

	pVector f0(0);
	for( i=0;i<nvert;i++ )
	{
		fwrite(vert[i].pos,3,sizeof(float),fp);
		fwrite(vert[i].norm,3,sizeof(float),fp);
		fwrite(vert[i].tx,2,sizeof(float),fp);
#ifdef P_MESH_SHORT_VERT
		fwrite(vert[i].tanu,3,sizeof(float),fp);
		fwrite(&f0.x,1,sizeof(float),fp);
		fwrite(vert[i].tanv,3,sizeof(float),fp);
		fwrite(&f0.x,3,sizeof(float),fp);
#else
		fwrite(vert[i].tanu,4,sizeof(float),fp);
		fwrite(vert[i].tanv,4,sizeof(float),fp);
		fwrite(vert[i].curv,2,sizeof(float),fp);
#endif
	}
#ifdef P_MESH_SHORT_FACE
	unsigned int *ui=new unsigned int[3*nface];
	for( i=0;i<3*nface;i++ )
		ui[i]=facevert[i];
	fwrite(ui,3*nface,sizeof(unsigned int),fp);
	delete ui;
#else
	fwrite(facevert,3*nface,sizeof(unsigned int),fp);
#endif

	for( i=0;i<nface;i++ )
		face[i].write(fp);
	for( i=0;i<nmat;i++ )
		mat[i].write(fp);
	for( i=0;i<ncam;i++ )
		cam[i].write(fp);
	for( i=0;i<nlight;i++ )
		light[i].write(fp);
	for( i=0;i<ndummy;i++ )
		dummy[i].write(fp);
	for( i=0;i<nobb;i++ )
		obb[i].write(fp);

	fclose(fp);
	flags&=~P_MESHFLAGS_DIRTY;
	return 1;
}

int pMesh::ray_intersect(const pVector& ro,const pVector& rd,pVector& ip,float& dist) const
{
	pVector v;
	float d;
	int i,ret=-1;

	if (octree.root)
	{
		pFace *f=octree.ray_intersect(ro,rd,v,d,0);
		if (f)
		{
			ret=f->vertindx/3;
			dist=d;
			ip=v;
		}
	}
	else
	{
		dist=BIG;
		for( i=0;i<nface;i++ )
			if (face[i].ray_intersect(vert,facevert,ro,rd,v,d) &&
				d<dist)
			{
				ip=v;
				dist=d;
				ret=i;
			}
	}

	return ret;
}

void pMesh::array_lock(int renderflag,int vb) const
{
#ifndef P_DISABLE_3D
	if (GLEW_ARB_vertex_buffer_object && vb && vertbuffer)
	{
		glBindBufferARB(GL_ARRAY_BUFFER_ARB,vertbuffer);
		if (facebuffer)
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB,facebuffer);
		
		glDisableClientState(GL_COLOR_ARRAY);

		glVertexPointer(3,GL_FLOAT,sizeof(pVertex),0);
		glEnableClientState(GL_VERTEX_ARRAY);

		if (renderflag&P_RENDERFLAG_NORMAL)
		{
			glNormalPointer(GL_FLOAT,sizeof(pVertex),(void *)(sizeof(float)*3));
			glEnableClientState(GL_NORMAL_ARRAY);
		}
		else
			glDisableClientState(GL_NORMAL_ARRAY);
		
		if (renderflag&P_RENDERFLAG_TEXTURE)
		{
			glTexCoordPointer(2,GL_FLOAT,sizeof(pVertex),(void *)(sizeof(float)*6));
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		}
		else
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);

		if ((renderflag&P_RENDERFLAG_TEXTURE2) && 
			g_render->maxtextureunits>1)
		{
			glClientActiveTextureARB(GL_TEXTURE1_ARB);
			glTexCoordPointer(2,GL_FLOAT,sizeof(pVertex),(void *)(sizeof(float)*6));
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glClientActiveTextureARB(GL_TEXTURE0_ARB);
		}
		else
		if (g_render->maxtextureunits>2)
		{
#ifdef P_MESH_SHORT_VERT
			if (renderflag&P_RENDERFLAG_TANGENT)
			{
				glClientActiveTextureARB(GL_TEXTURE2_ARB);
				glTexCoordPointer(3,GL_FLOAT,sizeof(pVertex),(void *)(sizeof(float)*11));
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				glClientActiveTextureARB(GL_TEXTURE1_ARB);
				glTexCoordPointer(3,GL_FLOAT,sizeof(pVertex),(void *)(sizeof(float)*8));
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				glClientActiveTextureARB(GL_TEXTURE0_ARB);
			}
			else
			{
				glClientActiveTextureARB(GL_TEXTURE2_ARB);
				glDisableClientState(GL_TEXTURE_COORD_ARRAY);
				glClientActiveTextureARB(GL_TEXTURE1_ARB);
				glDisableClientState(GL_TEXTURE_COORD_ARRAY);
				glClientActiveTextureARB(GL_TEXTURE0_ARB);
			}
#else
			if (renderflag&P_RENDERFLAG_TANGENT)
			{
				if (renderflag&P_RENDERFLAG_CURVATURE)
				{
					glClientActiveTextureARB(GL_TEXTURE3_ARB);
					glTexCoordPointer(2,GL_FLOAT,sizeof(pVertex),(void *)(sizeof(float)*16));
					glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				}
				glClientActiveTextureARB(GL_TEXTURE2_ARB);
				glTexCoordPointer(4,GL_FLOAT,sizeof(pVertex),(void *)(sizeof(float)*12));
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				glClientActiveTextureARB(GL_TEXTURE1_ARB);
				glTexCoordPointer(4,GL_FLOAT,sizeof(pVertex),(void *)(sizeof(float)*8));
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				glClientActiveTextureARB(GL_TEXTURE0_ARB);
			}
			else
			{
				glClientActiveTextureARB(GL_TEXTURE3_ARB);
				glDisableClientState(GL_TEXTURE_COORD_ARRAY);
				glClientActiveTextureARB(GL_TEXTURE2_ARB);
				glDisableClientState(GL_TEXTURE_COORD_ARRAY);
				glClientActiveTextureARB(GL_TEXTURE1_ARB);
				glDisableClientState(GL_TEXTURE_COORD_ARRAY);
				glClientActiveTextureARB(GL_TEXTURE0_ARB);
			}
#endif
		}
	}
	else
	{
		if (GLEW_ARB_vertex_buffer_object)
		{
			glBindBufferARB(GL_ARRAY_BUFFER_ARB,0);
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB,0);
		}

		glDisableClientState(GL_COLOR_ARRAY);

		glVertexPointer(3,GL_FLOAT,sizeof(pVertex),vert->pos);
		glEnableClientState(GL_VERTEX_ARRAY);

		if (renderflag&P_RENDERFLAG_NORMAL)
		{
			glNormalPointer(GL_FLOAT,sizeof(pVertex),vert->norm);
			glEnableClientState(GL_NORMAL_ARRAY);
		}
		else
			glDisableClientState(GL_NORMAL_ARRAY);
			
		if (renderflag&P_RENDERFLAG_TEXTURE)
		{
			glTexCoordPointer(2,GL_FLOAT,sizeof(pVertex),vert->tx);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		}
		else
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		
		if ((renderflag&P_RENDERFLAG_TEXTURE2) && 
			g_render->maxtextureunits>1)
		{
			glClientActiveTextureARB(GL_TEXTURE1_ARB);
			glTexCoordPointer(2,GL_FLOAT,sizeof(pVertex),vert->tx);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glClientActiveTextureARB(GL_TEXTURE0_ARB);
		}
		else
		if (g_render->maxtextureunits>2)
		{
#ifdef P_MESH_SHORT_VERT
			if (renderflag&P_RENDERFLAG_TANGENT)
			{
				glClientActiveTextureARB(GL_TEXTURE2_ARB);
				glTexCoordPointer(3,GL_FLOAT,sizeof(pVertex),vert->tanv);
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				glClientActiveTextureARB(GL_TEXTURE1_ARB);
				glTexCoordPointer(3,GL_FLOAT,sizeof(pVertex),vert->tanu);
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				glClientActiveTextureARB(GL_TEXTURE0_ARB);
			}
			else
			{
				glClientActiveTextureARB(GL_TEXTURE2_ARB);
				glDisableClientState(GL_TEXTURE_COORD_ARRAY);
				glClientActiveTextureARB(GL_TEXTURE1_ARB);
				glDisableClientState(GL_TEXTURE_COORD_ARRAY);
				glClientActiveTextureARB(GL_TEXTURE0_ARB);
			}
#else
			if (renderflag&P_RENDERFLAG_TANGENT)
			{
				if (renderflag&P_RENDERFLAG_CURVATURE)
				{
					glClientActiveTextureARB(GL_TEXTURE3_ARB);
					glTexCoordPointer(2,GL_FLOAT,sizeof(pVertex),vert->curv);
					glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				}
				glClientActiveTextureARB(GL_TEXTURE2_ARB);
				glTexCoordPointer(4,GL_FLOAT,sizeof(pVertex),vert->tanv);
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				glClientActiveTextureARB(GL_TEXTURE1_ARB);
				glTexCoordPointer(4,GL_FLOAT,sizeof(pVertex),vert->tanu);
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				glClientActiveTextureARB(GL_TEXTURE0_ARB);
			}
			else
			{
				glClientActiveTextureARB(GL_TEXTURE3_ARB);
				glDisableClientState(GL_TEXTURE_COORD_ARRAY);
				glClientActiveTextureARB(GL_TEXTURE2_ARB);
				glDisableClientState(GL_TEXTURE_COORD_ARRAY);
				glClientActiveTextureARB(GL_TEXTURE1_ARB);
				glDisableClientState(GL_TEXTURE_COORD_ARRAY);
				glClientActiveTextureARB(GL_TEXTURE0_ARB);
			}
#endif
		}
	}
#endif
}

void pMesh::array_draw(int vb) const
{
#ifndef P_DISABLE_3D
#ifdef P_MESH_SHORT_FACE
	glDrawElements(GL_TRIANGLES,nface*3,GL_UNSIGNED_SHORT,vb&&vertbuffer?0:facevert);
#else
	glDrawElements(GL_TRIANGLES,nface*3,GL_UNSIGNED_INT,vb&&vertbuffer?0:facevert);
#endif
#endif
}

void pMesh::array_unlock() const
{
#ifndef P_DISABLE_3D
	if (GLEW_ARB_vertex_buffer_object)
	{
		if (vertbuffer)
			glBindBufferARB(GL_ARRAY_BUFFER_ARB,0);
		if (facebuffer)
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB,0);
	}
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
#ifndef P_MESH_SHORT_VERT
	glClientActiveTextureARB(GL_TEXTURE3_ARB);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
#endif
	glClientActiveTextureARB(GL_TEXTURE2_ARB);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glClientActiveTextureARB(GL_TEXTURE1_ARB);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glClientActiveTextureARB(GL_TEXTURE0_ARB);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
#endif
}

void pMesh::draw(int renderflag,int rendermode,pRenderProfile *profile) const
{
#ifndef P_DISABLE_3D
	pMaterial *m;
	int i,j;
	int vb=g_render->vertbuffer&&vertbuffer;

	if(profile==0)
		profile=g_render->cur_profile;

	array_lock(renderflag,vb);

	j=0;
	if(0==(rendermode&(P_RENDERMODE_SHADOWS|P_RENDERMODE_TRANSP|P_RENDERMODE_PASS|P_RENDERMODE_GLOW)))
	{
		for( i=0;i<nfacemat;i++ )
		{
			m=&mat[face[j].material];
#ifdef P_TRANSPARENT
			if(m->opacity>=1.0f && (m->flags&P_MATFLAGS_NOLIGHT)==0)
#else
			if((m->flags&P_MATFLAGS_NOLIGHT)==0)
#endif
			{
				profile->load_mat(m,rendermode);
#ifdef P_MESH_SHORT_FACE
				glDrawElements(GL_TRIANGLES,3*facemat[i],GL_UNSIGNED_SHORT,vb?(void *)(j*3*sizeof(unsigned short)):&facevert[j*3]);
#else
				glDrawElements(GL_TRIANGLES,3*facemat[i],GL_UNSIGNED_INT,vb?(void *)(j*3*sizeof(unsigned int)):&facevert[j*3]);
#endif
				profile->unload_mat(m,rendermode);
			}
			j+=facemat[i];
		}
	}
	else
	if(rendermode&P_RENDERMODE_SHADOWS)
	{
		for( i=0;i<nfacemat;i++ )
		{
			m=&mat[face[j].material];
#ifdef P_TRANSPARENT
			if(m->opacity>=1.0f && (m->flags&P_MATFLAGS_NOSHADOW)==0)
#else
			if((m->flags&P_MATFLAGS_NOSHADOW)==0)
#endif
#ifdef P_MESH_SHORT_FACE
				glDrawElements(GL_TRIANGLES,3*facemat[i],GL_UNSIGNED_SHORT,vb?(void *)(j*3*sizeof(unsigned short)):&facevert[j*3]);
#else
				glDrawElements(GL_TRIANGLES,3*facemat[i],GL_UNSIGNED_INT,vb?(void *)(j*3*sizeof(unsigned int)):&facevert[j*3]);
#endif
			j+=facemat[i];
		}
	}
	else
#ifdef P_TRANSPARENT
	if(rendermode&P_RENDERMODE_TRANSP)
	{	
		for( i=0;i<nfacemat;i++ )
		{
			m=&mat[face[j].material];
			if(m->opacity<1.0f && (m->flags&P_MATFLAGS_NOLIGHT)==0)
			{
				profile->load_mat(m,rendermode);
#ifdef P_MESH_SHORT_FACE
				glDrawElements(GL_TRIANGLES,3*facemat[i],GL_UNSIGNED_SHORT,vb?(void *)(j*3*sizeof(unsigned short)):&facevert[j*3]);
#else
				glDrawElements(GL_TRIANGLES,3*facemat[i],GL_UNSIGNED_INT,vb?(void *)(j*3*sizeof(unsigned int)):&facevert[j*3]);
#endif
				profile->unload_mat(m,rendermode);
			}
			j+=facemat[i];
		}
	}
	else
#endif
	if(rendermode&P_RENDERMODE_PASS)
	{
		glColor4f(0,0,0,0);

		int k,n,p;
		for( i=0;i<nfacemat;i++ )
		{
			m=&mat[face[j].material];

			p=m->passes.num;
			while(p>0)
			{
				///n=p>g_render->maxtextureunits?g_render->maxtextureunits:p;
				n=p>2?2:p;
				for( k=0;k<n;k++ )
					m->passes.buf[p-k-1].setup_pass(GL_TEXTURE0_ARB+k);
				for( ;k<g_render->maxtextureunits;k++ )
				{
					glActiveTextureARB(GL_TEXTURE0_ARB+k);
					glDisable(GL_TEXTURE_2D);
				}

#ifdef P_MESH_SHORT_FACE
				glDrawElements(GL_TRIANGLES,3*facemat[i],GL_UNSIGNED_SHORT,vb?(void *)(j*3*sizeof(unsigned short)):&facevert[j*3]);
#else
				glDrawElements(GL_TRIANGLES,3*facemat[i],GL_UNSIGNED_INT,vb?(void *)(j*3*sizeof(unsigned int)):&facevert[j*3]);
#endif
				
				p-=n;
			}

			j+=facemat[i];
		}
	}
	else
	if(rendermode&P_RENDERMODE_GLOW)
	{
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
		for( i=0;i<nfacemat;i++ )
		{
			m=&mat[face[j].material];
			if (m->flags&P_MATFLAGS_NOGLOW)
				glColor3f(0,0,0);
			else
			{
				if (m->texselfillumid!=-1)
				{
					g_render->sel_tex(m->texselfillumid);
					glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_ADD);
				}
				else 
					glDisable(GL_TEXTURE_2D);
				glColor3fv(&m->selfillum.x);
			}
#ifdef P_MESH_SHORT_FACE
			glDrawElements(GL_TRIANGLES,3*facemat[i],GL_UNSIGNED_SHORT,vb?(void *)(j*3*sizeof(unsigned short)):&facevert[j*3]);
#else
			glDrawElements(GL_TRIANGLES,3*facemat[i],GL_UNSIGNED_INT,vb?(void *)(j*3*sizeof(unsigned int)):&facevert[j*3]);
#endif
			j+=facemat[i];
		}
		glDisable(GL_TEXTURE_2D);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	}

	array_unlock();
#endif
}

void find_min_med(float x,float y,float z,int& min,int& med)
{
	if (x>y)
		if (x>z)
		{	min=1;	med=2; 	}
		else 
		{	min=0;	med=1;	}
	else if (y>z)
		{	min=0;	med=2;	}
		else 
		{	min=0;	med=1;	}
}

void pMesh::compute_nuv(const pFace *f,const pVector& ip,pVector& n,pVector& uv) const
{
	float i[5],v[3][2],c[3][5],m[3][2],n1,n2,n3;
	int min,med,a;

	find_min_med(
		fabsf(f->face_normal.x),
		fabsf(f->face_normal.y),
		fabsf(f->face_normal.z),
		min,med);

	pVertex *vv;

	for( a=0;a<3;a++ )
	{
		vv=&vert[facevert[f->vertindx+a]];
		v[a][0]=vv->pos[min];
		v[a][1]=vv->pos[med];
		c[a][0]=vv->norm[0];
		c[a][1]=vv->norm[1];
		c[a][2]=vv->norm[2];
		c[a][3]=vv->tx[0];
		c[a][4]=vv->tx[1];
	}

	m[0][0]=ip[min]-v[0][0];
	m[0][1]=ip[med]-v[0][1];
	m[1][0]=v[2][0]-v[0][0];
	m[1][1]=v[2][1]-v[0][1];
	m[2][0]=v[1][0]-v[0][0];
	m[2][1]=v[1][1]-v[0][1];

	n1=m[1][0]*m[2][1]-m[1][1]*m[2][0];
	n2=m[0][0]*m[2][1]-m[0][1]*m[2][0];
	n3=m[0][0]*m[1][1]-m[0][1]*m[1][0];

	for( a=0;a<5;a++ )
		i[a]=((c[2][a]-c[0][a])*n2-(c[1][a]-c[0][a])*n3)/n1+c[0][a];

	n.vec(i[0],i[1],i[2]);
	n.normalize();
	uv.vec(i[3],i[4],0,0);
}

int pMesh::load_p3d(const char *file, float f_UVFactor, int octreedepth)
{
	pFile fp;
	if (fp.open(file)==false)
		{
		printf("pMesh:::Error fp.open\n");
		return 0;
		}

	int i,ver;
	fp.read(&i,sizeof(int));
	fp.read(&ver,sizeof(int));
	if (i!=P3D_FILEID || ver<P3D_FILEVER || ver>P3D_FILEVER+8)
	{
		printf("pMesh:::Error P3D_FILEID || ver<P3D_FILEVER || ver>P3D_FILEVER\n");
		fp.close();
		return 0;
	}

	reset();
	name=file;

	fp.read(&nvert,sizeof(int));
	fp.read(&nface,sizeof(int));
	fp.read(&nmat,sizeof(int));
	fp.read(&ncam,sizeof(int));
	fp.read(&nlight,sizeof(int));
	if (ver>=P3D_FILEVER+1)
		fp.read(&ndummy,sizeof(int));
	if (ver>=P3D_FILEVER+2)
		fp.read(&nobb,sizeof(int));

#ifdef P_MESH_SHORT_FACE
	if (nface>65535)
	{
		reset();
		fp.close();
		return 0;
	}
#endif
	
	set_numvert(nvert);
	set_numface(nface);
	set_nummat(nmat);
	set_numcam(ncam);
	set_numlight(nlight);
	set_numdummy(ndummy);
	set_numobb(nobb);
	
	fp.read(&ambient.x,4*sizeof(float));
	fp.read(&bgmode,sizeof(int));
	fp.read(&bgcolor.x,4*sizeof(float));
	bgpic.read(fp);

	for( i=0;i<nvert;i++ )
	{
		fp.read(vert[i].pos,3*sizeof(float));
		//vert[i].pos[0] *= 1.01515f;
		//vert[i].pos[2] *= 1.01515f;
		fp.read(vert[i].norm,3*sizeof(float));
		fp.read(vert[i].tx,2*sizeof(float));
		//vert[i].tx[0] *= 1.01515f;
		//vert[i].tx[1] *= 1.01515f;
		if (ver>=P3D_FILEVER+5)
		{
#ifdef P_MESH_SHORT_VERT
			fp.read(vert[i].tanu,3*sizeof(float));
			fp.seek(sizeof(float));
			fp.read(vert[i].tanv,3*sizeof(float));
			fp.seek(sizeof(float));
#else
			fp.read(vert[i].tanu,4*sizeof(float));
			fp.read(vert[i].tanv,4*sizeof(float));
#endif
		}
		else
		if (ver>=P3D_FILEVER+4)
		{
			fp.read(vert[i].tanu,3*sizeof(float));
			fp.read(vert[i].tanv,3*sizeof(float));
#ifndef P_MESH_SHORT_VERT
			vert[i].tanu[3]=0;
			vert[i].tanv[3]=0;
#endif
		}
		if (ver>=P3D_FILEVER+8)
		{
#ifdef P_MESH_SHORT_VERT
			fp.seek(2*sizeof(float));
#else
			fp.read(vert[i].curv,2*sizeof(float));
#endif
		}
	}

#ifdef P_MESH_SHORT_FACE
	unsigned int *ui=new unsigned int[3*nface];
	fp.read(ui,3*nface*sizeof(unsigned int));
	for( i=0;i<3*nface;i++ )
		facevert[i]=ui[i];
	delete ui;
#else
	fp.read(facevert,3*nface*sizeof(unsigned int));
#endif

	for( i=0;i<nface;i++ )
		face[i].read(fp,ver);
	for( i=0;i<nmat;i++ )
		mat[i].read(fp,ver);
	for( i=0;i<ncam;i++ )
		cam[i].read(fp,ver);
	for( i=0;i<nlight;i++ )
		light[i].read(fp,ver);
	if (ver>=P3D_FILEVER+1)
		for( i=0;i<ndummy;i++ )
			dummy[i].read(fp,ver);
	if (ver>=P3D_FILEVER+2)
		for( i=0;i<nobb;i++ )
			obb[i].read(fp,ver);

	fp.close();

	i=P_COMPUTE_FACENORM|P_COMPUTE_BBOX;
	if (ver<P3D_FILEVER+4)
		i|=P_COMPUTE_TANGENTS;
	if (ver<P3D_FILEVER+8)
		i|=P_COMPUTE_CURVATURE;
	compute_normals(f_UVFactor, i);
	if (ver<P3D_FILEVER+4)
		sort_facemat();
	compute_facemat();

	if (octreedepth)
		octree.build_tree(nface,face,vert,facevert,octreedepth);

	return 1;
}

#if 1
int pMesh::load_cal3d(std::string i_name,QunStreamSource &dataSrc,int octreedepth, float i_scale, bool f_flip)
{
	int integer = 0;
	float floating = 0;
	int influenceCount = 0;
	int tempint1,tempint2,tempint3;
	int i;

	name=i_name.c_str();

	// verify data Source
	if(!dataSrc.ok())
		{
		printf("ERROR:::pMesh::load_cal3d:::dataSrc error\n");
		return 0;
		}

	// get the material thread id of the submesh
	int coreMaterialThreadId;
	dataSrc.readInteger(coreMaterialThreadId);

	// get the number of vertices, faces, level-of-details and springs
	dataSrc.readInteger(nvert);
	dataSrc.readInteger(nface);

	int lodCount;
	dataSrc.readInteger(lodCount);
	int springCount;
	dataSrc.readInteger(springCount);
	// get the number of texture coordinates per vertex
	int textureCoordinateCount;
	dataSrc.readInteger(textureCoordinateCount);

	// Allocate Mesh Memory	
	set_numvert(nvert);
	set_numface(nface);

	ncam = 0;
	nlight = 0;
	ndummy = 0;
	nobb = 0;
	set_numcam(ncam);
	set_numlight(nlight);
	set_numdummy(ndummy);
	set_numobb(nobb);

#if 0
	for( i=0;i<ncam;i++ ) cam[i].read(fp,ver);
	for( i=0;i<nlight;i++ ) light[i].read(fp,ver);
	for( i=0;i<ndummy;i++ ) dummy[i].read(fp,ver);
	for( i=0;i<nobb;i++ ) obb[i].read(fp,ver);
#endif

	// check if an error happened
	if(!dataSrc.ok())
		{
		printf("ERROR:::pMesh::load_cal3d:::dataSrc error\n");
		return 0;
		}

	// load all vertices and their influences
	for(int vertexId = 0; vertexId < nvert; ++vertexId)
		{
		dataSrc.readFloat(vert[vertexId].pos[0]);
		dataSrc.readFloat(vert[vertexId].pos[1]);
		dataSrc.readFloat(vert[vertexId].pos[2]);

		if(i_scale != 1)
			{
			vert[vertexId].pos[0] *= i_scale;
			vert[vertexId].pos[1] *= i_scale;
			vert[vertexId].pos[2] *= i_scale;
			}

		dataSrc.readFloat(vert[vertexId].norm[0]);
		dataSrc.readFloat(vert[vertexId].norm[1]);
		dataSrc.readFloat(vert[vertexId].norm[2]);

		dataSrc.readInteger(/*vertex.collapseId*/integer);
		dataSrc.readInteger(/*vertex.faceCollapseCount*/integer);

		// check if an error happened
		if(!dataSrc.ok())
			{
			printf("ERROR:::pMesh::load_cal3d:::dataSrc error\n");
			return 0;
			}

		// load all texture coordinates of the vertex
		for(int textureCoordinateId = 0; textureCoordinateId < textureCoordinateCount; ++textureCoordinateId)
			{
			// load data of the influence
			dataSrc.readFloat(vert[vertexId].tx[0]);
			dataSrc.readFloat(vert[vertexId].tx[1]);

			// check if an error happened
			if(!dataSrc.ok())
				{
				printf("ERROR:::pMesh::load_cal3d:::dataSrc error\n");
				return 0;
				}
			}

#if 0
		/// PMESH UNASSIGNED DATA
		fp.read(vert[vertexId].tanu,4*sizeof(float));
		fp.read(vert[vertexId].tanv,4*sizeof(float));
		fp.read(vert[vertexId].curv,2*sizeof(float));
#endif

		// get the number of influences
		if(!dataSrc.readInteger(influenceCount) || (influenceCount < 0))
			{
			printf("ERROR:::pMesh::load_cal3d:::dataSrc error number of influences\n");
			return 0;
			}

		// load all influences of the vertex
		for(int influenceId = 0; influenceId < influenceCount; ++influenceId)
			{
			// load data of the influence
			dataSrc.readInteger(/*vertex.vectorInfluence[influenceId].boneId*/integer);
			dataSrc.readFloat(/*vertex.vectorInfluence[influenceId].weight*/floating);

			// check if an error happened
			if(!dataSrc.ok())
				{
				printf("ERROR:::pMesh::load_cal3d:::dataSrc influences\n");
				return 0;
				}
			}

		// load the physical property of the vertex if there are springs in the core submesh
		if(springCount > 0)
			{
			// load data of the physical property
			dataSrc.readFloat(/*physicalProperty.weight*/floating);

			// check if an error happened
			if(!dataSrc.ok())
				{
				printf("ERROR:::pMesh::load_cal3d:::dataSrc physical properties\n");
				return 0;
				}
			}
		}

	// load all springs
	for(int springId = 0; springId < springCount; ++springId)
		{
		// load data of the spring
		dataSrc.readInteger(/*spring.vertexId[0]*/integer);
		dataSrc.readInteger(/*spring.vertexId[1]*/integer);
		dataSrc.readFloat(/*spring.springCoefficient*/floating);
		dataSrc.readFloat(/*spring.idleLength*/floating);

		// check if an error happened
		if(!dataSrc.ok())
			{
			printf("ERROR:::pMesh::load_cal3d:::dataSrc error\n");
			return 0;
			}
		}

	// load all faces
	int justOnce = 0;
	bool flipModel = false;
	for(int faceId = 0; faceId < nface; ++faceId)
		{
		dataSrc.readInteger(tempint1);
		dataSrc.readInteger(tempint2);
		dataSrc.readInteger(tempint3);

		if(!f_flip)
			{
			facevert[(faceId*3)] = tempint1;
			facevert[(faceId*3)+1] = tempint2;
			facevert[(faceId*3)+2] = tempint3;
			}
		else
			{
			facevert[(faceId*3)] = tempint3;
			facevert[(faceId*3)+1] = tempint2;
			facevert[(faceId*3)+2] = tempint1;
			}

		//FIXME fractal design schemes material load or set real
		face[faceId].material = coreMaterialThreadId;
		face[faceId].flags = 0;
#if 0
		face[faceId].face_normal.x = vert[tempint1].norm[0];
		face[faceId].face_normal.y = vert[tempint1].norm[1];
		face[faceId].face_normal.z = vert[tempint1].norm[2];
#endif

		// check if an error happened
		if(!dataSrc.ok())
			{
			printf("ERROR:::pMesh::load_cal3d:::dataSrc load faces error\n");
			return 0;
			}
		}

	/// Set Background Lighting
	ambient.x = 0;
	ambient.y = 0;
	ambient.z = 0.2;
	ambient.w = 0;
	bgcolor.x = 0;
	bgcolor.y = 0;
	bgcolor.z = 0.2;
	bgcolor.w = 0;
	bgmode = 0;

#if 0
	set_nummat(nmat);
	for( i=0;i<nmat;i++ ) mat[i].read(fp,ver);
#endif

	i=P_COMPUTE_FACENORM|P_COMPUTE_BBOX;
	i|=P_COMPUTE_TANGENTS;
	i|=P_COMPUTE_CURVATURE;
	compute_normals(1, i);
	sort_facemat();
	compute_facemat();

	printf("Mesh Loaded nvert %i nface %i\n", nvert, nface);

	if (octreedepth)
		octree.build_tree(nface,face,vert,facevert,octreedepth);

	return 1;
}
#endif

void pMesh::compute_facemat()
{
	int i,j,k;

	nfacemat=0;
	j=-2;
	for( i=0;i<nface;i++ )
		if (face[i].material!=j)
		{
			j=face[i].material;
			nfacemat++;
		}

	set_numfacemat(nfacemat);

	j=-2;
	k=-1;
	for( i=0;i<nface;i++ )
		if (face[i].material!=j)
		{
			j=face[i].material;
			facemat[++k]=1;
		}
		else 
			facemat[k]++;
}

void pMesh::sort_facemat()
{
	int i,j;
#ifdef P_MESH_SHORT_FACE
	unsigned short *i1,*i2,k;
#else
	unsigned int *i1,*i2,k;
#endif
	pFace f;

	for( i=0;i<nface-1;i++ )
	for( j=i+1;j<nface;j++ )
	{
		if (face[i].material==face[j].material)
		{
			i++;
			if (i==j)
				continue;

			i1=&facevert[i*3];
			i2=&facevert[j*3];
			k=i1[0]; i1[0]=i2[0]; i2[0]=k;
			k=i1[1]; i1[1]=i2[1]; i2[1]=k;
			k=i1[2]; i1[2]=i2[2]; i2[2]=k;

			f=face[i];
			face[i]=face[j];
			face[j]=f;

			face[i].vertindx=i*3;
			face[j].vertindx=j*3;
		}
	}
}

void pMesh::group_faces_material(pFace **f,int num) const
{
	pFace *tmp;
	int s1,s2;
	int p1,p2;
	int i;

	p1=0;
	p2=num-1;
	while(p1<p2)
	{
		s1=f[p1]->material;
		s2=f[p2]->material;
		if (s1==s2)
			s2=-2;
		for( i=p1+1;i<p2;i++ )
			if (s1==f[i]->material)
			{
				tmp=f[i];
				f[i]=f[++p1];
				f[p1]=tmp;
			}
			else
			if (s2==f[i]->material)
			{
				tmp=f[i];
				f[i--]=f[--p2];
				f[p2]=tmp;
			}
		p1++;
		if (s2!=-2)
			p2--;
	}
}

#ifdef P_SUPPORT_3DS
#include "l3ds.h"
int pMesh::load_3ds(const char *file,int octreedepth)
{
	L3DS l3ds;
	if (l3ds.LoadFile(file))
	{
		reset();

		int i,j,nf=0,nv=0,nm=0,nc=0,nl=0;

		for( i=0;i<l3ds.GetMeshCount();i++ )
		{
			LMesh& m=l3ds.GetMesh(i);
			nf+=m.GetTriangleCount();
			nv+=m.Getnvert();
		}
		nl+=l3ds.GetLightCount();
		nm+=l3ds.GetMaterialCount();
		nc+=l3ds.GetCameraCount();
		
		set_numvert(nv);
		set_numface(nf);
		set_nummat(nm);
		set_numcam(nc);
		set_numlight(nl);
		set_numcam(nc);

		ambient.vec(0.25f);
		bgcolor.vec(0.0f);

		nf=0;
		nv=0;

		for( i=0;i<l3ds.GetMeshCount();i++ )
		{
			int vb=nv;

			LMesh& m=l3ds.GetMesh(i);
			for( j=0;j<m.Getnvert();j++ )
			{
				vert[nv].pos[0]=m.GetVertex(j).x;
				vert[nv].pos[1]=m.GetVertex(j).y;
				vert[nv].pos[2]=m.GetVertex(j).z;
				vert[nv].tx[0]=m.GetUV(j).x;
				vert[nv].tx[1]=m.GetUV(j).y;
				vert[nv].norm[0]=m.GetNormal(j).x;
				vert[nv].norm[1]=m.GetNormal(j).y;
				vert[nv].norm[2]=m.GetNormal(j).z;
				nv++;
			}

			for( j=0;j<m.GetTriangleCount();j++ )
			{
				facevert[nf*3]=m.GetTriangle(j).a+vb;
				facevert[nf*3+1]=m.GetTriangle(j).b+vb;
				facevert[nf*3+2]=m.GetTriangle(j).c+vb;
				face[nf].material=m.GetTriangle2(j).materialId;
				face[nf].vertindx=nf*3;
				nf++;
			}
		}
	
		for( i=0;i<l3ds.GetMaterialCount();i++ )
		{
			LMaterial& m=l3ds.GetMaterial(i);
			LColor3 c=m.GetDiffuseColor();
			mat[i].name=m.GetName().c_str();
			mat[i].diffuse.vec(c.r,c.g,c.b);
			c=m.GetSpecularColor();
			mat[i].specular.vec(c.r,c.g,c.b);
			mat[i].specular.w=m.GetShininess();
			mat[i].opacity=1-m.GetTransparency();
			LMap& p=m.GetTextureMap1();
			mat[i].texname=p.mapName;
			p=m.GetBumpMap();
			mat[i].texnormalname=p.mapName;
			mat[i].bump=p.strength;
			p=m.GetReflectionMap();
			mat[i].reflection=p.strength;
		}
		
		for( i=0;i<l3ds.GetLightCount();i++ )
		{
			LLight& l=l3ds.GetLight(i);
			light[i].name=l.GetName().c_str();
			light[i].pos.vec(
				l.GetPosition().x,
				l.GetPosition().y,
				l.GetPosition().z);
			light[i].pos.w=l.GetAttenuationend();
			light[i].color.vec(
				l.GetColor().r,
				l.GetColor().g,
				l.GetColor().b);
			light[i].flags=P_LIGHTFLAGS_ENABLED;
		}

		for( i=0;i<l3ds.GetCameraCount();i++ )
		{
			LCamera& c=l3ds.GetCamera(i);
			cam[i].name=c.GetName().c_str();
			cam[i].pos.vec(
				c.GetPosition().x,
				c.GetPosition().y,
				c.GetPosition().z);
			cam[i].fov=c.GetFOV();

			pVector t,v;
			t.vec(
				c.GetTarget().x,
				c.GetTarget().y,
				c.GetTarget().z);
			v=t-cam[i].pos;
			v.normalize();

			pVector up(0,0,1);
			cam[i].Z=-v;
			cam[i].Y=up-VECDOT(cam[i].Z,up)*cam[i].Z;
			cam[i].Y.normalize();
			cam[i].X.cross(cam[i].Y,cam[i].Z);
			cam[i].update_mat();
		}

		compute_normals(P_COMPUTE_FACENORM|P_COMPUTE_TANGENTS|P_COMPUTE_BBOX);
		sort_facemat();
		compute_facemat();
		if (octreedepth)
			octree.build_tree(nface,face,vert,facevert,octreedepth);

		return 1;
	}
	return 0;
}
#endif

void pMesh::draw_faces_shadow(const pVector& lightpos) const
{
#ifndef P_DISABLE_3D
	if(g_render->svtype==0)
	{
		pFace *ff=0;
		int i=0,j=nface;

		float *v1,*v2,*v3;
		for( i=0;i<j;i++ )
		{
			ff=&face[i];
			if (ff->flags&P_FACEFLAGS_NOSHADOW)
				continue;

			v1=(float *)&vert[facevert[ff->vertindx]];
			if (0>(v1[0]-lightpos.x)*ff->face_normal.x+
				  (v1[1]-lightpos.y)*ff->face_normal.y+
				  (v1[2]-lightpos.z)*ff->face_normal.z)
				continue;

			v2=(float *)&vert[facevert[ff->vertindx+1]];
			v3=(float *)&vert[facevert[ff->vertindx+2]];

			glTexCoord4fv(&ff->face_normal.x);

			//*glBegin(GL_TRIANGLES);
			glVertex4f(v1[0],v1[1],v1[2],1);
			glVertex4f(v2[0],v2[1],v2[2],1);
			glVertex4f(v3[0],v3[1],v3[2],1);
			glVertex4f(v3[0],v3[1],v3[2],0);
			glVertex4f(v2[0],v2[1],v2[2],0);
			glVertex4f(v1[0],v1[1],v1[2],0);
			//*glEnd();

			//*glBegin(GL_TRIANGLE_STRIP);
			glVertex4f(v1[0],v1[1],v1[2],1);
			glVertex4f(v1[0],v1[1],v1[2],0);
			glVertex4f(v2[0],v2[1],v2[2],1);
			glVertex4f(v2[0],v2[1],v2[2],0);
			glVertex4f(v3[0],v3[1],v3[2],1);
			glVertex4f(v3[0],v3[1],v3[2],0);
			glVertex4f(v1[0],v1[1],v1[2],1);
			glVertex4f(v1[0],v1[1],v1[2],0);
			//*glEnd();
		}
	}
	else
	{
		// drawing edge quads
		pFace *ff1,*ff2;

		float dot1,dot2;
		pVector lightdir;

		int *e=edge;

		array_lock(0,0);

		//*glBegin(GL_QUADS);
		int i;
		for(i=0;i<nedge;i++,e+=4)
		{
			ff1=&face[e[0]];
			if(ff1->flags&P_FACEFLAGS_NOSHADOW)
				continue;
			ff2=&face[e[1]];

			lightdir=pVector(vert[e[2]].pos[0],vert[e[2]].pos[1],vert[e[2]].pos[2])-lightpos;
			lightdir.normalize();
			
			dot1=VECDOT(lightdir,ff1->face_normal);
			dot2=VECDOT(lightdir,ff2->face_normal);

			if(dot1*dot2>0.0f)
				continue;
	
			if(dot1>0.0f)
			{
				glTexCoord3fv(&ff1->face_normal.x);
				glArrayElement(e[3]);
				glArrayElement(e[2]);

				glTexCoord4fv(&ff2->face_normal.x);
				glArrayElement(e[2]);
				glArrayElement(e[3]);
			}
			else
			{
				glTexCoord3fv(&ff2->face_normal.x);
				glArrayElement(e[2]);
				glArrayElement(e[3]);

				glTexCoord4fv(&ff1->face_normal.x);
				glArrayElement(e[3]);
				glArrayElement(e[2]);
			}
		}
		//*glEnd();

		int j=nface;

		glColor3f(0.0f,1.0f,0.0f);
		//*glBegin(GL_TRIANGLES);
		for(i=0;i<j;i++)
		{
			ff1=&face[i];
			if (ff1->flags&P_FACEFLAGS_NOSHADOW)
				continue;

			glTexCoord4fv(&ff1->face_normal.x);

			glArrayElement(facevert[ff1->vertindx]);
			glArrayElement(facevert[ff1->vertindx+1]);
			glArrayElement(facevert[ff1->vertindx+2]);
		}
		//*glEnd();

		array_unlock();
	}
#endif
}

void pMesh::compute_edges()
{
	int i,j,k,l;
	int eqcount;

	delete edge;
	edge=new int[3*nface*4];
	nedge=0;

	pVector v0,v1;
	const pVertex *vv0,*vv1;
	int face1,face2,vert1,vert2;

	int ind1;

	for(i=0;i<nface-1;i++)
		for(j=i+1;j<nface;j++)
		{
			eqcount=0;
			for(k=0;k<3;k++)
			{
				vv0=&vert[facevert[(i*3)+k]];
				v0.vec(vv0->pos[0],vv0->pos[1],vv0->pos[2]);

				for(l=0;l<3;l++)
				{
					vv1=&vert[facevert[(j*3)+l]];
					v1.vec(vv1->pos[0],vv1->pos[1],vv1->pos[2]);

					if((v1-v0).length2()<0.000001)
					{
						eqcount++;
						if(eqcount==1)
						{
							face1=i;
							face2=j;
							vert1=facevert[(i*3)+k];
							ind1=k;
						}
						else if(eqcount==2)
						{
							if(k==ind1+1)
							{
								vert2=facevert[(i*3)+k];
							}
							else
							{
								vert2=vert1;
								vert1=facevert[(i*3)+k];
							}

							k=3;
							break;
						}
					}
				}
			}

			if(eqcount==2)
			{
				edge[(nedge*4)]=face1;
				edge[(nedge*4)+1]=face2;
				edge[(nedge*4)+2]=vert1;
				edge[(nedge*4)+3]=vert2;

				nedge++;
			}
		}
}

void pMesh::operator=(const pMesh& in)
{
	set_numface(in.nface);
	set_numvert(in.nvert);
	set_nummat(in.nmat);
	set_numfacemat(in.nfacemat);
	set_numcam(in.ncam);
	set_numlight(in.nlight);
	set_numdummy(in.ndummy);
	set_numobb(in.nobb);

	int i;
	for( i=0;i<nface;i++ )
		face[i]=in.face[i];
	for( i=0;i<nvert;i++ )
		vert[i]=in.vert[i];
	for( i=0;i<nmat;i++ )
		mat[i]=in.mat[i];
	for( i=0;i<ncam;i++ )
		cam[i]=in.cam[i];
	for( i=0;i<nlight;i++ )
		light[i]=in.light[i];
	for( i=0;i<ndummy;i++ )
		dummy[i]=in.dummy[i];
	for( i=0;i<nobb;i++ )
		obb[i]=in.obb[i];
	for( i=0;i<nface*3;i++ )
		facevert[i]=in.facevert[i];
	for( i=0;i<nfacemat;i++ )
		facemat[i]=in.facemat[i];
}

// solve matrix system Ax=B using least squares
// A[n,2] and B[n,1] result stored in (a,b)
// R = (AT*A)^-1 * (AT*B)
void pMesh::solve_least_squares(int n,const float *A,const float *B,float& a,float& b)
{
	a=0;
	b=0;
	if (n<2) return;

	int i,j,k;

	// AT = transpose of A
	float *AT=new float[n*2];
	for( i=0;i<n;i++ )
	{
		AT[i]=A[i*2];
		AT[i+n]=A[i*2+1];
	}

	// M = AT * A
	float M[2][2];
	for( j=0;j<2;j++ )
	for( i=0;i<2;i++ )
	{
		M[j][i]=0;
		for( k=0;k<n;k++ )
			M[j][i]+=AT[j*n+k]*A[k*2+i];
	}

	// MI = inverse M
	float det,MI[2][2];
	det=M[0][0]*M[1][1]-M[0][1]*M[1][0];
	if (fabs(det)>0.001f)
	{
		det=1.0f/det;
		MI[0][0]=M[1][1]*det;
		MI[0][1]=-M[0][1]*det;
		MI[1][0]=-M[1][0]*det;
		MI[1][1]=M[0][0]*det;

		// ATB = AT * B
		float ATB[2]={ 0,0 };
		for( i=0;i<2;i++ )
		for( j=0;j<n;j++ )
			ATB[i]+=AT[i*n+j]*B[j];

		// (a,b) = MI * ATB
		a=MI[0][0]*ATB[0]+MI[0][1]*ATB[1];
		b=MI[1][0]*ATB[0]+MI[1][1]*ATB[1];
	}

	delete AT;
}

void pMesh::compute_curvature()
{
#ifndef P_MESH_SHORT_VERT
	pIntArray2 vertfaces;
	pIntArray ringverts;
	pFloatArray A,B;
	pString s;

	int i,j,k,l;
	pVector *pos,*vpos,*norm,*tanu,*tanv;
	pVector p,t;

#ifdef P_MESH_SHORT_FACE
	unsigned short *v;
#else
	unsigned int *v;
#endif

	pIntArray ia;
	for( i=0;i<nvert;i++ )
		vertfaces.add(ia);

	j=3*nface;
	for( i=0;i<j;i++ )
		vertfaces[facevert[i]].add(i/3);

	for( i=0;i<nvert;i++ )
	{
		A.clear();
		B.clear();

		pos=(pVector *)vert[i].pos;
		norm=(pVector *)vert[i].norm;
		tanu=(pVector *)vert[i].tanu;
		tanv=(pVector *)vert[i].tanv;

		ringverts.clear();
		ringverts.add(i);
		for( j=0;j<vertfaces.buf[i].num;j++ )
		{
			v=&facevert[vertfaces.buf[i].buf[j]*3];
			for( k=0;k<3;k++ )
			{
				for( l=0;l<ringverts.num;l++ )
					if (ringverts.buf[l]==(int)v[k])
						break;
				if (l==ringverts.num)
					ringverts.add(v[k]);
			}
		}

		for( j=1;j<ringverts.num;j++ )
		{
			vpos=(pVector *)vert[ringverts[j]].pos;
			t=*vpos-*pos;
			p.x=VECDOT(t,*tanu);
			p.y=VECDOT(t,*tanv);
			p.z=VECDOT(t,*norm);
			A.add(p.x*p.x);
			A.add(p.y*p.y);
			B.add(-p.z);
		}
		
		solve_least_squares(B.num,&A.buf[0],&B.buf[0],
			vert[i].curv[0],vert[i].curv[1]);
	}
#endif
}
