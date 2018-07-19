#include "GameGraphics.h"

namespace shooter
{

	void renderSpace(Worldspace& space, EventBus* bus)
	{
		for (int index = 0; index < space.usedSize(); ++index)
		{
			if (space.at(index) != nullptr)
			{
				Object* object = space.at(index);
				
				gfx::RenderDrawRectEvent* event = new gfx::RenderDrawRectEvent({static_cast<int>(object->getPosition().x), static_cast<int>(object->getPosition().y), static_cast<int>(object->getSize().x), static_cast<int>(object->getSize().y)}, {255, 255, 0, 0});
				
				bus->addEvent(event);
			}
		}
	}

	
	gfx::Sprite VisibleObject::getNextAnimationFrame()
	{
		if (m_animation)
		{
			return m_animation->getNextFrame();
		}
		else
			return gfx::Sprite {nullptr, nullptr};
	}

	
	
	GraphicsManager::GraphicsManager(evnt::EventBus* bus) : EventNode(bus)
	{
		loadSpriteSheet();
	}
	
	void GraphicsManager::loadSpriteSheet()
	{
		std::string filepath = file::getResourceDirectory("/gfx/spritesheet.png");
		
		EventReturnType* loadReturn = fireEventNow(new gfx::LoadTextureEvent(filepath));
		
		m_spriteSheet = static_cast<gfx::LoadTextureReturnType*>(loadReturn)->getTexture();
	}
	
	Animation* GraphicsManager::createAnimation(AnimationId anim)
	{
		using namespace gfx;
		
		std::vector<AnimationFrame> animTrack;
		
		bool isStatic = false;
		
		switch(anim)
		{
			case ANIMATION_REIMU_IDLE:
			{
				animTrack.push_back({{m_spriteSheet, new Rect {0, 0, 16, 16}}, 3});
				animTrack.push_back({{m_spriteSheet, new Rect {16, 0, 16, 16}}, 3});
				animTrack.push_back({{ m_spriteSheet, new Rect {32, 0, 16, 16}}, 3});
				break;
			}
			case ANIMATION_FAIRY_IDLE:
			{
				animTrack.push_back({{m_spriteSheet, new Rect {0, 16, 16, 16}}, 0});
				isStatic = true;
				break;
			}
			case ANIMATION_BULLET_SMALL:
			{
				animTrack.push_back({{m_spriteSheet, new Rect{16, 16, 16, 16}}, 0});
				isStatic = true;
				break;
			}
		}
	}
	
	
	EventReturnType* GraphicsManager::eventFired(evnt::Event* event)
	{
		if (event->getEventType() == EventType::GAME)
		{
			GameEvent* gameEvent = static_cast<GameEvent*>(event);
			
			switch (gameEvent->getGameEventType())
			{
				case (GameEventType::LOAD_ANIMATION):
				{
					LoadAnimationEvent* animEvent = static_cast<LoadAnimationEvent*>(gameEvent);
					
					Animation* anim = createAnimation(animEvent->getAnimId());
					
					*(animEvent->getAnimPtr2()) = anim; //this is kind of stupid tbh. oh well
					
				}
			}
		}
	}
}
