#ifndef MMLPLAYER_IS_INCLUDED
#define MMLPLAYER_IS_INCLUDED
/* { */

#include <chrono>
#include <string>
#include <vector>
#include <cstdint>
#include <ym2612.h>

#ifdef INFINITE
#undef INFINITE
#endif

/*
Default tones:

1  E.PIANO
2  PIANO
3  TRUMPET
4  TRUMPET
5  HARPSICHORD
6  ORGAN
7  OBOE
8  CLARINET
9  WOODWIND
10 GUITAR
11 KOTO
12 HARP
13 E.BASE
14 DRUM
15 DRUM
16 BELL
17 BELL
18 BELL
19 ELECTRIC
20 ELECTRIC
21 ELECTRIC
23 METALIC
24 METALIC
25 METALIC
26 PSG
27 FNYON
28 NOISE

*/

class MMLPlayer
{
public:
	static const unsigned long long sizeof_defaultFMB;
	static const unsigned char defaultFMB[];

	enum
	{
		NUM_CHANNELS=6,

		TEMPO_DEFAULT=120,
		TEMPO_MAX=255,

		OCTAVE_DEFAULT=4,
		OCTAVE_MAX=8,

		NOTE_LENGTH_DEFAULT=4,
		NOTE_LENGTH_MAX=64,

		VOLUME_DEFAULT=12,
		VOLUME_MAX=15,

		KEYON_TIME_FRACTION_DEFAULT=8,
		KEYON_TIME_FRACTION_MAX=8,

		INST_NUM_MAX=127,

		MMLPLAYER_VOLUME_DEFAULT=4096,

		OUTPUT_CHANNELS=2,
		OUTPUT_BYTES_PER_SAMPLE=2,
		MILLI=1000,
		MICRO=1000000,
		INFINITE=~0,
	};

	enum
	{
		ERROR_NOERROR,
		ERROR_UNDEFINED_COMMAND,
		ERROR_INSTRUMENT_NUMBER,
		ERROR_VOLUME,
		ERROR_OCTAVE,
		ERROR_NOTE_LENGTH,
		ERROR_TEMPO,
		ERROR_FRACTION,
	};

	static std::string ErrorCodeToStr(int errCode);

	class FMInst
	{
	public:
		std::string instName;
		unsigned char DT_MULTI[4];
		unsigned char TL[4];
		unsigned char KS_AR[4];
		unsigned char AMON_DR[4];
		unsigned char SR[4];
		unsigned char SL_RR[4];
		unsigned char FB_CNCT;
		unsigned char LR_AMS_PMS;

		void Clear(void);
	};
	class MMLError
	{
	public:
		int chNum;
		int pos;
		int errorCode;
		std::string MML;
		void Clear(void);
		std::vector <std::string> Format(void) const;
	};

private:
	YM2612 ym2612;
	std::string fmbName;
	FMInst inst[128];
	bool mute[NUM_CHANNELS];

	class PlayPointer
	{
	public:
		int pos=0;
		uint64_t keyOffAtInMicrosec=INFINITE;
		uint64_t toneEndAtInMicrosec=INFINITE;

		void Clear(void);
	};
	class Channel
	{
	public:
		PlayPointer ptr;
		unsigned int tempo=TEMPO_DEFAULT;
		unsigned int octave=OCTAVE_DEFAULT;
		unsigned int noteLength=NOTE_LENGTH_DEFAULT;
		unsigned int volume=VOLUME_DEFAULT;
		unsigned int keyOnTimeFraction=KEYON_TIME_FRACTION_DEFAULT;
		unsigned int instNum=0;
		std::string mml;

		void Clear(void);
		bool PlayDone(void) const;
	};
	uint64_t timeInMicrosec=0;
	Channel channels[NUM_CHANNELS];

protected:
	MMLError lastError;


public:
	/*!
	*/
	MMLPlayer();

	/*!
	*/
	void Clear(void);

	/*! Load FMB (tone definition).
	*/
	bool LoadFMB(const unsigned char fmb[6152]);

	/*! Clears MML and resets play pointers and timer.  It does not clear FMB.
	*/
	void ClearMML(void);

	/*! AddMML to the channel.
	*/
	bool AddMML(unsigned int ch,std::string mml);

	/*!
	*/
	std::vector <unsigned char> GenerateWave(uint64_t timeInMillisec);

	/*!
	*/
	bool PlayDone(void) const;
protected:
	bool InterpretMML(int chNum);
	void ReapplyEnvelope(int chNum);
	int GetNumber(int chNum);
	void OctaveNoteToBlockFnum(unsigned int &blk,unsigned int &fnum,int octave,int note,int sharpOrFlat) const;

public:
	/*!
	*/
	uint64_t GetTimeInMicrosec(void) const;



	/*!
	*/
	void MuteChannels(bool ch0Mute,bool ch1Mute,bool ch2Mute,bool ch3Mute,bool ch4Mute,bool ch5Mute);



	/*!
	*/
	int GetLastErrorCode(void) const;



	/*!
	*/
	MMLError GetLastError(void) const;
};



class MMLSegmentPlayer : public MMLPlayer
{
public:
	class Segment
	{
	public:
		std::string mml[MMLPlayer::NUM_CHANNELS];
	};


private:
	bool repeat=false;
	unsigned int playingSegment=0;
	std::vector <Segment> mmlSegments;


public:
	/*!
	*/
	void AddSegment(
		std::string ch0,
		std::string ch1="",
		std::string ch2="",
		std::string ch3="",
		std::string ch4="",
		std::string ch5="");



	/*! Generates wave for the next segment.
	    If repeat==false and the music reaches the end, it will return
	    an array with all zeros.
	    This is to deal with the situation that the stream player is using a
	    real RING buffer, in which case silent segment needs to be constantly
	    pumped to the buffer, or the remnant from the earlier segments will
	    be played after the end of the music.  (It happens with DirectSound)
	*/
	std::vector <unsigned char> GenerateWave(const uint64_t timeInMillisec);



	/*!
	*/
	void Clear(void);



	/*!
	*/
	bool PlayDone(void) const;



	/*!
	*/
	int GetCurrentSegment(void) const;



	/*! Not implemented yet.  Just for placeholder.
	*/
	void SetRepeat(bool repeat);

	/*! Not implemented yet.  Just for placeholder.
	*/
	bool GetRepeat(void) const;
};



/* } */
#endif
