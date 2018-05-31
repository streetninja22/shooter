#include "GameGraphics.h"


void shooter::renderSpace(Worldspace& space, EventBus* bus)
{
	for (int index = 0; index < space.usedSize(); ++index)
	{
		if (space.at(index) != nullptr)
		{
			Object* object = space.at(index);
			
			gfx::RenderDrawRectEvent* event = new gfx::RenderDrawRectEvent({static_cast<int>(object->getPosition().x), static_cast<int>(object->getPosition().y), static_cast<int>(object->getSize().x), static_cast<int>(object->getSize().y)}, {255, 255, 0, 0});
			
			bus->addEvent(event);
		}
	}
}
