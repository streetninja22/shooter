#pragma once

#include "System.h"
#include "includeSDL.h"
#include <string>
#include "Event.h"
#include "Exception.h"

namespace sound
{
	
	class SoundException : public Exception
	{
		
	public:
		SoundException(int code, std::string value) : Exception(code, value)
		{
		}
		
		
	};
	
	
	
	
	
	

	class Chunk
	{
		Mix_Chunk* m_chunk;
		
	public:
		Chunk()
		{
		}
		
		Chunk(Mix_Chunk* chunk) : m_chunk(chunk)
		{
		}
		
		~Chunk()
		{
			Mix_FreeChunk(m_chunk);
		}
		
		void setChunk(Mix_Chunk* chunk) { m_chunk = chunk; }
		
		Mix_Chunk* getChunk() { return m_chunk; }
		
	};


	class Music
	{
		Mix_Music* m_music;
		
	public:
		Music()
		{
		}
		
		Music(Mix_Music* music) : m_music(music)
		{
		}
		
		~Music()
		{
			Mix_FreeMusic(m_music);
		}
		
		void setMusic(Mix_Music* music) { m_music = music; }
		
		Mix_Music* getMusic() { return m_music; }
		
	};

	
	
	
	
	
	enum class SoundEventType
	{
		LOAD_CHUNK,
		LOAD_MUSIC,
		PLAY_CHUNK,
		PLAY_MUSIC,
		PAUSE_MUSIC,
		RESUME_MUSIC,
		TOGGLE_MUSIC,
		SET_VOLUME,
		SET_MUSIC_VOLUME,
		DEFAULT
	};
	
	
	class SoundEvent : public Event
	{
		
	public:
		SoundEvent() : Event(EventType::SOUND)
		{
		}
		
		virtual SoundEventType getSoundEventType() { return SoundEventType::DEFAULT; }
		
	};
	
	
	class SoundEventReturnType : public EventReturnType
	{
	public:
		SoundEventReturnType() : EventReturnType(EventType::SOUND)
		{
		}
		
		virtual SoundEventType getSoundEventType() { return SoundEventType::DEFAULT; }
	};
	
	
	
	
	
	class SoundSystem : public System
	{
		
		
	public:
		SoundSystem(EventBus* bus, int frequency = MIX_DEFAULT_FREQUENCY, int channels = MIX_DEFAULT_CHANNELS, int chunksize = 2048) : System(bus)
		{
			Mix_Init(MIX_INIT_MP3 | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG);
			
			if (!(Mix_OpenAudio(frequency, MIX_DEFAULT_FORMAT, channels, chunksize)))
			{
				//TODO: error logging
			}
		}
		
		~SoundSystem()
		{
			Mix_CloseAudio();
		}
		
		
		EventReturnType* eventFired(Event* event);
		

		Chunk* loadChunk(std::string filepath);
		Music* loadMusic(std::string filepath);
		
		
		void playChunk(Chunk* chunk, int loops = 0, int channel = -1);
		void playMusic(Music* music, bool looping = false);
		
		void pauseMusic();
		void resumeMusic();
		void toggleMusic();
		
		void setVolume(int volume, int channel = -1);
		void setMusicVolume(int volume);
		
	};
}
