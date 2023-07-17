#include "pch.h"
#include "paralelo3d.h"

float pLineSegment::distance2(const pLineSegment& ls) const
{
	pVector dir(end - start);
	pVector ls_dir(ls.end - ls.start);
	pVector kDiff(start - ls.start);
    float fA00 = dir.length2();
    float fA01 = -VECDOT(dir,ls_dir);
    float fA11 = ls_dir.length2();
    float fB0 = VECDOT(kDiff,dir);
    float fC = kDiff.length2();
    float fDet = fabsf(fA00*fA11-fA01*fA01);
    float fB1, fS, fT, fSqrDist, fTmp;

    if ( fDet >= 1e-05f )
    {
        // line segments are not parallel
        fB1 = -VECDOT(kDiff,ls_dir);
        fS = fA01*fB1-fA11*fB0;
        fT = fA01*fB0-fA00*fB1;
        
        if ( fS >= 0.0f )
        {
            if ( fS <= fDet )
            {
                if ( fT >= 0.0f )
                {
                    if ( fT <= fDet )  // region 0 (interior)
                    {
                        // minimum at two interior points of 3D lines
                        float fInvDet = 1.0f/fDet;
                        fS *= fInvDet;
                        fT *= fInvDet;
                        fSqrDist = fS*(fA00*fS+fA01*fT+2.0f*fB0) +
                            fT*(fA01*fS+fA11*fT+2.0f*fB1)+fC;
                    }
                    else  // region 3 (side)
                    {
                        fT = 1.0f;
                        fTmp = fA01+fB0;
                        if ( fTmp >= 0.0f )
                        {
                            fS = 0.0f;
                            fSqrDist = fA11+2.0f*fB1+fC;
                        }
                        else if ( -fTmp >= fA00 )
                        {
                            fS = 1.0f;
                            fSqrDist = fA00+fA11+fC+2.0f*(fB1+fTmp);
                        }
                        else
                        {
                            fS = -fTmp/fA00;
                            fSqrDist = fTmp*fS+fA11+2.0f*fB1+fC;
                        }
                    }
                }
                else  // region 7 (side)
                {
                    fT = 0.0f;
                    if ( fB0 >= 0.0f )
                    {
                        fS = 0.0f;
                        fSqrDist = fC;
                    }
                    else if ( -fB0 >= fA00 )
                    {
                        fS = 1.0f;
                        fSqrDist = fA00+2.0f*fB0+fC;
                    }
                    else
                    {
                        fS = -fB0/fA00;
                        fSqrDist = fB0*fS+fC;
                    }
                }
            }
            else
            {
                if ( fT >= 0.0f )
                {
                    if ( fT <= fDet )  // region 1 (side)
                    {
                        fS = 1.0f;
                        fTmp = fA01+fB1;
                        if ( fTmp >= 0.0f )
                        {
                            fT = 0.0f;
                            fSqrDist = fA00+2.0f*fB0+fC;
                        }
                        else if ( -fTmp >= fA11 )
                        {
                            fT = 1.0f;
                            fSqrDist = fA00+fA11+fC+2.0f*(fB0+fTmp);
                        }
                        else
                        {
                            fT = -fTmp/fA11;
                            fSqrDist = fTmp*fT+fA00+2.0f*fB0+fC;
                        }
                    }
                    else  // region 2 (corner)
                    {
                        fTmp = fA01+fB0;
                        if ( -fTmp <= fA00 )
                        {
                            fT = 1.0f;
                            if ( fTmp >= 0.0f )
                            {
                                fS = 0.0f;
                                fSqrDist = fA11+2.0f*fB1+fC;
                            }
                            else
                            {
                                 fS = -fTmp/fA00;
                                 fSqrDist = fTmp*fS+fA11+2.0f*fB1+fC;
                            }
                        }
                        else
                        {
                            fS = 1.0f;
                            fTmp = fA01+fB1;
                            if ( fTmp >= 0.0f )
                            {
                                fT = 0.0f;
                                fSqrDist = fA00+2.0f*fB0+fC;
                            }
                            else if ( -fTmp >= fA11 )
                            {
                                fT = 1.0f;
                                fSqrDist = fA00+fA11+fC+2.0f*(fB0+fTmp);
                            }
                            else
                            {
                                fT = -fTmp/fA11;
                                fSqrDist = fTmp*fT+fA00+2.0f*fB0+fC;
                            }
                        }
                    }
                }
                else  // region 8 (corner)
                {
                    if ( -fB0 < fA00 )
                    {
                        fT = 0.0f;
                        if ( fB0 >= 0.0f )
                        {
                            fS = 0.0f;
                            fSqrDist = fC;
                        }
                        else
                        {
                            fS = -fB0/fA00;
                            fSqrDist = fB0*fS+fC;
                        }
                    }
                    else
                    {
                        fS = 1.0f;
                        fTmp = fA01+fB1;
                        if ( fTmp >= 0.0f )
                        {
                            fT = 0.0f;
                            fSqrDist = fA00+2.0f*fB0+fC;
                        }
                        else if ( -fTmp >= fA11 )
                        {
                            fT = 1.0f;
                            fSqrDist = fA00+fA11+fC+2.0f*(fB0+fTmp);
                        }
                        else
                        {
                            fT = -fTmp/fA11;
                            fSqrDist = fTmp*fT+fA00+2.0f*fB0+fC;
                        }
                    }
                }
            }
        }
        else 
        {
            if ( fT >= 0.0f )
            {
                if ( fT <= fDet )  // region 5 (side)
                {
                    fS = 0.0f;
                    if ( fB1 >= 0.0f )
                    {
                        fT = 0.0f;
                        fSqrDist = fC;
                    }
                    else if ( -fB1 >= fA11 )
                    {
                        fT = 1.0f;
                        fSqrDist = fA11+2.0f*fB1+fC;
                    }
                    else
                    {
                        fT = -fB1/fA11;
                        fSqrDist = fB1*fT+fC;
                    }
                }
                else  // region 4 (corner)
                {
                    fTmp = fA01+fB0;
                    if ( fTmp < 0.0f )
                    {
                        fT = 1.0f;
                        if ( -fTmp >= fA00 )
                        {
                            fS = 1.0f;
                            fSqrDist = fA00+fA11+fC+2.0f*(fB1+fTmp);
                        }
                        else
                        {
                            fS = -fTmp/fA00;
                            fSqrDist = fTmp*fS+fA11+2.0f*fB1+fC;
                        }
                    }
                    else
                    {
                        fS = 0.0f;
                        if ( fB1 >= 0.0f )
                        {
                            fT = 0.0f;
                            fSqrDist = fC;
                        }
                        else if ( -fB1 >= fA11 )
                        {
                            fT = 1.0f;
                            fSqrDist = fA11+2.0f*fB1+fC;
                        }
                        else
                        {
                            fT = -fB1/fA11;
                            fSqrDist = fB1*fT+fC;
                        }
                    }
                }
            }
            else   // region 6 (corner)
            {
                if ( fB0 < 0.0f )
                {
                    fT = 0.0f;
                    if ( -fB0 >= fA00 )
                    {
                        fS = 1.0f;
                        fSqrDist = fA00+2.0f*fB0+fC;
                    }
                    else
                    {
                        fS = -fB0/fA00;
                        fSqrDist = fB0*fS+fC;
                    }
                }
                else
                {
                    fS = 0.0f;
                    if ( fB1 >= 0.0f )
                    {
                        fT = 0.0f;
                        fSqrDist = fC;
                    }
                    else if ( -fB1 >= fA11 )
                    {
                        fT = 1.0f;
                        fSqrDist = fA11+2.0f*fB1+fC;
                    }
                    else
                    {
                        fT = -fB1/fA11;
                        fSqrDist = fB1*fT+fC;
                    }
                }
            }
        }
    }
    else
    {
        // line segments are parallel
        if ( fA01 > 0.0f )
        {
            // direction vectors form an obtuse angle
            if ( fB0 >= 0.0f )
            {
                fS = 0.0f;
                fT = 0.0f;
                fSqrDist = fC;
            }
            else if ( -fB0 <= fA00 )
            {
                fS = -fB0/fA00;
                fT = 0.0f;
                fSqrDist = fB0*fS+fC;
            }
            else
            {
                fB1 = -VECDOT(kDiff,ls_dir);
                fS = 1.0f;
                fTmp = fA00+fB0;
                if ( -fTmp >= fA01 )
                {
                    fT = 1.0f;
                    fSqrDist = fA00+fA11+fC+2.0f*(fA01+fB0+fB1);
                }
                else
                {
                    fT = -fTmp/fA01;
                    fSqrDist = fA00+2.0f*fB0+fC+fT*(fA11*fT+2.0f*(fA01+fB1));
                }
            }
        }
        else
        {
            // direction vectors form an acute angle
            if ( -fB0 >= fA00 )
            {
                fS = 1.0f;
                fT = 0.0f;
                fSqrDist = fA00+2.0f*fB0+fC;
            }
            else if ( fB0 <= 0.0f )
            {
                fS = -fB0/fA00;
                fT = 0.0f;
                fSqrDist = fB0*fS+fC;
            }
            else
            {
                fB1 = -VECDOT(kDiff,ls_dir);
                fS = 0.0f;
                if ( fB0 >= -fA01 )
                {
                    fT = 1.0f;
                    fSqrDist = fA11+2.0f*fB1+fC;
                }
                else
                {
                    fT = -fB0/fA01;
                    fSqrDist = fC+fT*(2.0f*fB1+fA11*fT);
                }
            }
        }
    }

    return fabsf(fSqrDist);
}

float pLineSegment::distance(const pLineSegment& ls) const
{
	return sqrtf(distance2(ls));
}

static void Face (int i0, int i1, int i2, pVector& rkPnt,
    const pVector& rkDir, const pOrientedBoundBox& rkBox, const pVector& rkPmE,
    float* pfLParam, float& rfSqrDistance)
{
	pVector aid((rkBox.bb.max-rkBox.bb.min)*0.5f);
    float extent[3] = {aid.x, aid.y, aid.z};

    pVector kPpE;
    float fLSqr, fInv, fTmp, fParam, fT, fDelta;

    kPpE[i1] = rkPnt[i1] + extent[i1];
    kPpE[i2] = rkPnt[i2] + extent[i2];
    if ( rkDir[i0]*kPpE[i1] >= rkDir[i1]*rkPmE[i0] )
    {
        if ( rkDir[i0]*kPpE[i2] >= rkDir[i2]*rkPmE[i0] )
        {
            // v[i1] >= -e[i1], v[i2] >= -e[i2] (distance = 0)
            if ( pfLParam )
            {
                rkPnt[i0] = extent[i0];
                fInv = 1.0f/rkDir[i0];
                rkPnt[i1] -= rkDir[i1]*rkPmE[i0]*fInv;
                rkPnt[i2] -= rkDir[i2]*rkPmE[i0]*fInv;
                *pfLParam = -rkPmE[i0]*fInv;
            }
        }
        else
        {
            // v[i1] >= -e[i1], v[i2] < -e[i2]
            fLSqr = rkDir[i0]*rkDir[i0] + rkDir[i2]*rkDir[i2];
            fTmp = fLSqr*kPpE[i1] - rkDir[i1]*(rkDir[i0]*rkPmE[i0] +
                rkDir[i2]*kPpE[i2]);
            if ( fTmp <= 2.0f*fLSqr*extent[i1] )
            {
                fT = fTmp/fLSqr;
                fLSqr += rkDir[i1]*rkDir[i1];
                fTmp = kPpE[i1] - fT;
                fDelta = rkDir[i0]*rkPmE[i0] + rkDir[i1]*fTmp +
                    rkDir[i2]*kPpE[i2];
                fParam = -fDelta/fLSqr;
                rfSqrDistance += rkPmE[i0]*rkPmE[i0] + fTmp*fTmp +
                    kPpE[i2]*kPpE[i2] + fDelta*fParam;

                if ( pfLParam )
                {
                    *pfLParam = fParam;
                    rkPnt[i0] = extent[i0];
                    rkPnt[i1] = fT - extent[i1];
                    rkPnt[i2] = -extent[i2];
                }
            }
            else
            {
                fLSqr += rkDir[i1]*rkDir[i1];
                fDelta = rkDir[i0]*rkPmE[i0] + rkDir[i1]*rkPmE[i1] +
                    rkDir[i2]*kPpE[i2];
                fParam = -fDelta/fLSqr;
                rfSqrDistance += rkPmE[i0]*rkPmE[i0] + rkPmE[i1]*rkPmE[i1] +
                    kPpE[i2]*kPpE[i2] + fDelta*fParam;

                if ( pfLParam )
                {
                    *pfLParam = fParam;
                    rkPnt[i0] = extent[i0];
                    rkPnt[i1] = extent[i1];
                    rkPnt[i2] = -extent[i2];
                }
            }
        }
    }
    else
    {
        if ( rkDir[i0]*kPpE[i2] >= rkDir[i2]*rkPmE[i0] )
        {
            // v[i1] < -e[i1], v[i2] >= -e[i2]
            fLSqr = rkDir[i0]*rkDir[i0] + rkDir[i1]*rkDir[i1];
            fTmp = fLSqr*kPpE[i2] - rkDir[i2]*(rkDir[i0]*rkPmE[i0] +
                rkDir[i1]*kPpE[i1]);
            if ( fTmp <= 2.0f*fLSqr*extent[i2] )
            {
                fT = fTmp/fLSqr;
                fLSqr += rkDir[i2]*rkDir[i2];
                fTmp = kPpE[i2] - fT;
                fDelta = rkDir[i0]*rkPmE[i0] + rkDir[i1]*kPpE[i1] +
                    rkDir[i2]*fTmp;
                fParam = -fDelta/fLSqr;
                rfSqrDistance += rkPmE[i0]*rkPmE[i0] + kPpE[i1]*kPpE[i1] +
                    fTmp*fTmp + fDelta*fParam;

                if ( pfLParam )
                {
                    *pfLParam = fParam;
                    rkPnt[i0] = extent[i0];
                    rkPnt[i1] = -extent[i1];
                    rkPnt[i2] = fT - extent[i2];
                }
            }
            else
            {
                fLSqr += rkDir[i2]*rkDir[i2];
                fDelta = rkDir[i0]*rkPmE[i0] + rkDir[i1]*kPpE[i1] +
                    rkDir[i2]*rkPmE[i2];
                fParam = -fDelta/fLSqr;
                rfSqrDistance += rkPmE[i0]*rkPmE[i0] + kPpE[i1]*kPpE[i1] +
                    rkPmE[i2]*rkPmE[i2] + fDelta*fParam;

                if ( pfLParam )
                {
                    *pfLParam = fParam;
                    rkPnt[i0] = extent[i0];
                    rkPnt[i1] = -extent[i1];
                    rkPnt[i2] = extent[i2];
                }
            }
        }
        else
        {
            // v[i1] < -e[i1], v[i2] < -e[i2]
            fLSqr = rkDir[i0]*rkDir[i0]+rkDir[i2]*rkDir[i2];
            fTmp = fLSqr*kPpE[i1] - rkDir[i1]*(rkDir[i0]*rkPmE[i0] +
                rkDir[i2]*kPpE[i2]);
            if ( fTmp >= 0.0f )
            {
                // v[i1]-edge is closest
                if ( fTmp <= 2.0f*fLSqr*extent[i1] )
                {
                    fT = fTmp/fLSqr;
                    fLSqr += rkDir[i1]*rkDir[i1];
                    fTmp = kPpE[i1] - fT;
                    fDelta = rkDir[i0]*rkPmE[i0] + rkDir[i1]*fTmp +
                        rkDir[i2]*kPpE[i2];
                    fParam = -fDelta/fLSqr;
                    rfSqrDistance += rkPmE[i0]*rkPmE[i0] + fTmp*fTmp +
                        kPpE[i2]*kPpE[i2] + fDelta*fParam;

                    if ( pfLParam )
                    {
                        *pfLParam = fParam;
                        rkPnt[i0] = extent[i0];
                        rkPnt[i1] = fT - extent[i1];
                        rkPnt[i2] = -extent[i2];
                    }
                }
                else
                {
                    fLSqr += rkDir[i1]*rkDir[i1];
                    fDelta = rkDir[i0]*rkPmE[i0] + rkDir[i1]*rkPmE[i1] +
                        rkDir[i2]*kPpE[i2];
                    fParam = -fDelta/fLSqr;
                    rfSqrDistance += rkPmE[i0]*rkPmE[i0] + rkPmE[i1]*rkPmE[i1]
                        + kPpE[i2]*kPpE[i2] + fDelta*fParam;

                    if ( pfLParam )
                    {
                        *pfLParam = fParam;
                        rkPnt[i0] = extent[i0];
                        rkPnt[i1] = extent[i1];
                        rkPnt[i2] = -extent[i2];
                    }
                }
                return;
            }

            fLSqr = rkDir[i0]*rkDir[i0] + rkDir[i1]*rkDir[i1];
            fTmp = fLSqr*kPpE[i2] - rkDir[i2]*(rkDir[i0]*rkPmE[i0] +
                rkDir[i1]*kPpE[i1]);
            if ( fTmp >= 0.0f )
            {
                // v[i2]-edge is closest
                if ( fTmp <= 2.0f*fLSqr*extent[i2] )
                {
                    fT = fTmp/fLSqr;
                    fLSqr += rkDir[i2]*rkDir[i2];
                    fTmp = kPpE[i2] - fT;
                    fDelta = rkDir[i0]*rkPmE[i0] + rkDir[i1]*kPpE[i1] +
                        rkDir[i2]*fTmp;
                    fParam = -fDelta/fLSqr;
                    rfSqrDistance += rkPmE[i0]*rkPmE[i0] + kPpE[i1]*kPpE[i1] +
                        fTmp*fTmp + fDelta*fParam;

                    if ( pfLParam )
                    {
                        *pfLParam = fParam;
                        rkPnt[i0] = extent[i0];
                        rkPnt[i1] = -extent[i1];
                        rkPnt[i2] = fT - extent[i2];
                    }
                }
                else
                {
                    fLSqr += rkDir[i2]*rkDir[i2];
                    fDelta = rkDir[i0]*rkPmE[i0] + rkDir[i1]*kPpE[i1] +
                        rkDir[i2]*rkPmE[i2];
                    fParam = -fDelta/fLSqr;
                    rfSqrDistance += rkPmE[i0]*rkPmE[i0] + kPpE[i1]*kPpE[i1] +
                        rkPmE[i2]*rkPmE[i2] + fDelta*fParam;

                    if ( pfLParam )
                    {
                        *pfLParam = fParam;
                        rkPnt[i0] = extent[i0];
                        rkPnt[i1] = -extent[i1];
                        rkPnt[i2] = extent[i2];
                    }
                }
                return;
            }

            // (v[i1],v[i2])-corner is closest
            fLSqr += rkDir[i2]*rkDir[i2];
            fDelta = rkDir[i0]*rkPmE[i0] + rkDir[i1]*kPpE[i1] +
                rkDir[i2]*kPpE[i2];
            fParam = -fDelta/fLSqr;
            rfSqrDistance += rkPmE[i0]*rkPmE[i0] + kPpE[i1]*kPpE[i1] +
                kPpE[i2]*kPpE[i2] + fDelta*fParam;

            if ( pfLParam )
            {
                *pfLParam = fParam;
                rkPnt[i0] = extent[i0];
                rkPnt[i1] = -extent[i1];
                rkPnt[i2] = -extent[i2];
            }
        }
    }
}

static void CaseNoZeros (pVector& rkPnt, const pVector& rkDir,
    const pOrientedBoundBox& rkBox, float* pfLParam, float& rfSqrDistance)
{
	pVector aid((rkBox.bb.max-rkBox.bb.min)*0.5f);
    float extent[3] = {aid.x, aid.y, aid.z};

    pVector kPmE(rkPnt.x - extent[0], rkPnt.y - extent[1],
        rkPnt.z - extent[2]);

    float fProdDxPy, fProdDyPx, fProdDzPx, fProdDxPz, fProdDzPy, fProdDyPz;

    fProdDxPy = rkDir.x*kPmE.y;
    fProdDyPx = rkDir.y*kPmE.x;
    if ( fProdDyPx >= fProdDxPy )
    {
        fProdDzPx = rkDir.z*kPmE.x;
        fProdDxPz = rkDir.x*kPmE.z;
        if ( fProdDzPx >= fProdDxPz )
        {
            // line intersects x = e0
            Face(0,1,2,rkPnt,rkDir,rkBox,kPmE,pfLParam,rfSqrDistance);
        }
        else
        {
            // line intersects z = e2
            Face(2,0,1,rkPnt,rkDir,rkBox,kPmE,pfLParam,rfSqrDistance);
        }
    }
    else
    {
        fProdDzPy = rkDir.z*kPmE.y;
        fProdDyPz = rkDir.y*kPmE.z;
        if ( fProdDzPy >= fProdDyPz )
        {
            // line intersects y = e1
            Face(1,2,0,rkPnt,rkDir,rkBox,kPmE,pfLParam,rfSqrDistance);
        }
        else
        {
            // line intersects z = e2
            Face(2,0,1,rkPnt,rkDir,rkBox,kPmE,pfLParam,rfSqrDistance);
        }
    }
}

static void Case0 (int i0, int i1, int i2, pVector& rkPnt,
    const pVector& rkDir, const pOrientedBoundBox& rkBox, float* pfLParam,
    float& rfSqrDistance)
{
	pVector aid((rkBox.bb.max-rkBox.bb.min)*0.5f);
    float extent[3] = {aid.x, aid.y, aid.z};

    float fPmE0 = rkPnt[i0] - extent[i0];
    float fPmE1 = rkPnt[i1] - extent[i1];
    float fProd0 = rkDir[i1]*fPmE0;
    float fProd1 = rkDir[i0]*fPmE1;
    float fDelta, fInvLSqr, fInv;

    if ( fProd0 >= fProd1 )
    {
        // line intersects P[i0] = e[i0]
        rkPnt[i0] = extent[i0];

        float fPpE1 = rkPnt[i1] + extent[i1];
        fDelta = fProd0 - rkDir[i0]*fPpE1;
        if ( fDelta >= 0.0f )
        {
            fInvLSqr = 1.0f/(rkDir[i0]*rkDir[i0] + rkDir[i1]*rkDir[i1]);
            rfSqrDistance += fDelta*fDelta*fInvLSqr;
            if ( pfLParam )
            {
                rkPnt[i1] = -extent[i1];
                *pfLParam = -(rkDir[i0]*fPmE0+rkDir[i1]*fPpE1)*fInvLSqr;
            }
        }
        else
        {
            if ( pfLParam )
            {
                fInv = 1.0f/rkDir[i0];
                rkPnt[i1] -= fProd0*fInv;
                *pfLParam = -fPmE0*fInv;
            }
        }
    }
    else
    {
        // line intersects P[i1] = e[i1]
        rkPnt[i1] = extent[i1];

        float fPpE0 = rkPnt[i0] + extent[i0];
        fDelta = fProd1 - rkDir[i1]*fPpE0;
        if ( fDelta >= 0.0f )
        {
            fInvLSqr = 1.0f/(rkDir[i0]*rkDir[i0] + rkDir[i1]*rkDir[i1]);
            rfSqrDistance += fDelta*fDelta*fInvLSqr;
            if ( pfLParam )
            {
                rkPnt[i0] = -extent[i0];
                *pfLParam = -(rkDir[i0]*fPpE0+rkDir[i1]*fPmE1)*fInvLSqr;
            }
        }
        else
        {
            if ( pfLParam )
            {
                fInv = 1.0f/rkDir[i1];
                rkPnt[i0] -= fProd1*fInv;
                *pfLParam = -fPmE1*fInv;
            }
        }
    }

    if ( rkPnt[i2] < -extent[i2] )
    {
        fDelta = rkPnt[i2] + extent[i2];
        rfSqrDistance += fDelta*fDelta;
        rkPnt[i2] = -extent[i2];
    }
    else if ( rkPnt[i2] > extent[i2] )
    {
        fDelta = rkPnt[i2] - extent[i2];
        rfSqrDistance += fDelta*fDelta;
        rkPnt[i2] = extent[i2];
    }
}

static void Case00 (int i0, int i1, int i2, pVector& rkPnt,
    const pVector& rkDir, const pOrientedBoundBox& rkBox, float* pfLParam,
    float& rfSqrDistance)
{
	pVector aid((rkBox.bb.max-rkBox.bb.min)*0.5f);
    float extent[3] = {aid.x, aid.y, aid.z};

    float fDelta;

    if ( pfLParam )
        *pfLParam = (extent[i0] - rkPnt[i0])/rkDir[i0];

    rkPnt[i0] = extent[i0];

    if ( rkPnt[i1] < -extent[i1] )
    {
        fDelta = rkPnt[i1] + extent[i1];
        rfSqrDistance += fDelta*fDelta;
        rkPnt[i1] = -extent[i1];
    }
    else if ( rkPnt[i1] > extent[i1] )
    {
        fDelta = rkPnt[i1] - extent[i1];
        rfSqrDistance += fDelta*fDelta;
        rkPnt[i1] = extent[i1];
    }

    if ( rkPnt[i2] < -extent[i2] )
    {
        fDelta = rkPnt[i2] + extent[i2];
        rfSqrDistance += fDelta*fDelta;
        rkPnt[i1] = -extent[i2];
    }
    else if ( rkPnt[i2] > extent[i2] )
    {
        fDelta = rkPnt[i2] - extent[i2];
        rfSqrDistance += fDelta*fDelta;
        rkPnt[i2] = extent[i2];
    }
}

static void Case000 (pVector& rkPnt, const pOrientedBoundBox& rkBox,
    float& rfSqrDistance)
{
	pVector aid((rkBox.bb.max-rkBox.bb.min)*0.5f);
    float extent[3] = {aid.x, aid.y, aid.z};

    float fDelta;

    if ( rkPnt.x < -extent[0] )
    {
        fDelta = rkPnt.x + extent[0];
        rfSqrDistance += fDelta*fDelta;
        rkPnt.x = -extent[0];
    }
    else if ( rkPnt.x > extent[0] )
    {
        fDelta = rkPnt.x - extent[0];
        rfSqrDistance += fDelta*fDelta;
        rkPnt.x = extent[0];
    }

    if ( rkPnt.y < -extent[1] )
    {
        fDelta = rkPnt.y + extent[1];
        rfSqrDistance += fDelta*fDelta;
        rkPnt.y = -extent[1];
    }
    else if ( rkPnt.y > extent[1] )
    {
        fDelta = rkPnt.y - extent[1];
        rfSqrDistance += fDelta*fDelta;
        rkPnt.y = extent[1];
    }

    if ( rkPnt.z < -extent[2] )
    {
        fDelta = rkPnt.z + extent[2];
        rfSqrDistance += fDelta*fDelta;
        rkPnt.z = -extent[2];
    }
    else if ( rkPnt.z > extent[2] )
    {
        fDelta = rkPnt.z - extent[2];
        rfSqrDistance += fDelta*fDelta;
        rkPnt.z = extent[2];
    }
}

float distance_line_bbox(const pVector& start,const pVector& dir,const pOrientedBoundBox& obb,float& pfLParam,float& pfBParam0,float& pfBParam1,float& pfBParam2)
{
	pVector center(obb.get_center());
	pVector axis[3] = 
	{
		obb.transform.get_column3(0),
		obb.transform.get_column3(1),
		obb.transform.get_column3(2)
	};

    // compute coordinates of line in box coordinate system
    pVector kDiff(start-center);
    pVector kPnt(VECDOT(kDiff,axis[0]),VECDOT(kDiff,axis[1]),VECDOT(kDiff,axis[2]));
    pVector kDir(VECDOT(dir,axis[0]),VECDOT(dir,axis[1]),VECDOT(dir,axis[2]));

    // Apply reflections so that direction vector has nonnegative components.
    bool bReflect[3];
    int i;
    for (i = 0; i < 3; i++)
    {
        if ( kDir[i] < 0.0f )
        {
            kPnt[i] = -kPnt[i];
            kDir[i] = -kDir[i];
            bReflect[i] = true;
        }
        else
        {
            bReflect[i] = false;
        }
    }

    float fSqrDistance = 0.0f;

    if ( kDir.x > 0.0f )
    {
        if ( kDir.y > 0.0f )
        {
            if ( kDir.z > 0.0f )
            {
                // (+,+,+)
                CaseNoZeros(kPnt,kDir,obb,&pfLParam,fSqrDistance);
            }
            else
            {
                // (+,+,0)
                Case0(0,1,2,kPnt,kDir,obb,&pfLParam,fSqrDistance);
            }
        }
        else
        {
            if ( kDir.z > 0.0f )
            {
                // (+,0,+)
                Case0(0,2,1,kPnt,kDir,obb,&pfLParam,fSqrDistance);
            }
            else
            {
                // (+,0,0)
                Case00(0,1,2,kPnt,kDir,obb,&pfLParam,fSqrDistance);
            }
        }
    }
    else
    {
        if ( kDir.y > 0.0f )
        {
            if ( kDir.z > 0.0f )
            {
                // (0,+,+)
                Case0(1,2,0,kPnt,kDir,obb,&pfLParam,fSqrDistance);
            }
            else
            {
                // (0,+,0)
                Case00(1,0,2,kPnt,kDir,obb,&pfLParam,fSqrDistance);
            }
        }
        else
        {
            if ( kDir.z > 0.0f )
            {
                // (0,0,+)
                Case00(2,0,1,kPnt,kDir,obb,&pfLParam,fSqrDistance);
            }
            else
            {
                // (0,0,0)
                Case000(kPnt,obb,fSqrDistance);
                pfLParam = 0.0f;
            }
        }
    }

	// undo reflections
    for (i = 0; i < 3; i++)
    {
        if ( bReflect[i] )
            kPnt[i] = -kPnt[i];
    }

	pfBParam0 = kPnt.x;
    pfBParam1 = kPnt.y;
	pfBParam2 = kPnt.z;

    return fSqrDistance;
}

float pLineSegment::distance2(const pOrientedBoundBox& obb) const
{
	pVector dir(end-start);
    float fLP,fBP0,fBP1,fBP2;
    float fSqrDistance=distance_line_bbox(start,dir,obb,fLP,fBP0,fBP1,fBP2);
    if (fLP>=0.0f)
    {
        if (fLP<=1.0f)
            return fSqrDistance;
        else
            return obb.distance2(start+dir);
    }
    else
        return obb.distance2(start);
	return 0.0f;
}

float pLineSegment::distance(const pOrientedBoundBox& obb) const
{
	return sqrtf(distance2(obb));
}

P3D_API float pLineSegment::distance2(const pLineSegment& ls1,const pLineSegment& ls2,float& t1,float& t2)
{
	pVector dir(ls1.end - ls1.start);
	pVector ls_dir(ls2.end - ls2.start);
	pVector kDiff(ls1.start - ls2.start);
    float fA00 = dir.length2();
    float fA01 = -VECDOT(dir,ls_dir);
    float fA11 = ls_dir.length2();
    float fB0 = VECDOT(kDiff,dir);
    float fC = kDiff.length2();
    float fDet = fabsf(fA00*fA11-fA01*fA01);
    float fB1, fS, fT, fSqrDist, fTmp;

    if ( fDet >= 1e-05 )
    {
        // line segments are not parallel
        fB1 = -VECDOT(kDiff,ls_dir);
        fS = fA01*fB1-fA11*fB0;
        fT = fA01*fB0-fA00*fB1;
        
        if ( fS >= 0.0f )
        {
            if ( fS <= fDet )
            {
                if ( fT >= 0.0f )
                {
                    if ( fT <= fDet )  // region 0 (interior)
                    {
                        // minimum at two interior points of 3D lines
                        float fInvDet = 1.0f/fDet;
                        fS *= fInvDet;
                        fT *= fInvDet;
                        fSqrDist = fS*(fA00*fS+fA01*fT+2.0f*fB0) +
                            fT*(fA01*fS+fA11*fT+2.0f*fB1)+fC;
                    }
                    else  // region 3 (side)
                    {
                        fT = 1.0f;
                        fTmp = fA01+fB0;
                        if ( fTmp >= 0.0f )
                        {
                            fS = 0.0f;
                            fSqrDist = fA11+2.0f*fB1+fC;
                        }
                        else if ( -fTmp >= fA00 )
                        {
                            fS = 1.0f;
                            fSqrDist = fA00+fA11+fC+2.0f*(fB1+fTmp);
                        }
                        else
                        {
                            fS = -fTmp/fA00;
                            fSqrDist = fTmp*fS+fA11+2.0f*fB1+fC;
                        }
                    }
                }
                else  // region 7 (side)
                {
                    fT = 0.0f;
                    if ( fB0 >= 0.0f )
                    {
                        fS = 0.0f;
                        fSqrDist = fC;
                    }
                    else if ( -fB0 >= fA00 )
                    {
                        fS = 1.0f;
                        fSqrDist = fA00+2.0f*fB0+fC;
                    }
                    else
                    {
                        fS = -fB0/fA00;
                        fSqrDist = fB0*fS+fC;
                    }
                }
            }
            else
            {
                if ( fT >= 0.0f )
                {
                    if ( fT <= fDet )  // region 1 (side)
                    {
                        fS = 1.0f;
                        fTmp = fA01+fB1;
                        if ( fTmp >= 0.0f )
                        {
                            fT = 0.0f;
                            fSqrDist = fA00+2.0f*fB0+fC;
                        }
                        else if ( -fTmp >= fA11 )
                        {
                            fT = 1.0f;
                            fSqrDist = fA00+fA11+fC+2.0f*(fB0+fTmp);
                        }
                        else
                        {
                            fT = -fTmp/fA11;
                            fSqrDist = fTmp*fT+fA00+2.0f*fB0+fC;
                        }
                    }
                    else  // region 2 (corner)
                    {
                        fTmp = fA01+fB0;
                        if ( -fTmp <= fA00 )
                        {
                            fT = 1.0f;
                            if ( fTmp >= 0.0f )
                            {
                                fS = 0.0f;
                                fSqrDist = fA11+2.0f*fB1+fC;
                            }
                            else
                            {
                                 fS = -fTmp/fA00;
                                 fSqrDist = fTmp*fS+fA11+2.0f*fB1+fC;
                            }
                        }
                        else
                        {
                            fS = 1.0f;
                            fTmp = fA01+fB1;
                            if ( fTmp >= 0.0f )
                            {
                                fT = 0.0f;
                                fSqrDist = fA00+2.0f*fB0+fC;
                            }
                            else if ( -fTmp >= fA11 )
                            {
                                fT = 1.0f;
                                fSqrDist = fA00+fA11+fC+2.0f*(fB0+fTmp);
                            }
                            else
                            {
                                fT = -fTmp/fA11;
                                fSqrDist = fTmp*fT+fA00+2.0f*fB0+fC;
                            }
                        }
                    }
                }
                else  // region 8 (corner)
                {
                    if ( -fB0 < fA00 )
                    {
                        fT = 0.0f;
                        if ( fB0 >= 0.0f )
                        {
                            fS = 0.0f;
                            fSqrDist = fC;
                        }
                        else
                        {
                            fS = -fB0/fA00;
                            fSqrDist = fB0*fS+fC;
                        }
                    }
                    else
                    {
                        fS = 1.0f;
                        fTmp = fA01+fB1;
                        if ( fTmp >= 0.0f )
                        {
                            fT = 0.0f;
                            fSqrDist = fA00+2.0f*fB0+fC;
                        }
                        else if ( -fTmp >= fA11 )
                        {
                            fT = 1.0f;
                            fSqrDist = fA00+fA11+fC+2.0f*(fB0+fTmp);
                        }
                        else
                        {
                            fT = -fTmp/fA11;
                            fSqrDist = fTmp*fT+fA00+2.0f*fB0+fC;
                        }
                    }
                }
            }
        }
        else 
        {
            if ( fT >= 0.0f )
            {
                if ( fT <= fDet )  // region 5 (side)
                {
                    fS = 0.0f;
                    if ( fB1 >= 0.0f )
                    {
                        fT = 0.0f;
                        fSqrDist = fC;
                    }
                    else if ( -fB1 >= fA11 )
                    {
                        fT = 1.0f;
                        fSqrDist = fA11+2.0f*fB1+fC;
                    }
                    else
                    {
                        fT = -fB1/fA11;
                        fSqrDist = fB1*fT+fC;
                    }
                }
                else  // region 4 (corner)
                {
                    fTmp = fA01+fB0;
                    if ( fTmp < 0.0f )
                    {
                        fT = 1.0f;
                        if ( -fTmp >= fA00 )
                        {
                            fS = 1.0f;
                            fSqrDist = fA00+fA11+fC+2.0f*(fB1+fTmp);
                        }
                        else
                        {
                            fS = -fTmp/fA00;
                            fSqrDist = fTmp*fS+fA11+2.0f*fB1+fC;
                        }
                    }
                    else
                    {
                        fS = 0.0f;
                        if ( fB1 >= 0.0f )
                        {
                            fT = 0.0f;
                            fSqrDist = fC;
                        }
                        else if ( -fB1 >= fA11 )
                        {
                            fT = 1.0f;
                            fSqrDist = fA11+2.0f*fB1+fC;
                        }
                        else
                        {
                            fT = -fB1/fA11;
                            fSqrDist = fB1*fT+fC;
                        }
                    }
                }
            }
            else   // region 6 (corner)
            {
                if ( fB0 < 0.0f )
                {
                    fT = 0.0f;
                    if ( -fB0 >= fA00 )
                    {
                        fS = 1.0f;
                        fSqrDist = fA00+2.0f*fB0+fC;
                    }
                    else
                    {
                        fS = -fB0/fA00;
                        fSqrDist = fB0*fS+fC;
                    }
                }
                else
                {
                    fS = 0.0f;
                    if ( fB1 >= 0.0f )
                    {
                        fT = 0.0f;
                        fSqrDist = fC;
                    }
                    else if ( -fB1 >= fA11 )
                    {
                        fT = 1.0f;
                        fSqrDist = fA11+2.0f*fB1+fC;
                    }
                    else
                    {
                        fT = -fB1/fA11;
                        fSqrDist = fB1*fT+fC;
                    }
                }
            }
        }
    }
    else
    {
        // line segments are parallel
        if ( fA01 > 0.0f )
        {
            // direction vectors form an obtuse angle
            if ( fB0 >= 0.0f )
            {
                fS = 0.0f;
                fT = 0.0f;
                fSqrDist = fC;
            }
            else if ( -fB0 <= fA00 )
            {
                fS = -fB0/fA00;
                fT = 0.0f;
                fSqrDist = fB0*fS+fC;
            }
            else
            {
                fB1 = -VECDOT(kDiff,ls_dir);
                fS = 1.0f;
                fTmp = fA00+fB0;
                if ( -fTmp >= fA01 )
                {
                    fT = 1.0f;
                    fSqrDist = fA00+fA11+fC+2.0f*(fA01+fB0+fB1);
                }
                else
                {
                    fT = -fTmp/fA01;
                    fSqrDist = fA00+2.0f*fB0+fC+fT*(fA11*fT+2.0f*(fA01+fB1));
                }
            }
        }
        else
        {
            // direction vectors form an acute angle
            if ( -fB0 >= fA00 )
            {
                fS = 1.0f;
                fT = 0.0f;
                fSqrDist = fA00+2.0f*fB0+fC;
            }
            else if ( fB0 <= 0.0f )
            {
                fS = -fB0/fA00;
                fT = 0.0f;
                fSqrDist = fB0*fS+fC;
            }
            else
            {
                fB1 = -VECDOT(kDiff,ls_dir);
                fS = 0.0f;
                if ( fB0 >= -fA01 )
                {
                    fT = 1.0f;
                    fSqrDist = fA11+2.0f*fB1+fC;
                }
                else
                {
                    fT = -fB0/fA01;
                    fSqrDist = fC+fT*(2.0f*fB1+fA11*fT);
                }
            }
        }
    }

	t1 = fS;
    t2 = fT;

    return fabsf(fSqrDist);
}

P3D_API float pLineSegment::distance(const pLineSegment& ls1,const pLineSegment& ls2,float& t1,float& t2)
{
	return sqrtf(pLineSegment::distance2(ls1,ls2,t1,t2));
}

P3D_API float pLineSegment::distance2(const pLineSegment& ls,const pOrientedBoundBox& obb,float& lt,float& ot1,float& ot2,float& ot3)
{
	pVector dir(ls.end-ls.start);
    float fLP,fBP0,fBP1,fBP2;
    float fSqrDistance=distance_line_bbox(ls.start,dir,obb,fLP,fBP0,fBP1,fBP2);
    if (fLP>=0.0f)
    {
        if (fLP<=1.0f)
		{
			lt=fLP;
			ot1=fBP0;
			ot2=fBP0;
			ot3=fBP0;
            return fSqrDistance;
		}
        else
		{
			fSqrDistance=pOrientedBoundBox::distance2(obb,ls.start+dir,ot1,ot2,ot3);
			lt=1.0f;
            return fSqrDistance;
		}
    }
    else
	{
		fSqrDistance=pOrientedBoundBox::distance2(obb,ls.start,ot1,ot2,ot3);
        lt=0.0f;
        return fSqrDistance;
	}
}

P3D_API float pLineSegment::distance(const pLineSegment& ls,const pOrientedBoundBox& obb,float& lt,float& ot1,float& ot2,float& ot3)
{
	return sqrtf(pLineSegment::distance2(ls,obb,lt,ot1,ot2,ot3));
}
