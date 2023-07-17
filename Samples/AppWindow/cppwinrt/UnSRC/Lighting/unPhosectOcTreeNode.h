/*

	unPhosectOctreeNode
	Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

#ifndef unPhosectOcTreeNode_H
#define unPhosectOcTreeNode_H

#include "paralelo3d.h"
#include "Phosect/unPhosect.h"

//! OcTree node class.
/*! 
	This class implements an octree node used to speed up collision 
	detection with detail triangle meshes or curved Bezier faces.
*/
class unPhosectOcTreeNode 
{
	public:
		pBoundBox bbox;			//!< node bound box
		pArray<unPhosect *> pa_phosect;	//!< node faces
		unPhosectOcTreeNode *nodes[8];	//!< node childs
		float maxdist;			//!< distance from bbox center to camera

		pArray<pFace *> faces;	//!< node faces

		//! Default constructor.
		unPhosectOcTreeNode();

		//! Destructor.
		~unPhosectOcTreeNode();

		//! Copy constructor.
		/*!
			@param in the new octree node
		*/
		unPhosectOcTreeNode(unPhosectOcTreeNode& in);

		//! Split faces into child nodes if a subdivison is need (used on the pOcTree build process)
		/*!
			@param vert array of vertices used to build octree
			@param facevert array of indices used to build octree
			@param depth the current depth of octree
			@param the maximum depth of octree
		*/

		void build_node(pVertex *vert, unsigned int *facevert, int depth, int maxdepth);
};

#endif