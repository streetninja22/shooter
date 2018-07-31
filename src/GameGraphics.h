#pragma once

#include "Worldspace.h"
#include "Animation.h"
#include "framework/Event.h"
#include "framework/GraphicsEvents.h"
#include "framework/assets.h"
#include "gameevents.h"
#include "AnimationId.h"

namespace shooter
{
	
	void renderSpace(Worldspace& space, EventBus* bus);

	
	
	class VisibleObject : public Object
	{
	protected:
		Animation* m_animation;
		
	public:
		VisibleObject(Vector position, Vector size, Vector velocity = {0, 0}, Vector acceleration = {0, 0}, Worldspace* associatedSpace = nullptr, Behavior* behavior = nullptr, Animation* animation = nullptr) : Object(position, size, velocity, acceleration, associatedSpace, behavior), m_animation(animation)
		{
		}
		
		gfx::Sprite getNextAnimationFrame();
		
		virtual bool isVisibleObject() override { return true; }
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
		
		void renderSpace(Worldspace& space);
	};
	
	
	
	Animation* getAnimationFromEventReturn(EventReturnType* event);
}
