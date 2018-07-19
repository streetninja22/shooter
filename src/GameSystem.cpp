#include "GameSystem.h"
#include "GameGraphics.h"
#include "framework/InputSystem.h"
#include "framework/assets.h"
#include <sstream>


#include <iostream>

#include "framework/functions.h"


#include <vector>

namespace shooter
{
	
	
	class TestObject : public Enemy
	{
	public:
		TestObject(Animation* animation, Vector position, Vector size, Vector velocity = {0, 0}, Vector acceleration = {0, 0}, Worldspace* associatedSpace = nullptr, Behavior* behavior = nullptr) : Enemy(animation, position, size, velocity, acceleration, associatedSpace, behavior)
		{
			
		}
		
		
		virtual void onCollision(Object* collider)
		{
			//std::cout << "Collision detected!\n";
		}
		
		
	};
	
	class TestBehavior : public Behavior
	{
		Object* m_target;
		
	public:
		TestBehavior(Object* parentObject) : Behavior(parentObject)
		{
			m_target = nullptr;
		}
		
		Object* findTarget()
		{
			Worldspace* space = getParent()->getAssociatedSpace();
			
			for (int index = 0; index < space->usedSize(); ++index)
			{
				if (space->at(index) != nullptr)
				{
					if (space->at(index) != getParent())
					{
						m_target = space->at(index);
						return m_target;
					}
				}
			}
		}
		
		Vector findDirectionToTarget()
		{
			//find vector between points
			Vector direction = m_target->getCenter() - getParent()->getCenter();
			
			//normalize vector
			double length = sqrt(direction.x + direction.y); //use the pythagorean theroem to get the length of the vector between the parent and target
			
			Vector normalizedDirection = {direction.x / length, direction.y / length};
			
			return normalizedDirection;
		}
		
		virtual void stepBehavior(uint32_t timeStep) override
		{
			if (m_target == nullptr)
			{
				findTarget();
				return;
			}
			
			if (m_clock % 10 == 0)
			{
				m_parentObject->getAssociatedSpace()->add(new Object(m_parentObject->getCenter(), { 10, 10 }, findDirectionToTarget(), { 0, 0 }, m_parentObject->getAssociatedSpace(), nullptr));
			}
		}
		
	};
	
	
	
	GameSystem::GameSystem(EventBus* bus) : System(bus), m_gameBus(new evnt::EventBus()), m_space(new Worldspace(m_gameBus))
	{
		PlayerBehavior* player = new PlayerBehavior(nullptr, 6);

		m_space->add(new Player({ 128, 128 }, { 32, 32 }, { 0, 0 }, { 0, 0 }, m_space, player));

		m_space->add(new Enemy({ 28, 68 }, { 32, 32 }, { 0, 0 }, { 0, 0 }, m_space, new TestBehavior(nullptr)));

		m_player = player;


		//load font
		m_mainFont = static_cast<gfx::LoadFontReturnType*>(fireEventNow(new gfx::LoadFontEvent(file::getResourceDirectory("/font/Roboto/Roboto-Regular.ttf"), 12)))->getFont();

		if (m_mainFont != nullptr)
		{
			std::cout << "Font loaded successfully\n";
		}


	}
	

	//TODO: wtf this isn't what I meant to do, I need to fix this
	EventReturnType* GameSystem::eventFired(Event* event)
	{
		if (event->getEventType() == EventType::INPUT)
		{
			using namespace inpt;
			inpt::InputEvent* inEvent = dynamic_cast<inpt::InputEvent*>(event);

			if (inEvent->getInputType() == inpt::InputEventType::KEYBOARD)
			{
				inpt::KeyboardEvent* keyEvent = dynamic_cast<inpt::KeyboardEvent*>(event);

				bool state;

				if (keyEvent->getType() == KeyEventType::KEYDOWN)
					state = true;
				else
					state = false;

				switch (keyEvent->getKeyCode())
				{
				case KEYCODE_ARROW_LEFT:
					m_player->setActionStatus(PlayerBehavior::ACTION_MOVE_LEFT, state);
					break;

				case KEYCODE_ARROW_RIGHT:
					m_player->setActionStatus(PlayerBehavior::ACTION_MOVE_RIGHT, state);
					break;

				case KEYCODE_ARROW_UP:
					m_player->setActionStatus(PlayerBehavior::ACTION_MOVE_FORWARD, state);
					break;

				case KEYCODE_ARROW_DOWN:
					m_player->setActionStatus(PlayerBehavior::ACTION_MOVE_BACKWARD, state);
					break;

				case KEYCODE_SPACE:
				{
					if (state == true)
					{
						if (m_running == true)
							m_running = false;
						else
							m_running = true;
					}

					break;
				}
				}
			}

		}

		return nullptr;


	}



	void GameSystem::updateInput()
	{
		
	}


	void GameSystem::update(double framerate, long delay)
	{

		long start = getTicks();
		if (m_running)
			m_space->update();
		
		//show FPS and objects on field
		std::stringstream textStream;
		textStream << framerate << " : " << delay << "\n" << m_space->usedSize();

		gfx::LoadTextureReturnType* text = static_cast<gfx::LoadTextureReturnType*>(fireEventNow(new gfx::LoadTextEvent(textStream.str(), m_mainFont, { 255, 255, 255, 255 })));

		addEvent(new gfx::RenderImageEvent(text->getTexture(), NULL, new gfx::Rect{ 480, 32, 128, 32 }));

		
		//render
		renderSpace(*m_space, m_eventBus);
		
	}
	
	
	
}
