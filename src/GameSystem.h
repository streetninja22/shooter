#pragma once

#include "framework/System.h"
#include "Object.h"
#include "Worldspace.h"
#include "GameGraphics.h"
#include "Player.h"
#include "Enemy.h"


namespace shooter
{

	class GameSystem : public System
	{
		evnt::EventBus* m_gameBus;
		
		Worldspace* m_space;

		PlayerBehavior* m_player;

		bool m_running;

		gfx::Font* m_mainFont;
		
		
		gfx::Texture* m_sprites;
		
		Animation* m_animation;
		
	public:
		GameSystem(EventBus* bus);
		
		~GameSystem()
		{
			
		}
		
		virtual EventReturnType* eventFired(Event* event) override;

		void updateInput();
		
		void update(double framerate, long delay);
		
		
	};

}
