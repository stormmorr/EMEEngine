#include "pch.h"
#include "paralelo3d.h"

pMeshSkeleton::pMeshSkeleton() :
	m_time_ani(0),
	m_curani(-1),
	m_curtime(0),
	m_nextani(-1),
	m_nexttime(0),
	m_nextdur(0.25f)
{
	for( int i=0;i<P_MSMAXMTGANI;i++ )
	{
		m_curmtgani[i]=-1,
		m_curmtgtime[i]=0,
		m_curmtgweight[i]=1.0f;
		m_nextmtgani[i]=-1,
		m_nextmtgtime[i]=0,
		m_nextmtgdur[i]=0.25f;
		m_time_mtg[i]=0;
	}
}

pMeshSkeleton::~pMeshSkeleton()
{
	reset();
}

bool pMeshSkeleton::check_data() const
{
	if (nvert==0)
	{
		//*MessageBox(g_render->hwnd,"Error: no vertices.","P3D Skeleton Mesh",MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	if (nvert!=m_phy.nvert)
	{
		//*MessageBox(g_render->hwnd,"Error: num vertices p3d!=phy.","P3D Skeleton Mesh",MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	if (m_ani_rest.nbone!=m_phy.nbone)
	{
		//*MessageBox(g_render->hwnd,"Error: num bones in rest pose!=phy.","P3D Skeleton Mesh",MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	int i;

	for( i=0;i<m_ani.num;i++ )
		if (m_ani.buf[i] && 
			m_phy.nbone!=m_ani.buf[i]->nbone)
		{
			//*MessageBox(g_render->hwnd,"Error: num bones phy!=ani.","P3D Skeleton Mesh",MB_OK|MB_ICONEXCLAMATION);
			return false;
		}
	
	for( i=0;i<m_mtg.num;i++ )
		if (m_mtg.buf[i] &&
			nvert!=m_mtg.buf[i]->nvert)
		{
			//*MessageBox(g_render->hwnd,"Error: num verts p3d!=mtg.","P3D Skeleton Mesh",MB_OK|MB_ICONEXCLAMATION);
			return false;
		}

	return true;
}

void pMeshSkeleton::reset()
{
	m_mesh.reset();
	m_phy.reset();
	m_ani_rest.reset();
	reset_ani();
	reset_mtg();
	reset_mtgani();
}
	
void pMeshSkeleton::reset_ani()
{
	for( int i=0;i<m_ani.num;i++ )
		delete m_ani.buf[i];
	m_ani.free();
	m_curani=-1;
}

void pMeshSkeleton::reset_mtg()
{
	for( int i=0;i<m_mtg.num;i++ )
		delete m_mtg.buf[i];
	m_mtg.free();
}

void pMeshSkeleton::reset_mtgani()
{
	for( int i=0;i<m_mtgani.num;i++ )
		delete m_mtgani.buf[i];
	m_mtgani.free();
}
	
bool pMeshSkeleton::load_phy(const char *file)
{
	reset_ani();
	if (m_phy.load(file))
		return true;
	return false;
}

int pMeshSkeleton::load_ani(const char *file)
{
	pMSAni *ani=new pMSAni;
	if (ani->load(file)==false)
	{
		delete ani;
		return false;
	}
	if (ani->nbone==0)
	{
		delete ani;
		ani=0;
	}
	m_ani.add(ani);
	return true;
}

bool pMeshSkeleton::load_ani_rest(const char *file)
{
	return m_ani_rest.load(file);
}

void pMeshSkeleton::build()
{
	m_phy.build(&m_ani_rest);
	m_mesh=*this;
	m_mesh.update_buffers(3);
}

bool pMeshSkeleton::set_ani(int ani,float time,float duration)
{
	if (ani<-1 || ani>=m_ani.num || m_ani.buf[ani]==0)
		return false;

	if (m_curani==-1)
	{
		m_curani=ani;
		m_curtime=time;
		return true;
	}
	else
	if (m_nextani==-1)
	{
		m_nextani=(ani==-1?-2:ani);
		m_nexttime=time;
		m_nextdur=duration;
		return true;
	}

	return false;
}

bool pMeshSkeleton::set_mtgani(int channel,int mtgani,float time,float duration)
{
	if (mtgani<-1 || mtgani>=m_mtgani.num || m_mtgani.buf[mtgani]==0)
		return false;

	if (m_curmtgani[channel]==-1)
	{
		m_curmtgani[channel]=mtgani;
		m_curmtgtime[channel]=time;
		return true;
	}
	else
	if (m_nextmtgani[channel]==-1)
	{
		m_nextmtgani[channel]=(mtgani==-1?-2:mtgani);
		m_nextmtgtime[channel]=time;
		m_nextmtgdur[channel]=duration;
		return true;
	}

	return false;
}

void pMeshSkeleton::update(float time_ani,float time_mtg[P_MSMAXMTGANI])
{
	bool mtg_flag=false;
	m_time_ani=time_ani;

	// morpth target animation channels
	clear_mtg();
	for( int i=0;i<P_MSMAXMTGANI;i++ )
	{
		float weight=1.0;
		m_time_mtg[i]=time_mtg[i];

		if (m_curmtgani[i]>=m_mtgani.num)
			m_curmtgani[i]=-1;
		if (m_nextmtgani[i]>=m_mtgani.num)
			m_nextmtgani[i]=-1;

		// blending with next morpth target animation
		if (m_nextmtgani[i]==-2)
		{
			m_curmtgani[i]=-1;
			m_curmtgtime[i]=m_nextmtgtime[i];
			m_nextmtgani[i]=-1;
		}
		else
		if (m_nextmtgani[i]!=-1)
		{
			if (m_time_mtg[i]-m_nextmtgtime[i]>m_nextmtgdur[i])
			{
				m_curmtgani[i]=m_nextmtgani[i];
				m_curmtgtime[i]=m_nextmtgtime[i];
				m_nextmtgani[i]=-1;
			}
			else
			{
				weight=(m_time_mtg[i]-m_nextmtgtime[i])/m_nextmtgdur[i];
				update_mtgani(m_mtgani[m_nextmtgani[i]],m_time_mtg[i]-m_nextmtgtime[i],(1.0f-weight)*m_curmtgweight[i]);
			}
		}
		
		// current morpth target animation
		if (m_curmtgani[i]!=-1)
		{
			update_mtgani(m_mtgani[m_curmtgani[i]],m_time_mtg[i]-m_curmtgtime[i],weight*m_curmtgweight[i]);
			mtg_flag=true;
		}
	}

	// skelton animation
	if (m_curani>=m_ani.num)
		m_curani=-1;
	if (m_nextani>=m_ani.num)
		m_nextani=-1;

	// blend with next skeleton animation
	if (m_nextani!=-1)
	{
		if (m_nextani==-2)
		{
			m_curani=-1;
			m_curtime=m_nexttime;
			m_nextani=-1;
		}
		else
		if (m_time_ani-m_nexttime>m_nextdur)
		{
			m_curani=m_nextani;
			m_curtime=m_nexttime;
			m_nextani=-1;
		}
		else
		{
			set_skeleton(m_curani,m_time_ani-m_curtime,m_nextani,m_time_ani-m_nexttime);
			m_phy.postmultiply_restposeinv();
			build_mesh();
			return;
		}
	}
	
	// curent skeleton animation
	if (m_curani!=-1)
	{
		set_skeleton(m_curani,m_time_ani-m_curtime);
		m_phy.postmultiply_restposeinv();
		build_mesh();
	}
	else 
	if (mtg_flag)
		build_mesh();
}

bool pMeshSkeleton::get_time(float& cur_time,float& end_time)
{
	if (m_curani!=-1)
	{
		if (m_nextani!=-1)
		{
			pMSAni *a=m_ani.buf[m_nextani];
			//cur_time=fmodf((m_time-m_nexttime),a->kmaxtime);
			cur_time=m_time_ani-m_nexttime;
			if (cur_time>a->kmaxtime)
				cur_time=a->kmaxtime;
			end_time=a->kmaxtime;
			return false;
		}
		else
		{
			pMSAni *a=m_ani.buf[m_curani];
			//cur_time=fmodf((m_time-m_curtime),a->kmaxtime);
			cur_time=m_time_ani-m_curtime;
			if (cur_time>a->kmaxtime)
				cur_time=a->kmaxtime;
			end_time=a->kmaxtime;
		}
	}
	return true;
}

bool pMeshSkeleton::get_time_mtganim(int channel,float& cur_time,float& end_time)
{
	if (m_curmtgani[channel]!=-1)
	{
		if (m_nextmtgani[channel]!=-1)
		{
			pMSMtgAni *ma=m_mtgani.buf[m_nextmtgani[channel]];
//			cur_time=fmodf((m_time-m_nextmtgtime[channel]),ma->animtime);
			cur_time=m_time_mtg[channel]-m_nextmtgtime[channel];
			if (cur_time>ma->animtime)
				cur_time=ma->animtime;
			end_time=ma->animtime;
			return false;
		}
		else
		{
			pMSMtgAni *ma=m_mtgani.buf[m_curmtgani[channel]];
//			cur_time=fmodf((m_time-m_curmtgtime[channel]),ma->animtime);
			cur_time=m_time_mtg[channel]-m_curmtgtime[channel];
			if (cur_time>ma->animtime)
				cur_time=ma->animtime;
			end_time=ma->animtime;
		}
	}
	return true;
}

void pMeshSkeleton::set_skeleton(int ani,float t)
{
	pMSAni *a=m_ani.buf[ani];
	pMatrix *b=m_phy.bmat;

	//t=fmodf(t,a->kmaxtime);
	if (t>a->kmaxtime)
		t=a->kmaxtime;

	int i,j,k1,k2;
	for( i=0;i<a->nkey;i++ )
		if (t<=a->ktime[i])
			break;
	if (i==a->nkey)
		i--;

	if (i==0)
	{
		for( j=0;j<a->nbone;j++ )
		{
			a->krot[j].get_mat(b[j]);
			b[j].mf[12]=a->ktrans[j].x;
			b[j].mf[13]=a->ktrans[j].y;
			b[j].mf[14]=a->ktrans[j].z;
		}
	}
	if (i==a->nkey)
	{
		k1=(i-1)*a->nbone;
		for( j=0;j<a->nbone;j++ )
		{
			a->krot[k1+j].get_mat(b[j]);
			b[j].mf[12]=a->ktrans[k1+j].x;
			b[j].mf[13]=a->ktrans[k1+j].y;
			b[j].mf[14]=a->ktrans[k1+j].z;
		}
	}
	else
	{
		t=(t-a->ktime[i-1])/(a->ktime[i]-a->ktime[i-1]);

		k2=i*a->nbone;
		k1=k2-a->nbone;

		pQuaternion q;
		pVector v;
		
		for( j=0;j<a->nbone;j++ )
		{
			q.slerp(a->krot[k1+j],a->krot[k2+j],t);
			q.get_mat(b[j]);
			v=a->ktrans[k1+j]*(1.0f-t)+a->ktrans[k2+j]*t;
			b[j].mf[12]=v.x;
			b[j].mf[13]=v.y;
			b[j].mf[14]=v.z;
		}
	}
}

void pMeshSkeleton::set_skeleton(int ani1,float t1,int ani2,float t2)
{
	pMatrix *b=m_phy.bmat;

	pMSAni *a1=m_ani.buf[ani1];
	pMSAni *a2=m_ani.buf[ani2];

//	t1=fmodf(t1,a1->kmaxtime);
//	t2=fmodf(t2,a2->kmaxtime);
	if (t1>a1->kmaxtime)
		t1=a1->kmaxtime;
	if (t2>a2->kmaxtime)
		t2=a2->kmaxtime;

	int i,j,k1,k2;

	for( i=0;i<a1->nkey;i++ )
		if (t1<=a1->ktime[i])
			break;
	if (i==a1->nkey)
		i--;
	k1=i;

	for( i=0;i<a2->nkey;i++ )
		if (t2<=a2->ktime[i])
			break;
	if (i==a2->nkey)
		i--;
	k2=i;

	pQuaternion q,q1,q2;
	pVector v,v1,v2;
	float t;

	t=t2/m_nextdur;
	t1=(t1-a1->ktime[k1-1])/(a1->ktime[k1]-a1->ktime[k1-1]);
	t2=(t2-a2->ktime[k2-1])/(a2->ktime[k2]-a2->ktime[k2-1]);

	for( j=0;j<m_phy.nbone;j++ )
	{
		if (k1==0)
		{
			q1=a1->krot[j];
			v1=a1->ktrans[j];
		}
		else
		if (k1==a1->nkey)
		{
			i=(k1-1)*m_phy.nbone;
			q1=a1->krot[i+j];
			v1=a1->ktrans[i+j];
		}
		else
		{
			i=(k1-1)*m_phy.nbone;
			q1.slerp(a1->krot[i+j],a1->krot[i+j+m_phy.nbone],t1);
			v1=a1->ktrans[i+j]*(1.0f-t1)+a1->ktrans[i+j+m_phy.nbone]*t1;
		}

		if (k2==0)
		{
			q2=a2->krot[j];
			v2=a2->ktrans[j];
		}
		else
		if (k2==a2->nkey)
		{
			i=(k2-1)*m_phy.nbone;
			q2=a2->krot[i+j];
			v2=a2->ktrans[i+j];
		}
		else
		{
			i=(k2-1)*m_phy.nbone;
			q2.slerp(a2->krot[i+j],a2->krot[i+j+m_phy.nbone],t2);
			v2=a2->ktrans[i+j]*(1.0f-t2)+a2->ktrans[i+j+m_phy.nbone]*t2;
		}

		q.slerp(q1,q2,t);
		v=v1*(1.0f-t)+v2*t;

		q.get_mat(b[j]);
		b[j].mf[12]=v.x;
		b[j].mf[13]=v.y;
		b[j].mf[14]=v.z;
	}
}

void pMeshSkeleton::build_mesh()
{
	int i,j,c,p;
	pVector v,n,vv,nn;
	float f;
	
	bbox.reset();
	p=0;
	for( i=0;i<nvert;i++ )
	{
		vv=pVector(vert[i].pos[0],vert[i].pos[1],vert[i].pos[2]);
		nn=pVector(vert[i].norm[0],vert[i].norm[1],vert[i].norm[2]);
		vv+=m_phy.voffset[i];

		v.vec(0);
		n.vec(0);
		c=m_phy.vweightcount[i];
		for( j=0;j<c;j++ )
		{
			f=m_phy.wfactor[p+j];
			v += m_phy.bmat[m_phy.wboneindx[p+j]]*vv*f;
			n += m_phy.bmat[m_phy.wboneindx[p+j]].multiply_rotation(nn)*f;
		}
		p+=c;

		m_mesh.vert[i].pos[0]=v.x;
		m_mesh.vert[i].pos[1]=v.y;
		m_mesh.vert[i].pos[2]=v.z;

		f=n.x*n.x+n.y*n.y+n.z*n.z;
		f=1.0f/sqrtf(f);
		m_mesh.vert[i].norm[0]=n.x*f;
		m_mesh.vert[i].norm[1]=n.y*f;
		m_mesh.vert[i].norm[2]=n.z*f;

		if ((i&15)==0)
			bbox.add_point(v);
	}

	m_mesh.update_buffers(1);
}

///////////////////////////////

pMSPhy::pMSPhy() :
	nvert(0),
	vweightcount(0),
	voffset(0),
	nweight(0),
	wboneindx(0),
	wfactor(0),
	nbone(0),
	bparent(0),
	bmat(0),
	bmatrest(0)
{
}
	
pMSPhy::~pMSPhy()
{
	reset();
}

void pMSPhy::operator=(const pMSPhy& in)
{
	set_numvert(in.nvert);
	set_numweight(in.nweight);
	set_numbone(in.nbone);

	int i;

	for( i=0;i<nvert;i++ )
	{
		vweightcount[i]=in.vweightcount[i];
		voffset[i]=in.voffset[i];
	}

	for( i=0;i<nweight;i++ )
	{
		wboneindx[i]=in.wboneindx[i];
		wfactor[i]=in.wfactor[i];
	}

	for( i=0;i<nbone;i++ )
	{
		bparent[i]=in.bparent[i];
		bmat[i]=in.bmat[i];
		bmatrest[i]=in.bmatrest[i];
	}
}

void pMSPhy::reset()
{
	delete[] vweightcount;
	delete[] voffset;
	nvert=0;
	vweightcount=0;
	voffset=0;


	delete[] wboneindx;
	delete[] wfactor;
	nweight=0;
	wboneindx=0;
	wfactor=0;

	delete[] bmat;
	bmat=0;
	delete[] bmatrest;
	bmatrest=0;
	delete[] bparent;
	bparent=0;
	nbone=0;
}

void pMSPhy::set_numvert(int nv,bool keep_old)
{
	int i;
	
	int *tmp1=0;
	if (nv)
		tmp1=new int[nv];
	if (keep_old && vweightcount)
		for( i=0;i<nvert&&i<nv;i++ )
			tmp1[i]=vweightcount[i];
	delete[] vweightcount;
	vweightcount=tmp1;

	pVector *tmp2 = new pVector();
	if (nv)
		tmp2=new pVector[nv];
	if (keep_old && voffset)
		for( i=0;i<nvert&&i<nv;i++ )
			tmp2[i]=voffset[i];
	delete[] voffset;
	voffset=tmp2;

	nvert=nv;
}

void pMSPhy::set_numweight(int nw,bool keep_old)
{
	int i;

	int *tmp1=0;
	if (nw)
		tmp1=new int[nw];
	if (keep_old && wboneindx)
		for( i=0;i<nweight&&i<nw;i++ )
			tmp1[i]=wboneindx[i];
	delete[] wboneindx;
	wboneindx=tmp1;

	float *tmp2=0;
	if (nw)
		tmp2=new float[nw];
	if (keep_old && wfactor)
		for( i=0;i<nweight&&i<nw;i++ )
			tmp2[i]=wfactor[i];
	delete[] wfactor;
	wfactor=tmp2;

	nweight=nw;
}

void pMSPhy::set_numbone(int nb,bool keep_old)
{
	int i;

	pMatrix *tmp1=0;
	if (nb)
		tmp1=new pMatrix[nb];
	if (keep_old && bmat)
		for( i=0;i<nbone&&i<nb;i++ )
			tmp1[i]=bmat[i];
	delete[] bmat;
	bmat=tmp1;

	int *tmp2=0;
	if (nb)
		tmp2=new int[nb];
	if (keep_old && bparent)
		for( i=0;i<nbone&&i<nb;i++ )
			tmp2[i]=bparent[i];
	delete[] bparent;
	bparent=tmp2;

	nbone=nb;
}

bool pMSPhy::load(const char *file)
{
	pFile fp;
	if (fp.open(file)==false)
		return false;

	int i,j,k;

	reset();

	fp.read(&i,sizeof(int));
	fp.read(&j,sizeof(int));
	if (j!=1) 
	{
		fp.close();
		return false;
	}

	fp.read(&nvert,sizeof(int));
	set_numvert(nvert);

	fp.read(&nbone,sizeof(int));
	set_numbone(nbone);

	fp.read(&nweight,sizeof(int));
	set_numweight(nweight);

	fp.read(bparent,sizeof(int)*nbone);

	k=0;
	for( i=0;i<nvert;i++ )
	{
		fp.read(&vweightcount[i],sizeof(int));
		voffset[i].vec(0);
		for( j=0;j<vweightcount[i];j++ )
		{
			fp.read(&wboneindx[k],sizeof(int));
			fp.read(&wfactor[k],sizeof(float));
			k++;
		}
	}

	fp.close();

	return true;
}

bool pMSPhy::build(pMSAni *r)
{
	if (r->nbone!=nbone)
	return false;

	delete[] bmatrest;
	bmatrest=new pMatrix[nbone];

	pMatrix mat;
	pVector n,v,o;
	int i;
	for( i=0;i<nbone;i++ )
	{
		r->krot[i].get_mat(mat);
		mat.mf[12]=r->ktrans[i].x;
		mat.mf[13]=r->ktrans[i].y;
		mat.mf[14]=r->ktrans[i].z;
		mat.get_affine_inverse(bmatrest[i]);
	}

	return true;
}

void pMSPhy::postmultiply_restposeinv()
{
	int i;
	for( i=0;i<nbone;i++ )
		bmat[i]=bmatrest[i]*bmat[i];
}

///////////////////////////////

pMSAni::pMSAni() :
	nbone(0),
	nkey(0),
	kmaxtime(0),
	ktime(0),
	ktrans(0),
	krot(0)
{
}
	
pMSAni::~pMSAni()
{
	reset();
}

void pMSAni::operator=(const pMSAni& in)
{
	set_numkey(in.nbone,in.nkey);

	kmaxtime=in.kmaxtime;

	int i,j,k=0;
	for( i=0;i<nkey;i++ )
	{
		ktime[i]=in.ktime[i];
		for( j=0;j<nbone;j++ )
		{
			ktrans[k]=in.ktrans[k];
			krot[k]=in.krot[k];
			k++;
		}
	}
}

void pMSAni::reset()
{
	nbone=0;

	nkey=0;
	kmaxtime=0;
	delete[] ktime;
	delete[] ktrans;
	delete[] krot;
	ktime=0;
	ktrans=0;
	krot=0;
}

void pMSAni::set_numkey(int nb,int nk,bool keep_old)
{
	int i;

	float *tmp1=0;
	if (nk)
		tmp1=new float[nk];
	if (keep_old && ktime)
		for( i=0;i<nkey&&i<nk;i++ )
			tmp1[i]=ktime[i];
	delete[] ktime;
	ktime=tmp1;
	
	int k1=nbone*nkey;
	int k2=nk*nb;

	pVector *tmp2=0;
	if (k2)
		tmp2=new pVector[k2];
	if (keep_old && ktrans)
		for( i=0;i<k1;i++ )
			tmp2[i]=ktrans[i];
	delete[] ktrans;
	ktrans=tmp2;

	pQuaternion *tmp3=0;
	if (k2)
		tmp3=new pQuaternion[k2];
	if (keep_old && krot)
		for( i=0;i<k1;i++ )
			tmp3[i]=krot[i];
	delete[] krot;
	krot=tmp3;

	nbone=nb;
	nkey=nk;
}

bool pMSAni::load(const char *file)
{
	pFile fp;
	if (fp.open(file)==false)
		return false;

	int i,j,k;

	reset();

	fp.read(&i,sizeof(int));
	fp.read(&j,sizeof(int));
	if (j!=1) 
	{
		fp.close();
		return false;
	}

	fp.read(&nbone,sizeof(int));
	fp.read(&nkey,sizeof(int));
	fp.read(&kmaxtime,sizeof(float));

	set_numkey(nbone,nkey);
	
	k=0;
	for( i=0;i<nkey;i++ )
	{
		fp.read(&ktime[i],sizeof(float));
		for( j=0;j<nbone;j++ )
		{
			fp.read(&ktrans[k].x,sizeof(float)*3);
			fp.read(&krot[k].x,sizeof(float)*4);
			k++;
		}
	}

	fp.close();

	return true;
}

pMSMtg::pMSMtg() :
	noffset(0),offsetvert(0),offset(0)
{
}

pMSMtg::~pMSMtg()
{
	reset();
}

void pMSMtg::reset()
{
	delete[] offsetvert;
	delete[] offset;
	offsetvert=0;
	offset=0;
}

pMSMtg::pMSMtg(const pMSMtg &in)
{
	name=in.name;
	nvert=in.nvert;
	noffset=in.noffset;
	offsetvert=new int[noffset];
	offset=new pVector[noffset];
	for( int i=0;i<noffset;i++ )
	{
		offsetvert[i]=in.offsetvert[i];
		offset[i]=in.offset[i];
	}
}

void pMSMtg::operator=(const pMSMtg &in)
{
	reset();
	name=in.name;
	nvert=in.nvert;
	set_noffset(in.noffset);
	for( int i=0;i<noffset;i++ )
	{
		offsetvert[i]=in.offsetvert[i];
		offset[i]=in.offset[i];
	}
}

void pMSMtg::set_noffset(int n,int keep_old)
{
	int i;

	int *tmp1=0;
	if (n)
		tmp1=new int[n];
	if (keep_old && offsetvert)
		for( i=0;i<noffset&&i<n;i++ )
			tmp1[i]=offsetvert[i];
	delete[] offsetvert;
	offsetvert=tmp1;

	pVector *tmp2=0;
	if (n)
		tmp2=new pVector[n];
	if (keep_old && offset)
		for( i=0;i<noffset&&i<n;i++ )
			tmp2[i]=offset[i];
	delete[] offset;
	offset=tmp2;

	noffset=n;
}

int pMeshSkeleton::load_mtg(const char *file)
{
	pFile fp;
	if (fp.open(file)==false)
		return false;

	int i,j,k,n;

	fp.read(&i,sizeof(int));	
	fp.read(&j,sizeof(int));	
	fp.read(&k,sizeof(int));	
	if (j!=1 || k!=nvert)
	{
		fp.close();
		return false;
	}

	pMSMtg *mtg;
	char str[1024];
	
	fp.read(&j,sizeof(int));	
	for( i=0;i<j;i++ )
	{
		mtg=new pMSMtg;
		mtg->nvert=nvert;

		fp.read(&k,sizeof(int));
		fp.read(str,sizeof(char)*k);
		str[k]=0;
		mtg->name=str;
		
		fp.read(&n,sizeof(int));
		mtg->set_noffset(n);
		for( k=0;k<n;k++ )
		{
			fp.read(&mtg->offsetvert[k],sizeof(int));
			fp.read(&mtg->offset[k],sizeof(float)*3);
		}

		m_mtg.add(mtg);
	}

	fp.close();

	return true;
}

void pMeshSkeleton::blend_mtg(pMSMtg *mtg,float weight)
{
	int i;
	for( i=0;i<mtg->noffset;i++ )
		m_phy.voffset[mtg->offsetvert[i]]+=mtg->offset[i]*weight;
}

void pMeshSkeleton::clear_mtg()
{
	int i;
	for( i=0;i<m_phy.nvert;i++ )
		m_phy.voffset[i].vec(0);
}

int pMeshSkeleton::load_mtgani(const char *file)
{
	pFile fp;
	if (fp.open(file)==false)
		return false;
		
	int i,j,k,n;

	fp.read(&i,sizeof(int));
	fp.read(&j,sizeof(int));	
	if (j!=1)
	{
		fp.close();
		return false;
	}

	fp.read(&n,sizeof(int));

	pMSMtgAni *ma=new pMSMtgAni;
	ma->set_nanim(n);

	char str[1024];
	float f;
	
	for( i=0;i<n;i++ )
	{
		fp.read(&j,sizeof(int));
		fp.read(str,sizeof(char)*j);
		str[j]=0;

		ma->animmtg[i]=-1;
		for( k=0;k<m_mtg.num;k++ )
			if (m_mtg.buf[k]->name.compare(str)==0)
			{
				ma->animmtg[i]=k;
				break;
			}
	}
	
	ma->animtime=0;
	for( i=0;i<n;i++ )
	{
		fp.read(&j,sizeof(int));
		ma->anim[i].set_type(P_ANIMTYPE_VALUE_LINEAR);
		ma->anim[i].set_numkeys(j);
		for( k=0;k<j;k++ )
		{
			fp.read(&f,sizeof(float));
			ma->anim[i].keytime[k]=f;
			fp.read(&f,sizeof(float));
			ma->anim[i].keyvalue[k]=f;
		}
		if (j && ma->anim[i].keytime[j-1]>ma->animtime)
			ma->animtime=ma->anim[i].keytime[j-1];
	}

	m_mtgani.add(ma);

	fp.close();

	return true;
}

void pMeshSkeleton::update_mtgani(pMSMtgAni *ma,float time,float weight)
{
	int i;
	float f;
	for( i=0;i<ma->nanim;i++ )
	{
		if (ma->animmtg[i]!=-1 && 
			ma->animmtg[i]<m_mtg.num &&
			ma->anim[i].numkey>1)
		{
			ma->anim[i].update(time,&f);
			if (f>0.0001f)
				blend_mtg(m_mtg[ma->animmtg[i]],f*weight);
		}
	}
}

pMSMtgAni::pMSMtgAni() :
	nanim(0),
	animmtg(0),
	anim(0),
	animtime(0)
{
}

pMSMtgAni::~pMSMtgAni()
{
	reset();
}

void pMSMtgAni::reset()
{
	delete[] animmtg;
	delete[] anim;
	animmtg=0;
	anim=0;
}

pMSMtgAni::pMSMtgAni(const pMSMtgAni &in)
{
	set_nanim(in.nanim);
	animtime=in.animtime;
	int i;
	for( i=0;i<nanim;i++ )
	{
		animmtg[i]=in.animmtg[i];
		anim[i]=in.anim[i];
	}
}

void pMSMtgAni::operator=(const pMSMtgAni& in)
{
	reset();
	set_nanim(in.nanim);
	animtime=in.animtime;
	int i;
	for( i=0;i<nanim;i++ )
	{
		animmtg[i]=in.animmtg[i];
		anim[i]=in.anim[i];
	}
}

void pMSMtgAni::set_nanim(int n,bool keep_old)
{
	int i;

	int *tmp1=0;
	if (n)
		tmp1=new int[n];
	if (keep_old && animmtg)
		for( i=0;i<nanim&&i<n;i++ )
			tmp1[i]=animmtg[i];
	delete[] animmtg;
	animmtg=tmp1;
	
	pAnimation *tmp2=0;
	if (n)
		tmp2=new pAnimation[n];
	if (keep_old && anim)
		for( i=0;i<nanim&&i<n;i++ )
			tmp2[i]=anim[i];
	delete[] anim;
	anim=tmp2;

	nanim=n;
}

void pMeshSkeleton::set_mtgani_weight(int channel, float weight)
{
	m_curmtgweight[channel]=weight;
}

float pMSMtgAni::get_anim_factor(int n)
{
	if (n<0 || n>=nanim)
		return -1;
	return anim[n].lastvalue[0];
}

float pMeshSkeleton::get_mtg_factor(int mtgani_channel,const char *mtg_name)
{
	if (mtgani_channel<0 || mtgani_channel>=P_MSMAXMTGANI)
		return -1;
	if (m_curmtgani[mtgani_channel]<0)
		return -1;
	if (m_curmtgani[mtgani_channel]>=m_mtgani.num)
		return -1;

	pMSMtgAni *a=m_mtgani.buf[m_curmtgani[mtgani_channel]];
	
	for( int i=0;i<a->nanim;i++ ){
		if (a->animmtg[i]>=0 && a->animmtg[i]<m_mtg.num){
			if (m_mtg.buf[a->animmtg[i]]->name==mtg_name){
				return a->get_anim_factor(i)*m_curmtgweight[mtgani_channel];
			}
		}
	}
	return -1;
}
