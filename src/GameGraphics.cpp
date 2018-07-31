#include "GameGraphics.h"


#define SPRITE_SCALE_FACTOR 1

namespace shooter
{

	void GraphicsManager::renderSpace(Worldspace& space)
	{
		for (int index = 0; index < space.usedSize(); ++index)
		{
			if (space.at(index) != nullptr)
			{
				if (space.at(index)->isVisibleObject())
				{
					VisibleObject* object = dynamic_cast<VisibleObject*>(space.at(index));

					gfx::Sprite sprite = object->getNextAnimationFrame();
					
					gfx::Rect* dstRect = new gfx::Rect();
					
					dstRect->x = object->getPosition().x;
					dstRect->y = object->getPosition().y;
					
					dstRect->w = sprite.texture->getWidth() * SPRITE_SCALE_FACTOR;
					dstRect->h = sprite.texture->getHeight() * SPRITE_SCALE_FACTOR;
					
					addEvent(new gfx::RenderImageEvent(object->getNextAnimationFrame(), dstRect));
				}
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
				animTrack.push_back({{m_spriteSheet, new Rect {0, 0, 16, 16}}, 15});
				animTrack.push_back({{m_spriteSheet, new Rect {16, 0, 16, 16}}, 15});
				animTrack.push_back({{ m_spriteSheet, new Rect {32, 0, 16, 16}}, 15});
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
		
		Animation* returnAnim = new Animation(animTrack);
		
		returnAnim->setStatic(isStatic);
		
		return returnAnim;
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
					
					return new LoadAnimationReturnType(anim);
					
				}
			}
		}
		return nullptr;
	}
	
	
	
	Animation* getAnimationFromEventReturn(EventReturnType* event)
	{
		if (event != nullptr)
		{
			if (event->getType() == EventType::GAME)
			{
				if (dynamic_cast<GameEventReturnType*>(event)->getGameEventType() == GameEventType::LOAD_ANIMATION)
				{
					LoadAnimationReturnType* animEvent = dynamic_cast<LoadAnimationReturnType*>(event);

					return animEvent->getAnimation();
				}
			}
		}
		return nullptr;
	}
}
