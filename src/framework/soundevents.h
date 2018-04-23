#pragma once
#include "SoundSystem.h"


namespace sound
{

	class LoadSoundEvent : public SoundEvent
	{
		std::string m_filepath;
		
		
	public:
		LoadSoundEvent(std::string filepath) : m_filepath(filepath), SoundEvent()
		{
		}
		
		std::string getFilepath() { return m_filepath; }
		
	};

	class LoadMusicEvent : public LoadSoundEvent
	{
	public:
		LoadMusicEvent(std::string filepath) : LoadSoundEvent(filepath)
		{
		}
		
		SoundEventType getSoundEventType() { return SoundEventType::LOAD_MUSIC; }
	};

	class LoadChunkEvent : public LoadSoundEvent
	{
	public:
		LoadChunkEvent(std::string filepath) : LoadSoundEvent(filepath)
		{
		}
		
		SoundEventType getSoundEventType() { return SoundEventType::LOAD_CHUNK; }
	};
	
	
	
	
	
	
	
	class PlayChunkEvent : public SoundEvent
	{
		Chunk* m_chunk;
		
	public:
		PlayChunkEvent(Chunk* chunk) : m_chunk(chunk), SoundEvent()
		{
			
		}
		
		Chunk* getChunk() { return m_chunk; }
		
		SoundEventType getSoundEventType() { return SoundEventType::PLAY_CHUNK; }
	};
	
	class PlayMusicEvent : public SoundEvent
	{
		Music* m_music;
		
	public:
		PlayMusicEvent(Music* music) : m_music(music), SoundEvent()
		{
			
		}
		
		Music* getMusic() { return m_music; }
		
		SoundEventType getSoundEventType() { return SoundEventType::PLAY_MUSIC; }
	};
	
	
	
	
	
	class PauseMusicEvent : public SoundEvent
	{
	public:
		PauseMusicEvent() : SoundEvent()
		{
		}
		
		SoundEventType getSoundEventType() { return SoundEventType::PAUSE_MUSIC; }
	};
	
	class ResumeMusicEvent : public SoundEvent
	{
	public:
		ResumeMusicEvent() : SoundEvent()
		{
		}
		
		SoundEventType getSoundEventType() { return SoundEventType::RESUME_MUSIC; }
	};
	
	class ToggleMusicEvent : public SoundEvent
	{
	public:
		ToggleMusicEvent() : SoundEvent()
		{
		}
		
		SoundEventType getSoundEventType() { return SoundEventType::TOGGLE_MUSIC; }
	};
	
	
	
	class SetVolumeEvent : public SoundEvent
	{
		int m_volume;
		
	public:
		SetVolumeEvent() : SoundEvent()
		{
		}
		
		int getVolume() { return m_volume; }
		
		SoundEventType getSoundEventType() { return SoundEventType::SET_VOLUME; }
	};
	
	
	class SetMusicVolumeEvent : public SetVolumeEvent
	{
	public:
		SetMusicVolumeEvent() : SetVolumeEvent()
		{
		}
		
		SoundEventType getSoundEventType() { return SoundEventType::SET_MUSIC_VOLUME; }
	};
	
	
	
	
	class LoadChunkReturnType : public SoundEventReturnType
	{
		Chunk* m_chunk;
		
	public:
		LoadChunkReturnType() : SoundEventReturnType()
		{
		}
		
		LoadChunkReturnType(Chunk* chunk) : m_chunk(chunk), SoundEventReturnType()
		{
		}
		
		Chunk* getChunk() { return m_chunk; }
		void setChunk(Chunk* chunk) { m_chunk = chunk; }
		
		SoundEventType getSoundEventType() { return SoundEventType::LOAD_CHUNK; }
	};
	
	class LoadMusicReturnType : public SoundEventReturnType
	{
		Music* m_music;
		
	public:
		LoadMusicReturnType() : SoundEventReturnType()
		{
		}
		
		LoadMusicReturnType(Music* music) : m_music(music), SoundEventReturnType()
		{
		}
		
		Music* getMusic() { return m_music; }
		void setMusic(Music* music) { m_music = music; }
		
		SoundEventType getSoundEventTYpe() { return SoundEventType::LOAD_MUSIC; }
	};
	
}
