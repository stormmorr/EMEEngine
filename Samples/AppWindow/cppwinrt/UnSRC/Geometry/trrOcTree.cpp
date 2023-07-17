/*

	unTrrOctree
	Copyright OSIREM (C) 2007
	www.osirem.com SVN - svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

#include "trrOctree.h"

unTrrOcTree::unTrrOcTree()
{
	root=0;
}

unTrrOcTree::~unTrrOcTree()
{
	reset();
}

void unTrrOcTree::reset()
{
	delete root;
	root=0;
}

void unTrrOcTree::build_tree(int nf,pFace *f,pVertex *v,unsigned int *fv,int maxdepth)
{
	reset();
	root=new unTrrOcTreeNode;

	vert=v;
	facevert=fv;

	root->bbox.reset();

	int i,j;
	for( i=0;i<nf;i++ )
		{
		for( j=0;j<3;j++ ) root->bbox.add_point( &v[fv[f[i].vertindx+j]].pos[0] );

		root->faces.add(&f[i]);
		}

	root->build_node(vert,facevert,1,maxdepth);
}

pFace *unTrrOcTree::ray_intersect(const pVector& ro,const pVector& rd,pVector& ip,float& dist,int isshadowray) const
{
	float tmp_dist;
	pVector tmp_ip;

	int n,i,j,k=-1;
	pFace **f;

	pArray<unTrrOcTreeNode *> nodes;

	clip_ray(ro,rd,nodes);
	sort_nodes(nodes.buf,nodes.num);

	for( n=0;n<nodes.num;n++ )
	{
		dist=nodes[n]->maxdist+0.1f;
		j=nodes[n]->faces.num;
		f=nodes[n]->faces.buf;
		if (isshadowray)
		{
			for( i=0;i<j;i++ )
				if ((f[i]->flags&P_FACEFLAGS_NOSHADOW)==0)
				if (f[i]->ray_intersect(vert,facevert,ro,rd,tmp_ip,tmp_dist))
					if (tmp_dist<dist)
					{
						dist=tmp_dist;
						ip=tmp_ip;
						k=i;
					}
		}
		else
		{
			for( i=0;i<j;i++ )
				if (f[i]->ray_intersect(vert,facevert,ro,rd,tmp_ip,tmp_dist))
					if (tmp_dist<dist)
					{
						dist=tmp_dist;
						ip=tmp_ip;
						k=i;
					}
		}
		if (k!=-1)
			return f[k];
	}
	
	return 0;
}

void unTrrOcTree::clip_ray(const pVector& ro,const pVector& rd,pArray<unTrrOcTreeNode *>& nodes) const
{
	nodes.clear();

	float f;
	if (root->bbox.ray_intersect(ro,rd,f,root->maxdist)==-1)
		return;

	unTrrOcTreeNode *stack[OCTREE_MAXSTACK],*n;
	int nstack=1,i;
	stack[0]=root;

	while(nstack)
	{
		n=stack[--nstack];
		if (n->faces.num==0)
		{
			for( i=0;i<8;i++ )
				if (n->nodes[i] && 
					n->nodes[i]->bbox.ray_intersect(ro,rd,f,n->nodes[i]->maxdist)!=-1)
					stack[nstack++]=n->nodes[i];
		}
		else
			nodes.add(n);
	}
}

void unTrrOcTree::clip_frustum(const pFrustum& view,pArray<unTrrOcTreeNode *>& nodes) const
{
	nodes.clear();
	if (root==0)
		return;

	unTrrOcTreeNode *stack[OCTREE_MAXSTACK];

	if (view.clip_bbox(root->bbox)==0)
		return;

	unTrrOcTreeNode *n;
	int nstack=1,i;
	stack[0]=root;

	while(nstack)
	{
		n=stack[--nstack];
		if (n->faces.num==0)
		{
			for( i=0;i<8;i++ )
				if (n->nodes[i] && 
					view.clip_bbox(n->nodes[i]->bbox))
					stack[nstack++]=n->nodes[i];
		}
		else
			nodes.add(n);
	}
}

void unTrrOcTree::clip_frustum(int curdraw,const pFrustum& view,pArray<pFace *>& faces) const
{
	faces.clear();
	if (root==0)
		return;

	unTrrOcTreeNode *stack[OCTREE_MAXSTACK];

	if (view.clip_bbox(root->bbox)==0)
		return;

	unTrrOcTreeNode *n;
	int nstack=1,i;
	stack[0]=root;

	while(nstack)
	{
		n=stack[--nstack];
		if (n->faces.num==0)
		{
			for( i=0;i<8;i++ )
				if (n->nodes[i] && 
					view.clip_bbox(n->nodes[i]->bbox))
					stack[nstack++]=n->nodes[i];
		}
		else
		{
			for( i=0;i<n->faces.num;i++ )
				if (n->faces.buf[i]->lastdraw!=curdraw)
				{
					n->faces.buf[i]->lastdraw=curdraw;
					faces.add(n->faces.buf[i]);
				}
		}
	}
}

void unTrrOcTree::clip_bbox(int curdraw,const pBoundBox& bbox,pArray<pFace *>& faces,int shadow) const
{
	unTrrOcTreeNode *stack[OCTREE_MAXSTACK];

	faces.clear();

	if (bbox.clip_bbox(root->bbox.min,root->bbox.max)==0)
		return;

	unTrrOcTreeNode *n;
	int nstack=1,i;
	stack[0]=root;

	if (shadow)
	{
		pVector lightpos=(bbox.min+bbox.max)*0.5f;
		float lightrad=bbox.max.x-lightpos.x;
		while(nstack)
		{
			n=stack[--nstack];
			if (n->faces.num==0)
			{
				for( i=0;i<8;i++ )
					if (n->nodes[i] && 
						bbox.clip_bbox(n->nodes[i]->bbox.min,n->nodes[i]->bbox.max))
						stack[nstack++]=n->nodes[i];
			}
			else
			{
				for( i=0;i<n->faces.num;i++ )
					if (n->faces.buf[i]->lastdraw!=curdraw)
					{
						n->faces.buf[i]->lastdraw=curdraw;
						if (n->faces.buf[i]->distance(&lightpos.x)<lightrad &&
							(n->faces.buf[i]->flags&P_FACEFLAGS_NOSHADOW)==0)
							faces.add(n->faces.buf[i]);
					}
			}
		}
	}
	else
	{
		while(nstack)
		{
			n=stack[--nstack];
			if (n->faces.num==0)
			{
				for( i=0;i<8;i++ )
					if (n->nodes[i] && 
						bbox.clip_bbox(n->nodes[i]->bbox.min,n->nodes[i]->bbox.max))
						stack[nstack++]=n->nodes[i];
			}
			else
			{
				for( i=0;i<n->faces.num;i++ )
					if (n->faces.buf[i]->lastdraw!=curdraw)
					{
						n->faces.buf[i]->lastdraw=curdraw;
						faces.add(n->faces.buf[i]);
					}
			}
		}
	}
}

void unTrrOcTree::clip_frustum_bbox(int curdraw,const pFrustum& view,const pBoundBox& bbox,pArray<pFace *>& faces) const
{
	faces.clear();
	if (root==0)
		return;

	unTrrOcTreeNode *stack[OCTREE_MAXSTACK];

	if (bbox.clip_bbox(root->bbox.min,root->bbox.max)==0)
		return;

	unTrrOcTreeNode *n;
	int nstack=1,i;
	stack[0]=root;

	while(nstack)
	{
		n=stack[--nstack];
		if (n->faces.num==0)
		{
			for( i=0;i<8;i++ )
				if (n->nodes[i] && 
					view.clip_bbox(n->nodes[i]->bbox) && 
					bbox.clip_bbox(n->nodes[i]->bbox.min,n->nodes[i]->bbox.max))
					stack[nstack++]=n->nodes[i];
		}
		else
		{
			for( i=0;i<n->faces.num;i++ )
				if (n->faces.buf[i]->lastdraw!=curdraw)
				{
					n->faces.buf[i]->lastdraw=curdraw;
					faces.add(n->faces.buf[i]);
				}
		}
	}
}

void unTrrOcTree::draw_boxes(const pFrustum& view)
{
	pArray<unTrrOcTreeNode *> nodes;

	root->bbox.draw();

	clip_frustum(view,nodes);
	for( int i=0;i<nodes.num;i++ )
		nodes[i]->bbox.draw();
}

void unTrrOcTree::sort_nodes(unTrrOcTreeNode **n,int num) const
{
	unTrrOcTreeNode *tmp;
	int i,j;

	for( j=0;j<num;j++ )
	for( i=j+1;i<num;i++ )
	{
		if (n[j]->maxdist>n[i]->maxdist)
		{
			tmp=n[j];
			n[j]=n[i];
			n[i]=tmp;
		}
	}
}
