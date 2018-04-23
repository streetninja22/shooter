#pragma once

#include <functional>
#include <array>
#include <queue>

namespace evnt
{
	enum class EventType
	{
		DEFAULT,
		GRAPHICS,
		INPUT,
		SOUND,
	};


	class EventReturnType
	{
		EventType m_type;

	public:
		EventReturnType(EventType type) : m_type(type)
		{
		}

		virtual ~EventReturnType()
		{

		}

		EventType getType() { return m_type; }

	};

	class Event
	{

		EventType m_type;

	public:
		Event(EventType type) : m_type(type)
		{

		}

		virtual ~Event()
		{

		}

		virtual EventType getEventType() { return m_type; }
	};
    





    typedef std::function<EventReturnType*(Event*)> EventListener;

	class EventBus
	{
		//the current events to be called upon update
		std::queue<Event*> m_eventQueue;

		//the evetn listener functions to be called by this event bus
		std::vector<EventListener> m_eventListeners;

		//the list of EventReturnType values to be deleted upon garbage collection
		std::vector<EventReturnType*> m_returnGarbageList;

	public:
		EventBus() {}

		/* adds a listener function to the event bus
		* param listener The listener to add
		*/
		void addListener(EventListener listener)
		{
			m_eventListeners.push_back(listener);
		}

		/* adds an event to the queue
		* param event the event to add
		*/
		void addEvent(Event* event)
		{
			m_eventQueue.push(event);
		}

		/* Adds an EventReturnType value to the garbage collection list to be deleted next update
		* param value The EventReturnType to be garbage collected
		*/
		void addToGarbageList(EventReturnType* value)
		{
			m_returnGarbageList.push_back(value);
		}

		/* Does garbage collection on EventReturnType values which have passed through the bus
		*/
		void deleteOldReturnValues()
		{
			while (!m_returnGarbageList.empty())
			{
				if (m_returnGarbageList.back() != nullptr)
				{
					delete m_returnGarbageList.back();
					m_returnGarbageList.pop_back();
				}
			}
		}

		/* call the event listeners with the next event in queue
		*/
		void callListeners()
		{
			while (!m_eventQueue.empty())
			{
				for (auto& index : m_eventListeners)
				{
					EventReturnType* returned = (index)(m_eventQueue.front());

					if (returned != nullptr)
					{
						addToGarbageList(returned);
					} 
				}
				delete m_eventQueue.front();
				m_eventQueue.pop();
			}
		}

		/* Call all event listeners with the given event. Returns the return value of the first listener to give a non-null value
		* param event The event to be used as the argument of listener functions
		*/
		EventReturnType* fireEventNow(Event* event)
		{
			EventReturnType* returnValue = nullptr;

			for (EventListener index : m_eventListeners)
			{
				EventReturnType* returned = (index)(event);

				if (!(returned == nullptr))
				{
					if (returnValue == nullptr)
					{
						returnValue = returned;
					}
					addToGarbageList(returned);
				}
			}

			delete event;
			return returnValue;
		}

		void clearEventQueue()
		{
			for (int index = 0; index < m_eventQueue.size(); ++index)
			{
				delete m_eventQueue.front();
				m_eventQueue.pop();
			}
		}


		void update()
		{
			callListeners();
			deleteOldReturnValues();
		}

		~EventBus()
		{
			clearEventQueue();
		}

	};






	class EventNode
	{
	protected:
		EventBus *m_eventBus;

		/* node event listener
		* param event the event which caused the function to fire
		*/
		virtual EventReturnType* eventFired(Event* event)
		{
			return nullptr;
		}

		/* returns the class event listener
		*/
		EventListener getEventListener()
		{
			EventListener eventListener = [=](Event* event) -> EventReturnType*
			{
				return this->eventFired(event);
			};

			return eventListener;
		}

		/* adds event to the associated bus queue
		* param event the event to add
		*/
		void addEvent(Event* event)
		{
			m_eventBus->addEvent(event);
		}

	public:
		virtual void update()
		{

		}

		EventNode(EventBus* bus) : m_eventBus(bus)
		{
			bus->addListener(getEventListener());
		}

		virtual ~EventNode()
		{

		}
	};

}
