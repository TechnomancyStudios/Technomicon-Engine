#pragma once
#include <SDL_mixer.h>
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
private:
	Mix_Music* currentTrack;
	std::map<const char*, Mix_Music*> musicMap;
};