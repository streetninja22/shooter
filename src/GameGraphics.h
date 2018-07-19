#pragma once

#include "Worldspace.h"
#include "Animation.h"
#include "framework/Event.h"
#include "framework/GraphicsEvents.h"
#include "framework/assets.h"
#include "gameevents.h"

namespace shooter
{
	
	void renderSpace(Worldspace& space, EventBus* bus);
	
	
	
	enum AnimationId
	{
		ANIMATION_DEFAULT,
		ANIMATION_REIMU_IDLE,
		ANIMATION_FAIRY_IDLE,
		ANIMATION_BULLET_SMALL,
		ANIMATION_MAX,
	};

	
	
	class VisibleObject : public Object
	{
	protected:
		Animation* m_animation;
		
	public:
		VisibleObject(Vector position, Vector size, Vector velocity = {0, 0}, Vector acceleration = {0, 0}, Worldspace* associatedSpace = nullptr, Behavior* behavior = nullptr, Animation* animation = nullptr) : Object(position, size, velocity, acceleration, associatedSpace, behavior), m_animation(animation)
		{
		}
		
		gfx::Sprite getNextAnimationFrame();
	};
	
	
	
	
	
	
	class GraphicsManager : public evnt::EventNode
	{
		gfx::Texture* m_spriteSheet;
		
		
	public:
		GraphicsManager(evnt::EventBus* bus);
		
		~GraphicsManager()
		{
			delete m_spriteSheet;
		}
		
		
		void loadSpriteSheet();
		
		Animation* createAnimation(AnimationId anim);
		
		EventReturnType* eventFired(Event* event) override;
		
	};
}
