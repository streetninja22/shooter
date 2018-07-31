#pragma once

#include "framework/Event.h"
#include "GameGraphics.h"
#include "AnimationId.h"


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
	
	class GameEventReturnType : public evnt::EventReturnType
	{
		
	public:
		GameEventReturnType() : EventReturnType()
		{
		}
		
		evnt::EventType getType() override { return EventType::GAME; }
		
		virtual GameEventType getGameEventType() { return GameEventType::DEFAULT; }
	};
	
	
	
	
	
	
	
	
	
	class LoadAnimationEvent : public GameEvent
	{
		AnimationId m_animId;
		
	public:
		LoadAnimationEvent(AnimationId animId) : GameEvent(), m_animId(animId)
		{
		}
		
		AnimationId getAnimId() { return m_animId; }
		
		virtual GameEventType getGameEventType() override { return GameEventType::LOAD_ANIMATION; }
	};
	
	
	class LoadAnimationReturnType : public GameEventReturnType
	{
		Animation* m_animation;
		
	public:
		LoadAnimationReturnType(Animation* animation) : GameEventReturnType(), m_animation(animation)
		{
		}
		
		virtual GameEventType getGameEventTYpe() { return GameEventType::LOAD_ANIMATION; }
		
		Animation* getAnimation() { return m_animation; }
	};
	
}
