#pragma once

#include "framework/Event.h"
#include "GameGraphics.h"


namespace shooter
{
	
	enum class GameEventType
	{
		DEFAULT,
		LOAD_ANIMATION,
	};
	
	
	class GameEvent : public evnt::Event
	{
		
	public:
		GameEvent() : Event()
		{
		}
		
		evnt::EventType getEventType() override { return EventType::GAME; }
		
		virtual GameEventType getGameEventType() { return GameEventType::DEFAULT; }
	};
	
	
	
	class LoadAnimationEvent : public GameEvent
	{
		AnimationId m_animId;
		Animation* m_animPtr;
		
	public:
		LoadAnimationEvent(AnimationId animId, Animation* animPtr) : GameEvent(), m_animId(animId), m_animPtr(animPtr)
		{
		}
		
		AnimationId getAnimId() { return m_animId; }
		Animation* getAnimPtr() { return m_animPtr; }
		
		virtual GameEventType getGameEventType() override { return GameEventType::LOAD_ANIMATION; }
	};
	
}
