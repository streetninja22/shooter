#pragma once

#include "framework/System.h"
#include "Object.h"
#include "Worldspace.h"
#include "GameGraphics.h"


namespace shooter
{

	class GameSystem : public System
	{
		evnt::EventBus* m_gameBus;
		
		Worldspace* m_space;
		
	public:
		GameSystem(EventBus* bus);
		
		~GameSystem()
		{
			
		}
		
		
		void update();
		
		
	};

}
