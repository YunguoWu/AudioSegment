// main.cc : Defines the entry point for the console application.
//

#include <cstdlib>
#include <string>
#include <vector>
#include <set>

#include "vad_imp.h"
#include "wavio_16k_mono.h"

int main(int argc, char* argv[])
{
	if (argc != 5) {
		printf("Please correct input.\n");
		return 1;
	}

	int16_t *buffer, *pre_buf;
	WaveIo16k* wave_io = new WaveIo16k();
	int ret;
	int startMs, endMs, durationMs;
	int frameMS;
	startMs = atoi(argv[2]);
	endMs = atoi(argv[3]);
	durationMs = endMs - startMs + 1;
	frameMS = atoi(argv[4]);
	int size = DEFAULEFS / 1000 * durationMs;
	buffer = new int16_t[size];
	pre_buf = buffer;
	ret = wave_io->Read(argv[1], buffer, startMs, endMs);
	if (ret) {
		printf("Uncorrect time or file location.\n");
		return -1;
	}

	VadImp *vad = new VadImp();
	if ((ret = vad->Init())) {
		printf("VAD Init failed\n");
		return -1;
	}
	if ((ret = vad->SetMode(0))) {
		printf("VAD SetMode failed\n");
		return -1;
	}

	int frame_length = DEFAULEFS / 1000 * frameMS;
	if ((ret = vad->ValidRateAndFrameLength(DEFAULEFS, frame_length))) {
		printf("VAD ValidRateAndFrameLength failed\n");
		return 1;
	}

	std::vector<int > vad_ret;
	for (int i = 0; i < durationMs / frameMS; i++) {
		ret = vad->Process(DEFAULEFS, buffer, frame_length);
		buffer += frame_length;
		if (-1 == ret) {
			printf("VAD Process failed\n");
			return 1;
		}
		else if (ret == 0) {
			vad_ret.emplace_back(i);
			printf("0\n");
		}
		else if (ret == 1) {
			printf("1\n");
		}
	}
	std::set<int > chunk_ret;
	int stat_num = 0;
	int thr_value = 5;
	int i = 1;
	while (i < vad_ret.size()) {
		if (vad_ret[i] - vad_ret[i - 1] == 1) {
			stat_num++;
			if (stat_num >= thr_value) {
				chunk_ret.insert((vad_ret[i] + 1) * frame_length);
				stat_num = 0;
				i++;
				while (i < vad_ret.size() && vad_ret[i] - vad_ret[i - 1] == 1) {
					i++;
				}
				continue;
			}
			i++;
		}
		else {
			stat_num = 0;
			i++;
		}
	}

	chunk_ret.insert(size);
	buffer = pre_buf;
	char out_file[10];
	auto it = chunk_ret.begin();
	int start_idx = 0;
	int idx = 1;
	sprintf(out_file, "%03d.pcm", 0);
	wave_io->Write(out_file, buffer, size);
	for (it; it != chunk_ret.end(); it++) {
		sprintf(out_file, "%03d.pcm", idx);
		wave_io->Write(out_file, buffer, *it - start_idx);
		start_idx = *it;
		buffer = pre_buf + start_idx;
		idx++;
	}

	buffer = pre_buf;
	delete vad;
	delete wave_io;
	delete[] buffer;
	return 0;
}

