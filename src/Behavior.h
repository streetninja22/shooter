#pragma once

#include <stdint.h>

class Behavior
{
	uint32_t m_clock;
	
public:
	Behavior() : m_clock(0)
	{
		
	}
	
	virtual ~Behavior()
	{
		
	}
	
	virtual void stepBehavior(uint32_t timeStep=1)
	{
	}
	
	void update(uint32_t timeStep=1)
	{
		m_clock += timeStep;
		
		stepBehavior();
	}
	
};
