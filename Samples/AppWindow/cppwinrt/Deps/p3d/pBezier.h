/*! \file */

//! Any-dimension Bezier curve
/*! 
	This class implements a n-dimension Bezier curve. The curve and tangent can be 
	evaluated at any point, and the curve can be adaptively subdivided until the 
	curve error is less than a maximum error factor. The members in this class are: 
	the control points, the number of segments in the curve, the curve's dimension
	and the curve's pivot position. Some of its methods include: adding a control
	point to the curve, evaluate the curve and the tangent at a given point, loading
	a .bez file which contains data about a curve, adaptive subdivision of the 
	curve, and much more.
*/
class P3D_API pBezierCurve
{
protected:
	float distance(const float *p,const float *p1,const float *p2) const;
	void subdiv(float u1,float u2,const float *p1,const float *p2,float *points,int& npoints,float maxerror,int maxpoints) const;
	
public:
	float *p;		//!< curve control points
	int np,			//!< number of control points
		ns,			//!< number of bezier segments ((np-1)/3)
		nd;			//!< curve dimensions (2->2D, 3->3D, etc...)
	pVector pivot;	//!< curve pivot position

	//! Default constructor
	pBezierCurve();

	//! Copy-constructor
	pBezierCurve(const pBezierCurve& in);

	//! Destructor constructor
	virtual ~pBezierCurve();

	//! Atribuition operator
	void operator=(const pBezierCurve& in);
	
	//! Reset all allocated data
	void reset();
	//! Set the curve dimension from the given number (2: 2D, 3: 3D, ...)
	void set_dim(int ndim);
	//! Add a new point to the curve, the given array must have ndim floats
	void add_point(const float *f);
	//! Evaluate curve at point u (0..1), and store the resulting point in f (ndim floats)
	void evaluate(float u,float *f) const;
	//! Evaluate tangent of the curve at point u (0..1), and store the result in f (ndim floats)
	void evaluate_tangent(float u,float *f) const;
	
	//! Load a bezier curve from a .bez file
	int load_bez(const char *file);
	//! Adaptively subdivide the curve using maxerror threshold and store the resulting u coordinates in the given array
	int adaptative_subdiv(float maxerror,float *points,int maxpoints) const;
	//! Get the length of the curve
	float length() const;
};
