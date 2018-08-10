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
		TestObject(Vector position, Vector size, Vector velocity = {0, 0}, Vector acceleration = {0, 0}, Worldspace* associatedSpace = nullptr, Behavior* behavior = nullptr, Animation* animation = nullptr) : Enemy(position, size, velocity, acceleration, associatedSpace, behavior, animation)
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
		
		Animation* m_bulletAnimation;
		
	public:
		TestBehavior(Object* parentObject) : Behavior(parentObject), m_bulletAnimation(nullptr)
		{
			m_target = nullptr;
		}
		
		TestBehavior() : Behavior(), m_target(nullptr), m_bulletAnimation(nullptr)
		{
			
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
			if (m_bulletAnimation == nullptr)
			{
				m_bulletAnimation = getAnimationFromEventReturn(m_parentObject->fireEventNow(new LoadAnimationEvent(ANIMATION_BULLET_SMALL)));
				
			}
			
			if (m_target == nullptr)
			{
				findTarget();
				return;
			}
			
			if (m_clock % 10 == 0)
			{
				m_parentObject->getAssociatedSpace()->add(new Bullet(m_parentObject->getCenter(), { 10, 10 }, findDirectionToTarget(), { 0, 0 }, m_parentObject->getAssociatedSpace(), nullptr, m_bulletAnimation));
			}
		}
		
	};
	
	
	
	GameSystem::GameSystem(EventBus* bus) : System(bus), m_gameBus(new evnt::EventBus()), m_gfxManager(bus), m_space(new Worldspace(bus))
	{
		PlayerBehavior* player = new PlayerBehavior(nullptr, 6);
		
		Animation* playerAnim = getAnimationFromEventReturn(fireEventNow(new LoadAnimationEvent(AnimationId::ANIMATION_REIMU_IDLE)));
		
		Animation* enemyAnim = getAnimationFromEventReturn(fireEventNow(new LoadAnimationEvent(AnimationId::ANIMATION_FAIRY_IDLE)));
		

		m_space->add(new Player({ 128, 128 }, { 32, 32 }, { 0, 0 }, { 0, 0 }, m_space, player, playerAnim));

		m_space->add(new Enemy({ 28, 68 }, { 32, 32 }, { 0, 0 }, { 0, 0 }, m_space, new TestBehavior(nullptr), enemyAnim));

		m_player = player;


		//load font
		m_mainFont = static_cast<gfx::LoadFontReturnType*>(fireEventNow(new gfx::LoadFontEvent(file::getResourceDirectory("/font/Roboto/Roboto-Regular.ttf"), 12)))->getFont();

		if (m_mainFont != nullptr)
		{
			std::cout << "Font loaded successfully\n";
		}

		gfx::Texture* background = static_cast<gfx::LoadTextureReturnType*>(fireEventNow(new gfx::LoadTextureEvent(file::getResourceDirectory("/gfx/background.png"))))->getTexture();

		m_gfxManager.setBackground(background);
	}
	
	void GameSystem::interpretKeyboardInput(inpt::KeyCode keycode, bool keyState)
	{
		using namespace keybind;

		switch (keycode)
		{
		case MOVE_LEFT:
			m_player->setActionStatus(PlayerBehavior::ACTION_MOVE_LEFT, keyState);
			break;

		case MOVE_RIGHT:
			m_player->setActionStatus(PlayerBehavior::ACTION_MOVE_RIGHT, keyState);
			break;

		case MOVE_UP:
			m_player->setActionStatus(PlayerBehavior::ACTION_MOVE_FORWARD, keyState);
			break;

		case MOVE_DOWN:
			m_player->setActionStatus(PlayerBehavior::ACTION_MOVE_BACKWARD, keyState);
			break;

		case PAUSE:
		{
			if (keyState == true)
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

				
				interpretKeyboardInput(keyEvent->getKeyCode(), state);
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

		
		m_gfxManager.renderBackground();

		m_gfxManager.renderSpace(*m_space);
		
	}
	
	
	
}
