#include "mmlplayer.h"
#include "fssimplewindow.h"
#include "yssimplesound.h"



int main(void)
{
	MMLSegmentPlayer mmlplayer;

	mmlplayer.AddSegment(
		"@2T90L12V12",
		"@2T90L2S0M6000",
		"@2T90L4V12",
		"","","");

	mmlplayer.AddSegment(
		"O3G+O4C+EO3G+O4C+EO3G+O4C+EO3G+O4C+E",
		"O3C+1",
		"O2C+1",
		"","","");

	mmlplayer.AddSegment(
		"O3G+O4C+EO3G+O4C+EO3G+O4C+EO3G+O4C+E",
		"O2B1",
		"O1B1",
		"","","");

	mmlplayer.AddSegment(
		"O3AO4C+EO3AO4C+EO3AO4DF+O3AO4DF+",
		"O2AF+",
		"O1A2F+2",
		"","","");

	mmlplayer.AddSegment(
		"O3G+B+O4F+ O3G+O4C+EO3G+O4C+D+O3F+BO4D+",
		"O2G+1",
		"O1G+1",
		"","","");

	mmlplayer.AddSegment(
		"O3EG+O4C+O3G+O4C+EO3G+O4C+EO3G+O4C+E",
		"O3C+2.O4G+6G+12",
		"O2C+1",
		"","","");

	mmlplayer.AddSegment(
		"O3G+O4D+O4F+O3G+O4D+O4F+O3G+O4D+O4F+O3G+O4D+O4F+",
		"O4G+2.G+6G+12",
		"O2B+1",
		"","","");

	mmlplayer.AddSegment(
		"O3G+O4C+EO3G+O4C+EO3G+O4C+F+O3G+O4C+F+",
		"G+2A2",
		"O3C+2O2F+2",
		"","","");

	mmlplayer.AddSegment(
		"O3G+BO4EO3G+BO4EO3ABO4D+O3ABO4D+",
		"G+2F+4B4",
		"O2B2O2B2",
		"","","");

	mmlplayer.AddSegment(
		"O3G+BO4EO3G+BO4EO3G+BO4EO3G+BO4E",
		"O4E4R4R2",
		"O3E1",
		"","","");

	mmlplayer.AddSegment(
		"O3GBO4EO3GBO4EO3GBO4EO3GBO4E",
		"R4R2G6G12",
		"O3E1",
		"","","");

	mmlplayer.AddSegment(
		"O3GBO4FO3GBO4FO3GBO4FO3GBO4F",
		"G2.G6G12",
		"O3D",
		"","","");

	mmlplayer.AddSegment(
		"O3GO4CEO3GO4CEO3GO4C+EO3F+O4C+E",
		"G.F+4",
		"O3C4O2B4A+2",
		"","","");

	mmlplayer.AddSegment(
		"O3F+BO4DO3F+BO4DO3GBO4C+O3EBO4C+",
		"F+G4E4",
		"O2BE4G4",
		"","","");

	mmlplayer.AddSegment(
		"O3F+BO4DO3F+BO4DO3F+A+O4C+O3F+A+O4C+",
		"F+2F+2",
		"O2F+2F+2",
		"","","");

	mmlplayer.AddSegment(
		"O3BO4DF+O3BO4DF+O3BO4D+F+O3BO4D+F+",
		"R4R2B4",
		"O2B1",
		"","","");

	mmlplayer.AddSegment(
		"O3BO4EGO3BO4EGO3BO4EGO3BO4EG",
		"O5C2.O4A+4",
		"O2BO3EGE",
		"","","");

	mmlplayer.AddSegment(
		"O3BO4D+F+O3BO4D+F+O3BO4D+F+O3BO4D+F+",
		"B2.B4",
		"O2B1",
		"","","");

	mmlplayer.AddSegment(
		"O3BO4EGO3BO4EGO3BO4EGO3BO4EG",
		"O5C.O4A+4",
		"O2BO3EGE",
		"","","");

	mmlplayer.AddSegment(
		"O3BO4D+F+O3BO4D+F+O3BO4DE+O3BO4DE+",
		"O4B2B2",
		"O2B2G+2",
		"","","");

	mmlplayer.AddSegment(
		"O3BO4C+G+O3BO4C+G+O3AO4C+F+O3AO4C+F+",
		"B2A2",
		"O2E+2F+2",
		"","","");

	mmlplayer.AddSegment(
		"O3GBO4DO3GBO4DO3F+AO4D+O3F+AO4D+",
		"GF+",
		"O2B2B+",
		"","","");

	mmlplayer.AddSegment(
		"O3C+F+AC+F+AC+F+G+C+E+G+",
		"C+C+4C+4",
		"O2C+2C+2",
		"","","");

	mmlplayer.AddSegment(
		"O3F+AO4C+O3AO4C+F+C+F+AC+F+A",
		"R2R4O5C+6C+12",
		"O3F+1",
		"","","");

	mmlplayer.AddSegment(
		"C+G+BC+G+BC+G+BC+G+B",
		"C+2.C+6C+12",
		"O3E+1",
		"","","");

	mmlplayer.AddSegment(
		"C+F+AC+F+AC-F+AC+F+A",
		"C+2O4B+4O5C+4",
		"O3F+2D+C+",
		"","","");

	mmlplayer.AddSegment(
		"D+F+G+D+F+G+D+F+G+D+F+G+",
		"D+2.D+4",
		"O3C-2.C-",
		"","","");

	mmlplayer.AddSegment(
		"EG+O5C+O4EG+O5C+O4D+F+AC+EA+",
		"E2D+4C+4",
		"O3C+2O2F+4F+4",
		"","","");

	mmlplayer.AddSegment(
		"O4B+O3B+O4D+G+O3B+O4D+AO3B+O4D+F+O3B+O4D+",
		"O2F+1",
		"O1F+1",
		"","","");

	mmlplayer.AddSegment(
		"R12O3B+O4D+O3G+B+O4D+O3AB+O4D+O3G+B+O4D+",
		"O2G+1",
		"O1G+1",
		"","","");

	mmlplayer.AddSegment(
		"O3EO4EG+O5C+O4EG+O5EO4EG+O5C+O4EG+",
		"O2G+1",
		"O1G+1",
		"","","");

	mmlplayer.AddSegment(
		"R12O3EG+O4C+O3EG+O4EO3EG+O4C+O3EG+",
		"O2G+1",
		"O1G+1",
		"","","");

	mmlplayer.AddSegment(
		"O3D+AF+B+AO4D+O3B+O4F+D+AF+B+",
		"O2G+1",
		"O2G+1",
		"","","");

	mmlplayer.AddSegment(
		"O3EO4C+O3G+O4EC+G+EO5C+O4G+O5EC+O4G+",
		"O2G+1",
		"O1G+1",
		"","","");

	mmlplayer.AddSegment(
		"C+F+EA+F+O5C+O4A+O5EC+F+EA+",
		"O2G+1",
		"O1G+1",
		"","","");

	mmlplayer.AddSegment(
		"O4F+B+AO5D+O4B+O5F+D+AF+B+AO6D+",
		"O2G+1",
		"O1G+1",
		"","","");

	mmlplayer.AddSegment(
		"O5B+F+AD+F+O4B+O5D+O4AB+F+AD+",
		"O2G+1",
		"O1G+1",
		"","","");

	mmlplayer.AddSegment(
		"F+O3B+O4D+O3AB+F+AD+F+C+F+A",
		"O2G+1",
		"O1G+1",
		"","","");

	mmlplayer.AddSegment(
		"O2B+O3F+G+AG+F+D+F+AC+F+A",
		"O2G+1",
		"O1G+1",
		"","","");

	mmlplayer.AddSegment(
		"O2B+O3F+G+AG+F+DF+AC+F+A",
		"O2G+1",
		"O1G+1",
		"","","");

	mmlplayer.AddSegment(
		"O2B+O3F+G+AG+F+C+EO4C+O3C+EO4C+",
		"O2G+2A2",
		"O1G+2A2",
		"","","");

	mmlplayer.AddSegment(
		"O3D+F+O4C+O3D+F+O4C+O3D+F+B+O3D+F+B+",
		"O2F+2G+2",
		"O1F+2G+2",
		"","","");

	mmlplayer.AddSegment(
		"O3EG+O4C+O3G+O4C+EO3G+O4C+EO3G+O4C+E",
		"O3C+2R4O4G+6G+12",
		"O2G+1",
		"","","");

	mmlplayer.AddSegment(
		"O3G+O4D+F+O3G+O4D+F+O3G+O4D+F+O3G+O4D+F+",
		"O4G+2.G+6G+12",
		"O2B+1",
		"","","");

	mmlplayer.AddSegment(
		"O3G+O4C+EO3G+O4C+EO3AO4C+F+O3AO4C+F+",
		"G+2A2",
		"O3C+2O2F+2",
		"","","");

	mmlplayer.AddSegment(
		"O3G+BO4EO3G+BO4EO3ABO4D+O3ABO4D+",
		"O4G+2F+4B4",
		"O2B2B2",
		"","","");

	mmlplayer.AddSegment(
		"O3G+BO4EO3BO4EG+O3BO4EG+O3BO4EG+",
		"O4E4R4R4B6B12",
		"O3E1",
		"","","");

	mmlplayer.AddSegment(
		"O3BO4F+AO3BO4F+AO3BO4F+AO3BO4F+A",
		"O4B2.B6B12",
		"O3D+1",
		"","","");

	mmlplayer.AddSegment(
		"O3BO4EG+O3BO4EG+O3B+O4F+G+C+EG+",
		"B2B+4O5C+4",
		"O3E2DC+",
		"","","");

	mmlplayer.AddSegment(
		"O4D+F+G+O4D+F+G+EG+O5C+O4EG+O5C+",
		"O5D+2E2",
		"O2B+2O3C+2",
		"","","");

	mmlplayer.AddSegment(
		"O4DF+ADF+AO3B+O4F+G+O3B+O4F+G+",
		"O5D2O4B+2",
		"O2F+2G+2",
		"","","");

	mmlplayer.AddSegment(
		"O4C+EG+C+EG+C+E+G+C+E+G+",
		"O5C+2.C+4",
		"O3C+1",
		"","","");

	mmlplayer.AddSegment(
		"O4C+F+AC+F+AC+F+AC+F+A",
		"O5D.O4B+4",
		"O3C+F+AF+",
		"","","");

	mmlplayer.AddSegment(
		"C+E+G+C+E+G+C+E+G+C+E+G+",
		"O5C+2.C+4",
		"O3C+1",
		"","","");

	mmlplayer.AddSegment(
		"O4C+F+AC+F+AC+F+AC+F+A",
		"O5D2.O4B+4",
		"O3C+F+AF+",
		"","","");

	mmlplayer.AddSegment(
		"C+E+G+C+E+G+C+F+AC+F+A",
		"O5C+C+",
		"O3C+2O2F+2",
		"","","");

	mmlplayer.AddSegment(
		"O3BO4F+AO3BO4F+AO3BO4F+AO3BO4EG+",
		"O4B.B4",
		"O3D+2.E",
		"","","");

	mmlplayer.AddSegment(
		"O3AO4EG+O3AO4D+F+O3G+O4D+F+O3G+O4C+E",
		"O4A4A4G+4G+4",
		"O3C+D+O2B+O3C+",
		"","","");

	mmlplayer.AddSegment(
		"O3F+O4C+D+O3F+O4C+D+O3G+O4C+D+O3AO4C+D+",
		"O4F+G+4A4",
		"O2A2G+F+",
		"","","");

	mmlplayer.AddSegment(
		"O3G+O4C+EO3G+O4C+EO3F+B+O4D+O3F+B+O4D+",
		"G+G+",
		"G+2G+2",
		"","","");

	mmlplayer.AddSegment(
		"O3EG+O4C+O3G+O4C+EO3G+O4C+EO3G+O4C+E",
		"O4C+4R4R4O2G+6G+12",
		"O2G+2.",
		"","","");

	mmlplayer.AddSegment(
		"O3G+O4D+F+O3G+O4D+F+O3G+O4D+F+O3G+O4D+F+",
		"O2G+2.G+6G+12",
		"O1A+1",
		"","","");

	mmlplayer.AddSegment(
		"O3G+O4EC+G+EO5C+O4G+O5EC+G+EC+",
		"O2G+2.G+6G+12",
		"O1A+1",
		"","","");

	mmlplayer.AddSegment(
		"O4B+O5D+O4AB+F+AD+F+O3AAG+F+",
		"O2G+2.G+6G+12",
		"O1G+2.O3B+4",
		"","","");

	mmlplayer.AddSegment(
		"O4C+EC+G+EO5C+O4G+O5EC+G+EC+",
		"O2G+2.G+6G+12",
		"O2C+1",
		"","","");

	mmlplayer.AddSegment(
		"O4B+O5D+O4AB+F+AD+F+O3AAG+F+",
		"O2G+2.G+6G+12",
		"O1G+2.O3B+",
		"","","");

	mmlplayer.AddSegment(
		"O3EG+O4C+EC+O3G+C+EG+O4C+O3G+E",
		"O2G+2O3C+2",
		"O2C+1",
		"","","");

	mmlplayer.AddSegment(
		"O2G+O3C+EG+EC+O2G+O3C+O2G+EG+E",
		"O3G+2",
		"O3C+2",
		"","","");

	mmlplayer.AddSegment(
		"R2O4C+2",
		"R2O3E2",
		"O2C+2O3C+2",
		"","","");

	mmlplayer.AddSegment(
		"V10O4C+1",
		"V10O3E1",
		"V10O3C+1",
		"","","");


	YsSoundPlayer player;
	player.Start();

	YsSoundPlayer::Stream stream;
	player.StartStreaming(stream);

	YsSoundPlayer::SoundData nextWave;
	auto rawWave=mmlplayer.GenerateWave(100);  // Create for next 100ms
	nextWave.CreateFromSigned16bitStereo(YM2612::WAVE_SAMPLING_RATE,rawWave);

	FsOpenWindow(0,0,800,600,0);
	for(;;)
	{
		FsPollDevice();
		auto key=FsInkey();
		if(FSKEY_ESC==key)
		{
			break;
		}

		if(YSTRUE==player.StreamPlayerReadyToAcceptNextSegment(stream,nextWave))
		{
			player.AddNextStreamingSegment(stream,nextWave);
			auto rawWave=mmlplayer.GenerateWave(100);  // Create for next 100ms
			nextWave.CreateFromSigned16bitStereo(YM2612::WAVE_SAMPLING_RATE,rawWave);
		}
	}

	player.End();

	return 0;
}
