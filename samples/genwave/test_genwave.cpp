#include <fstream>
#include <iostream>
#include "mmlplayer.h"
#include "yssimplesound.h"



int main(void)
{
	MMLPlayer mml;
	std::vector <unsigned char> wav;

	mml.AddMML(0,"@1O4CDEFGAB");
	while(true!=mml.PlayDone())
	{
		auto w=mml.GenerateWave(100);
		wav.insert(wav.end(),w.begin(),w.end());
	}

	YsSoundPlayer::SoundData wavData;
	wavData.CreateFromSigned16bitStereo(YM2612::WAVE_SAMPLING_RATE,wav);

	auto waveFile=wavData.MakeWavByteData();

	std::ofstream ofp;
	ofp.open("genwave.wav",std::ios::out|std::ios::binary);
	ofp.write((const char *)waveFile.data(),waveFile.size());
	ofp.close();

	return 0;
}
