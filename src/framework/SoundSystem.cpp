#include "SoundSystem.h"
#include "soundevents.h"

namespace sound
{
	
	
	EventReturnType* SoundSystem::eventFired(Event* event)
	{
		if (event->getEventType() == EventType::SOUND)
		{
			SoundEvent* soundEvent = dynamic_cast<SoundEvent*>(event);
			
			switch(soundEvent->getSoundEventType())
			{
				case SoundEventType::LOAD_CHUNK:
				{
					LoadChunkEvent* loadEvent = dynamic_cast<LoadChunkEvent*>(soundEvent);
					
					return new LoadChunkReturnType(loadChunk(loadEvent->getFilepath()));
				}
					
				case SoundEventType::LOAD_MUSIC:
				{
					LoadMusicEvent* loadEvent = dynamic_cast<LoadMusicEvent*>(soundEvent);
					
					return new LoadMusicReturnType(loadMusic(loadEvent->getFilepath()));
				}
					
				case SoundEventType::PLAY_CHUNK:
				{
					PlayChunkEvent* playEvent = dynamic_cast<PlayChunkEvent*>(soundEvent);
					
					playChunk(playEvent->getChunk());
					break;
				}
					
				case SoundEventType::PLAY_MUSIC:
				{
					PlayMusicEvent* playEvent = dynamic_cast<PlayMusicEvent*>(soundEvent);
					
					playMusic(playEvent->getMusic());
					break;
				}
					
				case SoundEventType::PAUSE_MUSIC:
				{
					pauseMusic();
					break;
				}
					
				case SoundEventType::RESUME_MUSIC:
				{
					resumeMusic();
					break;
				}
					
				case SoundEventType::TOGGLE_MUSIC:
				{
					toggleMusic();
					break;
				}
					
				case SoundEventType::SET_VOLUME:
				{
					SetVolumeEvent* volumeEvent = dynamic_cast<SetVolumeEvent*>(soundEvent);
					
					setVolume(volumeEvent->getVolume());
					break;
				}
					
				case SoundEventType::SET_MUSIC_VOLUME:
				{
					SetVolumeEvent* volumeEvent = dynamic_cast<SetVolumeEvent*>(soundEvent);
					
					setMusicVolume(volumeEvent->getVolume());
					break;
				}
					
			}
		}
		return nullptr;
	}
	
	
	
	
	
	
	Chunk* SoundSystem::loadChunk(std::string filepath)
	{
		Mix_Chunk* sound = Mix_LoadWAV(filepath.c_str());
		
		if (sound == NULL)
		{
			throw new SoundException(4, Mix_GetError());
		}
		
		return new Chunk(sound);
	}
	
	
	Music* SoundSystem::loadMusic(std::string filepath)
	{
		Mix_Music* sound = Mix_LoadMUS(filepath.c_str());
		
		if (sound == NULL)
		{
			throw new SoundException(4, Mix_GetError());
		}
		
		return new Music(sound);
	}
	
	
	
	
	
	
	void SoundSystem::playChunk(Chunk* chunk, int loops, int channel)
	{
		Mix_PlayChannel(channel, chunk->getChunk(), loops);
	}
	
	void SoundSystem::playMusic(Music* music, bool looping)
	{
		Mix_PlayMusic(music->getMusic(), (looping ? -1 : 1));
	}
	
	
	
	
	
	void SoundSystem::pauseMusic()
	{
		Mix_PauseMusic();
	}
	
	void SoundSystem::resumeMusic()
	{
		Mix_ResumeMusic();
	}
	
	void SoundSystem::toggleMusic()
	{
		if (Mix_PausedMusic())
		{
			resumeMusic();
		}
		else
			pauseMusic();
	}
	
	
	
	void SoundSystem::setVolume(int volume, int channel)
	{
		Mix_Volume(channel, volume);
	}
	
	void SoundSystem::setMusicVolume(int volume)
	{
		Mix_VolumeMusic(volume);
	}
}
