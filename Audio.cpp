#include "Audio.h"

MusicPlayer::MusicPlayer()
{
	currentTrack = NULL;
	Mix_AllocateChannels(MAX_CHANNELS);

}

void MusicPlayer::PlayTrack(const char* trackName, int loops)
{
	Mix_PlayMusic(musicMap[trackName], loops);
}

void MusicPlayer::AddTrackToMap(const char* musicPath, const char* trackName)
{
	Mix_Music* music = Mix_LoadMUS(musicPath);

	if (music != NULL)
	{
		musicMap.insert(std::pair<const char*, Mix_Music*>(trackName, music));
		std::cout << "Track Sucessfully Added to Music Map!" << std::endl;
	}
	else
		std::cout << "Track Failed to be Added to Music Map!" << std::endl;
}

void MusicPlayer::FadeTrackIn(const char* trackName, int loops, int ms)
{
	Mix_FadeInMusic(musicMap[trackName], loops, ms);
}