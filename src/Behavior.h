#pragma once


class Behavior
{
	Uint32 m_clock;
	
public:
	Behavior() : m_clock(0)
	{
		
	}
	
	virtual void stepBehavior(Uint32 timeStep=1);
	
	void update(Uint32 timeStep=1)
	{
		m_clock += timeStep;
		
		stepBehavior();
	}
	
};
