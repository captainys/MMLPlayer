#include <iostream>
#include <algorithm>
#include <cstring>
#include "mmlplayer.h"



void MMLPlayer::FMInst::Clear(void)
{
	instName="";
	DT_MULTI[0]=0;
	DT_MULTI[1]=0;
	DT_MULTI[2]=0;
	DT_MULTI[3]=0;
	TL[0]=0;
	TL[1]=0;
	TL[2]=0;
	TL[3]=0;
	KS_AR[0]=0;
	KS_AR[1]=0;
	KS_AR[2]=0;
	KS_AR[3]=0;
	AMON_DR[0]=0;
	AMON_DR[1]=0;
	AMON_DR[2]=0;
	AMON_DR[3]=0;
	SR[0]=0;
	SR[1]=0;
	SR[2]=0;
	SR[3]=0;
	SL_RR[0]=0;
	SL_RR[1]=0;
	SL_RR[2]=0;
	SL_RR[3]=0;
	FB_CNCT=0;
	LR_AMS_PMS=0;
}



////////////////////////////////////////////////////////////



void MMLPlayer::Channel::Clear(void)
{
	// Segment player expects tempo, octave, noteLength inherited from the previous segment.
	// Don't clear them.
	// tempo=TEMPO_DEFAULT;
	// octave=OCTAVE_DEFAULT;
	// noteLength=NOTE_LENGTH_DEFAULT;

	ptr.Clear();
	mml="";
}

bool MMLPlayer::Channel::PlayDone(void) const
{
	return mml.size()<=ptr.pos && INFINITE==ptr.toneEndAtInMicrosec;
}



////////////////////////////////////////////////////////////



void MMLPlayer::PlayPointer::Clear(void)
{
	pos=0;
	keyOffAtInMicrosec=INFINITE;
	toneEndAtInMicrosec=INFINITE;
}



////////////////////////////////////////////////////////////



void MMLPlayer::MMLError::Clear(void)
{
	chNum=0;
	errorCode=0;
}



////////////////////////////////////////////////////////////



MMLPlayer::MMLPlayer()
{
	ym2612.state.volume=MMLPLAYER_VOLUME_DEFAULT;
	Clear();
}

void MMLPlayer::Clear(void)
{
	ClearMML();
	LoadFMB(defaultFMB);
	for(int chNum=0; chNum<NUM_CHANNELS; ++chNum)
	{
		mute[chNum]=false;
		ReapplyEnvelope(chNum);
	}
}

bool MMLPlayer::LoadFMB(const unsigned char fmb[6152])
{
	fmbName="";

	for(int i=0; i<8 && 0!=fmb[i]; ++i)
	{
		fmbName.push_back((char)fmb[i]);
	}

	fmb+=8;
	for(auto &ist : inst)
	{
		ist.Clear();
		for(int i=0; i<8 && 0!=fmb[i]; ++i)
		{
			ist.instName.push_back((char)fmb[i]);
		}

		ist.DT_MULTI[0]=fmb[8];
		ist.DT_MULTI[1]=fmb[9];
		ist.DT_MULTI[2]=fmb[10];
		ist.DT_MULTI[3]=fmb[11];
		ist.TL[0]      =fmb[12];
		ist.TL[1]      =fmb[13];
		ist.TL[2]      =fmb[14];
		ist.TL[3]      =fmb[15];
		ist.KS_AR[0]   =fmb[16];
		ist.KS_AR[1]   =fmb[17];
		ist.KS_AR[2]   =fmb[18];
		ist.KS_AR[3]   =fmb[19];
		ist.AMON_DR[0] =fmb[20];
		ist.AMON_DR[1] =fmb[21];
		ist.AMON_DR[2] =fmb[22];
		ist.AMON_DR[3] =fmb[23];
		ist.SR[0]      =fmb[24];
		ist.SR[1]      =fmb[25];
		ist.SR[2]      =fmb[26];
		ist.SR[3]      =fmb[27];
		ist.SL_RR[0]   =fmb[28];
		ist.SL_RR[1]   =fmb[29];
		ist.SL_RR[2]   =fmb[30];
		ist.SL_RR[3]   =fmb[31];
		ist.FB_CNCT    =fmb[32];
		ist.LR_AMS_PMS =fmb[33];

		fmb+=48;
	}
	return true;
}

void MMLPlayer::ClearMML(void)
{
	timeInMicrosec=0;
	for(auto &ch : channels)
	{
		ch.Clear();
	}
}

bool MMLPlayer::AddMML(unsigned int ch,std::string mml)
{
	if(ch<NUM_CHANNELS)
	{
		channels[ch].mml+=mml;
		return true;
	}
	return false;
}

std::vector <unsigned char> MMLPlayer::GenerateWave(uint64_t timeInMillisec)
{
	lastError.Clear();

	const uint64_t totalNumSamples=YM2612::WAVE_SAMPLING_RATE*timeInMillisec/MILLI;
	const uint64_t bufSize=4*totalNumSamples;
	std::vector <unsigned char> wave;

	wave.resize(bufSize);
	std::memset(wave.data(),0,bufSize);

	uint64_t wavePtr=0;
	while(wavePtr<bufSize)
	{
		// Play up to the next cue point.
		for(int chNum=0; chNum<NUM_CHANNELS; ++chNum)
		{
			auto &ch=channels[chNum];
			if(ch.ptr.keyOffAtInMicrosec<=timeInMicrosec)
			{
				if(chNum<3)
				{
					ym2612.WriteRegister(0,YM2612::REG_KEY_ON_OFF,chNum);
				}
				else
				{
					ym2612.WriteRegister(0,YM2612::REG_KEY_ON_OFF,(chNum+1));
				}
				ch.ptr.keyOffAtInMicrosec=INFINITE;
			}
			if(ch.ptr.toneEndAtInMicrosec<=timeInMicrosec || ch.ptr.toneEndAtInMicrosec==INFINITE)
			{
				ch.ptr.toneEndAtInMicrosec=INFINITE;
				if(true!=InterpretMML(chNum))
				{
					wave.clear();
					return wave;
				}
			}
		}


		// Break if no more channels are playing.
		// End of segment needs to be checked before generating a wave.
		// After the last MML interpretation, all channels next cue point is INFINITE away.
		// So is the nearest next cue point.
		// Which makes wave generator fill the buffer all the way, unless the loop breaks before the wave generation.
		unsigned int nPlaying=0;
		for(auto &ch : channels)
		{
			if(true!=ch.PlayDone())
			{
				++nPlaying;
				break;
			}
		}
		if(0==nPlaying)
		{
			break;
		}


		// Find next cue point.
		uint64_t nextCueInMicrosec=INFINITE;
		for(auto &ch : channels)
		{
			nextCueInMicrosec=std::min(nextCueInMicrosec,ch.ptr.keyOffAtInMicrosec);
			nextCueInMicrosec=std::min(nextCueInMicrosec,ch.ptr.toneEndAtInMicrosec);
		}

		// Generate wave up to the next cue point or the length of the wave.
		uint64_t dt=nextCueInMicrosec-timeInMicrosec;
		uint64_t numSamples=YM2612::WAVE_SAMPLING_RATE;
		numSamples*=dt;
		numSamples/=MICRO;
		if(0==numSamples)
		{
			numSamples=1;
		}

		numSamples=std::min(numSamples,totalNumSamples-(wavePtr/4));

		ym2612.MakeWaveForNSamples(wave.data()+wavePtr,numSamples);
		wavePtr+=numSamples*4;

		uint64_t actualDt=numSamples;
		actualDt*=MICRO;
		actualDt/=YM2612::WAVE_SAMPLING_RATE;
		timeInMicrosec+=actualDt;
	}

	wave.resize(wavePtr);

	return wave;
}

MMLPlayer::MMLError MMLPlayer::GetLastError(void) const
{
	return lastError;
}

bool MMLPlayer::InterpretMML(int chNum)
{
	auto &ch=channels[chNum];
	while(ch.ptr.pos<ch.mml.size() && INFINITE==ch.ptr.toneEndAtInMicrosec)
	{
		char cmd=ch.mml[ch.ptr.pos++];
		if('a'<=cmd && cmd<='z')
		{
			cmd=cmd+'A'-'a';
		}
		switch(cmd)
		{
		case ' ':
			// Ignore space
			break;
		case 'R':
			{
				int L=GetNumber(chNum);
				if(0==L)
				{
					L=ch.noteLength;
				}

				uint64_t noteDurationInMicrosec=60*MICRO*4;
				if('.'==ch.mml[ch.ptr.pos])
				{
					noteDurationInMicrosec*=3;
					noteDurationInMicrosec/=2;
					++ch.ptr.pos;
				}
				noteDurationInMicrosec/=(ch.tempo*L);

				ch.ptr.toneEndAtInMicrosec=timeInMicrosec+noteDurationInMicrosec;
			}
			break;
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'A':
		case 'B':
			{
				int sharpOrFlat=0;
				if('#'==ch.mml[ch.ptr.pos] || '+'==ch.mml[ch.ptr.pos])
				{
					sharpOrFlat=1;
					++ch.ptr.pos;
				}
				else if('-'==ch.mml[ch.ptr.pos])
				{
					sharpOrFlat=-1;
					++ch.ptr.pos;
				}

				int L=GetNumber(chNum);
				if(0==L)
				{
					L=ch.noteLength;
				}

				uint64_t noteDurationInMicrosec=60*MICRO*4;
				if('.'==ch.mml[ch.ptr.pos])
				{
					noteDurationInMicrosec*=3;
					noteDurationInMicrosec/=2;
					++ch.ptr.pos;
				}
				noteDurationInMicrosec/=(ch.tempo*L);

				unsigned int note;
				note=('C'<=cmd ? cmd-'C' : 5+cmd-'A');

				unsigned int blk,fnum;
				OctaveNoteToBlockFnum(blk,fnum,ch.octave,note,sharpOrFlat);

				unsigned char highByte,lowByte;
				highByte=(blk<<3)|(fnum>>8);
				lowByte=fnum&255;
				ym2612.WriteRegister((chNum<3 ? 0 : 3),YM2612::REG_FNUM2+chNum%3,highByte);
				ym2612.WriteRegister((chNum<3 ? 0 : 3),YM2612::REG_FNUM1+chNum%3,lowByte);
				if(true!=mute[chNum])
				{
					if(chNum<3)
					{
						ym2612.WriteRegister(0,YM2612::REG_KEY_ON_OFF,0xF0|chNum);
					}
					else
					{
						ym2612.WriteRegister(0,YM2612::REG_KEY_ON_OFF,0xF0|(chNum+1));
					}
				}

				ch.ptr.toneEndAtInMicrosec=timeInMicrosec+noteDurationInMicrosec;
				if('&'==ch.mml[ch.ptr.pos])
				{
					++ch.ptr.pos;
				}
				else
				{
					ch.ptr.keyOffAtInMicrosec=timeInMicrosec+noteDurationInMicrosec*ch.keyOnTimeFraction/KEYON_TIME_FRACTION_MAX;
				}
			}
			break;
		case 'V':
			{
				auto vol=GetNumber(chNum);
				if(vol<0 || VOLUME_MAX<vol)
				{
					lastError.errorCode=ERROR_VOLUME;
					lastError.chNum=chNum;
					return false;
				}
				ch.volume=vol;
				ReapplyEnvelope(chNum);
			}
			break;
		case 'O':
			{
				auto oct=GetNumber(chNum);
				if(oct<0 || OCTAVE_MAX<oct)
				{
					lastError.errorCode=ERROR_OCTAVE;
					lastError.chNum=chNum;
					return false;
				}
				ch.octave=oct;
			}
			break;
		case '>':
			if(ch.octave+1<=OCTAVE_MAX)
			{
				++ch.octave;
			}
			break;
		case '<':
			if(0<ch.octave)
			{
				--ch.octave;
			}
			break;
		case 'L':
			{
				auto len=GetNumber(chNum);
				if(len<0 || NOTE_LENGTH_MAX<len)
				{
					lastError.errorCode=ERROR_NOTE_LENGTH;
					lastError.chNum=chNum;
					return false;
				}
				ch.noteLength=len;
			}
			break;
		case 'S':
			GetNumber(chNum); // Ignore to allow F-BASIC V3.0 MML
			break;
		case 'M':
			GetNumber(chNum); // Ignore to allow F-BASIC V3.0 MML
			break;
		case 'T':
			{
				auto tempo=GetNumber(chNum);
				if(tempo<0 || TEMPO_MAX<tempo)
				{
					lastError.errorCode=ERROR_TEMPO;
					lastError.chNum=chNum;
					return false;
				}
				ch.tempo=tempo;
			}
			break;
		case '@':
			{
				auto instNum=GetNumber(chNum)-1;
				if(instNum<0 || INST_NUM_MAX<instNum)
				{
					lastError.errorCode=ERROR_INSTRUMENT_NUMBER;
					lastError.chNum=chNum;
					return false;
				}
				ch.instNum=instNum;
				ReapplyEnvelope(chNum);
			}
			break;
		default:
			lastError.errorCode=ERROR_UNDEFINED_COMMAND;
			lastError.chNum=chNum;
			return false;
		}
	}
	return true;
}

void MMLPlayer::OctaveNoteToBlockFnum(unsigned int &blk,unsigned int &fnum,int octave,int note,int sharpOrFlat) const
{
	static const int noteToFnum[]=
	{
		619,
		656,
		695,
		736,
		780,
		826,
		875,
		927,
		983,
		1041,
		1103,
		1169,

		// Values taken from F-BASIC 386.  Off-frequency?
		// 619, // "O4C"
		// 654, // "O4C#"
		// 693, // "O4D"
		// 734, // "O4D#"
		// 778, // "O4E"
		// 824, // "O4F"
		// 873, // "O4F#"
		// 925, // "O4G"
		// 980, // "O4G#"
		// 1038, // "O4A"
		// 1100, // "O4A#"
		// 1165, // "O4B"
	};

	// # #  # # #
	//c d ef g a b
	//0 1 23 4 5 6
	//0123456789ab
	if(note<=2)
	{
		note*=2;
	}
	else
	{
		note=note*2-1;
	}

	note+=sharpOrFlat;
	if(note<0)
	{
		note+=12;
		--octave;
	}
	if(12<=note)
	{
		note-=12;
		++octave;
	}

	if(8<=octave)
	{
		blk=7;
		fnum=noteToFnum[note]*2;
	}
	else
	{
		blk=octave;
		fnum=noteToFnum[note];
	}
}

int MMLPlayer::GetNumber(int chNum)
{
	auto &ch=channels[chNum];
	int num=0;
	while(ch.ptr.pos<ch.mml.size() && '0'<=ch.mml[ch.ptr.pos] && ch.mml[ch.ptr.pos]<='9')
	{
		num*=10;
		num+=(ch.mml[ch.ptr.pos++]-'0');
	}
	return num;
}

void MMLPlayer::ReapplyEnvelope(int chNum)
{
	auto &ch=channels[chNum];
	auto i=inst[ch.instNum];
	auto CONN=(i.FB_CNCT&7);

	int nCarrierSlots,carrierSlots[4];
	YM2612::GetCarrierSlotFromConnection(nCarrierSlots,carrierSlots,CONN);

	for(auto j=0; j<nCarrierSlots; ++j)
	{
		auto slotNum=carrierSlots[j];
		int TL=i.TL[slotNum];
		TL+=(15-ch.volume)*2;
		TL=std::min<int>(YM2612::TL_MAX,TL);
		i.TL[slotNum]=TL;
	}

	auto chBase=(chNum<3 ? 0 : 3);
	auto chLow=(chNum%3);
	ym2612.WriteRegister(chBase,YM2612::REG_DT_MULTI+0x00+chLow,i.DT_MULTI[0]);
	ym2612.WriteRegister(chBase,YM2612::REG_DT_MULTI+0x04+chLow,i.DT_MULTI[1]);
	ym2612.WriteRegister(chBase,YM2612::REG_DT_MULTI+0x08+chLow,i.DT_MULTI[2]);
	ym2612.WriteRegister(chBase,YM2612::REG_DT_MULTI+0x0C+chLow,i.DT_MULTI[3]);

	ym2612.WriteRegister(chBase,YM2612::REG_TL+0x00+chLow,i.TL[0]);
	ym2612.WriteRegister(chBase,YM2612::REG_TL+0x04+chLow,i.TL[1]);
	ym2612.WriteRegister(chBase,YM2612::REG_TL+0x08+chLow,i.TL[2]);
	ym2612.WriteRegister(chBase,YM2612::REG_TL+0x0C+chLow,i.TL[3]);

	ym2612.WriteRegister(chBase,YM2612::REG_KS_AR+0x00+chLow,i.KS_AR[0]);
	ym2612.WriteRegister(chBase,YM2612::REG_KS_AR+0x04+chLow,i.KS_AR[1]);
	ym2612.WriteRegister(chBase,YM2612::REG_KS_AR+0x08+chLow,i.KS_AR[2]);
	ym2612.WriteRegister(chBase,YM2612::REG_KS_AR+0x0C+chLow,i.KS_AR[3]);

	ym2612.WriteRegister(chBase,YM2612::REG_AM_DR+0x00+chLow,i.AMON_DR[0]);
	ym2612.WriteRegister(chBase,YM2612::REG_AM_DR+0x04+chLow,i.AMON_DR[1]);
	ym2612.WriteRegister(chBase,YM2612::REG_AM_DR+0x08+chLow,i.AMON_DR[2]);
	ym2612.WriteRegister(chBase,YM2612::REG_AM_DR+0x0C+chLow,i.AMON_DR[3]);

	ym2612.WriteRegister(chBase,YM2612::REG_SR+0x00+chLow,i.SR[0]);
	ym2612.WriteRegister(chBase,YM2612::REG_SR+0x04+chLow,i.SR[1]);
	ym2612.WriteRegister(chBase,YM2612::REG_SR+0x08+chLow,i.SR[2]);
	ym2612.WriteRegister(chBase,YM2612::REG_SR+0x0C+chLow,i.SR[3]);

	ym2612.WriteRegister(chBase,YM2612::REG_SL_RR+0x00+chLow,i.SL_RR[0]);
	ym2612.WriteRegister(chBase,YM2612::REG_SL_RR+0x04+chLow,i.SL_RR[1]);
	ym2612.WriteRegister(chBase,YM2612::REG_SL_RR+0x08+chLow,i.SL_RR[2]);
	ym2612.WriteRegister(chBase,YM2612::REG_SL_RR+0x0C+chLow,i.SL_RR[3]);

	ym2612.WriteRegister(chBase,YM2612::REG_SSG_EG+0x00+chLow,0);
	ym2612.WriteRegister(chBase,YM2612::REG_SSG_EG+0x04+chLow,0);
	ym2612.WriteRegister(chBase,YM2612::REG_SSG_EG+0x08+chLow,0);
	ym2612.WriteRegister(chBase,YM2612::REG_SSG_EG+0x0C+chLow,0);

	ym2612.WriteRegister(chBase,YM2612::REG_FB_CNCT+chLow,i.FB_CNCT);
	ym2612.WriteRegister(chBase,YM2612::REG_LR_AMS_PMS+chLow,i.LR_AMS_PMS);
}

bool MMLPlayer::PlayDone(void) const
{
	for(auto &ch : channels)
	{
		if(true!=ch.PlayDone())
		{
			return false;
		}
	}
	return true;
}

uint64_t MMLPlayer::GetTimeInMicrosec(void) const
{
	return timeInMicrosec;
}



////////////////////////////////////////////////////////////



void MMLSegmentPlayer::AddSegment(
		std::string ch0,
		std::string ch1,
		std::string ch2,
		std::string ch3,
		std::string ch4,
		std::string ch5)
{
	Segment seg;
	mmlSegments.push_back(seg);
	mmlSegments.back().mml[0]=ch0;
	mmlSegments.back().mml[1]=ch1;
	mmlSegments.back().mml[2]=ch2;
	mmlSegments.back().mml[3]=ch3;
	mmlSegments.back().mml[4]=ch4;
	mmlSegments.back().mml[5]=ch5;
}

std::vector <unsigned char> MMLSegmentPlayer::GenerateWave(uint64_t timeInMillisec)
{
	std::vector <unsigned char> rawWaveData;

	uint64_t timeInMicrosec=timeInMillisec*(MICRO/MILLI);

	int repeatCount=0;
	while(true!=this->PlayDone() && 0<timeInMicrosec)
	{
		if(true==MMLPlayer::PlayDone())
		{
			if(playingSegment<mmlSegments.size())
			{
				MMLPlayer::ClearMML();
				MMLPlayer::AddMML(0,mmlSegments[playingSegment].mml[0]);
				MMLPlayer::AddMML(1,mmlSegments[playingSegment].mml[1]);
				MMLPlayer::AddMML(2,mmlSegments[playingSegment].mml[2]);
				MMLPlayer::AddMML(3,mmlSegments[playingSegment].mml[3]);
				MMLPlayer::AddMML(4,mmlSegments[playingSegment].mml[4]);
				MMLPlayer::AddMML(5,mmlSegments[playingSegment].mml[5]);
				++playingSegment;
				if(true==repeat)
				{
					playingSegment=0;
					++repeatCount;
					if(mmlSegments.size()<=repeatCount)
					{
						// Prevent infinite loop.
						// If no data is generated by going through one loop of
						// the entire song, probably it should stop.
						return rawWaveData;
					}
				}
			}
		}

		auto rawWavePiece=MMLPlayer::GenerateWave(timeInMillisec);

		uint64_t rawWavePieceLengthInMicrosec=rawWavePiece.size()*MICRO/(YM2612::WAVE_SAMPLING_RATE*OUTPUT_CHANNELS*OUTPUT_BYTES_PER_SAMPLE);
		if(rawWavePieceLengthInMicrosec<timeInMicrosec)
		{
			timeInMicrosec-=rawWavePieceLengthInMicrosec;
		}
		else
		{
			timeInMicrosec=0;
		}

		if(0==rawWaveData.size())
		{
			rawWaveData.swap(rawWavePiece);
		}
		else
		{
			rawWaveData.insert(rawWaveData.end(),rawWavePiece.begin(),rawWavePiece.end());
		}
	}

	return rawWaveData;
}

bool MMLSegmentPlayer::PlayDone(void) const
{
	return (true==MMLPlayer::PlayDone() && mmlSegments.size()<=playingSegment);
}

void MMLPlayer::MuteChannels(bool ch0Mute,bool ch1Mute,bool ch2Mute,bool ch3Mute,bool ch4Mute,bool ch5Mute)
{
	mute[0]=ch0Mute;
	mute[1]=ch1Mute;
	mute[2]=ch2Mute;
	mute[3]=ch3Mute;
	mute[4]=ch4Mute;
	mute[5]=ch5Mute;
}

int MMLSegmentPlayer::GetCurrentSegment(void) const
{
	return playingSegment;
}
