#include "Audio.h"

MusicPlayer::MusicPlayer()
{
	currentTrack = NULL;
	Mix_AllocateChannels(MAX_CHANNELS);
	Mix_VolumeMusic(maxMusicVol);
}

void MusicPlayer::PlayTrack(const char* trackName, int loops)
{
	Mix_PlayMusic(musicMap[trackName], loops);
	currentTrack = musicMap[trackName];
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
	currentTrack = musicMap[trackName];
	/*
	switch (fadeState)
	{
		case MIX_NO_FADING:
		{
			Mix_HaltMusic();
			musicVol = 0;
			Mix_VolumeMusic(musicVol);
			fadeState = MIX_FADING_IN;
			fadeTimeMS = ms;
			PlayTrack(trackName, loops);
		}
		break;
		case MIX_FADING_IN:
		{

		}
		break;
		case MIX_FADING_OUT:
		{

		}
		break;
	}*/
}

void MusicPlayer::Update()
{
	switch (fadeState)
	{
		case MIX_NO_FADING:
		{
		
		}
		break;
		case MIX_FADING_IN:
		{
			if (musicVol < maxMusicVol)
			{
				if (fadeTimeMS > 0)
				{
					musicVol += (0.01f);
					Mix_VolumeMusic(musicVol);
				}
			}
			else
			{
				musicVol = maxMusicVol;
				fadeState = MIX_NO_FADING;
				fadeTimeMS = 0;
			}
		}
		break;
		case MIX_FADING_OUT:
		{

		}
		break;
	}
}