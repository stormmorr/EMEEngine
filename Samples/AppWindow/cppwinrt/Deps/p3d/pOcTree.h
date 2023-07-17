/*! \file */

#ifndef POCTREE_H
#define POCTREE_H

#define OCTREE_MINFACES 16
#define OCTREE_MAXSTACK 256

//! OcTree class.
/*! 
	This class implements an octree and is used to subdivide the space for 
	complex detail triangle meshes and Bezier curved faces speeding up collision
	detection with its triangles (used for point collision and bbox collision)
*/
class P3D_API pOcTree
{
	public:
		pOcTreeNode *root;	//!< root node for octree
		pVertex *vert;		//!< array of vertices used to build octree
#ifdef P_MESH_SHORT_FACE
		unsigned short *facevert;	//!< array of indices used to build octree
#else
		unsigned int *facevert;		//!< array of indices used to build octree
#endif

		//! Default constructor.
		pOcTree();
		
		//! Destructor.
		~pOcTree();
		
		//! Free the tree data.
		void reset();

		//! Builds the octree for the given triangle face or Bezier face.
		/*!
			@param nf the number of faces
			@param f array of faces
			@param v array of vertices
			@param fv array of indices
			@param maxdepth maximum depth of the octree
		*/
#ifdef P_MESH_SHORT_FACE
		void build_tree(int nf,pFace *f,pVertex *v,unsigned short *fv,int maxdepth);
#else
		void build_tree(int nf,pFace *f,pVertex *v,unsigned int *fv,int maxdepth);
#endif
		
		//! Recurse octree and ray intersect the triangles for the closest collision.
		/*!
			@param ro ray origin
			@param rd ray direction
			@param ip intersection point
			@param dist distance to intersection point
			@param isshadowray is (ro,rd) a shadow ray?
		*/
		pFace *ray_intersect(const pVector& ro,const pVector& rd,pVector& ip,float& dist,int isshadowray=0) const;

		//! Recurse octree and collects all octree nodes that had collided with the ray.
		/*!
			@param ro ray origin
			@param rd ray direction
			@param nodes array of nodes that had collided with the ray
		*/
		void clip_ray(const pVector& ro,const pVector& rd,pArray<pOcTreeNode *>& nodes) const;

		//! Recurse octree and collects all octree nodes inside a given frustum.
		/*!
			@param view a view frustum
			@param nodes array of nodes that had collided with the ray
		*/
		void clip_frustum(const pFrustum& view,pArray<pOcTreeNode *>& nodes) const;
		
		//! Recurse octree and collects all faces inside a given frustum.
		/*!
			This method only consider faces that its time stamp is different to current
			time stamp.
			@param curdraw the current time stamp (this information is stored in g_render->curdraw)
			@param view a view frustum
			@param faces array of faces inside the frustum
		*/
		void clip_frustum(int curdraw,const pFrustum& view,pArray<pFace *>& faces) const;
		
		//! Recurse octree and collects all faces inside a given bounding box.
		/*!
			This method only consider faces that its time stamp is different to current
			time stamp.
			If the shadow flag is equals to 1 so, this method consider that the bounding
			box is a kind of a light's region of influence and collect all faces inside this
			region of influence that cangenerate shadow.
			@param curdraw the current time stamp (this information is stored in g_render->curdraw)
			@param bbox a bounding box
			@param faces array of faces inside the bounding box
			@param shadow shadow flag
		*/
		void clip_bbox(int curdraw,const pBoundBox& bbox,pArray<pFace *>& faces,int shadow=0) const;
		
		//! Recurse octree and collects all faces inside the insertection between a frustum and a bounding box.
		/*!
			This method only consider faces that its time stamp is different to current
			time stamp.
			@param curdraw the current time stamp (this information is stored in g_render->curdraw)
			@param view a view frustum
			@param bbox a bounding box
			@param faces array of faces inside the insertection between the frustum and the bounding box
		*/
		void clip_frustum_bbox(int curdraw,const pFrustum& view,const pBoundBox& bbox,pArray<pFace *>& faces) const;

		//! Draw all octree nodes inside a given frustum.
		/*!
			@param view a view frustum
		*/
		void draw_boxes(const pFrustum& view);

		//! Given an array of octree nodes, apllies an increasing sort on this array.
		/*!
			@param n array of octree nodes
			@param num length of the array
		*/
		void sort_nodes(pOcTreeNode **n,int num) const;
};

#endif
