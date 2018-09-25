#include "Worldspace.h"
#include "exceptions.h"

namespace shooter
{
	
	Worldspace::Worldspace(EventBus* bus, bool enforcesBoundary, Vector boundarySize, double boundaryThreshold) : EventNode(bus), m_usedArrayLength(0),  m_space(std::array<Object*, 1028>()), m_boundarySize(boundarySize), m_boundaryThreshold(boundaryThreshold), m_enforcesBoundary(enforcesBoundary)
	{
	}
	
	
	void Worldspace::clearSpace()
	{
		for (Object* index : m_space)
		{
			if (index != nullptr)
				delete index;
		}
	}
	
	
	
	void Worldspace::add(Object* object)
	{
		for (int index = 0; index < m_space.size(); ++index)
		{
			if (m_space.at(index) == nullptr)
			{
				m_space.at(index) = object;
				object->changeAssociatedSpace(this);
				
				if (index >= m_usedArrayLength)
				{
					m_usedArrayLength = index + 1;
				}
				return;
			}
		}
	}
	
	
	
	void Worldspace::destroy(unsigned int index)
	{
		if (at(index) != nullptr)
		{
			delete at(index);
			getValueAt(index) = nullptr;
		}
	}
	
	
	unsigned int Worldspace::find(Object* object)
	{
		for (int index = 0;index < m_usedArrayLength; ++index)
		{
			if (at(index) == object)
			{
				return index;
			}
		}
		throw new ObjectNotFoundException();
	}
	
	
	void Worldspace::updateStates()
	{
		for (int index = 0; index < m_usedArrayLength; ++index)
		{
			if (at(index) != nullptr)
			{
				Vector originPos = at(index)->getPosition();
				
				at(index)->update();
				
				if (m_enforcesBoundary)
					enforceBoundary(at(index), originPos);
			}
		}
	}
	
	
	void Worldspace::updateCollisions()
	{
		for (int index1 = 0; index1 < m_usedArrayLength; ++index1)
		{
			for (int index2 = 0; index2 < index1; ++index2)
			{
				if (at(index1) != nullptr && at(index2) != nullptr)
					detectCollision(at(index1), at(index2));
			}
		}
	}
	
	
	bool Worldspace::detectBoundaryCollisionX(Object* object, double threshold)
	{
		if (object != nullptr)
		{
			double thresholdSpaceX = m_boundarySize.x * threshold;
			
			if (object->getPosition().x < 0 - thresholdSpaceX || object->getPosition().x + object->getSize().x > m_boundarySize.x + thresholdSpaceX)
				return true;
		}
		return false;
	}
	
	bool Worldspace::detectBoundaryCollisionY(Object* object, double threshold)
	{
		if (object != nullptr)
		{
			double thresholdSpaceY = m_boundarySize.y * threshold;
			
			if (object->getPosition().y < 0 - thresholdSpaceY || object->getPosition().y + object->getSize().y > m_boundarySize.y + thresholdSpaceY)
				return true;
		}
		return false;
	}
	
	bool Worldspace::detectBoundaryCollision(Object* object, double threshold)
	{
		if (detectBoundaryCollisionX(object, threshold) || detectBoundaryCollisionY(object, threshold))
			return true;
		return false;
	}
	
	void Worldspace::enforceBoundary(Object* object, Vector originPos)
	{
		//detect collision with boundary
		if (detectBoundaryCollision(object, 0))
		{
			
			switch(object->getObjectType())
			{
				case ObjectType::BULLET:
				{
					if (detectBoundaryCollision(object, m_boundaryThreshold))
						object->destroy();
					break;
				}
				case ObjectType::PLAYER:
				{
					//checks which side collision is with and only changes the axis it's colliding with
					if (detectBoundaryCollisionX(object, 0))
					{
						object->setPositionX(originPos.x);
					}
					if (detectBoundaryCollisionY(object, 0))
					{
						object->setPositionY(originPos.y);
					}
					
					break;
				}
			}
		}
	}
	
	
	void Worldspace::update()
	{
		updateStates();
		updateCollisions();
	}
	
}

