#import <Cocoa/Cocoa.h>
#import <AVFoundation/AVFoundation.h>



struct YsAVAudioEngine
{
#if !__has_feature(objc_arc)
    AVAudioEngine *enginePtr;
    AVAudioMixerNode *mixerNodePtr;
    AVAudioPlayerNode *primaryPlayerNodePtr;
    AVAudioFormat *audioFormatPtr;
#else
	void *enginePtr;
	void *mixerNodePtr;
	void *primaryPlayerNodePtr;
	void *audioFormatPtr;
#endif
};

extern struct YsAVAudioEngine *YsSimpleSound_OSX_CreateAudioEngine(void);
extern void YsSimpleSound_OSX_DeleteAudioEngine(struct YsAVAudioEngine *engine);


struct YsAVAudioEngine *YsSimpleSound_OSX_CreateAudioEngine(void)
{
	struct YsAVAudioEngine *engineInfoPtr=(struct YsAVAudioEngine *)malloc(sizeof(struct YsAVAudioEngine));

    AVAudioEngine *enginePtr=[[AVAudioEngine alloc] init];
    AVAudioMixerNode *mixerNodePtr=[enginePtr mainMixerNode];
    AVAudioPlayerNode *primaryPlayerNodePtr=[[AVAudioPlayerNode alloc] init];

    /* According to https://developer.apple.com/documentation/avfoundation/avaudioformat/1390416-initstandardformatwithsamplerate?language=objc
       the returned format always uses AVAudioPCMFormatFloat32.
    */
    AVAudioFormat *audioFormatPtr=[[AVAudioFormat alloc] initStandardFormatWithSampleRate:44100 channels:2];

    [enginePtr attachNode:primaryPlayerNodePtr];
    [enginePtr connect:primaryPlayerNodePtr to:mixerNodePtr format:audioFormatPtr];

    NSError *err=nil;
    [enginePtr startAndReturnError:&err];
    if(nil!=err)
    {
        printf("Error %ld\n",[err code]);
        printf("%s\n",[[err localizedDescription] UTF8String]);
    }

#if !__has_feature(objc_arc)
    engineInfoPtr->enginePtr=enginePtr;
    engineInfoPtr->mixerNodePtr=mixerNodePtr;
	engineInfoPtr->primaryPlayerNodePtr=primaryPlayerNodePtr;
	engineInfoPtr->audioFormatPtr=audioFormatPtr;
#else
	engineInfoPtr->enginePtr=(void *)CFBridgingRetain(enginePtr);
	engineInfoPtr->mixerNodePtr=(void *)CFBridgingRetain(mixerNodePtr);
	engineInfoPtr->primaryPlayerNodePtr=(void *)CFBridgingRetain(primaryPlayerNodePtr);
	engineInfoPtr->audioFormatPtr=(void *)CFBridgingRetain(audioFormatPtr);
#endif

	return engineInfoPtr;
}

void YsSimpleSound_OSX_DeleteAudioEngine(struct YsAVAudioEngine *engineInfoPtr)
{
    AVAudioEngine *enginePtr=nil;
    AVAudioMixerNode *mixerNodePtr=nil;
    AVAudioPlayerNode *primaryPlayerNodePtr=nil;
    AVAudioFormat *audioFormatPtr=nil;

#if !__has_feature(objc_arc)
    enginePtr=engineInfoPtr->enginePtr;
    mixerNodePtr=engineInfoPtr->mixerNodePtr;
	primaryPlayerNodePtr=engineInfoPtr->primaryPlayerNodePtr;
	audioFormatPtr=engineInfoPtr->audioFormatPtr;
#else
	enginePtr=(__bridge AVAudioEngine *)engineInfoPtr->enginePtr;
	mixerNodePtr=(__bridge AVAudioMixerNode *)engineInfoPtr->mixerNodePtr;
	primaryPlayerNodePtr=(__bridge AVAudioPlayerNode *)engineInfoPtr->primaryPlayerNodePtr;
	audioFormatPtr=(__bridge AVAudioFormat *)engineInfoPtr->audioFormatPtr;
#endif

	[enginePtr detachNode:primaryPlayerNodePtr];

#if !__has_feature(objc_arc)
	[enginePtr release];
	[primaryPlayerNodePtr release];
	[audioFormatPtr release];
#else
	CFBridgingRelease(engineInfoPtr->enginePtr);
	CFBridgingRelease(engineInfoPtr->primaryPlayerNodePtr);
	CFBridgingRelease(engineInfoPtr->audioFormatPtr);
#endif

	free(engineInfoPtr);
}

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
