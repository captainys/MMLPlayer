#include <stdio.h>
#include "yssimplesound.h"


struct YsAVAudioEngine;
struct YsAVAudioPlayer;

extern "C" struct YsAVAudioEngine *YsSimpleSound_OSX_CreateAudioEngine(void);
extern "C" void YsSimpleSound_OSX_DeleteAudioEngine(struct YsAVAudioEngine *engine);



extern "C" struct YsAVSound *YsSimpleSound_OSX_CreateSound(struct YsAVAudioEngine *engineInfoPtr,long long int sizeInBytes,const unsigned char wavByteData[],unsigned int samplingRate,unsigned int numChannels);
extern "C" void YsSimpleSound_OSX_DeleteSound(struct YsAVSound *ptr);
extern "C" void YsSimpleSound_OSX_PlayOneShot(struct YsAVAudioEngine *engineInfoPtr,struct YsAVSound *ptr);
extern "C" void YsSimpleSound_OSX_PlayBackground(struct YsAVAudioEngine *engineInfoPtr,struct YsAVSound *ptr);
extern "C" void YsSimpleSound_OSX_SetVolume(struct YsAVAudioEngine *engineInfoPtr,struct YsAVSound *ptr,float vol);
extern "C" void YsSimpleSound_OSX_Stop(struct YsAVAudioEngine *engineInfoPtr,struct YsAVSound *ptr);
extern "C" void YsSimpleSound_OSX_Pause(struct YsAVAudioEngine *engineInfoPtr,struct YsAVSound *ptr);
extern "C" void YsSimpleSound_OSX_Resume(struct YsAVAudioEngine *engineInfoPtr,struct YsAVSound *ptr);
extern "C" bool YsSimpleSound_OSX_IsPlaying(struct YsAVAudioEngine *engineInfoPtr,struct YsAVSound *ptr);
extern "C" double YsSimpleSound_OSX_GetCurrentPosition(struct YsAVAudioEngine *engineInfoPtr,struct YsAVSound *ptr);



class YsSoundPlayer::APISpecificData
{
public:
	APISpecificData();
	~APISpecificData();
	void CleanUp(void);
	YSRESULT Start(void);
	YSRESULT End(void);

	YsAVAudioEngine *enginePtr;
};

class YsSoundPlayer::SoundData::APISpecificDataPerSoundData
{
public:
	APISpecificDataPerSoundData();
	~APISpecificDataPerSoundData();
	void CleanUp(void);

	YsAVSound *sndPtr;
};



////////////////////////////////////////////////////////////



YsSoundPlayer::APISpecificData::APISpecificData()
{
	enginePtr=nullptr;
	CleanUp();
}
YsSoundPlayer::APISpecificData::~APISpecificData()
{
	CleanUp();
}

void YsSoundPlayer::APISpecificData::CleanUp(void)
{
	if(nullptr!=enginePtr)
	{
		printf("Ending AVAudioEngine.\n");
		YsSimpleSound_OSX_DeleteAudioEngine(enginePtr);
		enginePtr=nullptr;
	}
}

YSRESULT YsSoundPlayer::APISpecificData::Start(void)
{
	if(nullptr==enginePtr)
	{
		printf("Starting AVAudioEngine.\n");
		enginePtr=YsSimpleSound_OSX_CreateAudioEngine();
	}
	return YSOK;
}
YSRESULT YsSoundPlayer::APISpecificData::End(void)
{
	CleanUp();
	return YSOK;
}

////////////////////////////////////////////////////////////

YsSoundPlayer::APISpecificData *YsSoundPlayer::CreateAPISpecificData(void)
{
	return new APISpecificData;
}
void YsSoundPlayer::DeleteAPISpecificData(APISpecificData *ptr)
{
	delete ptr;
}

YSRESULT YsSoundPlayer::StartAPISpecific(void)
{
	return api->Start();
}
YSRESULT YsSoundPlayer::EndAPISpecific(void)
{
	return api->End();
}

void YsSoundPlayer::KeepPlayingAPISpecific(void)
{
}

YSRESULT YsSoundPlayer::PlayOneShotAPISpecific(SoundData &dat)
{
	if(nullptr!=dat.api->sndPtr)
	{
		YsSimpleSound_OSX_SetVolume(api->enginePtr,dat.api->sndPtr,dat.playBackVolume);
		YsSimpleSound_OSX_PlayOneShot(api->enginePtr,dat.api->sndPtr);
		return YSOK;
	}
	return YSERR;
}

YSRESULT YsSoundPlayer::PlayBackgroundAPISpecific(SoundData &dat)
{
	if(nullptr!=dat.api->sndPtr)
	{
		YsSimpleSound_OSX_SetVolume(api->enginePtr,dat.api->sndPtr,dat.playBackVolume);
		YsSimpleSound_OSX_PlayBackground(api->enginePtr,dat.api->sndPtr);
		return YSOK;
	}
	return YSERR;
}

YSBOOL YsSoundPlayer::IsPlayingAPISpecific(const SoundData &dat) const
{
	if(nullptr!=dat.api->sndPtr && YsSimpleSound_OSX_IsPlaying(api->enginePtr,dat.api->sndPtr))
	{
		return YSTRUE;
	}
	return YSFALSE;
}

double YsSoundPlayer::GetCurrentPositionAPISpecific(const SoundData &dat) const
{
	if(nullptr!=dat.api->sndPtr)
	{
		return YsSimpleSound_OSX_GetCurrentPosition(api->enginePtr,dat.api->sndPtr);
	}
	return 0.0;
}

void YsSoundPlayer::StopAPISpecific(SoundData &dat)
{
	if(nullptr!=dat.api->sndPtr)
	{
		YsSimpleSound_OSX_Stop(api->enginePtr,dat.api->sndPtr);
	}
}

void YsSoundPlayer::PauseAPISpecific(SoundData &dat)
{
	if(nullptr!=dat.api->sndPtr)
	{
		YsSimpleSound_OSX_Pause(api->enginePtr,dat.api->sndPtr);
	}
}

void YsSoundPlayer::ResumeAPISpecific(SoundData &dat)
{
	if(nullptr!=dat.api->sndPtr)
	{
		YsSimpleSound_OSX_Resume(api->enginePtr,dat.api->sndPtr);
	}
}

void YsSoundPlayer::SetVolumeAPISpecific(SoundData &dat,float vol)
{
	if(nullptr!=dat.api->sndPtr)
	{
		YsSimpleSound_OSX_SetVolume(api->enginePtr,dat.api->sndPtr,vol);
	}
}

////////////////////////////////////////////////////////////

YsSoundPlayer::SoundData::APISpecificDataPerSoundData::APISpecificDataPerSoundData()
{
	sndPtr=nullptr;
	CleanUp();
}
YsSoundPlayer::SoundData::APISpecificDataPerSoundData::~APISpecificDataPerSoundData()
{
	CleanUp();
}
void YsSoundPlayer::SoundData::APISpecificDataPerSoundData::CleanUp(void)
{
	if(nullptr!=sndPtr)
	{
		YsSimpleSound_OSX_DeleteSound(sndPtr);
		sndPtr=nullptr;
	}
}

////////////////////////////////////////////////////////////

YsSoundPlayer::SoundData::APISpecificDataPerSoundData *YsSoundPlayer::SoundData::CreateAPISpecificData(void)
{
	return new APISpecificDataPerSoundData;
}
void YsSoundPlayer::SoundData::DeleteAPISpecificData(APISpecificDataPerSoundData *ptr)
{
	delete ptr;
}

YSRESULT YsSoundPlayer::SoundData::PreparePlay(YsSoundPlayer &player)
{
	if(nullptr==api->sndPtr)
	{
		api->sndPtr=YsSimpleSound_OSX_CreateSound(player.api->enginePtr,dat.size(),dat.data(),PlayBackRate(),GetNumChannel());
		if(nullptr!=api->sndPtr)
		{
			return YSOK;
		}
	}
	return YSERR;
}

void YsSoundPlayer::SoundData::CleanUpAPISpecific(void)
{
	api->CleanUp();
}
