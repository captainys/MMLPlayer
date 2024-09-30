#include <iostream>
#include "mmlplayer.h"
#include "fssimplewindow.h"
#include "yssimplesound.h"

// Play a short segment, and keep the program open until the music is over.
// Also print current play-time on the terminal.

int main(void)
{
	MMLSegmentPlayer mmlplayer;

	mmlplayer.AddSegment(
		"O4V8CDEFGAB",
		"",
		"",
		"",
		"",
		"");


	// Open window for interaction.
	FsOpenWindow(0,0,800,600,0);

	// Need a sound player to communicate with the sound device.
	YsSoundPlayer player;
	player.Start();

	// Start streaming.
	YsSoundPlayer::Stream stream;
	YsSoundPlayer::StreamingOption streamOpt;
	streamOpt.ringBufferLengthMillisec=500;
	player.StartStreaming(stream,streamOpt);

	// Make first piece of wave.
	YsSoundPlayer::SoundData nextWave;
	auto rawWave=mmlplayer.GenerateWave(100);  // Create for next 100ms
	nextWave.CreateFromSigned16bitStereo(YM2612::WAVE_SAMPLING_RATE,rawWave);

	if(0!=mmlplayer.GetLastErrorCode())
	{
		for(auto msg : mmlplayer.GetLastError().Format())
		{
			std::cout << msg << std::endl;
		}
	}

	int endTimer=0;
	auto t0=std::chrono::high_resolution_clock::now();
	for(;;)
	{
		// Measure milliseconds since the last frame.
		auto t1=std::chrono::high_resolution_clock::now();
		auto millisec=std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count();
		if(0<millisec)
		{
			// Don't update timer if millisec is zero.
			// Maybe it was sub-millisecond since the last frame.
			t0=t1;
		}

		// If timer is set up, count down, and
		if(0<endTimer)
		{
			endTimer-=millisec;
			if(endTimer<=0)
			{
				// break if the timer is up.
				break;
			}
		}

		FsPollDevice();

		player.KeepPlaying();  // <- This line is only needed for Linux ALSA.

		auto key=FsInkey();
		if(FSKEY_ESC==key)
		{
			break;
		}

		// Add wave when the stream-player is able to accept next piece.
		if(YSTRUE==player.StreamPlayerReadyToAcceptNextSegment(stream,nextWave))
		{
			// Add already-prepared segment, and then,
			player.AddNextStreamingSegment(stream,nextWave);

			// Make next segment to be ready to pump to the buffer.
			auto rawWave=mmlplayer.GenerateWave(100);  // Create for next 100ms
			nextWave.CreateFromSigned16bitStereo(YM2612::WAVE_SAMPLING_RATE,rawWave);

			if(0!=mmlplayer.GetLastErrorCode())
			{
				for(auto msg : mmlplayer.GetLastError().Format())
				{
					std::cout << msg << std::endl;
				}
			}

			std::cout << mmlplayer.GetTimeInMicrosec() << "\n";
		}

		if(true==mmlplayer.PlayDone() && 0==endTimer)
		{
			// Set end-timer for the duration of the ring buffer.
			endTimer=streamOpt.ringBufferLengthMillisec;
		}
	}

	player.End();

	return 0;
}
