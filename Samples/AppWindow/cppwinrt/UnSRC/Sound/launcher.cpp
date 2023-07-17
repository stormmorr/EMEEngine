/*

QSound Launcher - geopomp.com - osirem.com
Copyright OSIREM LTD (C) 2015
www.osirem.com www.qage.org www.geopomp.com

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"

#include "launcher.h"

#include "xaudio2.h"

//*** INCLUDES
#include "Q-PortSHELL-VAR.h"
#include "Q-PortSHELL-FUN.h"
#include "Q-PortSHELL-Sound.h"

#include "Q-Includes.h"
#include "Q-AI-Cortex.h"
#include "Q-AI-Brain.h"
#include "Q-AI-Heart.h"
#include "Q-WE-PntSprite.h"
#include "Q-WE-WorldEffects.h"
#include "Q-ITEM-ItemDef.h"
#include "Q-Structs.h"
#include "Q-Prototypes.h"
#include "Q-GlobalHeader.h"

using namespace MMAudioPlayer;

namespace MMAudioPlayer
{

std::shared_ptr<MediaReader> g_MediaReader;
std::shared_ptr<Audio> g_Audio;
std::shared_mutex g_Audio_mutex;

SoundEffect::SoundEffect()
{
	std::string f_ref_CurrentPath = "SoundEffect::SoundEffect";

	m_audioAvailable = false;
	m_Loop = false;
	m_Scan = false;
	m_bFinish = false;

	m_AuPlus = -1;

	m_pitch = 0.65f;

#ifndef OSI_MEM_APP
	ac_Push(m_audioAvailable, f_ref_CurrentPath + g_ref_Div + "m_audioAvailable");
	ac_Push(m_Loop, f_ref_CurrentPath + g_ref_Div + "m_Loop");
	ac_Push(m_Scan, f_ref_CurrentPath + g_ref_Div + "m_Scan");
	ac_Push(m_bFinish, f_ref_CurrentPath + g_ref_Div + "m_bFinish");
	ac_Push(m_AuPlus, f_ref_CurrentPath + g_ref_Div + "m_AuPlus");
#endif
}

SoundEffect::~SoundEffect()
{
	Shutdown();
}

void SoundEffect::Shutdown(void)
{
	if(m_bPlaying == true)
		{
		m_sourceVoice->Discontinuity();
		m_sourceVoice->Stop();
		m_bPlaying = false;
		}

	currentPositionDelta=0;
	playPosCorrelation=0;

	if(m_sourceVoice != nullptr)
		{
		m_sourceVoice->DestroyVoice();

		//set exit flag from render thread
		SetEvent(m_musicRenderThreadHandle);

		m_sourceVoice = nullptr;

		delete m_sourceFormat;

		llTimeStamp = 0;

		CloseHandle(m_musicRenderThreadHandle);
		}
}

void SoundEffect::Initialize(
    _In_ IXAudio2* masteringEngine,
    _In_ WAVEFORMATEX* sourceFormat,
	_In_ QpoSoundPtr readerUrl,
	_In_ std::shared_ptr<SoundEffect> f_Self)
{
    if(masteringEngine == nullptr)
		{
        // Audio is not available so just return.
        m_audioAvailable = false;

        return;
		}

	readerUrl.copy_to(m_reader.put());

	// save each wave format
	m_sourceFormat = sourceFormat;

	callback = new StreamingVoiceCallback(f_Self);

    // Create a source voice for this sound effect.
    winrt::check_hresult(masteringEngine->CreateSourceVoice(&m_sourceVoice, m_sourceFormat, 0, 1.0f, callback, nullptr));

	// set flags
	m_Scan = true;
	m_audioAvailable = true;

	// set event
	m_musicRenderThreadHandle = CreateEventEx(nullptr, nullptr, CREATE_EVENT_MANUAL_RESET, WRITE_OWNER | EVENT_ALL_ACCESS);

	ResetEvent(m_musicRenderThreadHandle);
}

void SoundEffect::PlaySound(_In_ float volume, _In_ float f_pitch, _In_ float f_pan)
{
    if(m_audioAvailable == false)
		{
        // Audio is not available so bail.
        return;
		}

	setVolume(volume);

	setCurrentPosition(0.0f);

    // Interrupt sound effect if it is currently playing.
    winrt::check_hresult(m_sourceVoice->Stop());

    winrt::check_hresult(m_sourceVoice->FlushSourceBuffers());

	if(m_pitch != 0.f)
		{
        const float fr = XAudio2SemitonesToFrequencyRatio(m_pitch * 12.f);

		winrt::check_hresult(m_sourceVoice->SetFrequencyRatio(fr));

		m_pitch = f_pitch;
		}

    if(m_pan != 0.f)
		{
        float matrix[16];

        if(ComputePan(m_pan, m_sourceFormat->nChannels, matrix))
			{
			winrt::check_hresult(m_sourceVoice->SetOutputMatrix(nullptr, m_sourceFormat->nChannels, g_Audio->m_masterChannels, matrix));

			m_pan = f_pan;
			}
		}

	 ////////////////////////////////
	// Ready Buffers
	std::thread f_Thread(&SoundEffect::ScanThread, this);

	f_Thread.detach();
}

void SoundEffect::RePlaySound(void)
{
	PlaySound(m_Volume);
}

void SoundEffect::setVolume(float f_NewVolume)
{
	if(m_sourceVoice != nullptr)
		{
		m_Volume = f_NewVolume;

		winrt::check_hresult(m_sourceVoice->SetVolume(m_Volume));
		}
}

void SoundEffect::setPitch(float f_NewPitch)
{
	m_pitch = f_NewPitch;
}

void SoundEffect::ScanThread(void)
{
	DWORD dwActualStreamIndex = 0;
	DWORD dwStreamFlags = 0;

	int iSwap = 0;

	static const int BUFFER_COUNT = 3;
	QpoSound_DATA play_buffer[BUFFER_COUNT];
	
	while(m_Scan == true)
		{
		//wait for voice callback::OnVoiceProcessingPassStart 
		WaitForSingleObjectEx(m_musicRenderThreadHandle, INFINITE, TRUE);

		if(m_bPlaying == false)
			{
			ResetEvent(m_musicRenderThreadHandle);
			continue;
			}

		XAUDIO2_VOICE_STATE state;

		m_sourceVoice->GetState(&state);

		//queue is full, skip and wait again
		if(state.BuffersQueued >= BUFFER_COUNT)
			{
			continue;
			}

		Microsoft::WRL::ComPtr<IMFSample> sample;
		Microsoft::WRL::ComPtr<IMFMediaBuffer> buffer;

		LONGLONG tick = 0;

		m_reader->ReadSample(static_cast<DWORD>(MF_SOURCE_READER_FIRST_AUDIO_STREAM),0,&dwActualStreamIndex,&dwStreamFlags,&tick,&sample);

		if(dwStreamFlags & MF_SOURCE_READERF_ENDOFSTREAM || 
			dwStreamFlags & MF_SOURCE_READERF_CURRENTMEDIATYPECHANGED ||
			dwStreamFlags & MF_SOURCE_READERF_ERROR)
			{
			if(state.BuffersQueued == 0)
				{
				m_sourceVoice->Discontinuity();
				}

			m_sourceVoice->Stop();

			//just continue and wait for cleanup() exit 
			// or seek to pos and play again
			if(m_Loop == false)
				{
				m_bPlaying = false;

				m_bFinish = true;

				//EXIT LOOP - EXIT THREAD
				m_Scan = false;
				}
			else
				{
				setCurrentPosition(0.0f);

				m_sourceVoice->Start();
				}

			ResetEvent(m_musicRenderThreadHandle);
			}

		//ppSample is null, do nothing
		if(dwStreamFlags & MF_SOURCE_READERF_STREAMTICK)
			{
			ResetEvent(m_musicRenderThreadHandle);
			continue;
			}

		if(m_Scan == true)
			{
			llTimeStamp = tick;

			sample->ConvertToContiguousBuffer(&buffer);

			BYTE *pAudioData = nullptr;

			DWORD cbCurrentLength = 0;

			buffer->Lock(&pAudioData, nullptr, &cbCurrentLength);

			if(play_buffer[iSwap].size() < cbCurrentLength)
				{
				play_buffer[iSwap].resize(cbCurrentLength);
				}

			CopyMemory(play_buffer[iSwap].data(), pAudioData, cbCurrentLength);

			buffer->Unlock();

			XAUDIO2_BUFFER abuf = {0};
			abuf.AudioBytes = cbCurrentLength;
			abuf.pAudioData = play_buffer[iSwap].data();

			if(abuf.pAudioData && abuf.AudioBytes > 0)
				{
				m_sourceVoice->SubmitSourceBuffer(&abuf);
				}

			iSwap = ++iSwap % BUFFER_COUNT;
			}

		ResetEvent(m_musicRenderThreadHandle);
		}

	// lock up and reorder
	g_Audio_mutex.lock();

	for(int f_Jet = m_AuPlus; f_Jet < _->m_vec_SoundEffect.size() - 1; f_Jet++)
		{
		_->m_vec_SoundEffect[f_Jet + 1]->m_AuPlus--;
		_->m_vec_SoundEffect[f_Jet] = _->m_vec_SoundEffect[f_Jet + 1];
		}

	_->m_vec_SoundEffect.pop_back();

#if 0 // prolly unlikely easy reorder
	for(int f_Jet = 0; f_Jet < _->m_vec_SoundEffect.size(); f_Jet++)
		{
		_->m_vec_SoundEffect[f_Jet]->m_AuPlus = f_Jet;
		}
#endif

#ifdef ECOIN_DEBUG_BREAKS
	if(_->m_vec_SoundEffect.size() > 500)
		{
		__debugbreak();
		}
#endif //add debug msg

	g_Audio_mutex.unlock();
}

MediaReader::MediaReader()
{
	m_waveFormat = nullptr;
}

MediaReader::~MediaReader()
{
	if(m_waveFormat != nullptr)
		{
		m_waveFormat = nullptr;
		}
}

winrt::com_ptr<IMFSourceReader> MediaReader::LoadMedia(winrt::hstring f_hstr)
{
    winrt::check_hresult(MFStartup(MF_VERSION));

    // Creates a media source reader.
    winrt::com_ptr<IMFSourceReader> reader;

    winrt::check_hresult(
        MFCreateSourceReaderFromURL(
			f_hstr.c_str(),
            nullptr,
            reader.put()
            )
        );

    // Set the decoded output format as PCM.
    // XAudio2 on Windows can process PCM and ADPCM-encoded buffers.
    // When using MediaFoundation, this sample always decodes into PCM.
    winrt::com_ptr<IMFMediaType> mediaType;
    winrt::check_hresult(
        MFCreateMediaType(mediaType.put())
        );

    // Define the major category of the media as audio. For more info about major media types,
    // go to: https://msdn.microsoft.com/library/windows/desktop/aa367377.aspx
    winrt::check_hresult(
        mediaType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio)
        );

    // Define the sub-type of the media as uncompressed PCM audio. For more info about audio sub-types,
    // go to: https://msdn.microsoft.com/library/windows/desktop/aa372553.aspx
    winrt::check_hresult(
        mediaType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM)
        );

    // Sets the media type for a stream. This media type defines that format that the Source Reader 
    // produces as output. It can differ from the native format provided by the media source.
    // For more info, go to https://msdn.microsoft.com/library/windows/desktop/dd374667.aspx
    winrt::check_hresult(
        reader->SetCurrentMediaType(static_cast<uint32_t>(MF_SOURCE_READER_FIRST_AUDIO_STREAM), 0, mediaType.get())
        );

    // Get the current media type for the stream.
    // For more info, go to:
    // https://msdn.microsoft.com/library/windows/desktop/dd374660.aspx
    winrt::com_ptr<IMFMediaType> outputMediaType;
    winrt::check_hresult(
        reader->GetCurrentMediaType(static_cast<uint32_t>(MF_SOURCE_READER_FIRST_AUDIO_STREAM), outputMediaType.put())
        );

    // Converts the current media type into the WaveFormatEx buffer structure.
    UINT32 size = 0;
    WAVEFORMATEX* waveFormat;
    winrt::check_hresult(
        MFCreateWaveFormatExFromMFMediaType(outputMediaType.get(), &waveFormat, &size)
        );

    // Copies the waveFormat's block of memory to the starting address of the m_waveFormat variable in MediaReader.
    // Then free the waveFormat memory block.
    // For more info, go to https://msdn.microsoft.com/library/windows/desktop/aa366535.aspx and
    // https://msdn.microsoft.com/library/windows/desktop/ms680722.aspx

	m_waveFormat = waveFormat;

	g_StreamWaveForm[g_StreamIndex - 1] = waveFormat;

    PROPVARIANT propVariant;

    winrt::check_hresult(reader->GetPresentationAttribute(static_cast<uint32_t>(MF_SOURCE_READER_MEDIASOURCE), MF_PD_DURATION, &propVariant));

    // 'duration' is in 100ns units; convert to seconds, and round up
    // to the nearest whole byte.
    LONGLONG duration = propVariant.uhVal.QuadPart;

    unsigned int maxStreamLengthInBytes = static_cast<unsigned int>(
            ((duration * static_cast<ULONGLONG>(m_waveFormat->nAvgBytesPerSec)) + 10000000) /
            10000000
            );

	g_StreamLength[g_StreamIndex - 1] = maxStreamLengthInBytes;

    return reader;
}

void Audio::CreateDeviceIndependentResources()
{
    UINT32 flags = 0;

    winrt::check_hresult(XAudio2Create(&m_musicEngine, flags));

    HRESULT hr = m_musicEngine->CreateMasteringVoice(&m_musicMasteringVoice);

    if(FAILED(hr))
		{
        // Unable to create an audio device
		m_audioAvailable = false;

		__debugbreak();

		return;
		}

    winrt::check_hresult(XAudio2Create(&m_soundEffectEngine, flags));

    winrt::check_hresult(m_soundEffectEngine->CreateMasteringVoice(&m_soundEffectMasteringVoice));

	XAUDIO2_VOICE_DETAILS details;
	m_musicMasteringVoice->GetVoiceDetails(&details);

	m_masterChannels = details.InputChannels;
	m_masterRate = details.InputSampleRate;

    m_audioAvailable = true;
}

void Audio::Initialize()
{
	m_audioAvailable = true;

	CreateDeviceIndependentResources();
}

void SoundEffect::Start(void)
{
	if(m_sourceVoice != nullptr)
		{
		if(m_bFinish == true)
			{
			RePlaySound();
			}

		m_sourceVoice->Start();

		m_bPlaying = true;
		}
}

void SoundEffect::Stop(void)
{
	if(m_sourceVoice != nullptr)
		{
		//stop submitting new buffers from render thread
		m_bPlaying = false;

		m_sourceVoice->Stop();
		}
}

void SoundEffect::setCurrentPosition(double seconds)
{
	if(m_reader != nullptr)
		{
		bool bPlaying = m_bPlaying;

		if(bPlaying == true)
			{
			Stop();
			}

		m_sourceVoice->FlushSourceBuffers();

		XAUDIO2_VOICE_STATE state;
		m_sourceVoice->GetState(&state, 0);

		PROPVARIANT var;
		ZeroMemory(&var, sizeof(var));
		var.vt = VT_I8;

		LONGLONG pos = (LONGLONG)(seconds * ((float64)10000 * 1000));
		var.uhVal.QuadPart = pos;

		playPosCorrelation = state.SamplesPlayed;

		m_reader->SetCurrentPosition(GUID_NULL, var);
		currentPositionDelta = seconds;

		if(bPlaying == true)
			{
			Start();
			}
		}
}

double SoundEffect::GetDuration(void)
{
	if(m_reader != nullptr)
		{
		PROPVARIANT var;

		//it's just attribute, not accurate!
		m_reader->GetPresentationAttribute(static_cast<DWORD>(MF_SOURCE_READER_MEDIASOURCE), MF_PD_DURATION, &var);
		LONGLONG duration = var.uhVal.QuadPart;
		float64 durationInSeconds = (duration / (float64)(10000 * 1000));

		return durationInSeconds;
		}
	else
		{
		return 0;
		}
}

double SoundEffect::GetCurrentPosition(void)
{
	XAUDIO2_VOICE_STATE state;

	if((m_sourceVoice != nullptr) && (m_sourceFormat != nullptr))
		{
		m_sourceVoice->GetState(&state, 0);

		double currentPos = currentPos = (double)((double)state.SamplesPlayed - playPosCorrelation) / (double)m_sourceFormat->nSamplesPerSec;

		return currentPos + currentPositionDelta;
		}
	else
		{
		return 0.0f;
		}
}

float SoundEffect::GetVolume(void)
{
	float retval = 0;

	if(m_sourceVoice != nullptr)
		{
		m_sourceVoice->GetVolume(&retval);
		}

	return retval;
}

bool SoundEffect::ComputePan(float pan, unsigned int channels, float* matrix)
{
    memset(matrix, 0, sizeof(float) * 16);

    if(channels == 1)
		{
        // Mono panning
        float left = 1.f - pan;
        left = std::min<float>(1.f, left);
        left = std::max<float>(0.f, left);

        float right = pan + 1.f;
        right = std::min<float>(1.f, right);
        right = std::max<float>(0.f, right);

        matrix[0] = left;
        matrix[1] = right;
		}
    else if(channels == 2)
		{
        // Stereo panning
        if(-1.f <= pan && pan <= 0.f)
			{
            matrix[0] = .5f * pan + 1.f;    // .5 when pan is -1, 1 when pan is 0
            matrix[1] = .5f * -pan;         // .5 when pan is -1, 0 when pan is 0
            matrix[2] = 0.f;                //  0 when pan is -1, 0 when pan is 0
            matrix[3] = pan + 1.f;          //  0 when pan is -1, 1 when pan is 0
			}
        else
			{
            matrix[0] = -pan + 1.f;         //  1 when pan is 0,   0 when pan is 1
            matrix[1] = 0.f;                //  0 when pan is 0,   0 when pan is 1
            matrix[2] = .5f * pan;          //  0 when pan is 0, .5f when pan is 1
            matrix[3] = .5f * -pan + 1.f;   //  1 when pan is 0. .5f when pan is 1
			}
		}
    else
		{
        if(pan != 0.f)
			{
            //DebugTrace("WARNING: Only supports panning on mono or stereo source data, ignored\n");
			}

        return false;
		}

    return true;
}


};