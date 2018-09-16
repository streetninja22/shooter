#pragma once

#include "GameSystem.h"

namespace shooter
{
	
	class TestObject : public Enemy
	{
	public:
		TestObject(Vector position, Vector size, Vector velocity = {0, 0}, Vector acceleration = {0, 0}, Worldspace* associatedSpace = nullptr, Behavior* behavior = nullptr, Animation* animation = nullptr) : Enemy(position, size, velocity, acceleration, associatedSpace, behavior, animation)
		{
			
		}
		
		
		virtual void onCollision(Object* collider)
		{
			//std::cout << "Collision detected!\n";
		}
		
		
	};

	class TestBehavior : public Behavior
	{
		Object* m_target;
		
		Animation* m_bulletAnimation;
		
	public:
		TestBehavior() : Behavior(), m_bulletAnimation(nullptr)
		{
			m_target = nullptr;
		}
		
		Object* findTarget(Object* parent)
		{
			Worldspace* space = parent->getAssociatedSpace();
			
			for (int index = 0; index < space->usedSize(); ++index)
			{
				if (space->at(index) != nullptr)
				{
					if (space->at(index) != parent)
					{
						m_target = space->at(index);
						return m_target;
					}
				}
			}
		}
		
		Vector findDirectionToTarget(Object* parent)
		{
			//find vector between points
			Vector direction = m_target->getCenter() - parent ->getCenter();
			
			//normalize vector
			double length = sqrt(direction.x + direction.y); //use the pythagorean theroem to get the length of the vector between the parent and target
			
			Vector normalizedDirection = {direction.x / length, direction.y / length};
			
			return normalizedDirection;
		}
		
		virtual void stepBehavior(Object* parent, uint32_t timeStep) override
		{
			if (m_bulletAnimation == nullptr)
			{
				m_bulletAnimation = getAnimationFromEventReturn(parent->fireEventNow(new LoadAnimationEvent(ANIMATION_BULLET_SMALL)));
				
			}
			
			if (m_target == nullptr)
			{
				findTarget(parent);
				return;
			}
			
			if (m_clock % 10 == 0)
			{
				parent->getAssociatedSpace()->add(new Bullet((parent->getCenter() - 5), { 10, 10 }, findDirectionToTarget(parent), { 0, 0 }, parent->getAssociatedSpace(), nullptr, m_bulletAnimation));
			}
		}
		
	};
}
