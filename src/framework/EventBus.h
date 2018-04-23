#pragma once

#include "Event.h"
#include <vector>
#include <queue>
#include <functional>

namespace Event
{

	class EventBus
	{
		std::queue<Event> m_eventQueue;
		std::vector <std::function<void(Event)>> m_eventListeners;

	public:
		EventBus() {}
		~EventBus() {}

		void addListener(std::function<void(Event)> listener)
		{
			m_eventListeners.push_back(listener);
		}

		void addEvent(Event event)
		{
			m_eventQueue.push(event);
		}

		void callListeners()
		{
			while (!m_eventQueue.empty())
			{
				for (auto& index : m_eventListeners)
					(index)(m_eventQueue.front());
				m_eventQueue.pop();
			}
		}

	};

}