#include "GameSystem.h"
#include "GameGraphics.h"


#include <iostream>

namespace shooter
{
	
	
	class TestObject : public Object
	{
	public:
		TestObject(Vector position, Vector size, Vector velocity = {0, 0}, Vector acceleration = {0, 0}, Worldspace* associatedSpace = nullptr, Behavior* behavior = nullptr) : Object(position, size, velocity, acceleration, associatedSpace, behavior)
		{
			
		}
		
		
		virtual void onCollision(Object* collider)
		{
			std::cout << "Collision detected!\n";
		}
		
		
	};
	
	class TestBehavior : public Behavior
	{
		Object* m_target;
		
	public:
		TestBehavior(Object* parentObject) : Behavior(parentObject)
		{
			m_target = nullptr;
		}
		
		Object* findTarget()
		{
			Worldspace* space = getParent()->getAssociatedSpace();
			
			for (int index = 0; index < space->usedSize(); ++index)
			{
				if (space->at(index) != nullptr)
				{
					if (space->at(index) != getParent())
					{
						m_target = space->at(index);
						return m_target;
					}
				}
			}
		}
		
		Vector findDirectionToTarget()
		{
			//find vector between points
			Vector direction = m_target->getPosition() - getParent()->getPosition();
			
			//normalize vector
			double length = sqrt(direction.x + direction.y); //use the pythagorean theroem to get the length of the vector between the parent and target
			
			Vector normalizedDirection = {direction.x / length, direction.y / length};
			
			return normalizedDirection;
		}
		
		virtual void stepBehavior(uint32_t timeStep) override
		{
			if (m_target == nullptr)
			{
				findTarget();
				return;
			}
			
			getParent()->setVelocity(findDirectionToTarget());
		}
		
	};
	
	
	
	GameSystem::GameSystem(EventBus* bus) : System(bus), m_gameBus(new evnt::EventBus()), m_space(new Worldspace())
	{
		
		m_space->add(new TestObject({258, 128}, {128, 128}));
		
		TestBehavior* behavior = new TestBehavior(nullptr);
		Object* behavingObject = new TestObject({ 0, 200 }, { 30, 50 }, { 0, 0 }, { 0, 0 }, m_space, behavior);
		behavior->changeParent(behavingObject);
		
		m_space->add(behavingObject);
	}
	
	
	void GameSystem::update()
	{
		m_space->update();
		
		renderSpace(*m_space, m_eventBus);
		
	}
	
	
	
	
}
