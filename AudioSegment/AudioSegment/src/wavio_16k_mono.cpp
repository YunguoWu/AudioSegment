#include "wavio_16k_mono.h"

#include <assert.h>
#include <sys/stat.h>

const int SAMPLESOFMS = DEFAULEFS / 1000;
const int BYTESSAMPLE = sizeof(int16_t);

long long WaveIo16k::MsToByte(int ms) {
	if (ms < 0) {
		return -1;
	}
	else if (ms == 0) {
		return -1;
	}
	else {
		return SAMPLESOFMS * (ms - 1) * BYTESSAMPLE;
	}
}

int WaveIo16k::Read(const char* file, int16_t* buffer, int startMs, int endMs) {
	struct stat file_info;
	if (stat(file, &file_info) < 0) {
		return -1;
	}
	start = MsToByte(startMs);
	end = MsToByte(endMs);
	size_t size = (end - start + BYTESSAMPLE);
	fopen_s(&fp, file, "rb");
	if (start < 0 || end < 0 
		|| !fp || file_info.st_size < start + size) {
		return -1;
	}
	fseek(fp, HEADSIZE + start, SEEK_SET);
	fread(buffer, 1, size, fp);
	fclose(fp);
	fp = nullptr;
	return 0;
}

int WaveIo16k::Write(const char* file, int16_t* buffer, int startMs, int endMs) {
	start = MsToByte(startMs);
	end = MsToByte(endMs);
	fopen_s(&fp, file, "wb");
	if (start < 0 || end < 0
		|| !fp) {
		return -1;
	}
	size_t size = (end - start + BYTESSAMPLE);
	fwrite(buffer, 1, size, fp);
	fclose(fp);
	fp = nullptr;
	return 0;
}