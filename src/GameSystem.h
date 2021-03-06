#pragma once

#include "framework/System.h"
#include "Object.h"
#include "Worldspace.h"
#include "GameGraphics.h"
#include "Player.h"
#include "Enemy.h"
#include "gameevents.h"
#include "keybindings.h"
#include "enemies.h"


namespace shooter
{

	class GameSystem : public System
	{
		evnt::EventBus* m_gameBus;
		
		Worldspace* m_space;

		PlayerBehavior* m_player;

		bool m_running;

		gfx::Font* m_mainFont;
		
		GraphicsManager m_gfxManager;
		
		gfx::Texture* m_fpsCounter;
		
	public:
		GameSystem(EventBus* bus, Vector gamespaceSize);
		
		~GameSystem()
		{
			
		}
		
		virtual EventReturnType* eventFired(Event* event) override;

		void interpretKeyboardInput(inpt::KeyCode keycode, bool keyState);

		void renderFpsCounter(double framerate);
		
		void update(double framerate, long delay);
		
		void updateGameState();
		
		
	};

}
