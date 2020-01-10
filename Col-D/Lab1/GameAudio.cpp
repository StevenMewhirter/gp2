#include "GameAudio.h"

GameAudio::GameAudio()
{
	AudioDevice = alcOpenDevice(NULL); //open sound card
	if (AudioDevice == NULL)
	{
		std::cout << "cannot open sound card" << std::endl; // runs an error check
	}

	AudioContext = alcCreateContext(AudioDevice, NULL);

	if (AudioContext == NULL)
	{
		std::cout << "cannot open context" << std::endl;
	}

	alcMakeContextCurrent(AudioContext);
}

GameAudio::~GameAudio() // deconstructor for audio source and buffer data 
{
	for (unsigned int i = 0; i < AudioDatas.size(); i++) 
	{
		alDeleteSources(1, (unsigned int*)&AudioDatas[i].SID);
		if (AudioDatas[i].BID != -1)
		{
			alDeleteBuffers(1, (unsigned int*)&AudioDatas[i].BID);
			delete[] AudioDatas[i].Buff;
		}
	}
	alcDestroyContext(AudioContext);
	alcCloseDevice(AudioDevice);
}

bool GameAudio::isBigEndian()
{
	int a = 1;
	return !((char*)&a)[0];
}

int GameAudio::convertToInteger(char* buff, int length)// converts the data into an integer (i.e length)
{
	int a = 0;
	if (!isBigEndian())
		for (int i = 0; i < length; i++)
			((char*)&a)[i] = buff[i];
	else
		for (int i = 0; i < length; i++)
			((char*)&a)[3 - i] = buff[i];
	return a;
}

char* GameAudio::LinkWAV(const char* fn, int& chan, int& samplerate, int& bps, int& size) //reads the current data of the clip and returns it to the device
{
	char Buff[4];
	std::ifstream in(fn, std::ios::binary);
	in.read(Buff, 4);
	in.read(Buff, 4);
	in.read(Buff, 4); //WAV
	in.read(Buff, 4);	//fmt
	in.read(Buff, 4); //16 bit
	in.read(Buff, 2); //1
	in.read(Buff, 2);
	chan = convertToInteger(Buff, 2);
	in.read(Buff, 4);
	samplerate = convertToInteger(Buff, 4);
	in.read(Buff, 4);
	in.read(Buff, 2);
	in.read(Buff, 2);
	bps = convertToInteger(Buff, 2);
	in.read(Buff, 4);
	in.read(Buff, 4);
	size = convertToInteger(Buff, 4);

	char* soundData = new char[size];
	in.read(soundData, size);
	return soundData;
}

unsigned int GameAudio::loadingOfSound(const char* filename)
{
	bool found = false; //set a boolean to check if the data is there
	unsigned int SID, BID;
	char* soundData = NULL;
	for (unsigned int i = 0; i < AudioDatas.size(); i++)
	{
		if (AudioDatas[i].AudioName == filename && AudioDatas[i].BID != -1)
		{
			BID = AudioDatas[i].BID;
			found = true;
			break;
		}
	}
	if (!found) // if the sounds data is found convert it into formats that can be translated onto device
	{
		int channel, sampleRate, bps, size;
		soundData = LinkWAV(filename, channel, sampleRate, bps, size);
		unsigned int format;
		alGenBuffers(1, &BID);

		if (channel == 1)
		{
			if (bps == 8)
			{
				format = AL_FORMAT_MONO8;
			}
			else
			{
				format = AL_FORMAT_MONO16;
			}
		}
		else
		{
			if (bps == 8)
			{
				format = AL_FORMAT_STEREO8;
			}
			else
			{
				format = AL_FORMAT_STEREO16;
			}

		}

		alBufferData(BID, format, soundData, size, sampleRate);
	}
	alGenSources(1, &SID);
	alSourcei(SID, AL_BUFFER, BID);
	alSourcef(SID, AL_REFERENCE_DISTANCE, 1.0f);
	AudioDatas.push_back(data(SID, (!found ? BID : -1), soundData, filename));
	return SID; //returns the converted data 
}

void GameAudio::deletingOfSound(unsigned int id)
{}

void GameAudio::playingTheSound(unsigned int id)
{
	alSourcePlay(id);
}
void GameAudio::playingTheSound(unsigned int id, glm::vec3& pos)
{
	alSource3f(id, AL_POSITION, pos.x, pos.y, pos.z);
	alSourcePlay(id);
}
void GameAudio::stopPlayingSound(unsigned int id)
{
	alSourceStop(id);
}
void GameAudio::setupThelistener(glm::vec3& pos, glm::vec3& camLookAt)
{
	alListener3f(AL_POSITION, pos.x, pos.y, -pos.z);
	float orinet[6] = { camLookAt.x,camLookAt.y,camLookAt.z,0,1,0 };
	alListenerfv(AL_ORIENTATION, orinet);
}