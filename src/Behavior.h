#pragma once

#include <stdint.h>


#include <iostream>

namespace shooter
{
	class Object;

	class Behavior
	{
	protected:
		uint32_t m_clock;
		Object* m_parentObject;
		
	public:
		Behavior(Object* parentObject) : m_clock(0), m_parentObject(parentObject)
		{
			
		}
		
		Behavior() : m_clock(0), m_parentObject(nullptr)
		{
		}
		
		virtual ~Behavior()
		{
			
		}
		
		virtual void stepBehavior(uint32_t timeStep)
		{
		}
		
		void update(uint32_t timeStep=1)
		{
			m_clock += timeStep;
			
			stepBehavior(m_clock);
		}
		
		Object* getParent() { return m_parentObject; }
		void changeParent(Object* parentObject)
		{
			m_parentObject = parentObject;
			
		}
		
	};

}
