#include "pch.h"
#include "paralelo3d.h"

void pPeriodicFunc::write(FILE *fp) const
{
	fwrite(&m_type,1,sizeof(int),fp);
	fwrite(m_args,4,sizeof(float),fp);
}

void pPeriodicFunc::read(pFile& fp,int ver)
{
	fp.read(&m_type,sizeof(int));
	fp.read(&m_args,4*sizeof(float));
}

float pPeriodicFunc::eval(float time) const 
{
	float x = 0.0f;
	float y = 0.0f;

    // Evaluate a number of time based periodic functions
    // y = args[0] + args[1] * func( (time + arg[2]) * arg[3] )
    
    x = (time + m_args[2]) * m_args[3];
    x -= (int)x;

    switch (m_type)
		{
		case P_PERIODICFUNC_SIN:
			y = sinf(x * TWOPI);
			break;
			
		case P_PERIODICFUNC_TRIANGLE:
			if (x < 0.5f)
				y = 4.0f * x - 1.0f;
			else
				y = -4.0f * x + 3.0f;
			break;
			
		case P_PERIODICFUNC_SQUARE:
			if (x < 0.5f)
				y = 1.0f;
			else
				y = -1.0f;
			break;
			
		case P_PERIODICFUNC_SAWTOOTH:
			y = 2.0f*x - 1.0f;
			break;
			
		case P_PERIODICFUNC_INVERSESAWTOOTH:
			y = 1.0f - 2.0f*x;
			break;
		}

    return y * m_args[1] + m_args[0];
}
