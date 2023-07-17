/*! \file */

#ifndef PMSPHY_H
#define PMSPHY_H

#define P_MSMAXMTGANI 4

// morph target animation
class P3D_API pMSMtgAni
{
	friend class pMeshSkeleton;

protected:
	int nanim;			// num animations
	int *animmtg;		// morph target id array for each animation
	float animtime;		// animation length (max key time)
	pAnimation *anim;	// animation keys array for each animartion

public:
	pMSMtgAni();
	~pMSMtgAni();
	
	pMSMtgAni(const pMSMtgAni &in);
	void operator=(const pMSMtgAni &in);

	// free all data
	void reset();
	// sets number of animations
	void set_nanim(int n,bool keep_old=false);
	// get animation factor
	float get_anim_factor(int n);
};

// morpth target
class P3D_API pMSMtg
{
	friend class pMeshSkeleton;

protected:
	pString name;		// name
	int nvert;			// number of total vertices
	int noffset;		// number of vertices with offset
	int *offsetvert;	// vertex id for each offset
	pVector *offset;	// vertex offsets

public:
	pMSMtg();
	~pMSMtg();
	
	pMSMtg(const pMSMtg &in);
	void operator=(const pMSMtg &in);

	// free all data
	void reset();
	// sets number of offsets
	void set_noffset(int n,int keep_old=false);
};

// physique information (vertices to bone links)
class P3D_API pMSPhy
{
	friend class pMeshSkeleton;
	friend class pMSAni;

protected:
	int nvert;			// number of vertices
	int *vweightcount;	// number of weights per vertex
	pVector *voffset;	// vertices offsets from bones

	int nweight;		// number of total weights
	int *wboneindx;		// bone index for each weight
	float *wfactor;		// weight factor

	int nbone;			// number of bones
	int *bparent;		// array with each bone parent bone (-1 for root)
	pMatrix *bmat;		// currently animated bone matrices
	pMatrix *bmatrest;	// rest pose bone matrices

	void set_numvert(int nv,bool keep_old=false);
	void set_numweight(int nw,bool keep_old=false);
	void set_numbone(int nb,bool keep_old=false);

public:	
	pMSPhy();
	~pMSPhy();

	void operator=(const pMSPhy& in);

	void reset();
	bool load(const char *file);
	bool build(pMSAni *r);
	void postmultiply_restposeinv();
};

// skeleton animation
class P3D_API pMSAni
{
	friend class pMeshSkeleton;
	friend class pMSPhy;

protected:
	int nbone;			// number of bones

	int nkey;			// number of keys
	float kmaxtime;		// maximum animation key time
	float *ktime;		// time for each key
	pVector *ktrans;	// translation vectors for each bone for each key
	pQuaternion *krot;	// rotation quaternion for each bone for each key

	void set_numkey(int nb,int nk,bool keep_old=false);

public:
	pMSAni();
	~pMSAni();

	void operator=(const pMSAni& in);

	void reset();
	bool load(const char *file);
};

// skeleton mesh
class P3D_API pMeshSkeleton : public pMesh
{
protected:
	pMesh m_mesh;					// geometry
	pMSPhy m_phy;					// phisique
	pMSAni m_ani_rest;				// rest pose skeleton
	pArray<pMSAni *> m_ani;			// array of loaded animations
	pArray<pMSMtg *> m_mtg;			// array of loaded morph targets
	pArray<pMSMtgAni *> m_mtgani;	// array of loaded morph target animations
	
	float m_time_ani;					// current skeleton mesh ani time
	float m_time_mtg[P_MSMAXMTGANI];	// current skeleton mesh mtg time

	int m_curani;
	float m_curtime;
	int m_nextani;
	float m_nexttime;
	float m_nextdur;

	int m_curmtgani[P_MSMAXMTGANI];
	float m_curmtgtime[P_MSMAXMTGANI];
	float m_curmtgweight[P_MSMAXMTGANI];
	int m_nextmtgani[P_MSMAXMTGANI];
	float m_nextmtgtime[P_MSMAXMTGANI];
	float m_nextmtgdur[P_MSMAXMTGANI];

	void set_skeleton(int ani,float t);
	void set_skeleton(int ani1,float t1,int ani2,float t2);
	void build_mesh();

public:
	pMeshSkeleton();
	virtual ~pMeshSkeleton();

	void reset();
	void reset_ani();
	void reset_mtg();
	void reset_mtgani();
	bool check_data() const;

	bool load_phy(const char *file);
	bool load_ani_rest(const char *file);
	int load_ani(const char *file);
	int load_mtg(const char *file);
	int load_mtgani(const char *file);

	int get_numbones()
	{ return m_phy.nbone; }
	const pMatrix& get_bone(int i)
	{ return m_phy.bmat[i]; }
	const pMesh *get_draw_mesh() 
	{ return &m_mesh; };

	bool set_ani(int ani,float time,float duration);
	bool set_mtgani(int channel,int mtgani,float time,float duration);
	bool get_time(float& cur_time,float& end_time);
	bool get_time_mtganim(int channel,float& cur_time,float& end_time);
	void update(float time_ani,float time_mtg[P_MSMAXMTGANI]);
	void update_mtgani(pMSMtgAni *ma,float time,float weight=1.0f);
	void set_mtgani_weight(int channel, float weight);
	void clear_mtg();
	void blend_mtg(pMSMtg *m,float weight);
	void build();
	float get_mtg_factor(int mtgani_channel,const char *mtg_name);
};

#endif
