#pragma once

#include "general.h"
#include "Object.h"
#include <array>
#include "framework/Event.h"

namespace shooter
{

	class Worldspace : public EventNode
	{
				
		std::array<Object*, 1028> m_space;
		
		
		//Furthest point in array allocated so far
		unsigned short m_usedArrayLength;

		
		/* Returns a reference to the pointer at the given index
		 *
		 */
		Object*& getValueAt(unsigned int index) { return m_space.at(index); }
		
		Vector m_boundarySize;
		
		//by how far an object much exceed the boundary to be deleted. Represented in percentage of the boundary size
		double m_boundaryThreshold;
		
		bool m_enforcesBoundary;
		
	public:
		/* Clear the worldspace of allocated objects
		*/
		void clearSpace();
		
		/* Add an object to the worldspace
		*
		* @param object An already allocated pointer to the object to add
		*/
		void add(Object* object);
		
		/* Destroy an object in the worldspace
		 *
		 * @param index The index of the object to delete within the array
		 */
		void destroy(unsigned int index);
		
		/* Update the state of each object, including positon, velocity and behavior
		*/
		void updateStates();

		/* Detect and update the collisions of objects in the worldspace
		*/
		void updateCollisions();
		
		/* Detects whether the object collides with the boundary on the X axis
		*/
		bool detectBoundaryCollisionX(Object* object, double threshold);
		
		/* Detects whether the object collides with the boundary on the Y axis
		 */
		bool detectBoundaryCollisionY(Object* object, double threshold);
		
		/* Detects whether the object collides with the boundary
		*/
		bool detectBoundaryCollision(Object* object, double threshold);
		
		/* Deals with objects outside of the Space's boundary
		 @param object The object which is outside of the boundary
		 @param originPos The position before the object collided with the boundary
		*/
		void enforceBoundary(Object* object, Vector originPos);
		
		/* Updates the state of each object and updates collisions
		*/
		void update();
		
		
		Object* at(unsigned int index)		 { return m_space.at(index); }
		
		unsigned int totalSize()			 { return m_space.size(); }
		
		/* Get the size within the array which has already been allocated
		*/
		unsigned int usedSize()			   	 { return m_usedArrayLength; }
		
		/* Get the index of an object based on its pointer
		 *
		 * @param object The pointer to the object to find
		 */
		unsigned int find(Object* object);
		
		
		
		Worldspace(EventBus* bus, bool enforcesBoundary = false, Vector boundarySize = {0, 0}, double boundaryThreshold = 1);
		
		
		~Worldspace()
		{
			clearSpace();
		}
	};

}
