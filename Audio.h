#pragma once
#include <SDL2/SDL_mixer_ext.h>
//#include <SDL_mixer.h>
#include <iostream>
#include <map>

const int MAX_CHANNELS = 2;

enum AudioChannel
{
	SHIPSOUND,
	SOUND
};

class MusicPlayer
{
public:
	MusicPlayer();
	void FadeCurrentTrack();
	void FadeTrackTo(Mix_Music track, int time, int loops);
	void PlayTrack(const char* trackName, int loops);
	void FadeTrackIn(const char* trackName, int loops, int ms);
	void FadeTrackOut();
	void AddTrackToMap(const char* musicPath, const char* trackName);
	void StopTrack();
	void Update();
	Mix_Music* currentTrack;
	std::map<const char*, Mix_Music*> musicMap;
	Mix_Fading fadeState = MIX_NO_FADING;
	int fadeTimeMS = 0;
	int maxMusicVol = 128;
	float musicVol = 128.0f;
};