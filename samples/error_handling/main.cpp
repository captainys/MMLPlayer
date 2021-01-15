#include <fstream>
#include <iostream>
#include "mmlplayer.h"



void TryAndPrintError(MMLSegmentPlayer mml)
{
	while(true!=mml.PlayDone())
	{
		auto w=mml.GenerateWave(100);
		if(0!=mml.GetLastErrorCode())
		{
			for(auto msg : mml.GetLastError().Format())
			{
				std::cout << msg << std::endl;
			}
		}
	}
}

int main(void)
{
	MMLSegmentPlayer mml;
	std::vector <unsigned char> wav;

	mml.AddSegment(
		"O4CDEFGAB",
		"O4CDEFGAB",
		"O4CDEF/GAB",
		"O4CDEFGAB",
		"O4CDEFGAB",
		"O4CDEFGAB"
	);
	TryAndPrintError(mml);

	mml.Clear();
	mml.AddSegment(
		"O100CDEFGAB",
		"O4CDEFGAB",
		"O4CDEFGAB",
		"O4CDEFGAB",
		"O4CDEFGAB",
		"O4CDEFGAB"
	);
	TryAndPrintError(mml);

	mml.Clear();
	mml.AddSegment(
		"T9999O4CDEFGAB",
		"O4CDEFGAB",
		"O4CDEFGAB",
		"O4CDEFGAB",
		"O4CDEFGAB",
		"O4CDEFGAB"
	);
	TryAndPrintError(mml);

	mml.Clear();
	mml.AddSegment(
		"@9999O4CDEFGAB",
		"O4CDEFGAB",
		"O4CDEFGAB",
		"O4CDEFGAB",
		"O4CDEFGAB",
		"O4CDEFGAB"
	);
	TryAndPrintError(mml);

	return 0;
}
