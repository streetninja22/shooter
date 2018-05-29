#include "GameGraphics.h"


void shooter::renderSpace(Worldspace& space, EventBus* bus)
{
	for (int index = 0; index < space.usedSize(); ++index)
	{
		if (space.at(index) != nullptr)
		{
			Object* object = space.at(index);
			
			gfx::RenderDrawRectEvent* event = new gfx::RenderDrawRectEvent({object->getPosition().x, object->getPosition().y, object->getSize().x, object->getSize().y}, {255, 255, 0, 0});
			
			bus->addEvent(event);
		}
	}
}
