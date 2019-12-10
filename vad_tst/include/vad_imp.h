#ifndef VAD_IMP_H
#define VAD_IMP_H

#include "webrtc/common_audio/vad/include/webrtc_vad.h"

class VadImp {
private:
	VadInst * handle;

public:

	// Creates an instance to the VAD structure.
	//
	// - handle [o] : Pointer to the VAD instance that should be created.
	//
	// returns      : 0 - (OK), -1 - (Error)
	int Init();

	// Frees the dynamic memory of a specified VAD instance.
	//
	// - handle [i] : Pointer to VAD instance that should be freed.
	~VadImp();

	// Sets the VAD operating mode. A more aggressive (higher mode) VAD is more
	// restrictive in reporting speech. Put in other words the probability of being
	// speech when the VAD returns 1 is increased with increasing mode. As a
	// consequence also the missed detection rate goes up.
	//
	// - handle [i/o] : VAD instance.
	// - mode   [i]   : Aggressiveness mode (0, 1, 2, or 3).
	//
	// returns        : 0 - (OK),
	//                 -1 - (NULL pointer, mode could not be set or the VAD instance
	//                       has not been initialized).
	int SetMode(int mode);


	// Calculates a VAD decision for the |audio_frame|. For valid sampling rates
	// frame lengths, see the description of WebRtcVad_ValidRatesAndFrameLengths().
	//
	// - handle       [i/o] : VAD Instance. Needs to be initialized by
	//                        WebRtcVad_Init() before call.
	// - fs           [i]   : Sampling frequency (Hz): 8000, 16000, or 32000
	// - audio_frame  [i]   : Audio frame buffer.
	// - frame_length [i]   : Length of audio frame buffer in number of samples.
	//
	// returns              : 1 - (Active Voice),
	//                        0 - (Non-active Voice),
	//                       -1 - (Error)
	int Process(int fs, const int16_t* audio_frame,
		int frame_length);

	// Checks for valid combinations of |rate| and |frame_length|. We support 10,
	// 20 and 30 ms frames and the rates 8000, 16000 and 32000 Hz.
	//
	// - rate         [i] : Sampling frequency (Hz).
	// - frame_length [i] : Speech frame buffer length in number of samples.
	//
	// returns            : 0 - (valid combination), -1 - (invalid combination)
	int ValidRateAndFrameLength(int rate, int frame_length);
};

#endif