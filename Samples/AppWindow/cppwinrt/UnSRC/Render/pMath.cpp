#include "pch.h"
#include "paralelo3d.h"

P3D_API unsigned int rand2_a=0x9531c2b9,rand2_b=0x486a9eb7,rand2_c=0;

unsigned short int rand2()
{
	rand2_c=rand2_c*rand2_a+rand2_b;
	return (unsigned short int)(rand2_c>>8);
}

void *aligned_alloc(int n)
{
#pragma message("Not needed warning")
#if defined(WIN32)
	char *data=new char[n+20];
	unsigned int t=(unsigned int)data+4;
	t=((t&0xf)==0?0:16-(t&0xf));
	*((unsigned int *)&data[t])=t;
	return &data[t+4];
#else
	char *data=new char[n+20];
	return &data[0];
#endif
}

void aligned_free(void *data)
{
	if (data==0)
		return;
	unsigned int t=*(((int *)data)-1);
	char *d=(char *)data;
	d-=t+4;
	delete d;
}

float intpower(float x, unsigned int y)
{
	float t=x,s=1.0f;
	while(y)
	{
		if (y&1)
			s*=t;
 		y>>=1;
		t*=t;
	}
	return s;
}

void calc_reflection_vector(const pVector& Rd,const pVector& N,pVector& newRd)
{
    newRd=-2.0f*VECDOT(N,Rd)*N+Rd;
    newRd.normalize();
}

int calc_refraction_vector(const pVector Rd,const pVector& N,pVector& newRd,float n)
{
	if (n==1) 
	{
		newRd=Rd;
		return 1;
	}
	
	float dot = -VECDOT(N,Rd);
	bool side = dot>=0;
	float eta = side?1.0f/n:n;
	
	pVector Tlat = (N*dot+Rd)*eta;
	float TsinSq = Tlat.length2();	
	
	if (TsinSq>=1.0f) 
		return 0;
	
	if (side) 
		newRd.vec(-N.x,-N.y,-N.z);
	else
		newRd = N;
	newRd = newRd*sqrtf(1.0f-TsinSq)+Tlat;
	newRd.normalize();

	return 1;
}

void generate_orthonormal_basis(pVector& u,pVector& v,pVector& w,bool unit_length_w)
{
	if (!unit_length_w)
        w.normalize();

    if (fabsf(w.x)>=fabsf(w.y) && fabsf(w.x)>=fabsf(w.z))
    {
        u.x = -w.y;
        u.y = +w.x;
        u.z = 0.0f;
    }
    else
    {
        u.x = 0.0f;
        u.y = +w.z;
        u.z = -w.y;
    }

    u.normalize();
    v.cross(w,u);
}

int pPlane::ray_intersect(const pVector& ro,const pVector& rd,pVector& ip,float& dist) const
{
	float x=VECDOT(normal,rd);
	if (x>0)
		return 0;
	
	dist=(d0-VECDOT(normal,ro))/x;
	if (dist<0)
		return 0;

	ip=ro+rd*dist;

	return 1;
}

void pMatrix::set_transformation(const pVector& rot, const pVector& trans)
{
	// set rotation
	float p = rot.x*PIOVER180;
	float h = rot.y*PIOVER180;
	float r = rot.z*PIOVER180;
	float cos_r = cosf(r);
	float cos_h = cosf(h);
	float cos_p = cosf(p);
	float sin_r = sinf(r);
	float sin_h = sinf(h);
	float sin_p = sinf(p);
	mf[ 0] = cos_r*cos_h - sin_r*sin_p*sin_h;
	mf[ 1] = -sin_r*cos_p;
	mf[ 2] = cos_r*sin_h + sin_r*sin_p*cos_h;
	mf[ 4] = sin_r*cos_h + cos_r*sin_p*sin_h;
	mf[ 5] = cos_r*cos_p;
	mf[ 6] = sin_r*sin_h - cos_r*sin_p*cos_h;
	mf[ 8] = -cos_p*sin_h;
	mf[ 9] = sin_p;
	mf[10] = cos_p*cos_h;

	// set translation
	mf[12] = trans.x; mf[13] = trans.y; mf[14] = trans.z;

	mf[3] = mf[7] = mf[11] = 0.0f;
    mf[15] = 1.0f;
}

void pMatrix::get_transformation(pVector& rot, pVector& trans) const
{
	// get rotation
	rot.x = asinf(mf[9])*PIUNDER180;
	rot.y = atan2f(-mf[8],mf[10])*PIUNDER180;
	rot.z = atan2f(-mf[1],mf[5])*PIUNDER180;

	// get translation
	trans.x = mf[12];
	trans.y = mf[13];
	trans.z = mf[14];
}

void pMatrix::rotate( float ang, const pVector& dir )
{
	if (fabs(ang)<0.0001f)
		return;

	pMatrix mb;
	mb.set_rotation(ang,dir);
	*this=*this*mb;
}

void pMatrix::rotate(const pVector& from,const pVector& to,float maxang)
{
	float f=VECDOT(from,to);
	if(f<0.9999f)
	{
		f=acosf(f)*PIUNDER180;
		if(f>maxang)
			f=maxang;

		pVector c;
		c.cross(from, to);
		c.normalize();
		rotate(f,c);
	}
}

void pMatrix::set_rotation( float ang,const pVector& dir )
{
	if (fabs(ang)<0.0001f)
	{
		load_identity();
		return;
	}

	ang*=PIOVER180;

	float fCos=cosf( ang );
	float fSin=sinf( ang );

    mf[ 0] = ( dir.x * dir.x ) * ( 1.0f - fCos ) + fCos;
    mf[ 1] = ( dir.x * dir.y ) * ( 1.0f - fCos ) - (dir.z * fSin);
    mf[ 2] = ( dir.x * dir.z ) * ( 1.0f - fCos ) + (dir.y * fSin);

    mf[ 4] = ( dir.y * dir.x ) * ( 1.0f - fCos ) + (dir.z * fSin);
    mf[ 5] = ( dir.y * dir.y ) * ( 1.0f - fCos ) + fCos ;
    mf[ 6] = ( dir.y * dir.z ) * ( 1.0f - fCos ) - (dir.x * fSin);

    mf[ 8] = ( dir.z * dir.x ) * ( 1.0f - fCos ) - (dir.y * fSin);
    mf[ 9] = ( dir.z * dir.y ) * ( 1.0f - fCos ) + (dir.x * fSin);
    mf[10] = ( dir.z * dir.z ) * ( 1.0f - fCos ) + fCos;
    
    mf[ 3] = mf[ 7] = mf[11] = 0;
    mf[12] = mf[13] = mf[14] = 0;
    mf[15] = 1;
}

void pMatrix::set_rotation(const pVector& from,const pVector& to)
{
	float f=VECDOT(from,to);
	if(f<0.9999f)
	{
		f=acosf(f)*PIUNDER180;

		pVector c(from,to);
		c.normalize();
		set_rotation(f,c);
	}
}

void pMatrix::get_affine_inverse(pMatrix &mb) const
{
	get_rotation_inverse(mb);

	// invert row translation
	mb.mf[12] = -(mf[12]*mf[0] + mf[13]*mf[1] + mf[14]*mf[2]);
	mb.mf[13] = -(mf[12]*mf[4] + mf[13]*mf[5] + mf[14]*mf[6]);
	mb.mf[14] = -(mf[12]*mf[8] + mf[13]*mf[9] + mf[14]*mf[10]);
}

void pMatrix::get_rotation(pMatrix &mb) const
{
	mb.mf[0] = mf[0]; mb.mf[1] = mf[1]; mb.mf[2 ] = mf[2 ];
	mb.mf[4] = mf[4]; mb.mf[5] = mf[5]; mb.mf[6 ] = mf[6 ];
	mb.mf[8] = mf[8]; mb.mf[9] = mf[9]; mb.mf[10] = mf[10];
}

void pMatrix::get_rotation_inverse(pMatrix &mb) const
{
	// invert rotation
	mb.mf[0] = mf[0]; mb.mf[1] = mf[4]; mb.mf[2 ] = mf[8 ];
	mb.mf[4] = mf[1]; mb.mf[5] = mf[5]; mb.mf[6 ] = mf[9 ];
	mb.mf[8] = mf[2]; mb.mf[9] = mf[6]; mb.mf[10] = mf[10];
}

void pMatrix::align_z(const pVector& z,const pVector& up)
{
	pVector X,Y;

	Y=up-z*VECDOT(z,up);
	Y.normalize();
	X.cross(Y,z);

	set_column3(0,X);
	set_column3(1,Y);
	set_column3(2,z);
}

void pMatrix::align_z(const pVector& v)
{
	pVector X,Y;

	if(fabsf(v.z)>=0.99f)
	{
		Y.x=-v.y*v.x;
		Y.y=1-v.y*v.y;
		Y.z=-v.y*v.z;

		Y.normalize();
		X.cross(Y,v);
	}
	else 
	{
		Y.x=-v.z*v.x;
		Y.y=-v.z*v.y;
		Y.z=1.0f-v.z*v.z;

		Y.normalize();
		X.cross(Y,v);
	}

	set_column3(0,X);
	set_column3(1,Y);
	set_column3(2,v);
}

void pMatrix::interpolate(const pMatrix& m1, const pMatrix& m2,float t)
{
	pQuaternion q1(m1),q2(m2),q;
	q.slerp(q1,q2,t);

	pMatrix mb;
	q.get_mat(mb);

	mb.mf[12]=m1.mf[12]*(1-t)+m2.mf[12]*t;
	mb.mf[13]=m1.mf[13]*(1-t)+m2.mf[13]*t;
	mb.mf[14]=m1.mf[14]*(1-t)+m2.mf[14]*t;

	*this=mb;
}

pQuaternion::pQuaternion(const pMatrix &mat)
{
	float tr,s,q[4];
	int i,j,k;

	int nxt[3] = {1, 2, 0};

	tr = mat.mf[0] + mat.mf[5] + mat.mf[10];

	// check the diagonal
	if (tr > 0.0) 
	{
		s = sqrtf(tr + 1.0f);
		w = s/2.0f;
		s = 0.5f/s;
		x = (mat.mf[6] - mat.mf[9]) * s;
		y = (mat.mf[8] - mat.mf[2]) * s;
		z = (mat.mf[1] - mat.mf[4]) * s;
	} 
	else 
	{		
		// diagonal is negative
    	i = 0;
		if (mat.mf[5] > mat.mf[0]) i = 1;
		if (mat.mf[10] > mat.m[i][i]) i = 2;
		j = nxt[i];
		k = nxt[j];

		s=sqrtf((mat.m[i][i]-(mat.m[j][j] + mat.m[k][k])) + 1.0f);
      
		q[i]=s*0.5f;
            
		if(s!=0.0f) s = 0.5f/s;

		q[3] = (mat.m[j][k] - mat.m[k][j]) * s;
		q[j] = (mat.m[i][j] + mat.m[j][i]) * s;
		q[k] = (mat.m[i][k] + mat.m[k][i]) * s;

		x = q[0];
		y = q[1];
		z = q[2];
		w = q[3];
	}
}

void pQuaternion::get_mat(pMatrix &mat) const 
{
	float wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;

	// calculate coefficients
	x2 = x + x; 
	y2 = y + y; 
	z2 = z + z;
	xx = x * x2;
	xy = x * y2;   
	xz = x * z2;
	yy = y * y2;   
	yz = y * z2;   
	zz = z * z2;
	wx = w * x2;   
	wy = w * y2;   
	wz = w * z2;

	mat.mf[0] = 1.0f-(yy+zz); 	
	mat.mf[4] = xy - wz;
	mat.mf[8] = xz + wy;		
	mat.mf[12] = 0.0;

	mat.mf[1] = xy + wz;		
	mat.mf[5] = 1.0f-(xx + zz);
	mat.mf[9] = yz - wx;		
	mat.mf[13] = 0.0;

	mat.mf[2] = xz - wy;		
	mat.mf[6] = yz + wx;
	mat.mf[10] = 1.0f - (xx + yy);		
	mat.mf[14] = 0.0;

	mat.mf[3] = 0;			
	mat.mf[7] = 0;
	mat.mf[11] = 0;			
	mat.mf[15] = 1;
}

pQuaternion pQuaternion::operator +(const pQuaternion& q) const
{
	pQuaternion res;
	res.x=x+q.x;
	res.y=y+q.y;
	res.z=z+q.z;
	res.w=w+q.w;
	return res;
}

pQuaternion pQuaternion::operator*(const pQuaternion &q) const
{
	pQuaternion result;

	result.w = w * q.w - x * q.x - y * q.y - z * q.z;
	result.x = w * q.x + x * q.w + y * q.z - z * q.y;
	result.y = w * q.y + y * q.w + z * q.x - x * q.z;
	result.z = w * q.z + z * q.w + x * q.y - y * q.x;

	return result;
}

void pQuaternion::normalize()
{
	float factor = 1.0f/sqrtf(x*x+y*y+z*z+w*w);

	x*=factor;
	y*=factor;
	z*=factor;
	w*=factor;
}

void pQuaternion::get_rotate(float &angle, pVector &axis) const
{
	angle=acosf(w)*PIUNDER180*2.0f;

	float f=sinf(angle*PIOVER180*0.5f);

	axis.x=x/f;
	axis.y=y/f;
	axis.z=z/f;
}

pQuaternion pQuaternion::exp() const
{
	// If q = A*(x*i+y*j+z*k) where (x,y,z) is unit length, then
    // exp(q) = cos(A)+sin(A)*(x*i+y*j+z*k).  If sin(A) is near zero,
    // use exp(q) = cos(A)+A*(x*i+y*j+z*k) since A/sin(A) has limit 1.

    pQuaternion result;
    float angle=sqrtf(x*x + y*y + z*z);
    float sin_angle=sinf(angle);
    result.w=cosf(angle);

    int i;
    if(fabsf(sin_angle)>=EPSILON)
    {
        float coeff=sin_angle/angle;
        for(i=0;i<=2;i++)
            result[i]=coeff*((*this)[i]);
    }
    else
    {
        for(i=0;i<=2;i++)
            result[i]=((*this)[i]);
    }
    return result;
}

pQuaternion pQuaternion::log() const
{
	// If q = cos(A)+sin(A)*(x*i+y*j+z*k) where (x,y,z) is unit length, then
    // log(q) = A*(x*i+y*j+z*k).  If sin(A) is near zero, use log(q) =
    // sin(A)*(x*i+y*j+z*k) since sin(A)/A has limit 1.

    pQuaternion result;
    result.w=0.0f;
    int i;

    if(fabsf(w)<1.0f)
    {
        float angle=acosf(w);
        float sin_angle=sinf(angle);
        if(fabsf(sin_angle)>=EPSILON)
        {
            float coeff=angle/sin_angle;
            for(i=0;i<=2;i++)
                result[i]=coeff*((*this)[i]);
            return result;
        }
    }

    for(i=0;i<=2;i++)
        result[i]=((*this)[i]);
    return result;
}

void pQuaternion::slerp(const pQuaternion& q1, const pQuaternion& q2,float t)
{
    float v;        // complement to t
    float o;        // complement to v (t)
    float theta;    // angle between q1 & q2
    float sin_t;    // sin(theta)
    float cos_t;    // cos(theta)
    int flip;       // flag for negating q2

    cos_t = q1[0] * q2[0] + q1[1] * q2[1] + q1[2] * q2[2] + q1[3] * q2[3];

    if (cos_t < 0.0)
    {
		cos_t = -cos_t;
		flip = 1;
    }
    else 
		flip = 0;

    if (1.0 - cos_t < 1e-6)
    {
        v = 1.0f - t;
		o = t;
    }
    else
    {
        theta = acosf(cos_t);
        sin_t = sinf(theta);
        v = sinf(theta-t*theta) / sin_t;
        o = sinf(t*theta) / sin_t;
    }
    if (flip) o = -o;

    x = v * q1[0] + o * q2[0];
    y = v * q1[1] + o * q2[1];
    z = v * q1[2] + o * q2[2];
    w = v * q1[3] + o * q2[3];
}

void pQuaternion::squad_intermediate(const pQuaternion& q0,const pQuaternion& q1,const pQuaternion& q2)
{
	pQuaternion q1inv=q1;
	q1inv.x=-q1.x;
	q1inv.y=-q1.y;
	q1inv.z=-q1.z;
	
	pQuaternion p0=q1inv*q0;
	pQuaternion p2=q1inv*q2;
	pQuaternion arg=(p0.log()+p2.log())*(-0.25f);
	(*this)=q1+arg.exp();
}

void pQuaternion::squad(const pQuaternion& q1,const pQuaternion& q2,const pQuaternion& a1,const pQuaternion& a2,float t)
{
	pQuaternion qa,qb;
	qa.slerp(q1,q2,t);
	qb.slerp(a1,a2,t);
	slerp(qa,qb,2.0f*t*(1.0f-t));
}
