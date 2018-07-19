#include "Object.h"
#include "Worldspace.h"

namespace shooter
{
	
	void Object::move()
	{
		m_velocity += m_acceleration;
		m_position += m_velocity;
	}
	
	void Object::update()
	{
		if (m_behavior)
			m_behavior->update();
		
		move();
	}
	
	
	void Object::destroy()
	{
		unsigned int index = m_associatedSpace->find(this);
		
		m_associatedSpace->destroy(index);
	}
	
	
	
	void Object::addEvent(Event* event)
	{
		m_associatedSpace->addEvent(event);
	}

	
	
	
	
	bool checkCollision(const Object* a, const Object* b)
	{
		if ((a->getPosition().x < b->getPosition().x + b->getSize().x) && (a->getPosition().x + a->getSize().x > b->getPosition().x))
		{
			if ((a->getPosition().y < b->getPosition().y + b->getSize().y) && (a->getPosition().y + a->getSize().y > b->getPosition().y))
				{
					return true;
				}
		}

		return false;
	}
	
	bool detectCollision(Object* a, Object* b)
	{
		if (checkCollision(a, b))
		{
			a->onCollision(b);
			b->onCollision(a);
			return true;
		}
		return false;
	}
}
