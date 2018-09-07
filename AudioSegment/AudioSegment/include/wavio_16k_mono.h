#ifndef WAVIO_16K_MONO_H
#define WAVIO_16K_MONO_H

#include <cstdio>

#include "webrtc/typedefs.h"

#define DEFAULEFS 16000

class WaveIo16k {
private:
	const static int HEADSIZE = 44;
	FILE* fp = nullptr;
	long long start, end;

private:
	long long MsToByte(int ms);

public:
	int Read(const char* file, int16_t* buffer, int startMs, int endMs);
	int Write(const char* file, int16_t* buffer, int startMs, int endMs);
};

#endif