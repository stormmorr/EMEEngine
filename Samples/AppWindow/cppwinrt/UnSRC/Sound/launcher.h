/*

QSound Launcher - geopomp.com - osirem.com
Copyright OSIREM LTD (C) 2015
www.osirem.com www.qage.org www.geopomp.com

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef LAUNCHER_H
#define LAUNCHER_H

#include "Include/osimemory.h"
#include <vector>
#include <string>
#include <shared_mutex>

#include <mfapi.h>
#include <mfmediaengine.h>
#include <xaudio2.h>
#include <mfreadwrite.h>
#include <winerror.h>
#include <wincodec.h>

typedef double float64;

namespace MMAudioPlayer
{
typedef std::vector<BYTE> QpoSound_DATA;
typedef winrt::com_ptr<IMFSourceReader> QpoSoundPtr;

struct StreamingVoiceCallback;

class SoundEffect : public ecom_base
{
public:
	 ////////////////////////
	// Single Constructor //
	SoundEffect();
	~SoundEffect();

	 ////////////////////////////
	// Set Audio Data Readers //
	void Initialize(
		_In_ IXAudio2* masteringEngine,
		_In_ WAVEFORMATEX* sourceFormat,
		_In_ QpoSoundPtr readerUrl,
		_In_ std::shared_ptr<SoundEffect> f_Self
		);

	 /////////////////////////////////
	// ReFresh and Prepare Threads //
	void PlaySound(_In_ float volume, _In_ float f_pitch = 0.f, _In_ float f_pan = 0.f);
	void RePlaySound(void);

	bool ComputePan(float pan, unsigned int channels, float* matrix);

	 ///////////////////
	// worker thread //
	void ScanThread(void);

	// [ PlayBack Controls ]
	//
	void Start(void);
	void Stop(void);
	// [                   ]
	void setVolume(float f_NewVolume);
	float GetVolume(void);
	// [                   ]
	void setCurrentPosition(double seconds);
	double GetCurrentPosition(void);
	// [                   ]
	double GetDuration(void);
	//
	// [ PlayBack Controls ]

	// pitch alteration
	void setPitch(float f_NewPitch);

	 //////////
	// Exit //
	void Shutdown(void);

	 //////////////////////////
	//// MEMBER VARIABLES ////
	int m_AuPlus;

	QpoVec3d m_Position;

	bool m_Scan;
	bool m_Loop;
	bool m_audioAvailable;

	HANDLE m_musicRenderThreadHandle;

private:
	IXAudio2SourceVoice* m_sourceVoice;
	WAVEFORMATEX* m_sourceFormat;
	winrt::com_ptr<IMFSourceReader> m_reader;
	StreamingVoiceCallback* callback;

	LONGLONG playPosCorrelation;
	double currentPositionDelta;
	LONGLONG llTimeStamp;

	float m_Volume;

	float m_pitch;
	float m_pan;

	bool m_bPlaying;
	bool m_bFinish;
};

struct StreamingVoiceCallback : public IXAudio2VoiceCallback
{
private:
	std::shared_ptr<SoundEffect> m_SoundEffect;

public:
	StreamingVoiceCallback(std::shared_ptr<SoundEffect> f_SoundEffect) { m_SoundEffect = f_SoundEffect; }

	STDMETHOD_( void, OnVoiceProcessingPassStart )( UINT32 bytesRequired )
		{
		//unblock render thread
		SetEvent(m_SoundEffect->m_musicRenderThreadHandle);
		}

	STDMETHOD_( void, OnVoiceProcessingPassEnd )(){}
	STDMETHOD_( void, OnStreamEnd )(){}
	STDMETHOD_( void, OnBufferStart )( void* pContext ){}
	STDMETHOD_( void, OnBufferEnd )( void* pContext ){}
	STDMETHOD_( void, OnLoopEnd )( void* pContext ){}
	STDMETHOD_( void, OnVoiceError )( void* pContext, HRESULT error ){}
private:
};

class Audio : public ecom_base
{
public:
	Audio()
		{
		m_musicEngine = nullptr;
		m_musicMasteringVoice = nullptr;

		m_soundEffectEngine = nullptr;
		m_soundEffectMasteringVoice = nullptr;

		m_audioAvailable = false;
		}

	~Audio()
		{
		m_musicEngine->StopEngine();
		m_musicEngine->Release();

		m_musicMasteringVoice->DestroyVoice();
		m_soundEffectEngine->StopEngine();

		m_soundEffectEngine->Release();
		m_soundEffectMasteringVoice->DestroyVoice();

		m_audioAvailable = false;
		}

	void Initialize();
	void CreateDeviceIndependentResources();

	IXAudio2* MusicEngine() { return m_musicEngine; }
	IXAudio2* SoundEffectEngine() { return m_musicEngine; }

#if 0
	void SuspendAudio();
	void ResumeAudio();
#endif

	unsigned int m_masterChannels;
	unsigned int m_masterRate;

private:
	IXAudio2* m_musicEngine;
	IXAudio2MasteringVoice* m_musicMasteringVoice;

	IXAudio2* m_soundEffectEngine;
	IXAudio2MasteringVoice* m_soundEffectMasteringVoice;

	bool m_audioAvailable;
};

class MediaReader : public ecom_base
{
public:
	MediaReader();
	~MediaReader();

	winrt::com_ptr<IMFSourceReader> LoadMedia(winrt::hstring f_hstr);

	WAVEFORMATEX* m_waveFormat;
};

extern std::shared_ptr<MediaReader> g_MediaReader;
extern std::shared_ptr<Audio> g_Audio;
extern std::shared_mutex g_Audio_mutex;

};

#endif