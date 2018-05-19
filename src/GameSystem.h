#pragma once

#include "framework/System.h"
#include "Object.h"


namespace shooter
{

	class GameSystem : System
	{
		evnt::EventBus* m_gameBus;
		
		
	public:
		GameSystem(EventBus* bus) : System(bus), m_gameBus(new evnt::EventBus())
		{
			
		}
		
		~GameSystem()
		{
			
		}
		
		
		void update();
		
		
	};

}
