#import <Cocoa/Cocoa.h>
#import <AVFoundation/AVAudioPlayer.h>


#ifndef __has_feature
#define __has_feature(x) 0
#endif


struct YsNSSound
{
#if !__has_feature(objc_arc)
	AVAudioPlayer *snd;
#else
	void *snd;
#endif
};


extern struct YsNSSound *YsSimpleSound_OSX_CreateSound(long long int size,const unsigned char wavByteData[]);
extern void YsSimpleSound_OSX_DeleteSound(struct YsNSSound *ptr);
extern void YsSimpleSound_OSX_PlayOneShot(struct YsNSSound *ptr);
extern void YsSimpleSound_OSX_PlayBackground(struct YsNSSound *ptr);
extern void YsSimpleSound_OSX_SetVolume(struct YsNSSound *ptr,float vol);
extern void YsSimpleSound_OSX_Stop(struct YsNSSound *ptr);
extern void YsSimpleSound_OSX_Pause(struct YsNSSound *ptr);
extern void YsSimpleSound_OSX_Resume(struct YsNSSound *ptr);
extern bool YsSimpleSound_OSX_IsPlaying(struct YsNSSound *ptr);
extern double YsSimpleSound_OSX_GetCurrentPosition(struct YsNSSound *ptr);


struct YsNSSound *YsSimpleSound_OSX_CreateSound(long long int size,const unsigned char wavByteData[])
{
	struct YsNSSound *snd=NULL;
	NSData *nsData=nil;
	AVAudioPlayer *soundData=nil;

	snd=(struct YsNSSound *)malloc(sizeof(struct YsNSSound));
	snd->snd=nil;

	nsData=[NSData dataWithBytes:wavByteData length:size];
	soundData=[[AVAudioPlayer alloc] initWithData:nsData error:nil];
	[soundData prepareToPlay];
#if !__has_feature(objc_arc)
	snd->snd=soundData;
#else
	snd->snd=(void *)CFBridgingRetain(soundData);
#endif

	return snd;
}

void YsSimpleSound_OSX_DeleteSound(struct YsNSSound *ptr)
{
#if !__has_feature(objc_arc)
	[ptr->snd release];
#else
	CFBridgingRelease(ptr->snd);
#endif
	free(ptr);
}

void YsSimpleSound_OSX_PlayOneShot(struct YsNSSound *ptr)
{
	if(nil!=ptr)
	{
#if !__has_feature(objc_arc)
		AVAudioPlayer *snd=ptr->snd;
#else
		AVAudioPlayer *snd=(__bridge AVAudioPlayer *)(ptr->snd);
#endif
		snd.numberOfLoops=0;
		[snd play];
	}
}

void YsSimpleSound_OSX_PlayBackground(struct YsNSSound *ptr)
{
	if(nil!=ptr)
	{
#if !__has_feature(objc_arc)
		AVAudioPlayer *snd=ptr->snd;
#else
		AVAudioPlayer *snd=(__bridge AVAudioPlayer *)(ptr->snd);
#endif
		snd.numberOfLoops=-1;
		[snd play];
	}
}

void YsSimpleSound_OSX_SetVolume(struct YsNSSound *ptr,float vol)
{
	if(nil!=ptr)
	{
#if !__has_feature(objc_arc)
		NSSound *snd=ptr->snd;
#else
		NSSound *snd=(__bridge NSSound *)(ptr->snd);
#endif
		snd.volume=vol;
	}
}

void YsSimpleSound_OSX_Stop(struct YsNSSound *ptr)
{
	if(nil!=ptr)
	{
#if !__has_feature(objc_arc)
		NSSound *snd=ptr->snd;
#else
		NSSound *snd=(__bridge NSSound *)(ptr->snd);
#endif
		[snd stop];
	}
}

void YsSimpleSound_OSX_Pause(struct YsNSSound *ptr)
{
}

void YsSimpleSound_OSX_Resume(struct YsNSSound *ptr)
{
}

bool YsSimpleSound_OSX_IsPlaying(struct YsNSSound *ptr)
{
	if(nil!=ptr)
	{
#if !__has_feature(objc_arc)
		AVAudioPlayer *snd=ptr->snd;
#else
		AVAudioPlayer *snd=(__bridge AVAudioPlayer *)(ptr->snd);
#endif
		if(YES==[snd isPlaying])
		{
			return true;
		}
	}
	return false;
}

double YsSimpleSound_OSX_GetCurrentPosition(struct YsNSSound *ptr)
{
	if(nil!=ptr)
	{
#if !__has_feature(objc_arc)
		AVAudioPlayer *snd=ptr->snd;
#else
		AVAudioPlayer *snd=(__bridge AVAudioPlayer *)(ptr->snd);
#endif
		return [snd currentTime];
	}
	return 0.0;
}
