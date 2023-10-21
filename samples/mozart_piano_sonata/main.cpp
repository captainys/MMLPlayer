#include <iostream>
#include <string>
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
	YsSoundPlayer::StreamingOption streamOpt;
	streamOpt.ringBufferLengthMillisec=4000;
	player.StartStreaming(stream,streamOpt);

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

		if(YSTRUE==player.StreamPlayerReadyToAcceptNextSegment(stream,nextWave))
		{
			player.AddNextStreamingSegment(stream,nextWave);
			auto rawWave=mmlplayer.GenerateWave(100);  /// Create for next 100ms
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

const std::string MML[][12]=
{
	{
		"t150 @2",
		"t150 @2",
		"t150 @2",
		"t150 @2",
		"t150 @2",
		"t150 @2"
	},
// ----- BLOCK   2 -----
	{
		"o5d8.o4b16",
		"r4",
		"r4",
		"r4",
		"r4",
		"r4",
	},
// -----
	{
		"l4o5dr4o4g",
		"l8o3gbo4do3bo4do3b",
		"r4r2",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"o4f+r4o5a8.f+16",
		"o3ao4cdcdc",
		"r4r2",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"o5a4r4c4",
		"o3f+ao4do3ao4do3a",
		"r4r2",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"o4br4o5g8.f+16",
		"o3gbo4do3bo3g4",
		"r4r2",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"o5f+8e8e4g8.e16",
		"o4g2r4",
		"o4c2r4",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"o5e8d8d4g8.d16",
		"o4g2r4",
		"o3b2r4",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// ----- End of the first line
	{
		"o5ddd",
		"l4o4co3ba",
		"l4o3agf+",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l16o5def+gabo6cdco5bag",
		"o3br4g",
		"o3gr4e",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"o5f+edco4bo5do4bgao5co4af+",
		"r4go4c",
		"r4d2",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"o4g4r4g8.f+16",
		"o3bo2gr4",
		"o3gr2",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"o4f+8e8e4g8.e16",
		"o3g2r4",
		"o3c2r4",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// ----- End of the second line
	{
		"o4e8d8d4o5g8.d16",
		"o3g2r4",
		"o2b2r4",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"o5d4d4d4",
		"o4co3ba",
		"o3bag",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l16o5def+gabo6cdco5bag",
		"o3br4g",
		"o3gr4e",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"o5f+edco4bo5do4bgao5co4af+",
		"r4go4c",
		"r4d2",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"o4g4r8o3gbao4co3bo4d",
		"o3b4r8o2g8a8b8",
		"o3g4r8o1g8a8b8",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// ----- End of the third line
	{
		"o4c4r8l16o3ao4co3bo4dce",
		"o3c4r8o2a8b8o3c8",
		"o2c4r8o1a8b8o2c8",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"o4d4r8o3bo4dcedf",
		"l8o3d4r8o2bo3cd",
		"l8o2d4r8o1bo2cd",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"o4efdecedfegf+a",
		"o3edcdef+",
		"o2edcdef+",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"o4gaf+gegf+agbao5c",
		"o3gf+ef+ga",
		"o2gf+ef+ga",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// ----- End of the fourth line
	{
		"o4bo5co4abgbao5co4bo5dc+e",
		"o3bagabo4c+",
		"o2bagabo3c+",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l4o5do4dr4",
		"o4d4o3d4",
		"o3d4o2d4",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"r8o5agf+8&",
		"l8o4f+aeada",
		"r4r2",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"o5f+8e4d4c+8",
		"o4c+ao3bo4ao3ao4a",
		"r4r2",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"o5e16d8.f+16e8.g16f+8.",
		"o3bo4ac+ada",
		"r4r2",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// ----- End of the fifth line
	{
		"o5a8.g16e4r4",
		"o4eac+ao3ao4a",
		"r4r2",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"r8o5a16b16g8g16a16f+8f+16g16",
		"l16f+af+aeaeadada",
		"r4r2",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"e8e16f+16d8d16e16c+8c+16e16",
		"c+ac+ao3bo4ao3bo4ao3ao4ao3ao4a",
		"r4r2",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l16o5def+def+gef+gaf+",
		"o3bo4ao3bo4ac+ac+adada",
		"r4r2",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// ----- End of the first page
	{
		"l16o5agage4r4",
		"l16o4eaeac+ac+ao3agf+e",
		"r4r2",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l8ro5dc+dgf+",
		"l8rrrro5ed",
		"l8o3d4r4o4c+d",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"r8dc+dba",
		"r8r8r8r8o5gf+",
		"o3d4r4o4c+d",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"r8dc+do6dc+",
		"r8r8r8r8o5ba",
		"o3d4r4o4g+a",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"o6co5bg+af+g",
		"o5agfee-d",
		"o4f+gdc+co3b",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// ----- End of first line
	{
		"l16o5gec+o4ag+abao5geco4a",
		"o3a4r4o4e4",
		"r4r4o3a4",
		"r4r4o3g4",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"o5af+do4ag+abao5af+dc",
		"o4d4r4o4d4",
		"o3a4r4a4",
		"o3f+4r4f+4",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"o4bo5egbbagf+f+edc+",
		"o4e4f+4g4",
		"o3b4o4d4e4",
		"o3g4o3a2",
		"r4r2",
		"r4r2",
	},
// ----- End of the second line
	{
		"l8r8o5dc+do6dc+",
		"l8o4f+4r8r8o5ba",
		"l8o4d4r4g+a",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// ----
	{
		"o6co5bg+af+g",
		"o5agfee-d",
		"o4f+gdc+co3b",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l16o5gec+o4ag+abao5gec+o4a",
		"l8o3a4r8o4eee",
		"l8r4r8o4c+o3aa",
		"l8r4r8o3agg",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"o5af+do4ag+abao5af+do4a",
		"o4d4r8ddd",
		"o3a4r8aaa",
		"o3f+4r8f+f+f+",
		"r4r2",
		"r4r2",
	},
// ----- End of the third line
	{
		"l16o4bo5egbbagf+f+edc+",
		"l4o4ef+g",
		"l4o3bo4de",
		"l4o3ga2",
		"r4r2",
		"r4r2",
	},
// ----- Short notes may not be possible in FM-7
	{
		"l16o5d8df+egf+ag8&g16&g16f+32g32",
		"l4o4f+r8l16o3ao4c+o3bo4dc+e",
		"l4o4d4r2",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l16o5f+8df+egf+ag8&g16&g16f+32g32",
		"l16o4d4r8o3ao4c+o3bo4dce",
		"r4r2",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l4r8o5bag8&",
		"l4o5f+ed",
		"l4o4dc+o3b",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// ----- End of the fourth line
	{
		"l4o5g8f+ed8",
		"l4o5c+o4ba",
		"l4o3agf+",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l8o5d+er8gec+",
		"l8o4b4r8bge",
		"l4o3gca",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l16r16o5g+a+br16bg+ar16ef+g",
		"l4o5f+ed",
		"l4o4dc+o3b",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l16r16o5ge+f+r16c+d+er16ec+d",
		"l4o5c+o4ba",
		"l4o3agf+",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// ----- End of the fifth line
	{
		"l16o5egbgf+adf+egc+e",
		"l4o3gao2a",
		"r4r2",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l8o5d4r8co4bo5c+",
		"l8r4r8o4agg",
		"l8r4r8o4f+r8e",
		"l16o3do4dc+do3do4dc+do3do4dc+d",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l8o5d4r8o6cdc+",
		"l8o4a4r8o5agg",
		"l8o4f+4r8o5f+r8e",
		"l16o3do4dc+do3do4dc+do3do4dc+d",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l4o6dr4",
		"l4o5ar4",
		"l4o5f+4r4",
		"l4o3dr4",
		"r4r4",
		"r4r4",
	},
// ----- End of the second page (Repeat)
	{
		"r4",
		"r4",
		"r4",
		"r4",
		"r4",
		"r4",
	},
// -----
	{
		"l4o5g+32a32&a16&a8r4r4",
		"l4o4r4f+f+",
		"l4o4r4dd",
		"r2r4",
		"r2r4",
		"r2r4",
	},
// -----
	{
		"l16o5gf+edc+4r4",
		"l4o4r4gg",
		"l4o4r4ee",
		"r2r4",
		"r2r4",
		"r2r4",
	},
// -----
	{
		"o5d32o6d32&d16&d8r4r4",
		"o4r4a4a4",
		"o4r4f+4f+4",
		"r2r4",
		"r2r4",
		"r2r4",
	},
// -----
	{
		"l16o5e4&ef+gf+agf+e",
		"l4r4o4bo5c+",
		"l4r4o4ga",
		"r2r4",
		"r2r4",
		"r2r4",
	},
// -----
	{
		"l16o5g+ag+ao6c32o5a32&a16&a8r4",
		"l4r4o3f+f+",
		"l4r4o3dd",
		"r2r4",
		"r2r4",
		"r2r4",
	},
// -----
	{
		"l16o5agf+ed4c+8r8",
		"l4r4o3gg",
		"l4r4o3ee",
		"r2r4",
		"r2r4",
		"r2r4",
	},
// ----- End of the first line
	{
		"l16o6c+dc+de32d32&d16&d8r4",
		"l4r4o3aa",
		"l4r4o3f+f+",
		"r2r4",
		"r2r4",
		"r2r4",
	},
// -----
	{
		"l16o6d32o5e32&e16&e8&ed+ef+agf+e",
		"l4r4o3bo4c+",
		"l4r4o3ga",
		"r2r4",
		"r2r4",
		"r2r4",
	},
// -----
	{
		"l16o5d4r8o5e24d24c+24d8d8",
		"l8o3do4ddddd",
		"r2r4",
		"r2r4",
		"r2r4",
		"r2r4",
	},
// -----
	{
		"l8o5bagf+ed",
		"l8o5gf+edco4b",
		"l8o4dddddd",
		"r2r4",
		"r2r4",
		"r2r4",
	},
// -----
	{
		"l8o5c4r8d24c24o4b24o5cc",
		"l8o4a4r4r4",
		"l8o3do4ddddd",
		"r2r4",
		"r2r4",
		"r2r4",
	},
// ----- End of the second line
	{
		"l8o5agf+edc",
		"l8o5f+edco4ba",
		"l8o4dddddd",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l8o4b4r8o5c24o4b24a24bb",
		"l8o4g4r4r4",
		"l8o3do4ddddd",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l8o5gf+edco4b",
		"l8o4bao5co4bag",
		"l8o4dddddd",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l8o4a4r8d16e16f+g",
		"o4f+4r4r4",
		"l8o4d4r8o3d16e16f+g",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l8o4a4r8f+16g16ab",
		"l8o3a4r8f+16g16ab",
		"r4r2",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l16o5c4r8o6co5ba8ag",
		"o4c4r4r4",
		"r4r2",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// ----- End of the third line
	{
		"l16o5f+8f+ed8dc+d8.o4b",
		"r4r2",
		"r4r2",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"o5d4r4o4c4",
		"l8o3gbo4do3bo4do3b",
		"r4r2",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"o4f+4r4o5a8.f+16",
		"l8o3ao4cdcdc",
		"r4r2",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"o5a4r4c4",
		"l8o3f+ao4do3ao4do3a",
		"r4r2",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"o4b4r4o5e8.c16",
		"l8r8o4dco3br4",
		"l8o3gbag+r4",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l4o5er4o4a",
		"l8o3ao4cecec",
		"r4r2",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// ----- End of the fourth line
	{
		"l4g+r4o5b8.g+16",
		"l8o3bo4deded",
		"r4r2",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l4o5br4d",
		"l8o3g+bo4eo3bo4eo3b",
		"r4r2",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l4o5cr4o6c8.o5a16",
		"l8r8o4edcr4",
		"l8o3ao4co3bar4",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l4o5g8f8ff",
		"l8o3ao4cfo3abo4g",
		"r4r2",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l4o5d+eo6c8.o5g16",
		"l8o4cgo5co4geg",
		"r4r2",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l16o5e4egf+gagf+e",
		"l8o4cegece",
		"r4r2",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// ----- End of the fourth line
	{
		"l16o5c+8d8r8o3gbao4co3bo4d",
		"l8o4g4r8o2gab",
		"l8o3b4r8o1gab",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l16o4c4r8o3ao4co3bo4dce",
		"l8o3c4r8o2abo3c",
		"l8o2c4r8o1abo2c",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l16o4d4r8o3bo4do4cedf",
		"l8o3d4r8o2bo3cd",
		"l8o2d4r8o1bo2cd",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l16o4efdecedfegf+a",
		"l8o3edcdef+",
		"l8o2edcdef+",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// ----- End of the fifth line
	{
		"l16o4gaf+gegf+agbao5c",
		"l8o3gf+ef+ga",
		"l8o2gf+ef+ga",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l16o4bo5co4abgbao5co4bo5dc+e",
		"l8o3bagabo4c+",
		"l8o2bagabo3c+",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l4o5do4dr4",
		"l4o4do3dr4",
		"l4o3do2dr4",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l4r8o5dco4b8&",
		"l8o3bo4do3ao4do3go4d",
		"r4r2",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l4o4b8agf+8",
		"l8o3f+o4do3eo4do3do4d",
		"r4r2",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// ----- End of the third page
	{
		"o4a16g8.b16a8.o5c16o4b8.",
		"l8o3eo4do3f+o4do3go4d",
		"r4r2",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"o5d8.c16o4a4r4",
		"l8o3ao4do3f+o4do3do4d",
		"r4r2",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l16r8o6dec8cdo5b8bo6c",
		"l16o4bo5do4bo5do4ao5do4ao5do4go5do4go5d",
		"r4r2",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l16o5a8abg8gaf+8f+a",
		"l16o4f+o5do4f+o5do4eo5do4eo5do4do5do4do5d",
		"r4r2",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// ----- End of the first line
	{
		"l16o5gabgabo6co5abo6cdo5b",
		"l16o4eo5do4eo5do4f+o5do4f+o5do4go5do4go5d",
		"r4r2",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l16o6dcdco5a4r4",
		"l16o4ao5do4ao5do4f+o5do4f+o5do4dco3ba",
		"r4r2",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l8o4r8gf+go5co4b",
		"l8r4r4o4ag",
		"l4o3gr4f+8g8",
		"o2g4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l8r8o4gf+go5ed",
		"l8r2o5co4b",
		"o2g4r4o3f+8g8",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l8r8o4gf+go5gf+",
		"l8r2o5ed",
		"l8o2g4r4o4c+d",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// ----- End of the second line
	{
		"l8o5fec+do4bo5c",
		"l8o5dco4b-aa-g",
		"l8o3bo4co3gf+fe",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l16o5co4af+dc+dedo5co4af+d",
		"o3d4r4a4",
		"o3r2d4",
		"o3r2c4",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l16o5do3bgdc+dedo5do3bgd",
		"o3g4r4g4",
		"o3d4r4d4",
		"o2b4r4b4",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l16o4eao5ceedco4bbagf+",
		"l4o3abo4c",
		"l4o3ega",
		"l4o3cd2",
		"r4r2",
		"r4r2",
	},
// ----- End of the third line
	{
		"l8r8o4gf+go5gf+",
		"l8r2o5ed",
		"l8o3br4o4c+8d8",
		"o3g4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l8o5fecdo4bo5c",
		"l8o5dco4b-aa-g",
		"l8o3ao4co3gf+fe",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l16o6co5af+dc+dedo6co5af+d",
		"l8o3d4r8o4aaa",
		"l8r4r8o4f+dd",
		"l8r4r8o4dcc",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l16o6do5bgdc+dedo6do5bgd",
		"l8o4g4r8ggg",
		"l8o4d4r8ddd",
		"l8o3b4r8bbb",
		"r4r2",
		"r4r2",
	},
// ----- End of the fourth line
	{
		"l16o5eao6ceedco5bbagf+",
		"l4o4abo5c",
		"l4o4ega",
		"l4o4cd2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l16o5g8gbao6co5bo6dc8&c16o5a32o6c32",
		"l16o4b4r8df+egf+a",
		"o4g4r2",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l16o5b8o4gbao5co4bo5dc8&c16o4b32o5c32",
		"l16o4g4r8o3df+egf+a",
		"r4r2",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l4r8o5edc8&",
		"l4o4bag",
		"l4o3gf+e",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// ----- End of the fifth line
	{
		"l4o5c8o4bag8",
		"l4o4f+ed",
		"l4o3dco2b",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l8o4g+ar8o5co4ba",
		"l8o4er8agf+",
		"l4o3co2ao3d",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l16r16o6c+d+er16o6ec+dr16o5abo6c",
		"l4o5bag",
		"l4o4gf+e",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l16r16o6co5a+br16o5f+g+ar16o5af+g",
		"l4o5f+ed",
		"l4o4dco3b",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// ----- End of the sixth line
	{
		"l16o5egeco4bo5do4gbao5co4f+a",
		"l4o4cdo3d",
		"r4r2",
		"r4r2",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l8o4g4r8bo5cc",
		"l8r4r8o4fga",
		"l8r4r8o4def+",
		"l16o2go3gf+go2go3gf+go2go3gf+g",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"l8o4b4r8o5fef+",
		"l8o4g4r8o5dcc",
		"l8r4r8o4br8a",
		"l16o2go3gf+go2go3gf+go2go3gf+g",
		"r4r2",
		"r4r2",
	},
// -----
	{
		"o5g4r4",
		"o5d4r4",
		"o4b4r4",
		"o2g4r4",
		"r4r2",
		"r4r2",
	},
// ----- Fin
};

void SetUpMML(MMLSegmentPlayer &player)
{
// At this time, only first six channels.  Eventually I'm going to make it more channels.
	for(int i=0; i<sizeof(MML)/sizeof(MML[0]); ++i)
	{
		player.AddSegment(
			MML[i][0],
			MML[i][1],
			MML[i][2],
			MML[i][3],
			MML[i][4],
			MML[i][5]
		);
	}
}
