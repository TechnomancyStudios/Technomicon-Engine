#pragma once
#include <SDL_mixer.h>
#include <iostream>
#include <map>

class MusicPlayer
{
public:
	MusicPlayer();
	~MusicPlayer();
	void FadeCurrentTrack();
	void FadeTrackTo(Mix_Music track, int time, int loops);
	void PlayTrack(const char* trackName, int loops);
	void AddTrackToMap(const char* musicPath, const char* trackName);
	void StopTrack();
private:
	Mix_Music* currentTrack;
	std::map<const char*, Mix_Music*> musicMap;
};