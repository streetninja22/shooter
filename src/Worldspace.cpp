#include "Worldspace.h"
#include "exceptions.h"

namespace shooter
{
	
	Worldspace::Worldspace(EventBus* bus) : EventNode(bus), m_usedArrayLength(0), m_space(std::array<Object*, 1028>())
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
				at(index)->update();
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
	
	
	void Worldspace::update()
	{
		updateStates();
		updateCollisions();
	}
	
}

