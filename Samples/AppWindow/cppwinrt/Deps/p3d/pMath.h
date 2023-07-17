#ifndef P_MATH_H
#define P_MATH_H

#include <math.h>
#include "pDefines.h"

class pVector;
class pMatrix;
class pMatrix3;
class pQuaternion;

P3D_API extern unsigned int rand2_a,rand2_b,rand2_c;
P3D_API unsigned short int rand2();

//! random floating point number
#define FRAND ((float)rand2()*(3.05180e-5f)-1.0f)
//! absolute random floating point number
#define FABSRAND ((float)rand2()*1.525902e-5f)

//! two vectors dot product
#define VECDOT(v1,v2) ((v1).x*(v2).x+(v1).y*(v2).y+(v1).z*(v2).z)

//! lower bound for overflow detection
#define SMALL 1.0e-4f
//! upper bound for overflow detection
#define BIG   1.0e+10f
//! underflow detection
#define ISZERO(a) ((a)>-SMALL && (a)<SMALL)

#ifdef TWOPI
#undef TWOPI
#endif
//! represents the value of 2*pi
#define TWOPI			6.28318530718f

//#ifdef PI
//#undef PI
//#endif
//! represents the value of pi
//Q#define PI				3.14159265359f
//! represents 
//Q#define EPSILON         0.001f

//! represents the value of pi/2
#define PI2				1.57079632679f
//! represents the value of pi/180
#define PIOVER180		1.74532925199433E-002f
//! represents the value of 180/pi
#define PIUNDER180		5.72957795130823E+001f
//! represents cos(45)
#define COS45			0.7071067811865475244f
//! represents the square root of 3
#define SQRT3			1.7320508075688772935f
//! represents the inverse square root of 3
#define INVSQRT3		0.5773502691896257645f

//! returns the bitwise representation of a floating point number
#define FPBITS(fp)		(*(int *)&(fp))
//! returns the absolute value of a floating point number in bitwise form
#define FPABSBITS(fp)	(FPBITS(fp)&0x7FFFFFFF)
//! returns the signal bit of a floating point number
#define FPSIGNBIT(fp)	(FPBITS(fp)&0x80000000)
//! returns the absolute value of a floating point number
#define FPABS(fp)		(*((int *)&fp)=FPABSBITS(fp))
//! returns the value of 1.0f in bitwise form
#define FPONEBITS		0x3F800000

//! returns maximum of 2 values
#define MAX2(a,b) ((a)>(b)?(a):(b))
//! returns maximum of 3 values
#define MAX3(a,b,c) MAX2(MAX2(a,b),c)
//! returns grayscale value for float color components
#define Intensity3(r,g,b) ((r)*0.299f + (g)*0.587f + (b)*0.114f)
//! returns grayscale value for float color vector
#define Intensity(rgb) Intensity3(rgb.x,rgb.y,rgb.z)

//! Allocs aligned memory.
/*!
	@param n quantity (in bytes)
*/
P3D_API void *aligned_alloc(int n);

//! Frees aligned memory.
/*!
	@param data buffer to set free
*/
P3D_API void aligned_free(void *data);

//! Calculates a raised to the power of n.
/*!
	n must be an integer.
	@param a base
	@param n an integer exponent
*/
P3D_API float intpower(float a,unsigned int n);

//! Given an incident ray and a normal, stores the reflected ray into newRd.
/*!
	@param Rd incident ray
	@param N normal
	@param newRd holds the reflected ray
*/
P3D_API void calc_reflection_vector(const pVector &Rd,const pVector &N,pVector &newRd);

//! Given an incident ray, a normal and an index of refraction, stores the refracted ray into newRd.
/*!
	@param Rd incident ray
	@param N normal
	@param newRd holds the refracted ray
	@param n index of refraction
	@returns 1 if successful and 0 otherwise
*/
P3D_API int calc_refraction_vector(const pVector Rd,const pVector &N,pVector &newRd,float n);

//! Given three vectors, generates an orthonormal basis with them
/*!
	Input w must be initialize to a nonzero vector, output is {u,v,w}
    an orthonormal basis. A hint is provided about whether or not w is already
	unit length.
	@param u a vector
	@param v a vector
	@param w a vector (must be initialize to a nonzero vector)
	@param unit_length_w the hint about whether or not w is already unit length
*/
P3D_API void generate_orthonormal_basis(pVector& u,pVector& v,pVector& w,bool unit_length_w=true);

//! Vector class compound of 4 floating point real numbers.
/*!
	This is probably the most used class in the whole system. One can use pVector
	with 3 or 4 floats, as in the first case the 4th value remains zero. One must
	address the components of pVector by the letters x, y, z and w, or by indexes 
	0 to 3, and the operations of negation, normalization and cross product with another
	pVector object are provided.
*/
class P3D_API pDVector;
class P3D_API pVector
{
	public:
		float	x,	//!< the first component
				y,	//!< the second component
				z,	//!< the third component
				w;	//!< the fourth (of optional usage) component

	//! Default constructor.
	pVector() : x(0), y(0), z(0), w(1)
	{ }

	//! Constructor from a floating point value, sets x, y and z to this value, and w to 1.0f.
	/*!
		@param f a floating point value
	*/
	pVector(float f) 
	{ x=y=z=f; w=1.0f; }

	//! Copy-constructor.
	/*!
		@param v the new vector
	*/
	pVector(const pVector &v) : x(v.x), y(v.y), z(v.z), w(v.w) 
	{ }

	//! Constructor from 3 floating point numbers, sets x, y and z to their respective values, and w to 1.0f.
	/*!
		@param x0 the new x component value
		@param y0 the new y component value
		@param z0 the new z component value
	*/
	pVector(float x0,float y0,float z0)
	{ x=x0; y=y0; z=z0; w=1;}

	//! Constructor from 4 floating point numbers.
	/*!
		@param x0 the new x component value
		@param y0 the new y component value
		@param z0 the new z component value
		@param w0 the new w component value
	*/
	pVector(float x0,float y0,float z0,float w0)
	{ x=x0; y=y0; z=z0; w=w0; }

	//! Given two vectors, it builds another vector that is cross-product both.
	/*!
		@param v1 first operand
		@param v2 second operand
	*/
	pVector(const pVector& v1,const pVector& v2)
	{ cross(v1,v2); }

	//! Converts a pVector to a pDVector.
	/*!
		@param v a pVector
	*/
	explicit pVector(const pDVector& v);

	//! Atribuition operator.
	/*!
		@param in the new vector
	*/
	void operator=(const pVector &in) 
	{ x = in.x; y = in.y; z = in.z; w = in.w; }

	//! Nullifying function, sets x, y and z to zero, and w to 1.0f.
	void null(void)
	{ x=y=z=0; w=1; }

	//! Calculates the length of the pVector.
	/*!
		@return the length of the vector
	*/
	float length(void) const
	{ return sqrtf(x*x+y*y+z*z); }

	//! Calculates the square of the length.
	/*!
		This method is faster than length method because don't use sqrt function.
		@return the square of the length
	*/
	float length2(void) const
	{ return x*x+y*y+z*z; }

	//!	Calculates the distance to another pVector.
	/*!
		@param v another vector
		@return the distance to v vector
	*/
	float distto(const pVector &v) const
	{ return sqrtf((v.x-x)*(v.x-x)+(v.y-y)*(v.y-y)+(v.z-z)*(v.z-z)); }

	//!	Calculates the square of the distance to another pVector.
	/*!
		This method is faster than distto method because don't use sqrt function.
		@param v another vector
		@return square of the distance to v vector
	*/
	float distto2(const pVector &v) const
	{ return (v.x-x)*(v.x-x)+(v.y-y)*(v.y-y)+(v.z-z)*(v.z-z); }

	//!	Set all the components to the given floating point value.
	/*!
		@param f the given floating point value
	*/
	void vec(float f)
	{ x=y=z=f; w=1.0f; }

	//!	Set components to the given floating point values, and set w=1.0f.
	/*!
		@param x0 the new x component value
		@param y0 the new y component value
		@param z0 the new z component value
	*/
	void vec(float x0,float y0,float z0)
	{ x=x0; y=y0; z=z0; w=1; }

	//!	Set components to the given floating point values.
	/*!
		@param x0 the new x component value
		@param y0 the new y component value
		@param z0 the new z component value
		@param w0 the new w component value
	*/
	void vec(float x0,float y0,float z0,float w0)
	{ x=x0; y=y0; z=z0; w=w0; }

	//!	Negate the first 3 components.
	void negate(void)
	{ x=-x; y=-y; z=-z; }

	//!	Compute the cross-product of two given vectors.
	/*!
		The result is stored into this vector.
		@param v1 first operand
		@param v2 second operand
	*/
	void cross(const pVector &v1, const pVector &v2)
	{
		x=v1.y*v2.z-v1.z*v2.y;
		y=v1.z*v2.x-v1.x*v2.z;
		z=v1.x*v2.y-v1.y*v2.x;
	}

	//!	Compute the cross-product between this vector and another vector.
	/*!
		@param v2 second operand
		@return the cross vector
	*/
	pVector cross(const pVector &v2) const
	{
		const pVector &v1 = *this;
		return pVector (v1.y*v2.z - v1.z*v2.y,
						v1.z*v2.x - v1.x*v2.z,
						v1.x*v2.y - v1.y*v2.x);
	}

	//! Compute the dot-product between this vector and another vector.
	/*!
		@param v2 another vector
		@return the dot product
	*/
	float dot(const pVector &v2) const
	{ 
		return (x*v2.x + y*v2.y + z*v2.z); 
	}

	//!	Normalize the pVector.
	inline void normalize(void)
	{
		float len=x*x+y*y+z*z;
		if (len>0)
		{
		len=1.0f/sqrtf(len);
		x*=len; y*=len; z*=len;
		}
	}

	//! Calculates the luminance.
	/*!
		@return the luminance
	*/
	float color_intensity() const
	{ return x*0.299f+y*0.587f+z*0.114f; }

	//!	Reference indexing operator
	float& operator[](int i) { return (&x)[i]; };
	//!	Indexing operator
	float operator[](int i) const { return (&x)[i]; }

	//!	Negates the pVector (unary operator -).
	/*!
		@return the pVector negated
	*/
	pVector operator-() const
	{ return pVector(-x,-y,-z); }

	//! Multiplies a vector by a matrix.
	/*!
		@param m a matrix
		@return the transformed vector by the matrix
	*/
	pVector operator*(const pMatrix &m) const;

	pVector operator*(const pMatrix3 &m) const;

	//! Multiplies a pVector by a floating point value.
	/*!
		@param f a floating point value
	*/
	void operator*=(float f)
	{ x*=f; y*=f; z*=f; }

	//! Divides a pVector by a floating point value.
	/*!
		@param f a floating point value
	*/
	void operator/=(float f)
	{ float inv_f=1.0f/f; x*=inv_f; y*=inv_f; z*=inv_f; }

	//! Multiply a pVector by a floating point value.
	/*!
		@param f a floating point value
		@return the result of v*f
	*/
	pVector operator*(float f) const
	{ return pVector(x*f,y*f,z*f); }

	//! Divide a pVector by a floating point value.
	/*!
		@param f a floating point value
		@return the result of v/f
	*/
	pVector operator/(float f) const
	{ float inv_f=1.0f/f; return pVector(x*inv_f,y*inv_f,z*inv_f); }

	//! Subtracts pVector 'v' from the original pVector.
	/*!
		@param v vector to subtract
	*/
	void operator-=(const pVector &v)
	{ x-=v.x; y-=v.y; z-=v.z; }

	//! Adds the original pVector with another.
	/*!
		@param v another pVector
	*/
	void operator+=(const pVector &v)
	{ x+=v.x; y+=v.y; z+=v.z; }

	//! Multiplies the original pVector with another.
	/*!
		@param v another pVector
	*/
	void operator*=(const pVector &v)
	{ x*=v.x; y*=v.y; z*=v.z; }

	//! Divides the original pVector by another.
	/*!
		@param v another pVector
	*/
	void operator/=(const pVector &v)
	{ x/=v.x; y/=v.y; z/=v.z; }

	//! Subtracts pVector 'v' from original vector.
	/*!
		@param v second operand
		@return the result of original-v
	*/
	pVector operator-(const pVector &v) const
	{ return pVector(x-v.x,y-v.y,z-v.z); }

	//! Adds two vectors.
	/*!
		@param v second operand
		@return the result of original+v
	*/
	pVector operator+(const pVector &v) const
	{ return pVector(x+v.x,y+v.y,z+v.z); }

	//! Multiplication between vectors.
	/*!
		@param v second operand
		@return the result of original*v
	*/
	pVector operator*(const pVector &v) const
	{ return pVector(x*v.x,y*v.y,z*v.z); }

	//! Divides pVector 'v' by original vector.
	/*!
		@param v second operand
		@return the result of original/v
	*/
	pVector operator/(const pVector &v) const
	{ return pVector(x/v.x,y/v.y,z/v.z); }

	//! Compares original vector with pVector 'v'.
	/*!
		@param v second operand
		@return true if original is equals to v and false otherwise
	*/
	bool operator==(const pVector &v) const
	{
		if (x != v.x) return false;
		if (y != v.y) return false;
		if (z != v.z) return false;
		if (w != v.w) return false;
		return true;
	}

	//! Compares original vector with pVector 'v'.
	/*!
		@param v second operand
		@return true if original vector is different from v and false otherwise
	*/
	bool operator!=(const pVector &v) const
	{
		if (x != v.x) return true;
		if (y != v.y) return true;
		if (z != v.z) return true;
		if (w != v.w) return true;
		return false;
	}
};

//! Multiply a floating point value by a pVector.
/*!
	@param f a floating point value
	@param v a pVector
	@return the result of f*v
*/
inline pVector operator*(float f,pVector v)
{
	v.x*=f; v.y*=f; v.z*=f;
	return v;
}

//! Double precision version of pVector class.
class P3D_API pDVector
{
	public:
		double	x,	//!< the first component
				y,	//!< the second component
				z,	//!< the third component
				w;	//!< the fourth (of optional usage) component

	//! Default constructor.
	pDVector() : x(0.0),y(0.0),z(0.0),w(1.0)
	{ }

	//! Constructor from a floating point value, sets x, y and z to this value, and w to 1.0.
	/*!
		@param f a floating point value
	*/
	pDVector(double f) : x(f),y(f),z(f),w(1.0)
	{ }

	//! Copy-constructor.
	/*!
		@param v the new vector
	*/
	pDVector(const pDVector &v) : x(v.x),y(v.y),z(v.z),w(v.w) 
	{ }

	//! Constructor from 3 floating point numbers, sets x, y and z to their respective values, and w to 1.0f.
	/*!
		@param x0 the new x component value
		@param y0 the new y component value
		@param z0 the new z component value
	*/
	pDVector(double x0,double y0,double z0) : x(x0),y(y0),z(z0),w(1.0)
	{ }

	//! Constructor from 4 floating point numbers.
	/*!
		@param x0 the new x component value
		@param y0 the new y component value
		@param z0 the new z component value
		@param w0 the new w component value
	*/
	pDVector(double x0,double y0,double z0,double w0) : x(x0),y(y0),z(z0),w(w0)
	{ }

	//! Given two vectors, it builds another vector that is cross-product both.
	/*!
		@param v1 first operand
		@param v2 second operand
	*/
	pDVector(const pDVector& v1,const pDVector& v2)
	{ cross(v1,v2); }

	//! Converts a pVector to a pDVector.
	/*!
		@param v a pVector
	*/
	explicit pDVector(const pVector& v) : x(v.x),y(v.y),z(v.z),w(v.w)
	{ }

	//! Atribuition operator.
	/*!
		@param in the new vector
	*/
	void operator=(const pDVector &in) 
	{ x = in.x; y = in.y; z = in.z; w = in.w; }

	//! Nullifying function, sets x, y and z to zero, and w to 1.0.
	void null(void)
	{ x=y=z=0.0; w=1.0; }

	//! Calculates the length of the pDVector.
	/*!
		@return the length of the vector
	*/
	double length(void) const
	{ return sqrt(x*x+y*y+z*z); }

	//! Calculates the square of the length.
	/*!
		This method is faster than length method because don't use sqrt function.
		@return the square of the length
	*/
	double length2(void) const
	{ return x*x+y*y+z*z; }

	//!	Calculates the distance to another pDVector.
	/*!
		@param v another vector
		@return the distance to v vector
	*/
	double distto(const pDVector &v) const
	{ return sqrt((v.x-x)*(v.x-x)+(v.y-y)*(v.y-y)+(v.z-z)*(v.z-z)); }

	//!	Calculates the square of the distance to another pDVector.
	/*!
		This method is faster than distto method because don't use sqrt function.
		@param v another vector
		@return square of the distance to v vector
	*/
	double distto2(const pDVector &v) const
	{ return (v.x-x)*(v.x-x)+(v.y-y)*(v.y-y)+(v.z-z)*(v.z-z); }

	//!	Set all the components to the given floating point value.
	/*!
		@param f the given floating point value
	*/
	void vec(double f)
	{ x=y=z=f; w=1.0; }

	//!	Set components to the given floating point values, and set w=1.0f.
	/*!
		@param x0 the new x component value
		@param y0 the new y component value
		@param z0 the new z component value
	*/
	void vec(double x0,double y0,double z0)
	{ x=x0; y=y0; z=z0; w=1.0; }

	//!	Set components to the given floating point values.
	/*!
		@param x0 the new x component value
		@param y0 the new y component value
		@param z0 the new z component value
		@param w0 the new w component value
	*/
	void vec(double x0,double y0,double z0,double w0)
	{ x=x0; y=y0; z=z0; w=w0; }

	//!	Negate the first 3 components.
	void negate(void)
	{ x=-x; y=-y; z=-z; }

	//!	Compute the cross-product of two given vectors.
	/*!
		The result is stored into this vector.
		@param v1 first operand
		@param v2 second operand
	*/
	void cross(const pDVector &v1,const pDVector &v2)
	{
		x=v1.y*v2.z-v1.z*v2.y;
		y=v1.z*v2.x-v1.x*v2.z;
		z=v1.x*v2.y-v1.y*v2.x;
	}

	//!	Compute the cross-product between this vector and another vector.
	/*!
		@param v2 second operand
		@return the cross vector
	*/
	pDVector cross(const pDVector &v2) const
	{
		const pDVector &v1 = *this;
		return pDVector (v1.y*v2.z - v1.z*v2.y,
						 v1.z*v2.x - v1.x*v2.z,
						 v1.x*v2.y - v1.y*v2.x);
	}

	//! Compute the dot-product between this vector and another vector.
	/*!
		@param v2 another vector
		@return the dot product
	*/
	double dot(const pDVector &v2) const
	{ 
		return (x*v2.x + y*v2.y + z*v2.z); 
	}

	//!	Normalize the pVector.
	void normalize(void)
	{
		double len=x*x+y*y+z*z;
		if (len>0.0)
		{
			len=1.0/sqrt(len);
			x*=len; y*=len; z*=len;
		}
	}

	//!	Reference indexing operator
	double& operator[](int i) { return (&x)[i]; };
	//!	Indexing operator
	double operator[](int i) const { return (&x)[i]; }

	//!	Negates the pDVector (unary operator -).
	/*!
		@return the pDVector negated
	*/
	pDVector operator-() const
	{ return pDVector(-x,-y,-z); }

	//! Multiplies a pDVector by a floating point value.
	/*!
		@param f a floating point value
	*/
	void operator*=(double f)
	{ x*=f; y*=f; z*=f; }

	//! Divides a pDVector by a floating point value.
	/*!
		@param f a floating point value
	*/
	void operator/=(double f)
	{ double inv_f=1.0/f; x*=inv_f; y*=inv_f; z*=inv_f; }

	//! Multiply a pDVector by a floating point value.
	/*!
		@param f a floating point value
		@return the result of v*f
	*/
	pDVector operator*(double f) const
	{ return pDVector(x*f,y*f,z*f); }

	//! Divide a pDVector by a floating point value.
	/*!
		@param f a floating point value
		@return the result of v/f
	*/
	pDVector operator/(double f) const
	{ double inv_f=1.0/f; return pDVector(x*inv_f,y*inv_f,z*inv_f); }

	//! Subtracts pDVector 'v' from the original pDVector.
	/*!
		@param v vector to subtract
	*/
	void operator-=(const pDVector &v)
	{ x-=v.x; y-=v.y; z-=v.z; }

	//! Adds the original pDVector with another.
	/*!
		@param v another pDVector
	*/
	void operator+=(const pDVector &v)
	{ x+=v.x; y+=v.y; z+=v.z; }

	//! Multiplies the original pDVector with another.
	/*!
		@param v another pDVector
	*/
	void operator*=(const pDVector &v)
	{ x*=v.x; y*=v.y; z*=v.z; }

	//! Divides the original pDVector by another.
	/*!
		@param v another pDVector
	*/
	void operator/=(const pDVector &v)
	{ x/=v.x; y/=v.y; z/=v.z; }

	//! Subtracts pDVector 'v' from original vector.
	/*!
		@param v second operand
		@return the result of original-v
	*/
	pDVector operator-(const pDVector &v) const
	{ return pDVector(x-v.x,y-v.y,z-v.z); }

	//! Adds two vectors.
	/*!
		@param v second operand
		@return the result of original+v
	*/
	pDVector operator+(const pDVector &v) const
	{ return pDVector(x+v.x,y+v.y,z+v.z); }

	//! Multiplication between vectors.
	/*!
		@param v second operand
		@return the result of original*v
	*/
	pDVector operator*(const pDVector &v) const
	{ return pDVector(x*v.x,y*v.y,z*v.z); }

	//! Divides pDVector 'v' by original vector.
	/*!
		@param v second operand
		@return the result of original/v
	*/
	pDVector operator/(const pDVector &v) const
	{ return pDVector(x/v.x,y/v.y,z/v.z); }

	//! Compares original vector with pDVector 'v'.
	/*!
		@param v second operand
		@return true if original is equals to v and false otherwise
	*/
	bool operator==(const pDVector &v) const
	{
		if (x != v.x) return false;
		if (y != v.y) return false;
		if (z != v.z) return false;
		if (w != v.w) return false;
		return true;
	}

	//! Compares original vector with pDVector 'v'.
	/*!
		@param v second operand
		@return true if original vector is different from v and false otherwise
	*/
	bool operator!=(const pDVector &v) const
	{
		if (x != v.x) return true;
		if (y != v.y) return true;
		if (z != v.z) return true;
		if (w != v.w) return true;
		return false;
	}

	//! Multiplies a vector by a matrix.
	/*!
		@param m a matrix
		@return the transformed vector by the matrix
	*/
	pDVector operator*(const pMatrix &m) const;

	pDVector operator*(const pMatrix3 &m) const;
};

inline pVector::pVector(const pDVector& v) :
	x((float)v.x),
	y((float)v.y),
	z((float)v.z),
	w((float)v.w)
{ }

//! Plane representation class.
/*!
	This class implements a plane in 3D space.
*/
class P3D_API pPlane
{
	public:
		pVector normal;		//!< pPlane normal
		float d0;			//!< perpendicular distance from the pPlane to the origin

	//! Default constructor.
	pPlane() : d0(0) 
	{ }
	
	//! Constructor from components.
	/*!
		@param n plane normal
		@param dist perpendicular distance to origin
	*/
	pPlane(const pVector &n, float dist) : 
		normal(n),d0(dist)
	{ }

	//! Copy-constructor.
	/*!
		@param in the new plane
	*/
	pPlane(const pPlane &in) : normal(in.normal), d0(in.d0) 
	{ }

	//! Atribuition operator.
	/*!
		@param in the new plane
	*/
	void operator=(const pPlane &in) 
	{ 
		normal = in.normal;
		d0 = in.d0;
	}

	//! Compute the perpendicular distance from a point to the pPlane.
	/*!
		@param v a point
		@return the perpendicular distance from v to this plane
	*/
	float distance(const pVector &v) const
	{ return VECDOT(normal,v)-d0; }

	//! Intersect a ray (ro,rd) with the pPlane and return intersection point (ip) and distance to intersection (dist).
	/*!
		@param ro ray origin
		@param rd ray direction
		@param ip intersection point
		@param dist distance to intersection point
		@return 1 if exists an intersection and 0 otherwise
	*/
	int ray_intersect(const pVector &ro,const pVector &rd,pVector &ip,float &dist) const;
};

//! Matrix class compound of 4x4 floating point real numbers.
/*!
	This class implements a 4x4 matrix stored in column-major order, i.e,
	|00 10 20 30| or |0 4  8 12|
	|01 11 21 31|    |1 5  9 13|
	|02 12 22 32|    |2 6 10 14|
	|03 13 23 33|    |3 7 11 15|.
	This differs from the standard row-major C ordering for matrix elements whose
	the columns representing vectors become rows.
	The matrix can represent any linear transformation and is used for rotation,
	translation, scaling, etc...
*/
class P3D_API pMatrix
{
	public:
		union
		{
			float m[4][4];	//!< matrix elements
			float mf[16];	//!< matrix elements
		};

	//! Default constructor, sets the identity matrix.
	pMatrix() 
	{
		mf[0]=mf[5]=mf[10]=mf[15]=1.0f;
		mf[1]=mf[2]=mf[3]=
		mf[4]=mf[6]=mf[7]=
		mf[8]=mf[9]=mf[11]=
		mf[12]=mf[13]=mf[14]=0.0f;
	}

	//! Copy-constructor.
	/*!
		@param in the new matrix
	*/
	pMatrix(const pMatrix &in) 
	{ 
		mf[0]=in.mf[0];   mf[1]=in.mf[1];   mf[2]=in.mf[2];   mf[3]=in.mf[3];
		mf[4]=in.mf[4];   mf[5]=in.mf[5];   mf[6]=in.mf[6];   mf[7]=in.mf[7];
		mf[8]=in.mf[8];   mf[9]=in.mf[9];   mf[10]=in.mf[10]; mf[11]=in.mf[11];
		mf[12]=in.mf[12]; mf[13]=in.mf[13]; mf[14]=in.mf[14]; mf[15]=in.mf[15];
	}

	//! Atribuition operator.
	/*!
		@param in the new matrix
	*/
	void operator=(const pMatrix &in) 
	{ 
		mf[0]=in.mf[0];   mf[1]=in.mf[1];   mf[2]=in.mf[2];   mf[3]=in.mf[3];
		mf[4]=in.mf[4];   mf[5]=in.mf[5];   mf[6]=in.mf[6];   mf[7]=in.mf[7];
		mf[8]=in.mf[8];   mf[9]=in.mf[9];   mf[10]=in.mf[10]; mf[11]=in.mf[11];
		mf[12]=in.mf[12]; mf[13]=in.mf[13]; mf[14]=in.mf[14]; mf[15]=in.mf[15];
	}

	//! Nullify all elements.
	void null(void)
	{
		mf[0]=mf[1]=mf[2]=mf[3]= 
		mf[4]=mf[5]=mf[6]=mf[7]= 
		mf[8]=mf[9]=mf[10]=mf[11]= 
		mf[12]=mf[13]=mf[14]=mf[15]=0.0f;
	}

	//! Load the identity matrix.
	void load_identity(void)
	{
		mf[0]=mf[5]=mf[10]=mf[15]=1.0f;
		mf[1]=mf[2]=mf[3]=
		mf[4]=mf[6]=mf[7]=
		mf[8]=mf[9]=mf[11]=
		mf[12]=mf[13]=mf[14]=0.0f;
	}
	
	//! Access the i-th row of this matrix.
	/*!
		@param i i-th row of this matrix
		@return the i-th row of this matrix stored into a pVector
	*/
	pVector get_row3(const unsigned int i) const
	{ return pVector(mf[i], mf[i+4], mf[i+8], 1.0f); }
	pVector get_row4(const unsigned int i) const
	{ return pVector(mf[i], mf[i+4], mf[i+8], mf[i+12]); }

	//! Sets the i-th row of this matrix.
	/*!
		@param i i-th row of this matrix
		@param v holds the new value of the i-th row
	*/
	void set_row3(const unsigned int i,const pVector &v)
	{ mf[i] = v.x; mf[i+4] = v.y; mf[i+8] = v.z; }
	void set_row4(const unsigned int i,const pVector &v)
	{ mf[i] = v.x; mf[i+4] = v.y; mf[i+8] = v.z; mf[i+12] = v.w; }

	//! Access the i-th column of this matrix.
	/*!
		@param i i-th column of this matrix
		@return the i-th column of this matrix stored into a pVector
	*/
	pVector get_column3(const unsigned int i) const
	{ unsigned int col = i*4; return pVector(mf[col], mf[col+1], mf[col+2], 1.0f); }
	pVector get_column4(const unsigned int i) const
	{ unsigned int col = i*4; return pVector(mf[col], mf[col+1], mf[col+2], mf[col+3]); }

	//! Sets the i-th column of this matrix.
	/*!
		@param i i-th column of this matrix
		@param v holds the new value of the i-th column
	*/
	void set_column3(const unsigned int i,const pVector &v)
	{ unsigned int col = i*4; mf[col] = v.x; mf[col+1] = v.y; mf[col+2] = v.z; }
	void set_column4(const unsigned int i,const pVector &v)
	{ unsigned int col = i*4; mf[col] = v.x; mf[col+1] = v.y; mf[col+2] = v.z; mf[col+3] = v.w; }

	//! Access the translation vector of this matrix.
	/*!
		@return the translation vector of this matrix
	*/
	pVector get_translate() const
	{ return pVector(mf[12], mf[13], mf[14]); }

	//! Sets the translation vector of this matrix.
	/*!
		@param v holds the new translation vector
	*/
	void set_translate(const pVector &v)
	{ mf[12] = v.x; mf[13] = v.y; mf[14] = v.z; }

	//! Set the matrix as the rotation matrix of angle given by 'ang' around direction 'dir'.
	/*!
		@param ang rotation angle in degrees
		@param dir direction of rotation (must be an unit vector)
	*/
	void set_rotation(float ang,const pVector &dir);

	//! Set the matrix as the rotation that rotates 'from' vector to 'to' vector.
	/*!
		@param from a vector (must be an unit vector)
		@param to a vector (must be an unit vector)
	*/
	void set_rotation(const pVector& from,const pVector& to);

	//! Access the translation and rotation of this matrix.
	/*!
		The translation is stored into a pVector that represents the translation
		vector. The rotation is stored into a pVector that represents this rotation
		as euler angles, i.e, rot.x represents the angle associated with the x axis,
		and so on.
		@param rot the rotation as euler angles
		@param trans the translation vector
	*/
	void get_transformation(pVector &rot,pVector &trans) const;

	//! Set the matrix as the transformation matrix of a rotation and a translation.
	/*!
		The rotation is given to euler angles in x, y and z components of rot pVector.
		@param rot the rotation as euler angles
		@param trans the translation vector
	*/
	void set_transformation(const pVector &rot,const pVector &trans);

	//! Calculates the affine inverse matrix.
	/*!
		This methods suppose that the internal matrix is affine.
		@param m holds the inverse matrix
	*/
	void get_affine_inverse(pMatrix &m) const;

	//! Calculates the rotation component of this matrix.
	/*!
		@param m holds the rotation component of this matrix
	*/
	void get_rotation(pMatrix &m) const;

	//! Calculates the inverse of the rotation component of this matrix.
	/*!
		@param m holds the inverse the rotation component of this matrix
	*/
	void get_rotation_inverse(pMatrix &m) const;

	//! Multiply the matrix by another with rotation given by 'ang' around direction 'dir'.
	/*!
		Suppose that this matrix is the OpenGL current matrix; so, a call to this
		method is similar to glRotatef(ang, dir.x, dir.y, dir.z);
		@param ang rotation angle in degrees
		@param dir direction of rotation (must be an unit vector)
	*/
	void rotate(float ang,const pVector &dir);

	//! Set the matrix as the rotation that rotates 'from' vector to 'to' vector.
	/*!
		@param from a vector (must be an unit vector)
		@param to a vector (must be an unit vector)
		@param maxangle 
	*/
	void rotate(const pVector& from,const pVector& to,float maxang=360.0f);

	//! Align the z-axis of the rotation matrix with a given vector.
	/*!
		@param v the given vector
	*/
	void align_z(const pVector& v);
	void align_z(const pVector& z,const pVector& up);

	//! Multiplies a matrix by a vector.
	/*!
		@param v a vector
		@return the transformed vector by the matrix
	*/
	pVector operator*(const pVector &v) const
	{
		return pVector(
			v.x*mf[0] + v.y*mf[4] + v.z*mf[ 8] + /*v.w*/mf[12],
			v.x*mf[1] + v.y*mf[5] + v.z*mf[ 9] + /*v.w*/mf[13],
			v.x*mf[2] + v.y*mf[6] + v.z*mf[10] + /*v.w*/mf[14]/*,
			v.x*mf[3] + v.y*mf[7] + v.z*mf[11] + v.w*mf[15]*/
		);
	}

	//! Multiplies a matrix by a vector.
	/*!
		@param v a vector
		@return the transformed vector by the matrix
	*/
	pDVector operator*(const pDVector &v) const
	{
		return pDVector(
			v.x*mf[0] + v.y*mf[4] + v.z*mf[ 8] + /*v.w*/mf[12],
			v.x*mf[1] + v.y*mf[5] + v.z*mf[ 9] + /*v.w*/mf[13],
			v.x*mf[2] + v.y*mf[6] + v.z*mf[10] + /*v.w*/mf[14]/*,
			v.x*mf[3] + v.y*mf[7] + v.z*mf[11] + v.w*mf[15]*/
		);
	}

	//! Multiplies a matrix by a vector.
	/*!
		@param v a vector
		@return the transformed vector by the matrix
	*/
	pVector multiply_full(const pVector &v) const
	{
		return pVector(
			v.x*mf[0] + v.y*mf[4] + v.z*mf[ 8] + v.w*mf[12],
			v.x*mf[1] + v.y*mf[5] + v.z*mf[ 9] + v.w*mf[13],
			v.x*mf[2] + v.y*mf[6] + v.z*mf[10] + v.w*mf[14],
			v.x*mf[3] + v.y*mf[7] + v.z*mf[11] + v.w*mf[15]
		);
	}

	//! Multiply the original matrix by another matrix.
	/*!
		@param m1 another matrix
		@return the result of (this)*m1
	*/
	pMatrix operator*(const pMatrix &m1) const
	{
		pMatrix m2;

		m2.mf[ 0] = mf[ 0]*m1.mf[0] + mf[ 1]*m1.mf[4] + mf[ 2]*m1.mf[ 8];// + mf[ 3]*m1.mf[12];
		m2.mf[ 1] = mf[ 0]*m1.mf[1] + mf[ 1]*m1.mf[5] + mf[ 2]*m1.mf[ 9];// + mf[ 3]*m1.mf[13];
		m2.mf[ 2] = mf[ 0]*m1.mf[2] + mf[ 1]*m1.mf[6] + mf[ 2]*m1.mf[10];// + mf[ 3]*m1.mf[14];
		m2.mf[ 3] = 0.0f;//mf[ 0]*m1.mf[3] + mf[ 1]*m1.mf[7] + mf[ 2]*m1.mf[11] + mf[ 3]*m1.mf[15];

		m2.mf[ 4] = mf[ 4]*m1.mf[0] + mf[ 5]*m1.mf[4] + mf[ 6]*m1.mf[ 8];// + mf[ 7]*m1.mf[12];
		m2.mf[ 5] = mf[ 4]*m1.mf[1] + mf[ 5]*m1.mf[5] + mf[ 6]*m1.mf[ 9];// + mf[ 7]*m1.mf[13];
		m2.mf[ 6] = mf[ 4]*m1.mf[2] + mf[ 5]*m1.mf[6] + mf[ 6]*m1.mf[10];// + mf[ 7]*m1.mf[14];
		m2.mf[ 7] = 0.0f;//mf[ 4]*m1.mf[3] + mf[ 5]*m1.mf[7] + mf[ 6]*m1.mf[11] + mf[ 7]*m1.mf[15];

		m2.mf[ 8] = mf[ 8]*m1.mf[0] + mf[ 9]*m1.mf[4] + mf[10]*m1.mf[ 8];// + mf[11]*m1.mf[12];
		m2.mf[ 9] = mf[ 8]*m1.mf[1] + mf[ 9]*m1.mf[5] + mf[10]*m1.mf[ 9];// + mf[11]*m1.mf[13];
		m2.mf[10] = mf[ 8]*m1.mf[2] + mf[ 9]*m1.mf[6] + mf[10]*m1.mf[10];// + mf[11]*m1.mf[14];
		m2.mf[11] = 0.0f;//mf[ 8]*m1.mf[3] + mf[ 9]*m1.mf[7] + mf[10]*m1.mf[11] + mf[11]*m1.mf[15];

		m2.mf[12] = mf[12]*m1.mf[0] + mf[13]*m1.mf[4] + mf[14]*m1.mf[ 8] + /*mf[15]*/m1.mf[12];
		m2.mf[13] = mf[12]*m1.mf[1] + mf[13]*m1.mf[5] + mf[14]*m1.mf[ 9] + /*mf[15]*/m1.mf[13];
		m2.mf[14] = mf[12]*m1.mf[2] + mf[13]*m1.mf[6] + mf[14]*m1.mf[10] + /*mf[15]*/m1.mf[14];
		m2.mf[15] = 1.0f;//mf[12]*m1.mf[3] + mf[13]*m1.mf[7] + mf[14]*m1.mf[11] + mf[15]*m1.mf[15];

		return m2;
	}

	//! Multiply the original matrix by another matrix and stores the result into this matrix.
	/*!
		@param m1 another matrix
	*/
	void operator*=(const pMatrix &m1)
	{
		pMatrix m2;

		m2.mf[ 0] = mf[ 0]*m1.mf[0] + mf[ 1]*m1.mf[4] + mf[ 2]*m1.mf[ 8];// + mf[ 3]*m1.mf[12];
		m2.mf[ 1] = mf[ 0]*m1.mf[1] + mf[ 1]*m1.mf[5] + mf[ 2]*m1.mf[ 9];// + mf[ 3]*m1.mf[13];
		m2.mf[ 2] = mf[ 0]*m1.mf[2] + mf[ 1]*m1.mf[6] + mf[ 2]*m1.mf[10];// + mf[ 3]*m1.mf[14];
		m2.mf[ 3] = 0.0f;//mf[ 0]*m1.mf[3] + mf[ 1]*m1.mf[7] + mf[ 2]*m1.mf[11] + mf[ 3]*m1.mf[15];

		m2.mf[ 4] = mf[ 4]*m1.mf[0] + mf[ 5]*m1.mf[4] + mf[ 6]*m1.mf[ 8];// + mf[ 7]*m1.mf[12];
		m2.mf[ 5] = mf[ 4]*m1.mf[1] + mf[ 5]*m1.mf[5] + mf[ 6]*m1.mf[ 9];// + mf[ 7]*m1.mf[13];
		m2.mf[ 6] = mf[ 4]*m1.mf[2] + mf[ 5]*m1.mf[6] + mf[ 6]*m1.mf[10];// + mf[ 7]*m1.mf[14];
		m2.mf[ 7] = 0.0f;//mf[ 4]*m1.mf[3] + mf[ 5]*m1.mf[7] + mf[ 6]*m1.mf[11] + mf[ 7]*m1.mf[15];

		m2.mf[ 8] = mf[ 8]*m1.mf[0] + mf[ 9]*m1.mf[4] + mf[10]*m1.mf[ 8];// + mf[11]*m1.mf[12];
		m2.mf[ 9] = mf[ 8]*m1.mf[1] + mf[ 9]*m1.mf[5] + mf[10]*m1.mf[ 9];// + mf[11]*m1.mf[13];
		m2.mf[10] = mf[ 8]*m1.mf[2] + mf[ 9]*m1.mf[6] + mf[10]*m1.mf[10];// + mf[11]*m1.mf[14];
		m2.mf[11] = 0.0f;//mf[ 8]*m1.mf[3] + mf[ 9]*m1.mf[7] + mf[10]*m1.mf[11] + mf[11]*m1.mf[15];

		m2.mf[12] = mf[12]*m1.mf[0] + mf[13]*m1.mf[4] + mf[14]*m1.mf[ 8] + /*mf[15]*/m1.mf[12];
		m2.mf[13] = mf[12]*m1.mf[1] + mf[13]*m1.mf[5] + mf[14]*m1.mf[ 9] + /*mf[15]*/m1.mf[13];
		m2.mf[14] = mf[12]*m1.mf[2] + mf[13]*m1.mf[6] + mf[14]*m1.mf[10] + /*mf[15]*/m1.mf[14];
		m2.mf[15] = 1.0f;//mf[12]*m1.mf[3] + mf[13]*m1.mf[7] + mf[14]*m1.mf[11] + mf[15]*m1.mf[15];

		*this=m2;
	}

	//! Multiply the original matrix by another matrix and stores the result into this matrix.
	//! Full multiplication 4x4 times 4x4 including projection column
	/*!
		@param m1 another matrix
	*/
	void multiply_full(const pMatrix &m1)
	{
		pMatrix m2;

		m2.mf[ 0] = mf[ 0]*m1.mf[0] + mf[ 1]*m1.mf[4] + mf[ 2]*m1.mf[ 8] + mf[ 3]*m1.mf[12];
		m2.mf[ 1] = mf[ 0]*m1.mf[1] + mf[ 1]*m1.mf[5] + mf[ 2]*m1.mf[ 9] + mf[ 3]*m1.mf[13];
		m2.mf[ 2] = mf[ 0]*m1.mf[2] + mf[ 1]*m1.mf[6] + mf[ 2]*m1.mf[10] + mf[ 3]*m1.mf[14];
		m2.mf[ 3] = mf[ 0]*m1.mf[3] + mf[ 1]*m1.mf[7] + mf[ 2]*m1.mf[11] + mf[ 3]*m1.mf[15];

		m2.mf[ 4] = mf[ 4]*m1.mf[0] + mf[ 5]*m1.mf[4] + mf[ 6]*m1.mf[ 8] + mf[ 7]*m1.mf[12];
		m2.mf[ 5] = mf[ 4]*m1.mf[1] + mf[ 5]*m1.mf[5] + mf[ 6]*m1.mf[ 9] + mf[ 7]*m1.mf[13];
		m2.mf[ 6] = mf[ 4]*m1.mf[2] + mf[ 5]*m1.mf[6] + mf[ 6]*m1.mf[10] + mf[ 7]*m1.mf[14];
		m2.mf[ 7] = mf[ 4]*m1.mf[3] + mf[ 5]*m1.mf[7] + mf[ 6]*m1.mf[11] + mf[ 7]*m1.mf[15];

		m2.mf[ 8] = mf[ 8]*m1.mf[0] + mf[ 9]*m1.mf[4] + mf[10]*m1.mf[ 8] + mf[11]*m1.mf[12];
		m2.mf[ 9] = mf[ 8]*m1.mf[1] + mf[ 9]*m1.mf[5] + mf[10]*m1.mf[ 9] + mf[11]*m1.mf[13];
		m2.mf[10] = mf[ 8]*m1.mf[2] + mf[ 9]*m1.mf[6] + mf[10]*m1.mf[10] + mf[11]*m1.mf[14];
		m2.mf[11] = mf[ 8]*m1.mf[3] + mf[ 9]*m1.mf[7] + mf[10]*m1.mf[11] + mf[11]*m1.mf[15];

		m2.mf[12] = mf[12]*m1.mf[0] + mf[13]*m1.mf[4] + mf[14]*m1.mf[ 8] + mf[15]*m1.mf[12];
		m2.mf[13] = mf[12]*m1.mf[1] + mf[13]*m1.mf[5] + mf[14]*m1.mf[ 9] + mf[15]*m1.mf[13];
		m2.mf[14] = mf[12]*m1.mf[2] + mf[13]*m1.mf[6] + mf[14]*m1.mf[10] + mf[15]*m1.mf[14];
		m2.mf[15] = mf[12]*m1.mf[3] + mf[13]*m1.mf[7] + mf[14]*m1.mf[11] + mf[15]*m1.mf[15];

		*this=m2;
	}

	//! Multiplies the rotation component of this matrix by a vector.
	/*!
		@param v a vector
		@return the transformed vector by the matrix
	*/
	pVector multiply_rotation(const pVector &v) const
	{
		pVector r;
		r.x = v.x*mf[0] + v.y*mf[4] + v.z*mf[8];
		r.y = v.x*mf[1] + v.y*mf[5] + v.z*mf[9];
		r.z = v.x*mf[2] + v.y*mf[6] + v.z*mf[10];
		return r;
	}

   //! Multiplies the transpose of this matrix by a vector.
	/*!
		@param v a vector
		@return the transformed vector by the matrix
	*/
	pVector multiply_rotation_transpose(const pVector &v) const
	{
		pVector r;
		r.x = v.x*mf[0] + v.y*mf[1] + v.z*mf[2];
		r.y = v.x*mf[4] + v.y*mf[5] + v.z*mf[6];
		r.z = v.x*mf[8] + v.y*mf[9] + v.z*mf[10];
		return r;
	}

	//! Orthonormalize this matrix.
	/*!
		When a matrix suffers many composite operations (like, multiplications)
		its elements tend to accumulate precision errors. So, eventually, it is
		necessary orthonormalize the matrix.
	*/
	void orthonormalize()
	{
		pVector nx, ny, nz;
		nx = get_column3(0);
		ny = get_column3(1);
		nz.cross(nx, ny);
		nz.normalize();
		mf[8] = nz.x;
		mf[9] = nz.y;
		mf[10] = nz.z;
		ny.cross(nz, nx);
		ny.normalize();
		mf[4] = ny.x;
		mf[5] = ny.y;
		mf[6] = ny.z;
		nx.cross(ny, nz);
		nx.normalize();
		mf[0] = nx.x;
		mf[1] = nx.y;
		mf[2] = nx.z;
	}

	//! Interpolate between two matrices (rotation and translation)
	void interpolate(const pMatrix& m1, const pMatrix& m2,float t);
};

//! Matrix class compound of 4x4 floating point real numbers.
/*!
	This class implements a 4x4 matrix stored in column-major order, i.e,
	|00 10 20 30| or |0 4  8 12|
	|01 11 21 31|    |1 5  9 13|
	|02 12 22 32|    |2 6 10 14|
	|03 13 23 33|    |3 7 11 15|.
	This differs from the standard row-major C ordering for matrix elements whose
	the columns representing vectors become rows.
	The matrix can represent any linear transformation and is used for rotation,
	translation, scaling, etc...
*/
class P3D_API pMatrix3
{
	public:
		union
		{
			float m[3][3];	//!< matrix elements
			float mf[9];	//!< matrix elements
		};

	//! Default constructor, sets the identity matrix.
	pMatrix3() 
	{
		mf[0]=mf[4]=mf[8]=1.0f;
		mf[1]=mf[2]=mf[3]=
		mf[5]=mf[6]=mf[7]=0.0f;
	}

	//! Copy-constructor.
	/*!
		@param in the new matrix
	*/
	pMatrix3(const pMatrix3 &in) 
	{ 
		mf[0]=in.mf[0];   mf[1]=in.mf[1];   mf[2]=in.mf[2];
		mf[3]=in.mf[3];   mf[4]=in.mf[4];   mf[5]=in.mf[5];
		mf[6]=in.mf[6];   mf[7]=in.mf[7];	mf[8]=in.mf[8];
	}

	//! Atribuition operator.
	/*!
		@param in the new matrix
	*/
	void operator=(const pMatrix3 &in) 
	{ 
		mf[0]=in.mf[0];   mf[1]=in.mf[1];   mf[2]=in.mf[2];
		mf[3]=in.mf[3];   mf[4]=in.mf[4];   mf[5]=in.mf[5];
		mf[6]=in.mf[6];   mf[7]=in.mf[7];   mf[8]=in.mf[8];
	}

	//! Nullify all elements.
	void null(void)
	{
		mf[0]=mf[1]=mf[2]=mf[3]= 
		mf[4]=mf[5]=mf[6]=mf[7]= 
		mf[8]=0.0f;
	}

	//! Load the identity matrix.
	void load_identity(void)
	{
		mf[0]=mf[4]=mf[8]=1.0f;
		mf[1]=mf[2]=mf[3]=
		mf[5]=mf[6]=mf[7]=0.0f;
	}
	
	//! Access the i-th row of this matrix.
	/*!
		@param i i-th row of this matrix
		@return the i-th row of this matrix stored into a pVector
	*/
	pVector get_row3(const unsigned int i) const
	{ return pVector(mf[i], mf[i+3], mf[i+6], 1.0f); }

	//! Sets the i-th row of this matrix.
	/*!
		@param i i-th row of this matrix
		@param v holds the new value of the i-th row
	*/
	void set_row3(const unsigned int i,const pVector &v)
	{ mf[i] = v.x; mf[i+3] = v.y; mf[i+6] = v.z; }

	//! Access the i-th column of this matrix.
	/*!
		@param i i-th column of this matrix
		@return the i-th column of this matrix stored into a pVector
	*/
	pVector get_column3(const unsigned int i) const
	{ unsigned int col = i*3; return pVector(mf[col], mf[col+1], mf[col+2], 1.0f); }

	//! Sets the i-th column of this matrix.
	/*!
		@param i i-th column of this matrix
		@param v holds the new value of the i-th column
	*/
	void set_column3(const unsigned int i,const pVector &v)
	{ unsigned int col = i*3; mf[col] = v.x; mf[col+1] = v.y; mf[col+2] = v.z; }

///////// Real Transformation CPP /////////
#if 0
	//! Set the matrix as the rotation matrix of angle given by 'ang' around direction 'dir'.
	/*!
		@param ang rotation angle in degrees
		@param dir direction of rotation (must be an unit vector)
	*/
	void set_rotation(float ang,const pVector &dir);

	//! Set the matrix as the rotation that rotates 'from' vector to 'to' vector.
	/*!
		@param from a vector (must be an unit vector)
		@param to a vector (must be an unit vector)
	*/
	void set_rotation(const pVector& from,const pVector& to);

	//! Access the translation and rotation of this matrix.
	/*!
		The translation is stored into a pVector that represents the translation
		vector. The rotation is stored into a pVector that represents this rotation
		as euler angles, i.e, rot.x represents the angle associated with the x axis,
		and so on.
		@param rot the rotation as euler angles
		@param trans the translation vector
	*/
	void get_transformation(pVector &rot,pVector &trans) const;

	//! Set the matrix as the transformation matrix of a rotation and a translation.
	/*!
		The rotation is given to euler angles in x, y and z components of rot pVector.
		@param rot the rotation as euler angles
		@param trans the translation vector
	*/
	void set_transformation(const pVector &rot,const pVector &trans);

	//! Calculates the affine inverse matrix.
	/*!
		This methods suppose that the internal matrix is affine.
		@param m holds the inverse matrix
	*/
	void get_affine_inverse(pMatrix3 &m) const;

	//! Calculates the rotation component of this matrix.
	/*!
		@param m holds the rotation component of this matrix
	*/
	void get_rotation(pMatrix3 &m) const;

	//! Calculates the inverse of the rotation component of this matrix.
	/*!
		@param m holds the inverse the rotation component of this matrix
	*/
	void get_rotation_inverse(pMatrix3 &m) const;

	//! Multiply the matrix by another with rotation given by 'ang' around direction 'dir'.
	/*!
		Suppose that this matrix is the OpenGL current matrix; so, a call to this
		method is similar to glRotatef(ang, dir.x, dir.y, dir.z);
		@param ang rotation angle in degrees
		@param dir direction of rotation (must be an unit vector)
	*/
	void rotate(float ang,const pVector &dir);

	//! Set the matrix as the rotation that rotates 'from' vector to 'to' vector.
	/*!
		@param from a vector (must be an unit vector)
		@param to a vector (must be an unit vector)
		@param maxangle 
	*/
	void rotate(const pVector& from,const pVector& to,float maxang=360.0f);

	//! Align the z-axis of the rotation matrix with a given vector.
	/*!
		@param v the given vector
	*/
	void align_z(const pVector& v);
	void align_z(const pVector& z,const pVector& up);
#endif

	//! Multiplies a matrix by a vector.
	/*!
		@param v a vector
		@return the transformed vector by the matrix
	*/
	pVector operator*(const pVector &v) const
	{
		return pVector(
			v.x*mf[0] + v.y*mf[3] + v.z*mf[ 6],
			v.x*mf[1] + v.y*mf[4] + v.z*mf[ 7],
			v.x*mf[2] + v.y*mf[5] + v.z*mf[8]);
	}

	//! Multiplies a matrix by a vector.
	/*!
		@param v a vector
		@return the transformed vector by the matrix
	*/
	pDVector operator*(const pDVector &v) const
	{
		return pDVector(
			v.x*mf[0] + v.y*mf[3] + v.z*mf[ 6],
			v.x*mf[1] + v.y*mf[4] + v.z*mf[ 7],
			v.x*mf[2] + v.y*mf[5] + v.z*mf[8]);
	}

	//! Multiplies a matrix by a vector.
	/*!
		@param v a vector
		@return the transformed vector by the matrix
	*/
	pVector multiply_full(const pVector &v) const
	{
		return pVector(
			v.x*mf[0] + v.y*mf[3] + v.z*mf[ 6],
			v.x*mf[1] + v.y*mf[4] + v.z*mf[ 7],
			v.x*mf[2] + v.y*mf[5] + v.z*mf[8]);
	}

	//! Multiply the original matrix by another matrix.
	/*!
		@param m1 another matrix
		@return the result of (this)*m1
	*/
	pMatrix3 operator*(const pMatrix3 &m1) const
	{
		pMatrix3 m2;

		m2.mf[ 0] = mf[ 0]*m1.mf[0] + mf[ 1]*m1.mf[3] + mf[ 2]*m1.mf[ 6];
		m2.mf[ 1] = mf[ 0]*m1.mf[1] + mf[ 1]*m1.mf[4] + mf[ 2]*m1.mf[ 7];
		m2.mf[ 2] = mf[ 0]*m1.mf[2] + mf[ 1]*m1.mf[5] + mf[ 2]*m1.mf[ 8];

		m2.mf[ 3] = mf[ 3]*m1.mf[0] + mf[ 4]*m1.mf[3] + mf[ 5]*m1.mf[ 6];
		m2.mf[ 4] = mf[ 3]*m1.mf[1] + mf[ 4]*m1.mf[4] + mf[ 5]*m1.mf[ 7];
		m2.mf[ 5] = mf[ 3]*m1.mf[2] + mf[ 4]*m1.mf[5] + mf[ 5]*m1.mf[ 8];

		m2.mf[ 6] = mf[ 6]*m1.mf[0] + mf[ 7]*m1.mf[3] + mf[8]*m1.mf[ 6];
		m2.mf[ 7] = mf[ 6]*m1.mf[1] + mf[ 7]*m1.mf[4] + mf[8]*m1.mf[ 7];
		m2.mf[ 8] = mf[ 6]*m1.mf[2] + mf[ 7]*m1.mf[5] + mf[8]*m1.mf[ 8];

		return m2;
	}

	//! Multiply the original matrix by another matrix and stores the result into this matrix.
	/*!
		@param m1 another matrix
	*/
	void operator*=(const pMatrix3 &m1)
	{
		pMatrix3 m2;

		m2.mf[ 0] = mf[ 0]*m1.mf[0] + mf[ 1]*m1.mf[3] + mf[ 2]*m1.mf[ 6];
		m2.mf[ 1] = mf[ 0]*m1.mf[1] + mf[ 1]*m1.mf[4] + mf[ 2]*m1.mf[ 7];
		m2.mf[ 2] = mf[ 0]*m1.mf[2] + mf[ 1]*m1.mf[5] + mf[ 2]*m1.mf[ 8];

		m2.mf[ 3] = mf[ 3]*m1.mf[0] + mf[ 4]*m1.mf[3] + mf[ 5]*m1.mf[ 6];
		m2.mf[ 4] = mf[ 3]*m1.mf[1] + mf[ 4]*m1.mf[4] + mf[ 5]*m1.mf[ 7];
		m2.mf[ 5] = mf[ 3]*m1.mf[2] + mf[ 4]*m1.mf[5] + mf[ 5]*m1.mf[ 8];

		m2.mf[ 6] = mf[ 6]*m1.mf[0] + mf[ 7]*m1.mf[3] + mf[8]*m1.mf[ 6];
		m2.mf[ 7] = mf[ 6]*m1.mf[1] + mf[ 7]*m1.mf[4] + mf[8]*m1.mf[ 7];
		m2.mf[ 8] = mf[ 6]*m1.mf[2] + mf[ 7]*m1.mf[5] + mf[8]*m1.mf[ 8];

		*this=m2;
	}

	//! Multiply the original matrix by another matrix and stores the result into this matrix.
	//! Full multiplication 4x4 times 4x4 including projection column
	/*!
		@param m1 another matrix
	*/
	void multiply_full(const pMatrix3 &m1)
	{
		pMatrix3 m2;

		m2.mf[ 0] = mf[ 0]*m1.mf[0] + mf[ 1]*m1.mf[3] + mf[ 2]*m1.mf[ 6];
		m2.mf[ 1] = mf[ 0]*m1.mf[1] + mf[ 1]*m1.mf[4] + mf[ 2]*m1.mf[ 7];
		m2.mf[ 2] = mf[ 0]*m1.mf[2] + mf[ 1]*m1.mf[5] + mf[ 2]*m1.mf[ 8];

		m2.mf[ 3] = mf[ 3]*m1.mf[0] + mf[ 4]*m1.mf[3] + mf[ 5]*m1.mf[ 6];
		m2.mf[ 4] = mf[ 3]*m1.mf[1] + mf[ 4]*m1.mf[4] + mf[ 5]*m1.mf[ 7];
		m2.mf[ 5] = mf[ 3]*m1.mf[2] + mf[ 4]*m1.mf[5] + mf[ 5]*m1.mf[ 8];

		m2.mf[ 6] = mf[ 6]*m1.mf[0] + mf[ 7]*m1.mf[3] + mf[8]*m1.mf[ 6];
		m2.mf[ 7] = mf[ 6]*m1.mf[1] + mf[ 7]*m1.mf[4] + mf[8]*m1.mf[ 7];
		m2.mf[ 8] = mf[ 6]*m1.mf[2] + mf[ 7]*m1.mf[5] + mf[8]*m1.mf[ 8];

		*this=m2;
	}

	//! Multiplies the rotation component of this matrix by a vector.
	/*!
		@param v a vector
		@return the transformed vector by the matrix
	*/
	pVector multiply_rotation(const pVector &v) const
	{
		pVector r;
		r.x = v.x*mf[0] + v.y*mf[3] + v.z*mf[6];
		r.y = v.x*mf[1] + v.y*mf[4] + v.z*mf[7];
		r.z = v.x*mf[2] + v.y*mf[5] + v.z*mf[8];
		return r;
	}

   //! Multiplies the transpose of this matrix by a vector.
	/*!
		@param v a vector
		@return the transformed vector by the matrix
	*/
	pVector multiply_rotation_transpose(const pVector &v) const
	{
		pVector r;
		r.x = v.x*mf[0] + v.y*mf[1] + v.z*mf[2];
		r.y = v.x*mf[3] + v.y*mf[4] + v.z*mf[5];
		r.z = v.x*mf[6] + v.y*mf[7] + v.z*mf[8];
		return r;
	}

	//! Orthonormalize this matrix.
	/*!
		When a matrix suffers many composite operations (like, multiplications)
		its elements tend to accumulate precision errors. So, eventually, it is
		necessary orthonormalize the matrix.
	*/
	void orthonormalize()
	{
		pVector nx, ny, nz;
		nx = get_column3(0);
		ny = get_column3(1);
		nz.cross(nx, ny);
		nz.normalize();
		mf[6] = nz.x;
		mf[7] = nz.y;
		mf[8] = nz.z;
		ny.cross(nz, nx);
		ny.normalize();
		mf[3] = ny.x;
		mf[4] = ny.y;
		mf[5] = ny.z;
		nx.cross(ny, nz);
		nx.normalize();
		mf[0] = nx.x;
		mf[1] = nx.y;
		mf[2] = nx.z;
	}

//////// Real Tranformation CPP /////////
#if 0
	//! Interpolate between two matrices (rotation and translation)
	void interpolate(const pMatrix3& m1, const pMatrix3& m2,float t);
#endif
};

inline pVector pVector::operator*(const pMatrix &m) const
{
	return pVector(
		x*m.mf[0] + y*m.mf[4] + z*m.mf[ 8] + /*w*/m.mf[12],
		x*m.mf[1] + y*m.mf[5] + z*m.mf[ 9] + /*w*/m.mf[13],
		x*m.mf[2] + y*m.mf[6] + z*m.mf[10] + /*w*/m.mf[14]/*,
		x*m.mf[3] + y*m.mf[7] + z*m.mf[11] + w*m.mf[15]*/
	);
}

inline pDVector pDVector::operator*(const pMatrix &m) const
{
	return pDVector(
		x*m.mf[0] + y*m.mf[4] + z*m.mf[ 8] + /*w*/m.mf[12],
		x*m.mf[1] + y*m.mf[5] + z*m.mf[ 9] + /*w*/m.mf[13],
		x*m.mf[2] + y*m.mf[6] + z*m.mf[10] + /*w*/m.mf[14]/*,
		x*m.mf[3] + y*m.mf[7] + z*m.mf[11] + w*m.mf[15]*/
	);
}

inline pVector pVector::operator*(const pMatrix3 &m) const
{
	return pVector(
		x*m.mf[0] + y*m.mf[3] + z*m.mf[ 6],
		x*m.mf[1] + y*m.mf[4] + z*m.mf[ 7],
		x*m.mf[2] + y*m.mf[5] + z*m.mf[ 8]);
}

inline pDVector pDVector::operator*(const pMatrix3 &m) const
{
	return pDVector(
		x*m.mf[0] + y*m.mf[3] + z*m.mf[ 6],
		x*m.mf[1] + y*m.mf[4] + z*m.mf[ 7],
		x*m.mf[2] + y*m.mf[5] + z*m.mf[ 8]);
}

//! Quaternion representation class
/*!
	This class implements a quaternion that represents a rotation of 'theta' degrees around an axis 'dir', 
	where: x=dir.x*sin(theta/2), y=dir.y*sin(theta/2), z=dir.z*sin(theta/2), w=cos(theta/2)
*/
class P3D_API pQuaternion : public pVector
{
	public:

	//! Default constructor.
	pQuaternion() : pVector() 
	{ }

	//! Copy-constructor.
	/*!
		@param in the new quaternion
	*/
	pQuaternion(const pQuaternion &in) : 
		pVector(in) 
	{ }

	//! Construct the quaternion from a matrix.
	/*!
		@param mat a matrix
	*/
	pQuaternion(const pMatrix &mat);

	//! Construct the quaternion from the angle and axis.
	/*!
		@param angle rotation angle in degrees
		@param axis axis of rotation (must be an unit vector)
	*/
	pQuaternion(float angle,const pVector &axis)
	{
		float f=sinf(angle*PIOVER180*0.5f);
		x=axis.x*f;
		y=axis.y*f;
		z=axis.z*f;
		w=cosf(angle*PIOVER180*0.5f);
	}

	//! Normalize the quaternion.
	void normalize();

	//! Converts the quaternion into a matrix.
	/*!
		@param mat holds the same quaternion transformation 
	*/
	void get_mat(pMatrix &mat) const;

	//! Get the rotation angle and axis.
	/*!
		@param angle rotation angle in degrees
		@param axis normalized axis of rotation
	*/
	void get_rotate(float &angle,pVector &axis) const;

	//! Calculates the power of an unit quaternion. 
	pQuaternion exp() const;

	//! Calculates the logarithm of an unit quaternion. 
	pQuaternion log() const;

	//! Interpolate two quaternions accordingly to parameter t [0,1].
	/*!
		@param q1 a quaternion
		@param q2 a quaternion
		@param t interpolation parameter [0,1]
	*/
	void slerp(const pQuaternion &q1,const pQuaternion &q2,float t);

	void squad_intermediate(const pQuaternion& q0,const pQuaternion& q1,const pQuaternion& q2);
	void squad(const pQuaternion& q1,const pQuaternion& q2,const pQuaternion& a1,const pQuaternion& a2,float t);

	//! Multiplication between quaternions.
	/*!
		@param q second operator
		@return the result of (this)*q
	*/
	pQuaternion operator*(const pQuaternion &q) const;

	//! Multiply a pQuaternion by a floating point value.
	/*!
		@param f a floating point value
		@return the result of q*f
	*/
	pQuaternion operator*(float f) const
	{ pQuaternion q; q.vec(x*f,y*f,z*f,w*f); return q; }

	//! Addition between quaternions.
	/*!
		@param q second operator
		@return the result of (this)+q
	*/
	pQuaternion operator+(const pQuaternion &q) const;
};

//! Vertex representation class
/*!
	This class encapsulates some attributes of graphical pipeline vertices.
*/
class P3D_API pVertex 
{
	public:
		pVertex() {};
		pVertex(float x, float y, float z)
			{
			pos[0] = x;
			pos[1] = y;
			pos[2] = z;
			}

		float pos[3];	//!< position
		float norm[3];	//!< normal
		float tx[2];	//!< s,t texture coordinates
#ifdef P_MESH_SHORT_VERT
		float tanu[3];	//!< tangent (xyz:vector)
		float tanv[3];	//!< binormal (xyz:vector)
#else
		float tanu[4];	//!< tangent (xyz:vector,w:scale)
		float tanv[4];	//!< binormal (xyz:vector,w:scale)
		float curv[2];	//!< curvature (in each tangent dir)
#endif

	//! Assignment operation.
	/*!
		@param in the new vertex
	*/
	void operator=(const pVertex &in)
	{
		pos[0]=in.pos[0];
		pos[1]=in.pos[1];
		pos[2]=in.pos[2];
		norm[0]=in.norm[0];
		norm[1]=in.norm[1];
		norm[2]=in.norm[2];
		tx[0]=in.tx[0];
		tx[1]=in.tx[1];
		tanu[0]=in.tanu[0];
		tanu[1]=in.tanu[1];
		tanu[2]=in.tanu[2];
		tanv[0]=in.tanv[0];
		tanv[1]=in.tanv[1];
		tanv[2]=in.tanv[2];
#ifndef P_MESH_SHORT_VERT
		tanu[3]=in.tanu[3];
		tanv[3]=in.tanv[3];
		curv[0]=in.curv[0];
		curv[1]=in.curv[1];
#endif
	}
};

#endif
