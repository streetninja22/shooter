#pragma once

#include "general.h"
#include "Behavior.h"
#include "Animation.h"

#include <framework/Event.h>

namespace shooter
{
	enum class ObjectType
	{
		DEFAULT,
		PLAYER,
		BULLET,
		ENEMY,
		SHOT,

	};




	class Worldspace;

	class Object
	{
	protected:
		Vector m_position;
		Vector m_size;
		Vector m_velocity;
		Vector m_acceleration;
		
		Worldspace* m_associatedSpace;
		
		Behavior* m_behavior;
		
	public:
		/*Create a blank object*/
		Object()
		{
			
		}
		
		Object(Vector position, Vector size, Vector velocity = {0, 0}, Vector acceleration = {0, 0}, Worldspace* associatedSpace = nullptr, Behavior* behavior = nullptr) : m_position(position), m_size(size), m_velocity(velocity), m_acceleration(acceleration), m_associatedSpace(associatedSpace), m_behavior(behavior)
		{
			if (m_behavior != nullptr)
				m_behavior->changeParent(this);
		}
		
		
		virtual ~Object()
		{
			if (m_behavior != nullptr)
				delete m_behavior;
		}
		
		
		//access functions
		Vector getPosition()								const { return m_position; }
		Vector getSize()									const { return m_size; }
		Vector getVelocity()								const { return m_velocity; }
		Vector getAcceleration()							const { return m_acceleration; }
		Worldspace* getAssociatedSpace()					const { return m_associatedSpace; }

		virtual ObjectType getObjectType()					const { return ObjectType::DEFAULT; }

		Vector getCenter()									const { return m_position + m_size / 2; }
		
		
		void setPosition(Vector newPosition)				{ m_position = newPosition; }
		void setSize(Vector newSize)						{ m_size = newSize; }
		void setVelocity(Vector newVelocity)				{ m_velocity = newVelocity; }
		void setAcceleration(Vector newAcceleration)		{ m_acceleration = newAcceleration; }
		void changeAssociatedSpace(Worldspace* space)		{ m_associatedSpace = space; }
		
		
		//Tells if object is a VisibleObject or not. Overloaded in VisibleObject classs
		virtual bool isVisibleObject() 						{ return false; }
		
		/* Function called when colliding with another object
		 */
		virtual void onCollision(Object* collider)
		{
		}

		/* Destroy and delete this object
		*/
		virtual void destroy(); //TODO make this not crash the game
		
		
		/* Update the position and velocity of object
		 */
		void move();
		
		
		/* Update the object, including position and behavior
		 */
		void update();


		/* Adds an event to the queue of the game of the associated space
		*/
		void addEvent(evnt::Event* event);
		
		/* Adds an event to the queue of the game of the associated space
		 */
		evnt::EventReturnType* fireEventNow(evnt::Event* event);
		
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
