/*

	unPhosectOctreeNode
	Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

#include "unPhosectOcTreeNode.h"

unPhosectOcTreeNode::unPhosectOcTreeNode()
{
	int i;
	for( i=0;i<8;i++ ) nodes[i]=0;
	maxdist=0;
}

unPhosectOcTreeNode::~unPhosectOcTreeNode()
{
	for( int i=0;i<8;i++ ) delete nodes[i];
}

void unPhosectOcTreeNode::build_node(pVertex *vert,unsigned int *facevert,int depth,int maxdepth)
{
	if (faces.num<=OCTREE_MINFACES || depth>=maxdepth) return;
	depth++;

	int i,j;
	pVector center=(bbox.min+bbox.max)*0.5f;

	for( i=0;i<8;i++ ) nodes[i]=new unPhosectOcTreeNode;
	
	nodes[0]->bbox.min.vec(bbox.min.x,bbox.min.y,bbox.min.z);
	nodes[0]->bbox.max.vec(center.x,center.y,center.z);

	nodes[1]->bbox.min.vec(center.x,center.y,bbox.min.z);
	nodes[1]->bbox.max.vec(bbox.max.x,bbox.max.y,center.z);

	nodes[2]->bbox.min.vec(center.x,bbox.min.y,bbox.min.z);
	nodes[2]->bbox.max.vec(bbox.max.x,center.y,center.z);
	
	nodes[3]->bbox.min.vec(bbox.min.x,center.y,bbox.min.z);
	nodes[3]->bbox.max.vec(center.x,bbox.max.y,center.z);

	nodes[4]->bbox.min.vec(bbox.min.x,bbox.min.y,center.z);
	nodes[4]->bbox.max.vec(center.x,center.y,bbox.max.z);

	nodes[5]->bbox.min.vec(center.x,center.y,center.z);
	nodes[5]->bbox.max.vec(bbox.max.x,bbox.max.y,bbox.max.z);

	nodes[6]->bbox.min.vec(center.x,bbox.min.y,center.z);
	nodes[6]->bbox.max.vec(bbox.max.x,center.y,bbox.max.z);
	
	nodes[7]->bbox.min.vec(bbox.min.x,center.y,center.z);
	nodes[7]->bbox.max.vec(center.x,bbox.max.y,bbox.max.z);

	pBoundBox bb;
	for( i=0;i<faces.num;i++ )
		{
		bb.reset();
		bb.add_point(&vert[facevert[faces[i]->vertindx]].pos[0]);
		bb.add_point(&vert[facevert[faces[i]->vertindx+1]].pos[0]);
		bb.add_point(&vert[facevert[faces[i]->vertindx+2]].pos[0]);
		for( j=0;j<8;j++ ) if (nodes[j]->bbox.clip_bbox(bb.min,bb.max)) nodes[j]->faces.add(faces[i]);
		}

	int tot=0;
	for( i=0;i<8;i++ ) tot+=nodes[i]->faces.num;

	if (faces.num*4<tot)
		{
		for( i=0;i<8;i++ )
			{
			delete nodes[i];
			nodes[i]=0;
			}
		}
	else
		{
		faces.free();

		for( i=0;i<8;i++ )
			{
			if (nodes[i]->faces.num==0)
				{
				delete nodes[i];
				nodes[i]=0;
				}
			else if (nodes[i]->faces.num>OCTREE_MINFACES) nodes[i]->build_node(vert,facevert,depth,maxdepth);
			}
		}
}
