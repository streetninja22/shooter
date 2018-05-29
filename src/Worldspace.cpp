#include "Worldspace.h"

namespace shooter
{
	
	Worldspace::Worldspace() : m_usedArrayLength(0), m_space(std::array<Object*, 1028>())
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
				
				if (index > m_usedArrayLength)
				{
					m_usedArrayLength = index;
				}
				return;
			}
		}
	}
	
	
	
	void Worldspace::updatePositions()
	{
		for (int index = 0; index < m_usedArrayLength; ++index)
		{
			if (at(index) != nullptr)
				at(index)->move();
		}
	}
	
	
	void Worldspace::updateCollisions()
	{
		for (int index1 = 0; index1 < m_usedArrayLength; ++index1)
		{
			for (int index2 = ++index1; index2 <= m_usedArrayLength; ++index2)
			{
				if (at(index1) != nullptr && at(index2) != nullptr)
					detectCollision(at(index1), at(index2));
			}
		}
	}
	
	
	void Worldspace::update()
	{
		updatePositions();
		updateCollisions();
	}
	
}

