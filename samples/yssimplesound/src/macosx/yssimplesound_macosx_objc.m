#import <Cocoa/Cocoa.h>
#import <AVFoundation/AVFoundation.h>



struct YsAVAudioEngine
{
#if !__has_feature(objc_arc)
    AVAudioEngine *enginePtr;
    AVAudioMixerNode *mixerNodePtr;
    AVAudioPlayerNode *primaryPlayerNodePtr;
    AVAudioFormat *primaryAudioFormatPtr;
#else
	void *enginePtr;
	void *mixerNodePtr;
	void *primaryPlayerNodePtr;
	void *primaryAudioFormatPtr;
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
	AVAudioFormat *primaryAudioFormatPtr=[[AVAudioFormat alloc] initStandardFormatWithSampleRate:44100 channels:2];

    [enginePtr attachNode:primaryPlayerNodePtr];
    [enginePtr connect:primaryPlayerNodePtr to:mixerNodePtr format:primaryAudioFormatPtr];

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
	engineInfoPtr->primaryAudioFormatPtr=primaryAudioFormatPtr;
#else
	engineInfoPtr->enginePtr=(void *)CFBridgingRetain(enginePtr);
	engineInfoPtr->mixerNodePtr=(void *)CFBridgingRetain(mixerNodePtr);
	engineInfoPtr->primaryPlayerNodePtr=(void *)CFBridgingRetain(primaryPlayerNodePtr);
	engineInfoPtr->primaryAudioFormatPtr=(void *)CFBridgingRetain(primaryAudioFormatPtr);
#endif

	return engineInfoPtr;
}

void YsSimpleSound_OSX_DeleteAudioEngine(struct YsAVAudioEngine *engineInfoPtr)
{
    AVAudioEngine *enginePtr=nil;
    AVAudioMixerNode *mixerNodePtr=nil;
    AVAudioPlayerNode *primaryPlayerNodePtr=nil;

#if !__has_feature(objc_arc)
    enginePtr=engineInfoPtr->enginePtr;
    mixerNodePtr=engineInfoPtr->mixerNodePtr;
	primaryPlayerNodePtr=engineInfoPtr->primaryPlayerNodePtr;
#else
	enginePtr=(__bridge AVAudioEngine *)engineInfoPtr->enginePtr;
	mixerNodePtr=(__bridge AVAudioMixerNode *)engineInfoPtr->mixerNodePtr;
	primaryPlayerNodePtr=(__bridge AVAudioPlayerNode *)engineInfoPtr->primaryPlayerNodePtr;
#endif

	[enginePtr detachNode:primaryPlayerNodePtr];

#if !__has_feature(objc_arc)
	[engineInfoPtr->enginePtr release];
	[engineInfoPtr->primaryPlayerNodePtr release];
	[engineInfoPtr->primaryAudioFormatPtr release];
#else
	CFBridgingRelease(engineInfoPtr->enginePtr);
	CFBridgingRelease(engineInfoPtr->primaryPlayerNodePtr);
	CFBridgingRelease(engineInfoPtr->primaryAudioFormatPtr);
#endif

	free(engineInfoPtr);
}

struct YsAVSound
{
	int bufferCount;
	uint64_t samplingRate;

#if !__has_feature(objc_arc)
    AVAudioEngine *enginePtr;

    AVAudioPlayerNode *playerNodePtr;
    AVAudioPCMBuffer *PCMBufferPtr;
    AVAudioFormat *audioFormatPtr;
#else
	void *enginePtr;

	void *playerNodePtr;
	void *PCMBufferPtr;
	void *audioFormatPtr;
#endif
};


extern struct YsAVSound *YsSimpleSound_OSX_CreateSound(struct YsAVAudioEngine *engineInfoPtr,long long int sizeInBytes,const unsigned char wavByteData[],unsigned int samplingRate,unsigned int numChannels);
extern void YsSimpleSound_OSX_DeleteSound(struct YsAVSound *ptr);
extern void YsSimpleSound_OSX_PlayOneShot(struct YsAVAudioEngine *engineInfoPtr,struct YsAVSound *ptr);
extern void YsSimpleSound_OSX_PlayBackground(struct YsAVAudioEngine *engineInfoPtr,struct YsAVSound *ptr);
extern void YsSimpleSound_OSX_SetVolume(struct YsAVAudioEngine *engineInfoPtr,struct YsAVSound *ptr,float vol);
extern void YsSimpleSound_OSX_Stop(struct YsAVAudioEngine *engineInfoPtr,struct YsAVSound *ptr);
extern void YsSimpleSound_OSX_Pause(struct YsAVAudioEngine *engineInfoPtr,struct YsAVSound *ptr);
extern void YsSimpleSound_OSX_Resume(struct YsAVAudioEngine *engineInfoPtr,struct YsAVSound *ptr);
extern bool YsSimpleSound_OSX_IsPlaying(struct YsAVAudioEngine *engineInfoPtr,struct YsAVSound *ptr);
extern double YsSimpleSound_OSX_GetCurrentPosition(struct YsAVAudioEngine *engineInfoPtr,struct YsAVSound *ptr);


struct YsAVSound *YsSimpleSound_OSX_CreateSound(struct YsAVAudioEngine *engineInfoPtr,long long int sizeInBytes,const unsigned char wavByteData[],unsigned int samplingRate,unsigned int numChannels)
{
	long long int numSamples=sizeInBytes/2;


    /* According to https://developer.apple.com/documentation/avfoundation/avaudioformat/1390416-initstandardformatwithsamplerate?language=objc
       the returned format always uses AVAudioPCMFormatFloat32.
    */
    AVAudioFormat *audioFormatPtr=[[AVAudioFormat alloc] initStandardFormatWithSampleRate:samplingRate channels:numChannels];

    AVAudioPCMBuffer *PCMBufferPtr=[[AVAudioPCMBuffer alloc] initWithPCMFormat:audioFormatPtr frameCapacity:numSamples];
    [PCMBufferPtr setFrameLength:numSamples];

    int stride=[PCMBufferPtr stride];
    for(int ch=0; ch<[audioFormatPtr channelCount]; ++ch)
    {
		const unsigned char *channelSrcPtr=wavByteData+2*ch;
        for(int i=0; i<[PCMBufferPtr frameLength] && i<numSamples; ++i)
        {
			int data=(channelSrcPtr[1]<<8)|channelSrcPtr[0];
			data=(data&0x7FFF)-(data&0x8000);
            [PCMBufferPtr floatChannelData][ch][i*stride]=(float)data/32768.0f;;
			channelSrcPtr+=2;
        }
    }

    AVAudioPlayerNode *playerNodePtr=[[AVAudioPlayerNode alloc] init];

#if !__has_feature(objc_arc)
    AVAudioEngine *enginePtr=engineInfoPtr->enginePtr;
    AVAudioMixerNode *mixerNodePtr=engineInfoPtr->mixerNodePtr;
#else
	AVAudioEngine *enginePtr=(__bridge AVAudioEngine *)engineInfoPtr->enginePtr;
	AVAudioMixerNode *mixerNodePtr=(__bridge AVAudioMixerNode *)engineInfoPtr->mixerNodePtr;
#endif

    [enginePtr attachNode:playerNodePtr];
    [enginePtr connect:playerNodePtr to:mixerNodePtr format:audioFormatPtr];


	struct YsAVSound *snd=NULL;
	snd=(struct YsAVSound *)malloc(sizeof(struct YsAVSound));
	snd->playerNodePtr=nil;
	snd->PCMBufferPtr=nil;
	snd->audioFormatPtr=nil;
	snd->bufferCount=0;
	snd->samplingRate=samplingRate;

#if !__has_feature(objc_arc)
	snd->enginePtr=enginePtr;
	snd->playerNodePtr=playerNodePtr;
	snd->PCMBufferPtr=PCMBufferPtr;
	snd->audioFormatPtr=audioFormatPtr;
#else
	snd->enginePtr=(void*)CFBridgingRetain(enginePtr);
	snd->playerNodePtr=(void*)CFBridgingRetain(playerNodePtr);
	snd->PCMBufferPtr=(void*)CFBridgingRetain(PCMBufferPtr);
	snd->audioFormatPtr=(void*)CFBridgingRetain(audioFormatPtr);
#endif

	return snd;
}

void YsSimpleSound_OSX_DeleteSound(struct YsAVSound *ptr)
{
#if !__has_feature(objc_arc)
    AVAudioEngine *enginePtr=ptr->enginePtr;
	AVAudioPlayerNode *playerNodePtr=ptr->playerNodePtr;
#else
	AVAudioEngine *enginePtr=(__bridge AVAudioEngine *)ptr->enginePtr;
	AVAudioPlayerNode *playerNodePtr=(__bridge AVAudioPlayerNode *)ptr->playerNodePtr;
#endif

	[enginePtr detachNode:playerNodePtr];

#if !__has_feature(objc_arc)
	[ptr->playerNodePtr release];
	[ptr->PCMBufferPtr release];
	[ptr->audioFormatPtr release];
#else
	CFBridgingRelease(ptr->playerNodePtr);
	CFBridgingRelease(ptr->PCMBufferPtr);
	CFBridgingRelease(ptr->audioFormatPtr);
#endif
	free(ptr);
}

/* For future reference.  Lambda in Objective-C.  Another failure of Objective-C.
void (^YsAVPlayerCompletion)()=^()
{
	printf("Objective-C go to hell.\n");
};
See also http://fuckingblocksyntax.com/
*/

void YsSimpleSound_OSX_PlayOneShot(struct YsAVAudioEngine *engineInfoPtr,struct YsAVSound *ptr)
{
	if(nil!=ptr)
	{
#if !__has_feature(objc_arc)
	    AVAudioEngine *enginePtr=engineInfoPtr->enginePtr;
	    AVAudioMixerNode *mixerNodePtr=engineInfoPtr->mixerNodePtr;
		AVAudioPlayerNode *playerNodePtr=ptr->playerNodePtr;
		AVAudioPCMBuffer *PCMBufferPtr=ptr->PCMBuffer;
#else
		AVAudioEngine *enginePtr=(__bridge AVAudioEngine *)engineInfoPtr->enginePtr;
		AVAudioMixerNode *mixerNodePtr=(__bridge AVAudioMixerNode *)engineInfoPtr->mixerNodePtr;
		AVAudioPlayerNode *playerNodePtr=(__bridge AVAudioPlayerNode *)ptr->playerNodePtr;
		AVAudioPCMBuffer *PCMBufferPtr=(__bridge AVAudioPCMBuffer *)ptr->PCMBufferPtr;
#endif

		[playerNodePtr play];
	    /* The following line won't give an error, but not useful.
		[playerNodePtr scheduleBuffer:PCMBufferPtr completionHandler:YsAVPlayerCompletion()]; 
		*/

		++ptr->bufferCount;

		__block struct YsAVSound *soundCopy=ptr;
	    [playerNodePtr scheduleBuffer:PCMBufferPtr completionHandler:^{
			// How can I write a captured variable correctly?
			if(0<soundCopy->bufferCount)  // Apparently stop method also invokes this completionHandler.
			{
				--soundCopy->bufferCount;
			}
		}];
	}
}

void YsSimpleSound_OSX_PlayBackground(struct YsAVAudioEngine *engineInfoPtr,struct YsAVSound *ptr)
{
	if(nil!=ptr)
	{
#if !__has_feature(objc_arc)
	    AVAudioEngine *enginePtr=engineInfoPtr->enginePtr;
	    AVAudioMixerNode *mixerNodePtr=engineInfoPtr->mixerNodePtr;
		AVAudioPlayerNode *playerNodePtr=ptr->playerNodePtr;
		AVAudioPCMBuffer *PCMBufferPtr=ptr->PCMBuffer;
#else
		AVAudioEngine *enginePtr=(__bridge AVAudioEngine *)engineInfoPtr->enginePtr;
		AVAudioMixerNode *mixerNodePtr=(__bridge AVAudioMixerNode *)engineInfoPtr->mixerNodePtr;
		AVAudioPlayerNode *playerNodePtr=(__bridge AVAudioPlayerNode *)ptr->playerNodePtr;
		AVAudioPCMBuffer *PCMBufferPtr=(__bridge AVAudioPCMBuffer *)ptr->PCMBufferPtr;
#endif

		[playerNodePtr play];
		++ptr->bufferCount;
	    [playerNodePtr scheduleBuffer:PCMBufferPtr atTime:nil options:AVAudioPlayerNodeBufferLoops completionHandler:^{
			/* How can I write a captured variable correctly? ->

			Surprise!  Surprise!
			According to:
				https://www.mikeash.com/pyblog/friday-qa-2011-06-03-objective-c-blocks-vs-c0x-lambdas-fight.html
			automatic reference counting does not apply to the captured variables.
			Sounds like I cannot stop the player simply by [playerNodePtr stop];
			*/
		}];
	}
}

void YsSimpleSound_OSX_SetVolume(struct YsAVAudioEngine *engineInfoPtr,struct YsAVSound *ptr,float vol)
{
	if(nil!=ptr)
	{
	}
}

void YsSimpleSound_OSX_Stop(struct YsAVAudioEngine *engineInfoPtr,struct YsAVSound *ptr)
{
	if(nil!=ptr)
	{
#if !__has_feature(objc_arc)
	    AVAudioEngine *enginePtr=engineInfoPtr->enginePtr;
	    AVAudioMixerNode *mixerNodePtr=engineInfoPtr->mixerNodePtr;
		__block AVAudioPlayerNode *playerNodePtr=ptr->playerNodePtr;
		AVAudioPCMBuffer *PCMBufferPtr=ptr->PCMBuffer;
#else
		AVAudioEngine *enginePtr=(__bridge AVAudioEngine *)engineInfoPtr->enginePtr;
		AVAudioMixerNode *mixerNodePtr=(__bridge AVAudioMixerNode *)engineInfoPtr->mixerNodePtr;
		__block AVAudioPlayerNode *playerNodePtr=(__bridge AVAudioPlayerNode *)ptr->playerNodePtr;
		AVAudioPCMBuffer *PCMBufferPtr=(__bridge AVAudioPCMBuffer *)ptr->PCMBufferPtr;
#endif

		[playerNodePtr stop];
		ptr->bufferCount=0;
	}
}

void YsSimpleSound_OSX_Pause(struct YsAVAudioEngine *engineInfoPtr,struct YsAVSound *ptr)
{
}

void YsSimpleSound_OSX_Resume(struct YsAVAudioEngine *engineInfoPtr,struct YsAVSound *ptr)
{
}

bool YsSimpleSound_OSX_IsPlaying(struct YsAVAudioEngine *engineInfoPtr,struct YsAVSound *ptr)
{
	if(nil!=ptr)
	{
#if !__has_feature(objc_arc)
		AVAudioPlayerNode *playerNodePtr=ptr->playerNodePtr;
#else
		AVAudioPlayerNode *playerNodePtr=(__bridge AVAudioPlayerNode *)ptr->playerNodePtr;
#endif
		// if(YES==[playerNodePtr isPlaying])  <- It didn't help.
		if(0<ptr->bufferCount)
		{
			return true;
		}
	}
	return false;
}

double YsSimpleSound_OSX_GetCurrentPosition(struct YsAVAudioEngine *engineInfoPtr,struct YsAVSound *ptr)
{
	if(nil!=ptr)
	{
#if !__has_feature(objc_arc)
	    AVAudioEngine *enginePtr=engineInfoPtr->enginePtr;
	    AVAudioMixerNode *mixerNodePtr=engineInfoPtr->mixerNodePtr;
		__block AVAudioPlayerNode *playerNodePtr=ptr->playerNodePtr;
		AVAudioPCMBuffer *PCMBufferPtr=ptr->PCMBuffer;
#else
		AVAudioEngine *enginePtr=(__bridge AVAudioEngine *)engineInfoPtr->enginePtr;
		AVAudioMixerNode *mixerNodePtr=(__bridge AVAudioMixerNode *)engineInfoPtr->mixerNodePtr;
		__block AVAudioPlayerNode *playerNodePtr=(__bridge AVAudioPlayerNode *)ptr->playerNodePtr;
		AVAudioPCMBuffer *PCMBufferPtr=(__bridge AVAudioPCMBuffer *)ptr->PCMBufferPtr;
#endif

		AVAudioTime *t=[playerNodePtr playerTimeForNodeTime:[playerNodePtr lastRenderTime]];
		uint64_t samplePos=[t sampleTime];

		return (double)samplePos/(double)ptr->samplingRate;
	}
	return 0.0;
}
