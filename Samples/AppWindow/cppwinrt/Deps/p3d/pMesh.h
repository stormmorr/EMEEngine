/*! \file */

#ifndef PMESH_H
#define PMESH_H

#include <string>

#ifdef UNIFICATION
#include "cal3d/streamsource.h"
#else
#include "../../../UNCal3DUWP/cal3d/src/cal3d/streamsource.h"
#endif

#if 0
#include "bvh.h"
#include "aap.h"
#include "vec4d.h"
#endif

//! Triangle Mesh class
/*!
	This class implements a 3D object triangle mesh. It supports loading of	P3D
	and 3DS files. If Vertex Buffer Object extension (VBO) is supported by current
	graphics card it is used to process all geometry data. Moreover, it allows
	calculus of tangent and binormal vectors per vextex to be used to bump mapping.
*/
class P3D_API pMesh
{
	public:
		int flags;					//!< bit flags (P_MESHFLAGS_DIRTY)
		int nvert;					//!< number of vertices of this mesh
		int nface;					//!< number of faces of this mesh
		int nfacemat;				//!< 
		int nmat;					//!< number of materials used in this mesh
		int ncam;					//!< number of cameras associated with this mesh
		int nlight;					//!< number of source lights associated with this mesh
		int ndummy;					//!< number of attach points associated with this mesh
		int nobb;					//!< number of oriented bounding boxes associated with this mesh
#ifdef P_MESH_SHORT_FACE
		unsigned short *facevert;	//!< array of vertex indices
#else
		unsigned int *facevert;		//!< array of vertex indices
#endif
		int *facemat;				//!< number of triangels per material type
		pFace *face;				//!< array of faces
		pVertex *vert;				//!< array of vertices
		pMaterial *mat;				//!< array of materials
		pCamera *cam;				//!< array of cameras
		pLight *light;				//!< array of source lights
		pDummy *dummy;				//!< array of attach points
		pOrientedBoundBox *obb;		//!< array of oriented bounding boxes
		pVector ambient;			//!< self ilumination
		pVector bgcolor;			//!< background color
		pString bgpic;				//!< path of background picture file
		pBoundBox bbox;				//!< axis-aligned bounding box of mesh
		pString name;				//!< path of mesh file
		unsigned int vertbuffer;	//!< vertex buffer id (if VBO is supported)
		unsigned int facebuffer;	//!< face buffer id (if VBO is supported)
		pOcTree octree;				//!< octree associated with this mesh
		int bgmode;
		int *edge;
		int nedge;

#if 0
		// for building BVH
		pColdet::bvh_tree *_tree;
		pColdet::vec3f *_tri_centers;
		pColdet::aabb *_tri_boxes;
		//std::vector<Digi::Vertex> m_tri_nrms;

		// for collide
		unsigned int _num_box_tests;
		unsigned int _num_trf_tests;
		unsigned int _num_contacts;
		unsigned int *_contacts;

		void acBuildBVH(void);
		void acDeleteBVH(void);
		int acRefitBVH(void);
		void acDisplayBVH(int);

		//void acCollide(DigiModel *mdl);
		void acSelfCollide(void);

		void acColorCollide(void);

		int NumBoxTest() { return _num_box_tests; }
		int NumTriTest() { return _num_trf_tests; }
		int NumContact() { return _num_contacts; }
		bool acGetContact(int i, unsigned int &id1, unsigned int &id2);
#endif

	//! Default constrcutor.
	pMesh();

	//! Destructor.
	virtual ~pMesh();

	//! Free all memory of mesh and resets all data.
	void reset();

	//! Operator =
	void operator=(const pMesh& in);

	//! Compute several attributes associated with mesh accordingly to 'mode'.
	/*!
		Attributes that can be computed are: normal per face, normal per vertex,
		tangent and binormal vectors per vertex and a axis-aligned bounding box.
		These attributes can be selected by the parameter mode that is a bit flag.
		By default, all parameters are computed.
		@param mode bit flag (P_COMPUTE_FACENORM,P_COMPUTE_VERTNORM,P_COMPUTE_TANGENTS,P_COMPUTE_BBOX,P_COMPUTE_ALL)
	*/
	void compute_normals(float f_UVFactor, int mode);

	//! Computes tangent and binormal vectors per vertex (to bump mapping technique).
	void compute_tangents();

	//! If VBO is supported, this method update both vertex and face buffers.
	/*!
		This method must be called ever that the array of vertices or the array of
		vertex indices are changed. 
		@param flags Bit 1 for updating vertex array and bit 2 for face array.
	*/
	void update_buffers(float f_UVFactor, int flags=3);

	//! Update the number of faces.
	/*!
		@param nf the new number of faces
		@param keepold if 1, old faces are kept, if 0 old faces are lost
	*/
	void set_numface(int nf,int keepold=1);
	void set_numvert(int nv,int keepold=1);
	void set_nummat(int nm,int keepold=1);
	void set_numfacemat(int nfm,int keepold=1);
	void set_numcam(int nc,int keepold=1);
	void set_numlight(int nl,int keepold=1);
	void set_numdummy(int nd,int keepold=1);
	void set_numobb(int no,int keepold=1);

	int save_p3d(const char *file);
	int load_p3d(const char *file, float f_UVFactor, int octreedepth=0);
	int load_cal3d(std::string i_name, QunStreamSource &dataSrc, int octreedepth, float i_scale);
	int load_cal3d(std::string i_name, QunStreamSource &dataSrc, int octreedepth, float i_scale, bool f_flip);
#ifdef P_SUPPORT_3DS
	int load_3ds(const char *file,int octreedepth=0);
#endif
	void draw(int renderflag,int rendermode,pRenderProfile *profile=NULL) const;
	void draw_faces_shadow(const pVector& lightpos) const;

	int ray_intersect(const pVector& ro,const pVector& rd,pVector& ip,float& dist) const;

	void array_lock(int drawflag,int vb) const;
	void array_draw(int vb) const;
	void array_unlock() const;

	void compute_edges();
	void compute_facemat();
	void compute_nuv(const pFace *f,const pVector& ip,pVector& normal,pVector& texcoord) const;
	void sort_facemat();
	void group_faces_material(pFace **f,int num) const;
	void compute_curvature();
	void solve_least_squares(int n,const float *A,const float *B,float& a,float& b);

private:
	friend class bvh_tree;
	friend class bvh_node;
};

#endif
