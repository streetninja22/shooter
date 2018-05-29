#pragma once

#include "general.h"
#include "Behavior.h"

namespace shooter
{
	class Worldspace;

	class Object
	{
		Pair m_position;
		Pair m_size;
		Pair m_velocity;
		Pair m_acceleration;
		
		Worldspace* m_associatedSpace;
		
		Behavior* m_behavior;
		
	public:
		/*Create a blank object*/
		Object()
		{
			
		}
		
		Object(Pair position, Pair size, Pair velocity = {0, 0}, Pair acceleration = {0, 0}, Worldspace* associatedSpace = nullptr, Behavior* behavior = nullptr) : m_position(position), m_size(size), m_velocity(velocity), m_acceleration(acceleration), m_associatedSpace(associatedSpace), m_behavior(behavior)
		{
			
		}
		
		
		virtual ~Object()
		{
			if (m_behavior != nullptr)
				delete m_behavior;
		}
		
		
		//access functions
		Pair getPosition()								const { return m_position; }
		Pair getSize()									const { return m_size; }
		Pair getVelocity()								const { return m_velocity; }
		Pair getAcceleration()							const { return m_acceleration; }
		Worldspace* getAssociatedSpace()				const { return m_associatedSpace; }
		
		
		void setPosition(Pair newPosition)				{ m_position = newPosition; }
		void setSize(Pair newSize)						{ m_size = newSize; }
		void setVelocity(Pair newVelocity)				{ m_velocity = newVelocity; }
		void setAcceleration(Pair newAcceleration)		{ m_acceleration = newAcceleration; }
		void changeAssociatedSpace(Worldspace* space)	{ m_associatedSpace = space; }
		
		
		/* Function called when colliding with another object
		 */
		virtual void onCollision(Object* collider)
		{
		}
		
		
		/* Update the position and velocity of object
		 */
		void move();
		
		
		/* Update the object, including position and behavior
		 */
		void update();
		
		/* Destroy and delete this object
		 */
		void destroy();
		
	};
	
	
	
	
	
	/* Check if two objects are colliding
	 *
	 * @param a The first object
	 * @param b The second object
	 */
	bool checkCollision(const Object* a, const Object* b);
	
	
	/* Check if two objects are colliding, and then call their onCollision functions if so
	 *
	 * @param a The first object
	 * @param b The second object
	 */
	bool detectCollision(Object* a, Object* b);
}
