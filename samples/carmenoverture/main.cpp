#include <iostream>
#include "mmlplayer.h"
#include "fssimplewindow.h"
#include "yssimplesound.h"



void SetUpMML(MMLSegmentPlayer &player);

int main(void)
{
	MMLSegmentPlayer mmlplayer;

	SetUpMML(mmlplayer);


	FsOpenWindow(0,0,800,600,0);

	YsSoundPlayer player;
	player.Start();

	YsSoundPlayer::Stream stream;
	player.StartStreaming(stream);

	YsSoundPlayer::SoundData nextWave;
	auto rawWave=mmlplayer.GenerateWave(1000);  // Create for next 100ms

	std::vector <unsigned char> entirePlayback=rawWave;

	nextWave.CreateFromSigned16bitStereo(YM2612::WAVE_SAMPLING_RATE,rawWave);

	for(;;)
	{
		FsPollDevice();

		player.KeepPlaying();  // <- This line is only needed for Linux ALSA.

		auto key=FsInkey();
		if(FSKEY_ESC==key)
		{
			break;
		}

		if(YSTRUE==player.StreamPlayerReadyToAcceptNextSegment(stream,nextWave))
		{
			player.AddNextStreamingSegment(stream,nextWave);
			auto rawWave=mmlplayer.GenerateWave(1000);  /// Create for next 100ms
			entirePlayback.insert(entirePlayback.end(),rawWave.begin(),rawWave.end());
			nextWave.CreateFromSigned16bitStereo(YM2612::WAVE_SAMPLING_RATE,rawWave);
		}
	}

	{
		nextWave.CreateFromSigned16bitStereo(YM2612::WAVE_SAMPLING_RATE,entirePlayback);
		auto wavData=nextWave.MakeWavByteData();
		FILE *fp=fopen("carmenoverture.wav","wb");
		fwrite(wavData.data(),1,wavData.size(),fp);
		fclose(fp);
	}

	player.End();

	return 0;
}

void SetUpMML(MMLSegmentPlayer &player)
{
// At this time, only first six channels.  Eventually I'm going to make it more channels.

	// ----- Main Theme
	// ----- 1
	player.AddSegment(
		"q8v15t130@34",     /* チェレスタ */
		"q8v15t130@22",     /* ハープシコード*/
		"q8v15t130@17",     /* Electric Piano */
		"q8v15t130@70",     /* Orchestra Brass - 5th row*/
		"q8v15t130@2",      /* Horn - 9th row*/
		"q8v15t130@74"     /* Cello - Alternate or unison or 9th or 5th row */
		//,
		//v15t130o4@1      /* Cymbal 1 */
		//v15t130o4@1      /* Cymbal 1 */
		//v15t130o4@2      /* Drum 1 */
		//v15t130o4@2      /* Drum 1 */
		//v15t130o4@3      /* Snare Drum */
		//v15t130o4@3      /* Snare Drum */
	);
// 
	player.AddSegment(
		"q5L16o5a8aaaede",
		"q5L16o5a8aaaede",
		"q5L16o4a8aaaede",
		"L8o2arer",
		"L8o3arer",
		"L8o4rara"
		//,
		//"c4r4",
		//"c4r4",
		//"r4c4",
		//"r4c4",
		//"r4c4",
		//"r4c4",
	);
//
	player.AddSegment(
		"L16o5a8aaabo6c+o5b",
		"L16o5a8aaabo6c+o5b",
		"L16o4a8aaabo5c+o4b",
		"L8o2arer",
		"L8o3arer",
		"L8o4rara"
		//,
		//"c4r4",
		//"c4r4",
		//"r4c4",
		//"r4c4",
		//"r4c4",
		//"r4c4",
	);
//
	player.AddSegment(
		"L16o5a8aabag+a",
		"L16o5a8aabag+a",
		"L16o4a8aabag+a",
		"L8o2arg+r",
		"L8o3arg+r",
		"L8o4rarg+"
		//,
		//"c4r4",
		//"c4r4",
		//"r4c4",
		//"r4c4",
		//"r4c4",
		//"r4c4",
	);
// TR: Vibrate with the base and base+2
	player.AddSegment(
		"q8L32o5b>c+<b>c+<b>c+<b>c+<b>c+<b>c+<L16a+b",
		"q8L32o5b>c+<b>c+<b>c+<b>c+<b>c+<b>c+<L16a+b",
		"q8L32o4b>c+<b>c+<b>c+<b>c+<b>c+<b>c+<L16a+b",
		"L8o2f+rer",
		"L8o3f+rer",
		"L8o4rf+re"
		//,
		//"c4r4",
		//"c4r4",
		//"r4c4",
		//"r4c4",
		//"r4c4",
		//"r4c4",
	);
// 
	player.AddSegment(
		"L16o6d8dddo5aga",
		"L16o6d8dddo5aga",
		"L16o5d8dddo4aga",
		"o2drar",
		"o3drar",
		"o4rdra"
		//,
		//"r4",
		//"r4",
		//"c4",
		//"c4",
		//"c4",
		//"c4",
	);
//  ----- 6
	player.AddSegment(
		"6o6d8dddef+e",
		"6o6d8dddef+e",
		"6o5d8dddef+e",
		"o2drar",
		"o3drar",
		"o4rdra"
		//,
		//"r4",
		//"r4",
		//"c4",
		//"c4",
		//"c4",
		//"c4",
	);

	player.AddSegment(
		"6o6d8dc+o5b8ba",
		"6o6d8dc+o5b8ba",
		"6o5d8dc+o4b8ba",
		"o2drg+r",
		"o3drg+r",
		"o4rdrg+"
		//,
		//"r4",
		//"r4",
		//"c4",
		//"c4",
		//"c4",
		//"c4",
	);

	player.AddSegment(
		"L32o5g+a+g+a+g+a+g+a+g+a+g+a+L16f+g+",
		"L32o5g+a+g+a+g+a+g+a+g+a+g+a+L16f+g+",
		"L32o4g+a+g+a+g+a+g+a+g+a+g+a+L16f+g+",
		"o2c+rer",
		"o3c+rer",
		"o4rc+re"
		//,
		//"r4",
		//"r4",
		//"c4",
		//"c4",
		//"c4",
		//"c4",
	);
// 
// L16o5a8aaaede
// L16o5a8aaaede
// L16o4a8aaaede
// o2arer
// o3arer
// o4rara
// r4
// r4
// c4
// c4
// c4
// c4
// 
// 6o5a8aaabo6c+o5b
// 6o5a8aaabo6c+o5b
// 6o4a8aaabo5c+o4b
// o2arer
// o3arer
// o4rara
// r4
// r4
// c4
// c4
// c4
// c4
// 
// 6o5a8aabag+a
// 6o5a8aabag+a
// 6o4a8aabag+a
// o2arg+r
// o3arg+r
// o4rarg+
// r4
// r4
// c4
// c4
// c4
// c4
//  ----- 12
// L32o5b>c+<b>c+<b>c+<b>c+<b>c+<b>c+<L16a+b
// L32o5b>c+<b>c+<b>c+<b>c+<b>c+<b>c+<L16a+b
// L32o4b>c+<b>c+<b>c+<b>c+<b>c+<b>c+<L16a+b
// o2f+rer
// o3f+rer
// o4rf+re
// r4
// r4
// c4
// c4
// c4
// c4
// 
// L16o6e8eeq8edq5cd
// L16o6e8eeq8edq5cd
// L16o4e8eeq8edq5cd
// o2crgr
// o3cro2gr
// o4rcrg
// r4
// r4
// c4
// c4
// c4
// c4
// 
// 6o6e8eeq8edq5cd
// 6o6e8eeq8edq5cd
// 6o4e8eeq8edq5cd
// o2crgr
// o3cro2gr
// o4rcrg
// r4
// r4
// c4
// c4
// c4
// c4
// 
// 6o6e8o5ef+g+8eo6c+
// 6o6e8o5ef+g+8eo6c+
// 6o5e8o4ef+g+8eo5c+
// 6o2e8o3g+g+g+8g+g+
// 6o3e8eee8ee
// 6o4e8eee8ee
// r4
// r4
// c4
// c4
// c4
// c4
// 
// o5b4&a8r8
// o5b4&a8r8
// o4b4&a8r8
// g+4a8r8
// e4a8r8
// r8e16e16a8r8
// r4
// r4
// c4
// c4
// c4
// c4
//  Repeat - Main Theme
//  
// L16o5a8aaaede
// L16o5a8aaaede
// L16o4a8aaaede
// o2arer
// o3arer
// o4rara
// r4
// r4
// c4
// c4
// c4
// c4
// 
// 6o5a8aaabo6c+o5b
// 6o5a8aaabo6c+o5b
// 6o4a8aaabo5c+o4b
// o2arer
// o3arer
// o4rara
// r4
// r4
// c4
// c4
// c4
// c4
// 
// 6o5a8aabag+a
// 6o5a8aabag+a
// 6o4a8aabag+a
// o2arg+r
// o3arg+r
// o4rarg+
// r4
// r4
// c4
// c4
// c4
// c4
//  TR: Vibrate with the base and base+2
// L32o5b>c+<b>c+<b>c+<b>c+<b>c+<b>c+<L16a+b
// L32o5b>c+<b>c+<b>c+<b>c+<b>c+<b>c+<L16a+b
// L32o4b>c+<b>c+<b>c+<b>c+<b>c+<b>c+<L16a+b
// o2f+rer
// o3f+rer
// o4rf+re
// r4
// r4
// c4
// c4
// c4
// c4
// 
// L16o6d8dddo5aga
// L16o6d8dddo5aga
// L16o5d8dddo4aga
// o2drar
// o3drar
// o4rdra
// r4
// r4
// c4
// c4
// c4
// c4
//  ----- 6
// 6o6d8dddef+e
// 6o6d8dddef+e
// 6o5d8dddef+e
// o2drar
// o3drar
// o4rdra
// r4
// r4
// c4
// c4
// c4
// c4
// 
// 6o6d8dc+o5b8ba
// 6o6d8dc+o5b8ba
// 6o5d8dc+o4b8ba
// o2drg+r
// o3drg+r
// o4rdrg+
// r4
// r4
// c4
// c4
// c4
// c4
// 
// L32o5g+a+g+a+g+a+g+a+g+a+g+a+L16f+g+
// L32o5g+a+g+a+g+a+g+a+g+a+g+a+L16f+g+
// L32o4g+a+g+a+g+a+g+a+g+a+g+a+L16f+g+
// o2c+rer
// o3c+rer
// o4rc+re
// r4
// r4
// c4
// c4
// c4
// c4
// 
// L16o5a8aaaede
// L16o5a8aaaede
// L16o4a8aaaede
// o2arer
// o3arer
// o4rara
// r4
// r4
// c4
// c4
// c4
// c4
// 
// 6o5a8aaabo6c+o5b
// 6o5a8aaabo6c+o5b
// 6o4a8aaabo5c+o4b
// o2arer
// o3arer
// o4rara
// r4
// r4
// c4
// c4
// c4
// c4
// 
// 6o5a8aabag+a
// 6o5a8aabag+a
// 6o4a8aabag+a
// o2arg+r
// o3arg+r
// o4rarg+
// r4
// r4
// c4
// c4
// c4
// c4
//  ----- 12
// L32o5b>c+<b>c+<b>c+<b>c+<b>c+<b>c+<L16a+b
// L32o5b>c+<b>c+<b>c+<b>c+<b>c+<b>c+<L16a+b
// L32o4b>c+<b>c+<b>c+<b>c+<b>c+<b>c+<L16a+b
// o2f+rer
// o3f+rer
// o4rf+re
// r4
// r4
// c4
// c4
// c4
// c4
// 
// L16o6e8eeq8edq5cd
// L16o6e8eeq8edq5cd
// L16o4e8eeq8edq5cd
// o2crgr
// o3cro2gr
// o4rcrg
// r4
// r4
// c4
// c4
// c4
// c4
// 
// 6o6e8eeq8edq5cd
// 6o6e8eeq8edq5cd
// 6o4e8eeq8edq5cd
// o2crgr
// o3cro2gr
// o4rcrg
// r4
// r4
// c4
// c4
// c4
// c4
// 
// 6o6e8o5ef+g+8eo6c+
// 6o6e8o5ef+g+8eo6c+
// 6o5e8o4ef+g+8eo5c+
// 6o2e8o3g+g+g+8g+g+
// 6o3e8eee8ee
// 6o4e8eee8ee
// r4
// r4
// c4
// c4
// c4
// c4
// 
// o5b4&a8r8
// o5b4&a8r8
// o4b4&a8r8
// g+4a8r8
// e4a8r8
// r8e16e16a8r8
// r4
// r4
// c4
// c4
// c4
// c4
//  Repeat
//  ----- 17
//  Sub(?) theme
// 0v8L8o6c+f+c+o5b /* Oboe */
//  v8L8o6c+f+c+o5b /* Flute */
//  v8L8o4c+f+c+o4b /* Clarinet */
//  v8L8o3f+c+f+g+  /* Horn */
// r2@16   /* Grand Piano */
// r2@42   /* Timpani */
// 
// 
// 
// 
// 
// 
// 
// o5ag+16f+16g+c+
// o5ag+16f+16g+c+
// o4ag+16f+16g+c+
// o3ab16o4c+16o3bc+
// 6r4o5q4c+c+q8c+8
// 6r4o4q4c+c+q8c+8
// 
// 
// 
// 
// 
// 
// 
// o5f+g+ao6c+
// o5f+g+ao6c+
// o4f+g+ao5c+
// o3ag+f+a
// 
// 
// 
// 
// 
// 
// 
// 
// 
// o6e+d+16e+16c+o5c+
// o6e+d+16e+16c+o5c+
// o5e+d+16e+16c+o4c+
// o3g+f+16g+16e+c+
// 6r4q4o5c+c+q8c+8
// 6r4q4o4c+c+q8c+8
// 
// 
// 
// 
// 
// 
// 
// o6c+f+c+o5b
// o6c+f+c+o5b
// o5c+f+c+o4b
// o3f+c+f+g+
// 
// 
// 
// 
// 
// 
// 
// 
// 
// o5ag+16f+16g+c+
// o5ag+16f+16g+c+
// o4ag+16f+16g+c+
// o3ab16o4c+16o3bc+
// 6r4o5q4c+c+q8c+8
// 6r4o4q4c+c+q8c+8
// 
// 
// 
// 
// 
// 
// 
// o5f+g+ao6c+
// o5f+g+ao6c+
// o4f+g+ao5c+
// o3ag+f+a
// 
// 
// 
// 
// 
// 
// 
// 
//  24
// o6e+d+16e+16c+r
// o6e+d+16e+16c+r
// o5e+d+16e+16c+r
// o3g+f+16g+16e+r
// 6o5q4g+g+q8g+8c+8r8
// 6o4q4g+g+q8g+8c+8r8
// 
// 
// 
// 
// 
// 
// 
// 
//  v13L16o6ddd8eee8
// 6v13L16o6ddd8eee8
// 3v13L16o5ddd8eee8
// 0v13L16o4ddd8ddd8
// 0v13L16o3ddd8eee8 /* Temporarily row 5 */
// 3r2
// 
// 
// 
// 
// 
// 
// 
// 6o6f+f+f+8ddd8
// 6o6f+f+f+8ddd8
// 6o5f+f+f+8ddd8
// 6o4ddd8ddd8
// 6o3f+f+f+8ddd8 /* Temporarily row 5 */
// 
// 
// 
// 
// 
// 
// 
// 
// 0L8o6c+o5g+o6c+d
//  L8o6c+o5g+o6c+d
//  L8o5c+o4g+o5c+d
//  L8o4c+o3g+o4c+d
// 2o6g+a+g+a+g+a+g+a+g+a+g+a+g+a+g+a+
// 6o4c+4.q4c+c+q8
// 
// 
// 
// 
// 
// 
// 
// o6c+o5g+o6c+r
// o6c+o5g+o6c+r
// o5c+o4g+o5c+r
// o4c+o3g+o4c+r
// 2o6g+a+g+a+g+a+g+a+g+a+g+a+g+a+g+a+
// c+4.r8
// 
// 
// 
// 
// 
// 
//  L16o6ddd8eee8
// 6L16o6ddd8eee8
// 3L16o5ddd8eee8
// 0L16o4ddd8ddd8
// 0L16o3ddd8eee8 /* Temporarily row 5 */
// 
// 
// 
// 
// 
// 
// 
//  
// 6o6f+f+f+8ddd8
// 6o6f+f+f+8ddd8
// 6o5f+f+f+8ddd8
// 6o4ddd8ddd8
// 6o3f+f+f+8ddd8 /* Temporarily row 5 */
// 
// 
// 
// 
// 
// 
// 
//  ----- 31
// 0v2L32o6g+a+g+a+g+a+v3g+a+g+a+g+a+g+a+g+a+
//  v2L32o6g+a+g+a+g+a+v3g+a+g+a+g+a+g+a+g+a+
//  v2L32o5g+a+g+a+g+a+v3g+a+g+a+g+a+g+a+g+a+
//  v2L8o3g+o2g+v3ao3a
// L8o3g+o2g+v3ao3a
// L16o4r8q4c+c+v3q8c+4
// 
// 
// 
// 
// 
// 
// 
// L32o6g+a+g+a+g+a+v7g+a+g+a+g+a+g+a+g+a+
// L32o6g+a+g+a+g+a+v7g+a+g+a+g+a+g+a+g+a+
// L32o5g+a+g+a+g+a+v7g+a+g+a+g+a+g+a+g+a+
// L8o3a+o3c+v7db
// L8o3a+o3c+v7db
// L16o4r8q4c+c+v7q8c+4
// 
// 
// 
// 
// 
// 
//  
// L32o6g+a+g+a+g+a+v11g+a+g+a+g+a+g+a+g+a+
// L32o6g+a+g+a+g+a+v11g+a+g+a+g+a+g+a+g+a+
// L32o5g+a+g+a+g+a+v11g+a+g+a+g+a+g+a+g+a+
// L8o3b+d+v11eo4c+
// L8o3b+d+v11eo4c+
// L16o4r8q4c+c+v11q8c+4
// 
// 
// 
// 
// 
// 
//  
// 3L32o6g+a+g+a+g+a+v15g+a+g+a+g+a+@34L16gg+
// 3L32o6g+a+g+a+g+a+v15g+a+g+a+g+a+@22L16gg+
// 3L32o5g+a+g+a+g+a+v15g+a+g+a+g+a+@17L16gg+
// 3L8o4do3dv15d+e
// 3L8o4do3dv15d+e
// 3L16o4r8q4c+c+v15q8c+4
// 
// 
// 
// 
// 
// 
//  Main Theme
// 4v15L16q5o6a8o5aaaede
// 2v15L16q5o6a8o5aaaede
// 7v15L16q5o4a8aaaede
// 0v15L8o2arer
//  v15L8o3arer
// 4v15L8o4rara
// v15c4r4
// v15c4r4
// v15r4c4
// v15r4c4
// v15r4c4
// v15r4c4
//  
// 6o5a8aaabo6c+o5b
// 6o5a8aaabo6c+o5b
// 6o4a8aaabo5c+o4b
// o2arer
// o3arer
// o4rara
// r4
// r4
// c4
// c4
// c4
// c4
//  
// 6o5a8aabag+a
// 6o5a8aabag+a
// 6o4a8aabag+a
// o2arg+r
// o3arg+r
// o4rarg+
// r4
// r4
// c4
// c4
// c4
// c4
//  ----- 38
// L32o5b>c+<b>c+<b>c+<b>c+<b>c+<b>c+<L16a+b
// L32o5b>c+<b>c+<b>c+<b>c+<b>c+<b>c+<L16a+b
// L32o4b>c+<b>c+<b>c+<b>c+<b>c+<b>c+<L16a+b
// o2f+rer
// o3f+rer
// o4rf+re
// r4
// r4
// c4
// c4
// c4
// c4
//  
// L16o6d8dddo5aga
// L16o6d8dddo5aga
// L16o5d8dddo4aga
// o2drar
// o3drar
// o4rdra
// r4
// r4
// c4
// c4
// c4
// c4
// 
// 6o6d8dddef+e
// 6o6d8dddef+e
// 6o5d8dddef+e
// o2drar
// o3drar
// o4rdra
// r4
// r4
// c4
// c4
// c4
// c4
// 
// 6o6d8dc+o5b8ba
// 6o6d8dc+o5b8ba
// 6o5d8dc+o4b8ba
// o2drg+r
// o3drg+r
// o4rdrg+
// r4
// r4
// c4
// c4
// c4
// c4
// 
// L32o5g+a+g+a+g+a+g+a+g+a+g+a+L16f+g+
// L32o5g+a+g+a+g+a+g+a+g+a+g+a+L16f+g+
// L32o4g+a+g+a+g+a+g+a+g+a+g+a+L16f+g+
// o2c+rer
// o3c+rer
// o4rc+re
// r4
// r4
// c4
// c4
// c4
// c4
// 
// L16o5a8aaaede
// L16o5a8aaaede
// L16o4a8aaaede
// o2arer
// o3arer
// o4rara
// r4
// r4
// c4
// c4
// c4
// c4
// 
// 6o5a8aaabo6c+o5b
// 6o5a8aaabo6c+o5b
// 6o4a8aaabo5c+o4b
// o2arer
// o3arer
// o4rara
// r4
// r4
// c4
// c4
// c4
// c4
//  ---- 45
// 6o5a8aabag+a
// 6o5a8aabag+a
// 6o4a8aabag+a
// o2arg+r
// o3arg+r
// o4rarg+
// r4
// r4
// c4
// c4
// c4
// c4
// 
// L32o5b>c+<b>c+<b>c+<b>c+<b>c+<b>c+<L16a+b
// L32o5b>c+<b>c+<b>c+<b>c+<b>c+<b>c+<L16a+b
// L32o4b>c+<b>c+<b>c+<b>c+<b>c+<b>c+<L16a+b
// o2f+rer
// o3f+rer
// o4rf+re
// r4
// r4
// c4
// c4
// c4
// c4
// 
// 6q5o6e8eeq8edq5cd
// 6q5o6e8eeq8edq5cd
// 6q5o4e8eeq8edq5cd
// o2crgr
// o3cro2gr
// o4rcrg
// r4
// r4
// c4
// c4
// c4
// c4
// 
// 6o6e8eeq8edq5cd
// 6o6e8eeq8edq5cd
// 6o4e8eeq8edq5cd
// o2crgr
// o3cro2gr
// o4rcrg
// r4
// r4
// c4
// c4
// c4
// c4
// 
// 6o6e8o5ef+g+8eo6c+
// 6o6e8o5ef+g+8eo6c+
// 6o5e8o4ef+g+8eo5c+
// 6o2e8o3g+g+g+8g+g+
// 6o3e8eee8ee
// 6o4e8eee8ee
// r4
// r4
// c4
// c4
// c4
// c4
// 
// o5b4&a8r8
// o5b4&a8r8
// o4b4&a8r8
// g+4a8r8
// e4a8r8
// r8e16e16a8r8
// r4
// r4
// c4
// c4
// c4
// c4
//  Second theme
//  ----- Change Instruments
// t130@72     /* Violin 1 */
// t130@73     /* Violin 2 */
// t130@70     /* Orchestra */
// t130@70     /* Orchestra */
// t130@5      /* Tronbone */
// t130@2      /* Horn */
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// o4frfr
// o3frfr
// 
// 
// 
// 
// 
// 
//  ----- 52
// 
// 
// 
// 
// o4frfr
// o3frfr
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// o4frfr
// o3frfr
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// o4frfr
// o3frfr
// 
// 
// 
// 
// 
// 
// 
// o5cd8.c16
// o4cd8.c16
// o5cd8.c16
// 
// o4frfr
// o3frfr
// 
// 
// 
// 
// 
// 
// 
// o4aa
// o3aa
// o4aa
// 
// o4frfr
// o3frfr
// 
// 
// 
// 
// 
// 
// 
// 6o4b-32a32&a&aga8.b-
// 6o3b-32a32&a&aga8.b-
// 6o4b-32a32&a&aga8.b-
// 
// o4frfr
// o3frfr
// 
// 
// 
// 
// 
// 
// 
// o4a4.r8
// o3a4.r8
// o4a4.r8
// 
// o4frfr
// o3frfr
// 
// 
// 
// 
// 
// 
// 
// o4b-g8.o5c16
// o3b-g8.o4c16
// o4b-g8.o5c16
// 
// o4grcr
// o3grcr
// 
// 
// 
// 
// 
// 
//  ----- 60
// a2
// a2
// a2
// 
// o4frer
// o3frer
// 
// 
// 
// 
// 
// 
// 
// o4fd8.g16
// o3fd8.g16
// o4fd8.g16
// 
// o4dro3g
// o3dro2g
// 
// 
// 
// 
// 
// 
// 
// o4c4.r8
// o3c4.r8
// o4c4.r8
// 
// o4cro5cr
// o3cro4cr
// 
// 
// 
// 
// 
// 
// 
// g2
// g2
// g2
// 
// o3b-ro4er
// o2b-ro3er
// 
// 
// 
// 
// 
// 
// 
// o4go5dco4b-
// o3go4dco3b-
// o4go5dco4b-
// 
// o3b-rgr
// o2b-rgr
// 
// 
// 
// 
// 
// 
// 
// o4b-32a32&a16gab-
// o3b-32a32&a16gab-
// o4b-32a32&a16gab-
// 
// o3fra
// o2fra
// 
// 
// 
// 
// 
// 
// 
// a4.r8
// a4.r8
// a4.r8
// 
// o4drfr
// o3drfr
// 
// 
// 
// 
// 
// 
// 
// o4ea
// o3ea
// o4ea
// 
// o4ercr
// o3ercr
// 
// 
// 
// 
// 
// 
// 
// o4ag+8.b16
// o3ag+8.b16
// o4ag+8.b16
// 
// o3bro4er
// o2bro3er
// 
// 
// 
// 
// 
// 
// 
// e2&
// e2&
// e2&
// 
// o3aro4er
// o2aro3er
// 
// 
// 
// 
// 
// 
// 
// e2&
// e2&
// e2&
// 
// o4c+ro3a
// o3c+ro2a
// 
// 
// 
// 
// 
// 
// 
// 3L8o5ed24e24d24c+d
// 3L8o4ed24e24d24c+d
// 3L8o5ed24e24d24c+d
// 5r2
// 5L8o3b-ro4dr
// 5L8o2b-ro3dr
// 
// 
// 
// 
// 
// 
// 
// o4gab-4&
// o3gab-4&
// o4gab-4&
// 
// o4b-rfr
// o3b-rfr
// 
// 
// 
// 
// 
// 
// 
// o4b-a24b-24a24fo5d
// o3b-a24b-24a24fo4d
// o4b-a24b-24a24fo5d
// 
// cr8r4
// cr8r4
// 
// 
// 
// 
// 
// 
//  ----- 74
// c4.r8
// c4.r8
// c4.r8
// L8r8o5a24b-24a24fo6d
// L8r8o4a24b-24a24fo5d
// L8r8o5a24b-24a24fo6d
// 
// 
// 
// 
// 
// 
// 
// L8ro4f24g24f24cb-
// L8ro3f24g24f24cb-
// L8ro4f24g24f24cb-
// c8r8r4
// c8r8r4
// c8r8r4
// 
// 
// 
// 
// 
// 
// 
// a4g32a32g16&g8
// a4g32a32g16&g8
// a4g32a32g16&g8
// o3c8r8
// o3c8r8
// o3c8r8
// 
// 
// 
// 
// 
// 
//  - Second theme last half
// f8@22v15L16o5cdefga
// f8@23v15L16o4cdefga
// f8@35v15L16o5cdefga
// r8@70v15L16o4cdefga    /* Orchestra */
// r8@5 v15L16o3cdefga    /* Tronbone */
// r8@70v15L16o4cdefga    /* Orchestra */
// 
// 
// 
// 
// 
// 
// 
// 6o5b-ab-o6cdefg
// 6o4b-ab-o5cdefg
// 6o5b-ab-o6cdefg
// 6o4b-o5cdefgab-
// 6o3b-o4cdefgab-
// 6o4b-o5cdefgab-
// 
// 
// 
// 
// 
// 
// 
// o6crdr16c16
// o5crdr16c16
// o6crdr16c16
// o6cr8dr16c16
// o4cr8dr16c16
//  L8o3frcr    /* Horn */
// 
// 
// 
// 
// 
// 
//  ----- 80
// o5arar
// o4arar
// o5arar
// o5arar
// o3arar
// o3frcr
// 
// 
// 
// 
// 
// 
// 
// o5b-32a32&a16r16g16ar16b-16
// o4b-32a32&a16r16g16ar16b-16
// o5b-32a32&a16r16g16ar16b-16
// o5b-32a32&a16r16g16ar16b-16
// o3b-32a32&a16r16g16ar16b-16
// o3frcr
// 
// 
// 
// 
// 
// 
// 
// a4.r8
// a4.r8
// a4.r8
// a4.r8
// a4.r8
// o3frcr
// 
// 
// 
// 
// 
// 
// 
// o5b-r8gr16o6c16
// o4b-r8gr16o5c16
// o5b-r8gr16o6c16
// o5b-r8gr16o6c16
// o3b-r8gr16o4c16
// o3grcr
// 
// 
// 
// 
// 
// 
// 
// a4.r8
// a4.r8
// a4.r8
// a4.r8
// a4.r8
// o3frcr
// 
// 
// 
// 
// 
// 
// 
// o5frdr16g16
// o4frdr16g16
// o5frdr16g16
// o5frdr16g16
// o3frdr16g16
// o3dro2gr
// 
// 
// 
// 
// 
// 
// 
// c4.r8
// c4.r8
// c4.r8
// c4.r8
// c4.r8
// o3cro4cr
// 
// 
// 
// 
// 
// 
//  ----- 87
// o5g2
// o4g2
// o5g2
// o5g2
// o3g2
// L8o3b-ro4dr
// 
// 
// 
// 
// 
// 
// 
// o5go6dco5b-
// o4go5dco4b-
// o5go6dco5b-
// o5go6dco5b-
// o3go4dco3b-
// o3b-rgr
// 
// 
// 
// 
// 
// 
// 
// o5b-32a32&a16gab-
// o4b-32a32&a16gab-
// o5b-32a32&a16gab-
// o5b-32a32&a16gab-
// o3b-32a32&a16gab-
// o3frar
// 
// 
// 
// 
// 
// 
// 
// a4.r8
// a4.r8
// a4.r8
// a4.r8
// a4.r8
// o3frdr
// 
// 
// 
// 
// 
// 
// 
// o5ea
// o4ea
// o5ea
// o5ea
// o3ea
// o3ero4cr
// 
// 
// 
// 
// 
// 
// 
// a4g+8.b16
// a4g+8.b16
// a4g+8.b16
// a4g+8.b16
// a4g+8.b16
// o3brer
// 
// 
// 
// 
// 
// 
// 
// 2o7ef+ef+ef+ef+ef+ef+d+16e16
// 2o6ef+ef+ef+ef+ef+ef+d+16e16
// 2o5ef+ef+ef+ef+ef+ef+d+16e16
// 2o6ef+ef+ef+ef+ef+ef+d+16e16
// 2o5ef+ef+ef+ef+ef+ef+d+16e16
// o3arer
// 
// 
// 
// 
// 
// 
//  ----- 94
// 2o7fg+fg+fg+fg+fg+fg+e16f16
// 2o6fg+fg+fg+fg+fg+fg+e16f16
// 2o5fg+fg+fg+fg+fg+fg+e16f16
// 2o6fg+fg+fg+fg+fg+fg+e16f16
// 2o5fg+fg+fg+fg+fg+fg+e16f16
// o3c+ro2ar
// 
// 
// 
// 
// 
// 
// 
// o6g+16r16f+24g+24f+24e+f+
// o5g+16r16f+24g+24f+24e+f+
// o6g+16r16f+24g+24f+24e+f+
// o6g+16r16f+24g+24f+24e+f+
// o3g+16r16f+24g+24f+24e+f+
// o3drf+r
// 
// 
// 
// 
// 
// 
// 
// o5bo6c+d4&
// o4bo5c+d4&
// o5bo6c+d4&
// o5bo6c+d4&
// o3bo6c+d4&
// o3dro2ar
// 
// 
// 
// 
// 
// 
// 
// o6d16r16c+24d24c+24o5ao6f+
// o5d16r16c+24d24c+24o4ao5f+
// o6d16r16c+24d24c+24o5ao6f+
// o6d16r16c+24d24c+24o5ao6f+
// o4d16r16c+24d24c+24o3ao4f+
// o2c+r8r4
// 
// 
// 
// 
// 
// 
// 
// e4.r8
// e4.r8
// e4.r8
// e4.r8
// 3L8ro4e16e16ee
// 3L8ro3e16e16ee
// 
// 
// 
// 
// 
// 
// 
// 5L8ro5a24b24a24eo6d
// 5L8ro4a24b24a24eo5d
// 5L8ro5a24b24a24eo6d
// 5L8ro5a24b24a24eo6d
// 5L8ro3a24b24a24eo4d
// 5o3e8r8r4
// 
// 
// 
// 
// 
// 
// 
// o6c+ro5br
// o5c+ro4br
// o6c+ro5br
// o4c+ro3br
// o4c+ro3br
// o3r4er
// 
// 
// 
// 
// 
// 
//  ----- Main Theme Pattern 2
//  ----- 101
// 5t130@34     /* チェレスタ */
// 5t130@22     /* ハープシコード*/
// 5t130@17     /* Electric Piano */
// 5t130@70     /* Orchestra Brass - 5th row*/
// 5t130@2      /* Horn - 9th row*/
// 5t130@74     /* Cello - Alternate or unison or 9th or 5th row */
// 
// 
// 
// 
// 
// 
//  
// 6q5o5a8aaaede
// 6q5o5a8aaaede
// 6q5o4a8aaaede
// o2arer
// o3arer
// o4rara
// r4
// r4
// c4
// c4
// c4
// c4
// 
// 6o5a8aaabo6c+o5b
// 6o5a8aaabo6c+o5b
// 6o4a8aaabo5c+o4b
// o2arer
// o3arer
// o4rara
// r4
// r4
// c4
// c4
// c4
// c4
// 
// 6o5a8aabag+a
// 6o5a8aabag+a
// 6o4a8aabag+a
// o2arg+r
// o3arg+r
// o4rarg+
// r4
// r4
// c4
// c4
// c4
// c4
//  TR: Vibrate with the base and base+2
// L32o5b>c+<b>c+<b>c+<b>c+<b>c+<b>c+<L16a+b
// L32o5b>c+<b>c+<b>c+<b>c+<b>c+<b>c+<L16a+b
// L32o4b>c+<b>c+<b>c+<b>c+<b>c+<b>c+<L16a+b
// o2f+rer
// o3f+rer
// o4rf+re
// r4
// r4
// c4
// c4
// c4
// c4
// 
// L16o6d8dddo5aga
// L16o6d8dddo5aga
// L16o5d8dddo4aga
// o2drar
// o3drar
// o4rdra
// r4
// r4
// c4
// c4
// c4
// c4
// 
// 6o6d8dddef+e
// 6o6d8dddef+e
// 6o5d8dddef+e
// o2drar
// o3drar
// o4rdra
// r4
// r4
// c4
// c4
// c4
// c4
// 
// 6o6d8dc+o5b8ba
// 6o6d8dc+o5b8ba
// 6o5d8dc+o4b8ba
// o2drg+r
// o3drg+r
// o4rdrg+
// r4
// r4
// c4
// c4
// c4
// c4
//  ----- 108
// L32o5g+a+g+a+g+a+g+a+g+a+g+a+L16f+g+
// L32o5g+a+g+a+g+a+g+a+g+a+g+a+L16f+g+
// L32o4g+a+g+a+g+a+g+a+g+a+g+a+L16f+g+
// o2c+rer
// o3c+rer
// o4rc+re
// r4
// r4
// c4
// c4
// c4
// c4
// 
// L16o5a8aaaede
// L16o5a8aaaede
// L16o4a8aaaede
// o2arer
// o3arer
// o4rara
// r4
// r4
// c4
// c4
// c4
// c4
// 
// 6o5a8aaabo6c+o5b
// 6o5a8aaabo6c+o5b
// 6o4a8aaabo5c+o4b
// o2arer
// o3arer
// o4rara
// r4
// r4
// c4
// c4
// c4
// c4
// 
// 6o5a8aabag+a
// 6o5a8aabag+a
// 6o4a8aabag+a
// o2arg+r
// o3arg+r
// o4rarg+
// r4
// r4
// c4
// c4
// c4
// c4
// 
// L32o5b>c+<b>c+<b>c+<b>c+<b>c+<b>c+<L16a+b
// L32o5b>c+<b>c+<b>c+<b>c+<b>c+<b>c+<L16a+b
// L32o4b>c+<b>c+<b>c+<b>c+<b>c+<b>c+<L16a+b
// o2f+rer
// o3f+rer
// o4rf+re
// r4
// r4
// c4
// c4
// c4
// c4
// 
// 6q5o6e8eeq8edq5cd
// 6q5o6e8eeq8edq5cd
// 6q5o4e8eeq8edq5cd
// o2crgr
// o3cro2gr
// o4rcrg
// r4
// r4
// c4
// c4
// c4
// c4
//  ----- 114
// 6o6e8eeq8edq5cd
// 6o6e8eeq8edq5cd
// 6o4e8eeq8edq5cd
// o2crgr
// o3cro2gr
// o4rcrg
// r4
// r4
// c4
// c4
// c4
// c4
// 
// 6o6q8edq5cdq8edq5cd
// 6o6q8edq5cdq8edq5cd
// 6o4q8edq5cdq8edq5cd
// o2cgcg
// o3co2go3co2g
// o4cgcg
// c4
// c4
// c4
// c4
// c4
// c4
// 
// 6o6q8edq5cdq8edq5cd
// 6o6q8edq5cdq8edq5cd
// 6o4q8edq5cdq8edq5cd
// o2cgcg
// o3co2go3co2g
// o4cgcg
// c4
// c4
// c4
// c4
// c4
// c4
// 
// L32o6ef+ef+ef+ef+ef+ef+ef+ef+
// L32o6ef+ef+ef+ef+ef+ef+ef+ef+
// L32o4ef+ef+ef+ef+ef+ef+ef+ef+
// 6o3e8eee12e12e12
// 6o2e8eee12e12e12
// 6o3e8eee12e12e12
// 
// 
// 
// 
// 2cccccccccccccccc
// 2cccccccccccccccc
// 
// 2o6ef+ef+ef+ef+d+32e32&e16e8
// 2o6ef+ef+ef+ef+d+32e32&e16e8
// 2o4ef+ef+ef+ef+d+32e32&e16e8
// 2o3eeee8e8
// 2o2eeee8e8
// 2o3eeee8e8
// 
// 
// 
// 
// 2cccccccccccccccc
// 2cccccccccccccccc
// 
// o6aro5ar
// o6aro5ar
// o4aro3ar
// o5ero4ar
// o5c+ro4ar
// o2aro3ar
// 
// 
// 
// 
// 
// 
}
