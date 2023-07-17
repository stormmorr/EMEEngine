/*! \file */

#ifndef PANIMATION_H
#define PANIMATION_H

class P3D_API pAnimation
{
	public:
		int type;
		int keysize;
		int valuesize;

		int numkey;
		float *keytime;
		float *keyvalue;
		
		float curtime;
		int curtimekey;
		static int typesize[6];
		static int typevaluesize[6];

		float lastvalue[4];

	pAnimation();
	~pAnimation();

	pAnimation(const pAnimation& in);
	void operator=(const pAnimation& in);

	void reset();
	void set_type(int t);
	void set_numkeys(int nk,int zero_mem=1,int keep_old=0);
	float get_maxtime();

	void write(FILE *fp) const;
	void read(pFile& fp,int ver);

	void update(float time,float* value);
	void update_loop(float time,float* value);
	void evaluate_bezier(const float *p,int n,float f,float *o) const;
};

#endif
