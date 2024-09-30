#include <iostream>
#include "mmlplayer.h"
#include "fssimplewindow.h"
#include "yssimplesound.h"

// Play a short segment, and keep the program open until the user presses the ESC key.

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

	for(;;)
	{
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
		}
	}

	player.End();

	return 0;
}
