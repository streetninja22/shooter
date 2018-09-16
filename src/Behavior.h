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
		
	public:
		Behavior() : m_clock(0)
		{
			
		}
		
		virtual ~Behavior()
		{
			
		}
		
		virtual void stepBehavior(Object* parent, uint32_t timeStep)
		{
		}
		
		void resetClock()
		{
			m_clock = 0;
		}
		
		void update(Object* parent, uint32_t timeStep=1)
		{
			m_clock += timeStep;
			
			if (parent != nullptr)
				stepBehavior(parent, m_clock);
		}
		
		
	};

}
