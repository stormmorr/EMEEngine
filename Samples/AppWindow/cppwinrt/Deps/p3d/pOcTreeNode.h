/*! \file */

#ifndef POCTREENODE_H
#define POCTREENODE_H

//! OcTree node class.
/*! 
	This class implements an octree node used to speed up collision 
	detection with detail triangle meshes or curved Bezier faces.
*/
class P3D_API pOcTreeNode 
{
	public:
		pBoundBox bbox;			//!< node bound box
		pArray<pFace *> faces;	//!< node faces
		pOcTreeNode *nodes[8];	//!< node childs
		float maxdist;			//!< distance from bbox center to camera
		
		//! Default constructor.
		pOcTreeNode();

		//! Destructor.
		~pOcTreeNode();

		//! Copy constructor.
		/*!
			@param in the new octree node
		*/
		pOcTreeNode(pOcTreeNode& in);

		//! Split faces into child nodes if a subdivison is need (used on the pOcTree build process)
		/*!
			@param vert array of vertices used to build octree
			@param facevert array of indices used to build octree
			@param depth the current depth of octree
			@param the maximum depth of octree
		*/
#ifdef P_MESH_SHORT_FACE
		void build_node(pVertex *vert,unsigned short *facevert,int depth,int maxdepth);
#else
		void build_node(pVertex *vert,unsigned int *facevert,int depth,int maxdepth);
#endif
};

#endif
