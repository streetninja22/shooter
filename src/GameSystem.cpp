#include "GameSystem.h"
#include "GameGraphics.h"


#include <iostream>

namespace shooter
{
	
	
	class TestObject : public Object
	{
	public:
		TestObject(Pair position, Pair size, Pair velocity = {0, 0}, Pair acceleration = {0, 0}) : Object(position, size, velocity, acceleration)
		{
			
		}
		
		
		virtual void onCollision(Object* collider)
		{
			std::cout << "Collision detected!\n";
		}
		
		
	};
	
	
	
	GameSystem::GameSystem(EventBus* bus) : System(bus), m_gameBus(new evnt::EventBus()), m_space(new Worldspace())
	{
		
		m_space->add(new TestObject({0, 0}, {128, 128}));
		m_space->add(new TestObject({128, 0}, {128, 128}));
	}
	
	
	void GameSystem::update()
	{
		m_space->update();
		
		renderSpace(*m_space, m_eventBus);
		
	}
	
	
	
	
}
