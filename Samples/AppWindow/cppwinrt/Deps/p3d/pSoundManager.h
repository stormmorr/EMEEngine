#ifndef PSOUNDMANAGER_H
#define PSOUNDMANAGER_H

//! Global access to sound manager
class pSoundManager;
P3D_API extern pSoundManager *g_soundmanager;

class P3D_API pSoundManager
{
	public:

		float m_doppler_factor;
		float m_doppler_velocity;
		pArray<unsigned int> m_soundid;
		pArray<pSound *> m_sounds;

		pSoundManager();
		~pSoundManager();

		void reset();
		int load_sound(const char *sndfile);

		void set_listener(const float *pos,const float *dir,const float *up);
		void set_listener(const pVector& pos,const pVector& dir,const pVector& up);

		void update_doppler_factor();
		void update_doppler_velocity();
};

#endif