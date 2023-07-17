#ifndef PSOUND_H
#define PSOUND_H

class P3D_API pSound
{
	private:

		ALenum m_format;
		ALvoid *m_data;
		ALsizei m_size;
		ALsizei m_freq;
		ALboolean m_looping;

		int load_WAV(char *file);

	public:

		pString m_name;
		ALuint m_bufferid;

		pSound();
		pSound(const pSound& in);
		
		~pSound();
		
		void operator=(const pSound& in);

		int load_sound(char *file);
};

#endif