//****************************************************************************//
// vector.h                                                                   //
// Copyright (C) 2001, 2002 Bruno 'Beosil' Heidelberger                       //
//****************************************************************************//
// This library is free software; you can redistribute it and/or modify it    //
// under the terms of the GNU Lesser General Public License as published by   //
// the Free Software Foundation; either version 2.1 of the License, or (at    //
// your option) any later version.                                            //
//****************************************************************************//

#ifndef CAL_VECTOR_H
#define CAL_VECTOR_H

//****************************************************************************//
// Includes                                                                   //
//****************************************************************************//

#include "cal3d/global.h"
#include "cal3d/matrix.h"

//****************************************************************************//
// Forward declarations                                                       //
//****************************************************************************//

class QunQuaternion;
//class QunMatrix;

//****************************************************************************//
// Class declaration                                                          //
//****************************************************************************//

 /*****************************************************************************/
/** The vector class.
  *****************************************************************************/

class CAL3D_API QunVector
{
// member variables
public:
  float x ,y ,z;

// constructors/destructor
public:
  inline QunVector(): x(0.0f), y(0.0f), z(0.0f) {};
  inline QunVector(const QunVector& v) : x(v.x), y(v.y), z(v.z) {};
  inline QunVector(float vx, float vy, float vz): x(vx), y(vy), z(vz) {};
  inline ~QunVector() {};

// member functions
public:
  inline float& operator[](unsigned int i) 
  {
	  return (&x)[i];
  }

  inline const float& operator[](unsigned int i) const
  {
	  return (&x)[i];
  }

  inline void operator=(const QunVector& v)
  {
	  x = v.x;
	  y = v.y;
	  z = v.z;
  }

  inline void operator+=(const QunVector& v)
  {
	  x += v.x;
	  y += v.y;
	  z += v.z;
  }
  
  
  inline void operator-=(const QunVector& v)
  {
	  x -= v.x;
	  y -= v.y;
	  z -= v.z;
  }

  inline void operator*=(const float d)
  {
	  x *= d;
	  y *= d;
	  z *= d;
  }

  void operator*=(const QunQuaternion& q);

  inline void operator*=(const QunMatrix &m)
  {
	  float ox = x;
	  float oy = y;
	  float oz = z;
	  x = m.dxdx*ox + m.dxdy*oy + m.dxdz*oz;
	  y = m.dydx*ox + m.dydy*oy + m.dydz*oz;
	  z = m.dzdx*ox + m.dzdy*oy + m.dzdz*oz;
  }  

  inline void operator/=(const float d)
  {
	  x /= d;
	  y /= d;
	  z /= d;
  }

  inline bool operator==(const QunVector& v) const
  {
	  return ((x == v.x) && (y == v.y) && (z == v.z));
  }

  inline bool operator!=(const QunVector& v) const
  {
    return !operator==(v);
  }

  inline void blend(float d, const QunVector& v)
  {
	  x += d * (v.x - x);
	  y += d * (v.y - y);
	  z += d * (v.z - z);
  }

  inline void clear() 
  {
	  x=0.0f;
	  y=0.0f;
	  z=0.0f;		  
  }

  inline float length() const
  {
	  return (float)sqrt(x * x + y * y + z * z);
  }
  inline float normalize()
  {
	  // calculate the length of the vector
	  float length;
	  length = (float) sqrt(x * x + y * y + z * z);
	  
	  float	lenRecip = 1.0f / length;
	  
	  // normalize the vector
	  x *= lenRecip;
	  y *= lenRecip;
	  z *= lenRecip;
	  
	  return length;
  }
  
  void set(float vx, float vy, float vz)
  {
	  x = vx;
	  y = vy;
	  z = vz;
  }

};

static inline QunVector operator+(const QunVector& v, const QunVector& u)
{
  return QunVector(v.x + u.x, v.y + u.y, v.z + u.z);
}

static inline QunVector operator-(const QunVector& v, const QunVector& u)
{
	return QunVector(v.x - u.x, v.y - u.y, v.z - u.z);
}

static inline QunVector operator*(const QunVector& v, const float d)
{
	return QunVector(v.x * d, v.y * d, v.z * d);
}

static inline QunVector operator*(const float d, const QunVector& v)
{
	return QunVector(v.x * d, v.y * d, v.z * d);
}

static inline QunVector operator/(const QunVector& v, const float d)
{
	return QunVector(v.x / d, v.y / d, v.z / d);
}

static inline float operator*(const QunVector& v, const QunVector& u)
{
	return v.x * u.x + v.y * u.y + v.z * u.z;
}  

static inline QunVector operator%(const QunVector& v, const QunVector& u)
{
	return QunVector(v.y * u.z - v.z * u.y, v.z * u.x - v.x * u.z, v.x * u.y - v.y * u.x);
}


 /*****************************************************************************/
/** The plane class.
  *****************************************************************************/


class CAL3D_API QunPlane
{
   public:
      float a,b,c,d;
      
      // These methods are made only to calculate the bounding boxes,
      // don't use them in you program
      
      float eval(const QunVector &p);
	  float dist(QunVector &p);
      void setPosition(const QunVector &p);
      void setNormal(QunVector &p);
};

 /*****************************************************************************/
/** The bounding box class.
  *****************************************************************************/


class CAL3D_API QunBoundingBox
{
   public:
     QunPlane plane[6];
     
     void computePoints(QunVector *p);
   
};



#endif

//****************************************************************************//
