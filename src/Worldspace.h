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
		
		
		//Rectangle which determines the size of the game area. If 0, then it is infinite. Besides certain types, objects outside are destroyed.
		Vector zoneLimitRectPosition;
		Vector zoneLimitRectSize;
		
		
		
	public:
		/* Clear the worldspace of allocated objects
		*/
		void clearSpace();
		
		/* Add an object to the worldspace
		*
		* @param object An already allocated pointer to the object to add
		*/
		void add(Object* object);
		
		/* Update the state of each object, including positon, velocity and behavior
		*/
		void updateStates();

		/* Detect and update the collisions of objects in the worldspace
		*/
		void updateCollisions();
		
		/* Updates the state of each object and updates collisions
		*/
		void update();
		
		
		Object* at(unsigned int index)		 { return m_space.at(index); }
		
		unsigned int totalSize()			 { return m_space.size(); }
		
		/* Get the size within the array which has already been allocated
		*/
		unsigned int usedSize()			   	 { return m_usedArrayLength; }
		
		
		Worldspace();
		
		
		~Worldspace()
		{
			clearSpace();
		}
	};

}
