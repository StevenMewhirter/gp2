#pragma once

#include <glm\glm.hpp>
#include <AL\al.h>
#include <AL\alc.h>
#include <vector>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <SDL\SDL.h>
#include <glm/gtc/type_ptr.hpp>

class GameAudio
{
	struct data {
		int SID, BID; //source and buffer
		char* Buff;//Buffer
		std::string AudioName;//filename
		data(unsigned int sid, unsigned int bid, char* bf, const char* an)
		{
			this->SID = sid;
			this->BID = bid;
			this->Buff = bf;
			this->AudioName = an;
		}

	};

	struct Vector3
	{
		float x, y, z;
	};
	std::vector<data> AudioDatas;
	ALCcontext* AudioContext;
	ALCdevice* AudioDevice;
	bool isBigEndian();
	int convertToInteger(char* Buff, int length);
	char* LinkWAV(const char* fn, int& chan, int& samplerate, int& bps, int& size);

public:
	GameAudio();
	~GameAudio();
	unsigned int loadingOfSound(const char* filename);
	void deletingOfSound(unsigned int id);
	void playingTheSound(unsigned int id);
	void playingTheSound(unsigned int id, glm::vec3& pos);
	void stopPlayingSound(unsigned int id);
	void setupThelistener(glm::vec3& pos, glm::vec3& camLookAt);

private:

};


