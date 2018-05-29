#pragma once

#include "general.h"
#include "Object.h"
#include <array>

namespace shooter
{

	class Worldspace
	{
				
		std::array<Object*, 1028> m_space;
		
		
		//Furthest point in array allocated so far
		unsigned short m_usedArrayLength;
		
		
		
	public:
		
		void clearSpace();
		
		void add(Object* object);
		
		void updatePositions();
		
		void updateCollisions();
		
		void update();
		
		
		Object* at(unsigned int index)
		{
			return m_space.at(index);
		}
		
		unsigned int totalSize()
		{
			return m_space.size();
		}
		
		unsigned int usedSize()
		{
			return m_usedArrayLength;
		}
		
		
		Worldspace();
		
		
		~Worldspace()
		{
			clearSpace();
		}
	};

}
