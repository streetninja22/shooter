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
		Animation** m_animPtrPtr; //pointer to the pointer to the animation, used to set the animation after loading. This is a pointer to a pointer because we want to change what the pointer of the Object's animation is to, but don't want to change by value
		
	public:
		LoadAnimationEvent(AnimationId animId, Animation** animPtrPtr) : GameEvent(), m_animId(animId), m_animPtrPtr(animPtrPtr)
		{
		}
		
		AnimationId getAnimId() { return m_animId; }
		Animation** getAnimPtr2() { return m_animPtrPtr; }
		
		virtual GameEventType getGameEventType() override { return GameEventType::LOAD_ANIMATION; }
	};
	
}
