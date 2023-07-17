#include "pch.h"
#include "paralelo3d.h"

float pOrientedBoundBox::distance2(const pVector& pt) const
{
	pVector center(get_center());
	pVector axis[3] = 
	{
		transform.get_column3(0),
		transform.get_column3(1),
		transform.get_column3(2)
	};
	pVector aid((bb.max-bb.min)*0.5f);
    float extent[3] = {aid.x, aid.y, aid.z};

	// compute coordinates of point in box coordinate system
    pVector kDiff(pt - center);
    pVector kClosest(VECDOT(kDiff,axis[0]),VECDOT(kDiff,axis[1]),VECDOT(kDiff,axis[2]));

    // project test point onto box
    float fSqrDistance = 0.0;
    float fDelta;

    if ( kClosest.x < -extent[0] )
    {
        fDelta = kClosest.x + extent[0];
        fSqrDistance += fDelta*fDelta;
        kClosest.x = -extent[0];
    }
    else if ( kClosest.x > extent[0] )
    {
        fDelta = kClosest.x - extent[0];
        fSqrDistance += fDelta*fDelta;
        kClosest.x = extent[0];
    }

    if ( kClosest.y < -extent[1] )
    {
        fDelta = kClosest.y + extent[1];
        fSqrDistance += fDelta*fDelta;
        kClosest.y = -extent[1];
    }
    else if ( kClosest.y > extent[1] )
    {
        fDelta = kClosest.y - extent[1];
        fSqrDistance += fDelta*fDelta;
        kClosest.y = extent[1];
    }

    if ( kClosest.z < -extent[2] )
    {
        fDelta = kClosest.z + extent[2];
        fSqrDistance += fDelta*fDelta;
        kClosest.z = -extent[2];
    }
    else if ( kClosest.z > extent[2] )
    {
        fDelta = kClosest.z - extent[2];
        fSqrDistance += fDelta*fDelta;
        kClosest.z = extent[2];
    }

    return fSqrDistance;
}

float pOrientedBoundBox::distance(const pVector& pt) const
{
	return sqrtf(distance2(pt));
}

void pOrientedBoundBox::write(FILE *fp) const
{
	name.write(fp);
	bb.write(fp);
	fwrite(&transform.mf[0],3,sizeof(float),fp);
	fwrite(&transform.mf[4],3,sizeof(float),fp);
	fwrite(&transform.mf[8],3,sizeof(float),fp);
	fwrite(&transform.mf[12],3,sizeof(float),fp);
}

void pOrientedBoundBox::read(pFile& fp,int ver)
{
	name.read(fp);
	bb.read(fp,ver);
	fp.read(&transform.mf[0],3*sizeof(float));
	fp.read(&transform.mf[4],3*sizeof(float));
	fp.read(&transform.mf[8],3*sizeof(float));
	fp.read(&transform.mf[12],3*sizeof(float));
}

void pOrientedBoundBox::draw()
{
#ifndef P_DISABLE_3D
	glPushMatrix();
	glMultMatrixf(&transform.mf[0]);
	bb.draw();
	glPopMatrix();
#endif
}

P3D_API float pOrientedBoundBox::distance2(const pOrientedBoundBox& obb,const pVector& pt,float& ot1,float& ot2,float& ot3)
{
	pVector center(obb.get_center());
	pVector axis[3] = 
	{
		obb.transform.get_column3(0),
		obb.transform.get_column3(1),
		obb.transform.get_column3(2)
	};
	pVector aid((obb.bb.max-obb.bb.min)*0.5f);
    float extent[3] = {aid.x, aid.y, aid.z};

	// compute coordinates of point in box coordinate system
    pVector kDiff(pt - center);
    pVector kClosest(VECDOT(kDiff,axis[0]),VECDOT(kDiff,axis[1]),VECDOT(kDiff,axis[2]));

    // project test point onto box
    float fSqrDistance = 0.0;
    float fDelta;

    if ( kClosest.x < -extent[0] )
    {
        fDelta = kClosest.x + extent[0];
        fSqrDistance += fDelta*fDelta;
        kClosest.x = -extent[0];
    }
    else if ( kClosest.x > extent[0] )
    {
        fDelta = kClosest.x - extent[0];
        fSqrDistance += fDelta*fDelta;
        kClosest.x = extent[0];
    }

    if ( kClosest.y < -extent[1] )
    {
        fDelta = kClosest.y + extent[1];
        fSqrDistance += fDelta*fDelta;
        kClosest.y = -extent[1];
    }
    else if ( kClosest.y > extent[1] )
    {
        fDelta = kClosest.y - extent[1];
        fSqrDistance += fDelta*fDelta;
        kClosest.y = extent[1];
    }

    if ( kClosest.z < -extent[2] )
    {
        fDelta = kClosest.z + extent[2];
        fSqrDistance += fDelta*fDelta;
        kClosest.z = -extent[2];
    }
    else if ( kClosest.z > extent[2] )
    {
        fDelta = kClosest.z - extent[2];
        fSqrDistance += fDelta*fDelta;
        kClosest.z = extent[2];
    }

	ot1=kClosest.x;
	ot2=kClosest.y;
	ot3=kClosest.z;

    return fSqrDistance;
}

P3D_API float pOrientedBoundBox::distance(const pOrientedBoundBox& obb,const pVector& pt,float& ot1,float& ot2,float& ot3)
{
	return pOrientedBoundBox::distance2(obb,pt,ot1,ot2,ot3);
}
