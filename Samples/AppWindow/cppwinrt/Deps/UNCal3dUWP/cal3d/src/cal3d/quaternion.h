//****************************************************************************//
// quaternion.h                                                               //
// Copyright (C) 2001, 2002 Bruno 'Beosil' Heidelberger                       //
//****************************************************************************//
// This library is free software; you can redistribute it and/or modify it    //
// under the terms of the GNU Lesser General Public License as published by   //
// the Free Software Foundation; either version 2.1 of the License, or (at    //
// your option) any later version.                                            //
//****************************************************************************//

#ifndef CAL_QUATERNION_H
#define CAL_QUATERNION_H

//****************************************************************************//
// Includes                                                                   //
//****************************************************************************//

#include "cal3d/global.h"
#include "cal3d/vector.h"

//****************************************************************************//
// Forward declarations                                                       //
//****************************************************************************//

//class QunVector;

//****************************************************************************//
// Class declaration                                                          //
//****************************************************************************//

 /*****************************************************************************/
/** The quaternion class.
  *****************************************************************************/

class CAL3D_API QunQuaternion
{
	// member variables
public:
	float x;
	float y;
	float z;
	float w;
	
	// constructors/destructor
public:
	inline QunQuaternion() : x(0.0f), y(0.0f), z(0.0f), w(1.0f){};
	inline QunQuaternion(const QunQuaternion& q): x(q.x), y(q.y), z(q.z), w(q.w) {};
	inline QunQuaternion(float qx, float qy, float qz, float qw): x(qx), y(qy), z(qz), w(qw) {};
	inline ~QunQuaternion() {};
	
	// member functions	
public:
	inline float& operator[](unsigned int index)
	{
		return (&x)[index];
	}
	
	inline const float& operator[](unsigned int index) const
	{
		return (&x)[index];
	}	
	
	inline void operator=(const QunQuaternion& q)
		{
		x = q.x;
		y = q.y;
		z = q.z;
		w = q.w;
	}
	
	inline void operator*=(const QunQuaternion& q)
	{
		float mx( x ), my( y ), mz( z ), mw( w );
		float qx(q.x), qy(q.y), qz(q.z), qw(q.w);
		
		x = mw * qx + mx * qw + my * qz - mz * qy;
		y = mw * qy - mx * qz + my * qw + mz * qx;
		z = mw * qz + mx * qy - my * qx + mz * qw;
		w = mw * qw - mx * qx - my * qy - mz * qz;
	}
	
	inline void operator+=(const QunQuaternion& q)
	{
		x += q.x;
		y += q.y;
		z += q.z;
		w += q.w;
	}
	
	inline void operator*=(const QunVector& v)
	{
		float qx, qy, qz, qw;
		qx = x;
		qy = y;
		qz = z;
		qw = w;
		
		x = qw * v.x            + qy * v.z - qz * v.y;
		y = qw * v.y - qx * v.z            + qz * v.x;
		z = qw * v.z + qx * v.y - qy * v.x;
		w =          - qx * v.x - qy * v.y - qz * v.z;
	}

	inline void operator*=( float s )
	{
		x *= s;
		y *= s;
		z *= s;
		w *= s;
	}

  inline bool operator==(const QunQuaternion& rhs) const
  {
    return x == rhs.x &&
           y == rhs.y &&
           z == rhs.z &&
           w == rhs.w;
  }

  inline bool operator!=(const QunQuaternion& rhs) const
  {
    return !operator==(rhs);
  }
/*	
	static inline QunQuaternion operator*(const QunQuaternion& q, const QunQuaternion& r)
	{
		return QunQuaternion(
			r.w * q.x + r.x * q.w + r.y * q.z - r.z * q.y,
			r.w * q.y - r.x * q.z + r.y * q.w + r.z * q.x,
			r.w * q.z + r.x * q.y - r.y * q.x + r.z * q.w,
			r.w * q.w - r.x * q.x - r.y * q.y - r.z * q.z
			);
	}
*/	
	inline void blend(float d, const QunQuaternion& q)
	{
		float norm;
		norm = x * q.x + y * q.y + z * q.z + w * q.w;
		
		bool bFlip;
		bFlip = false;
		
		if(norm < 0.0f)
		{
			norm = -norm;
			bFlip = true;
		}
		
		float inv_d;
		if(1.0f - norm < 0.000001f)
		{
			inv_d = 1.0f - d;
		}
		else
		{
			float theta;
			theta = (float) acos(norm);
			
			float s;
			s = (float) (1.0f / sin(theta));
			
			inv_d = (float) sin((1.0f - d) * theta) * s;
			d = (float) sin(d * theta) * s;
		}
		
		if(bFlip)
		{
			d = -d;
		}
		
		x = inv_d * x + d * q.x;
		y = inv_d * y + d * q.y;
		z = inv_d * z + d * q.z;
		w = inv_d * w + d * q.w;
	}
	
	inline void clear()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 1.0f;
	}
	inline void conjugate()
	{
		x = -x;
		y = -y;
		z = -z;
	}
	
	inline void invert()
	{
		conjugate();
		const float norm = (x*x) + (y*y) + (z*z) + (w*w);
		
		if (norm == 0.0f) return;
		
		const float inv_norm = 1 / norm;
		*this *= inv_norm;
	}
	
	inline void set(float qx, float qy, float qz, float qw)
	{
		x = qx;
		y = qy;
		z = qz;
		w = qw;
	}

	void compress(short &s0, short &s1, short &s2);
	void decompress(short &s0, short &s1, short &s2);

/*	
	static inline QunQuaternion shortestArc( const QunVector& from, const QunVector& to )
	{
		QunVector cross = from % to; //Compute vector cross product
		float dot = from * to ;      //Compute dot product
		
		dot = (float) sqrt( 2*(dot+1) ) ; //We will use this equation twice
		
		cross /= dot ; //Get the x, y, z components
		
		//Return with the w component (Note that w is inverted because Qun3D has
		// left-handed rotations )
		return QunQuaternion( cross[0], cross[1], cross[2], -dot/2 ) ; 
		
	}

  */
};


static inline QunQuaternion operator*(const QunQuaternion& q, const QunQuaternion& r)
{
	return QunQuaternion(
		r.w * q.x + r.x * q.w + r.y * q.z - r.z * q.y,
		r.w * q.y - r.x * q.z + r.y * q.w + r.z * q.x,
		r.w * q.z + r.x * q.y - r.y * q.x + r.z * q.w,
		r.w * q.w - r.x * q.x - r.y * q.y - r.z * q.z
		);
}

static inline float dot( const QunQuaternion& q, const QunQuaternion& r )
{
	return	q.x * r.x +
			q.y * r.y +
			q.z * r.z +
			q.w * r.w;
}


static inline QunQuaternion shortestArc( const QunVector& from, const QunVector& to )
{
	QunVector cross = from % to; //Compute vector cross product
	float dot = from * to ;      //Compute dot product
	
	dot = (float) sqrt( 2*(dot+1) ) ; //We will use this equation twice
	
	cross /= dot ; //Get the x, y, z components
	
	//Return with the w component (Note that w is inverted because Qun3D has
	// left-handed rotations )
	return QunQuaternion( cross[0], cross[1], cross[2], -dot/2 ) ; 
	
}


#endif

//****************************************************************************//
