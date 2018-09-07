#include "vad_imp.h"

int VadImp::Init() {
	int ret = WebRtcVad_Create(&handle);
	if (ret) {
		return ret;
	}
	ret = WebRtcVad_Init(handle);
	return ret;
}

VadImp::~VadImp() {
	if (handle) {
		WebRtcVad_Free(handle);
	}
}

int VadImp::SetMode(int mode) {
	return WebRtcVad_set_mode(handle, mode);
}

int VadImp::Process(int fs, const int16_t* audio_frame,
	int frame_length) {
	return WebRtcVad_Process(handle, fs, audio_frame, frame_length);
}

int VadImp::ValidRateAndFrameLength(int rate, int frame_length) {
	return WebRtcVad_ValidRateAndFrameLength(rate, frame_length);
}

