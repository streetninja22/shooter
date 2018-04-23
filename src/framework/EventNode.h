#pragma once

#include "Event.h"
#include "EventBus.h"


namespace Event
{
	class EventNode
	{
	protected:
		EventBus *m_eventBus;

		virtual void eventFired(Event event)
		{

		}

		std::function<void(Event)> getEventListener()
		{
			auto eventListener = [=](Event event) -> void {
				this->eventFired(event);
			};

			return eventListener;
		}

		void addEvent(Event event)
		{
			m_eventBus->addEvent(event);
		}
		
	public:

		EventNode(EventBus* bus) : m_eventBus(bus)
		{
			bus->addListener(getEventListener());
		}
	};

}
