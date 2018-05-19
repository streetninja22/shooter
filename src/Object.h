#pragma once

#include "general.h"
#include "Worldspace.h"
#include "Behavior.h"

namespace shooter
{

	class Object
	{
		Pair m_position;
		Pair m_size;
		Pair m_velocity;
		Pair m_acceleration;
		
		Worldspace* associatedSpace;
		
	public:
		Object()
		{
			
		}
		
		
		virtual void onCollision();
		
		virtual void update();
		
	};
}
