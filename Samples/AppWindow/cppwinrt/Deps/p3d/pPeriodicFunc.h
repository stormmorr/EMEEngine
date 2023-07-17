/*! \file */

#ifndef PPERIODICFUNC
#define PPERIODICFUNC

//! Periodic function class
/*!
	This class implements a shader typical function, whose type can be:

	Sin
	Triangle
	Square
	Saw-tooth
	Inverse saw-tooth
*/
class P3D_API pPeriodicFunc
{
	public:

		int m_type;			//!< function type (P_PERIODICFUNC_NONE, P_PERIODICFUNC_SIN, P_PERIODICFUNC_TRIANGLE, P_PERIODICFUNC_SQUARE, P_PERIODICFUNC_SAWTOOTH, P_PERIODICFUNC_INVERSESAWTOOTH)
		float m_args[4];	//!< function arguments (offset, amplitude, phase offset and rate)

		//! Default constructor.
		pPeriodicFunc() :
			m_type(0)
		{
			m_args[0] = m_args[1] = 0.5f;
			m_args[2] = 0.0f;
			m_args[3] = 1.0f;
		}

		//! Copy-constructor.
		/*!
			@param in the new periodic function
		*/
		pPeriodicFunc(const pPeriodicFunc& in) :
			m_type(in.m_type)
		{
			m_args[0]=in.m_args[0];
			m_args[1]=in.m_args[1];
			m_args[2]=in.m_args[2];
			m_args[3]=in.m_args[3];
		}

		//! Assignment operator.
		/*!
			@param in the new periodic function
		*/
		void operator=(const pPeriodicFunc& in)
		{
			m_type=in.m_type;
			m_args[0]=in.m_args[0];
			m_args[1]=in.m_args[1];
			m_args[2]=in.m_args[2];
			m_args[3]=in.m_args[3];
		}

		//! Writes periodic function's data into file fp.
		/*!
			@param fp a file
		*/
		void write(FILE *fp) const;

		//! Reads to memory periodic function's data into file fp.
		/*!
			@param fp a file
		*/
		void read(pFile& fp,int ver);

		//! Evaluate the function with the current arguments.
		/*!
			@param time function parameter
			@return return value of the function
		*/
		float eval(float time) const;
};

#endif
