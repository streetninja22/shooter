#pragma once

#include "Event.h"

using namespace evnt;
class System : public EventNode
{

public:
	System(EventBus* bus) : EventNode(bus)
	{

	}
};
