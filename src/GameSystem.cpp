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
	GameSystem::GameSystem(EventBus* bus, Vector gamespaceSize) : System(bus), m_gameBus(new evnt::EventBus()), m_gfxManager(bus), m_space(new Worldspace(bus, true, gamespaceSize, 0.5)), m_running(true), m_fpsCounter(nullptr)
	{
		Animation* playerAnim = getAnimationFromEventReturn(fireEventNow(new LoadAnimationEvent(AnimationId::ANIMATION_REIMU_IDLE)));
		
		Animation* enemyAnim = getAnimationFromEventReturn(fireEventNow(new LoadAnimationEvent(AnimationId::ANIMATION_FAIRY_IDLE)));
		
		Player* player = new Player({ 128, 128 }, { 32, 32 }, { 0, 0 }, { 0, 0 }, m_space, new PlayerBehavior(6, new ReimuFireBehavior()), playerAnim);

		
		
		m_space->add(player);

		m_space->add(new Enemy({ 28, 68 }, { 32, 32 }, { 0, 0 }, { 0, 0 }, m_space, new TestBehavior(), enemyAnim));

		m_player = static_cast<PlayerBehavior*>(player->getMainBehavior());


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
				
		case SHOOT:
			m_player->setActionStatus(PlayerBehavior::ACTION_SHOOT, keyState);
			break;
				
		case BOMB:
				m_player->setActionStatus(PlayerBehavior::ACTION_BOMB, keyState);
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

	void GameSystem::renderFpsCounter(double framerate)
	{
		std::stringstream fpsText;
		fpsText << framerate;
		
		if (m_fpsCounter != nullptr)
			delete m_fpsCounter;
		
		gfx::Texture* m_fpsCounter = static_cast<gfx::LoadTextureReturnType*>(fireEventNow(new gfx::LoadTextEvent(fpsText.str(), m_mainFont, gfx::Color{255, 255, 255, 0})))->getTexture();
		
		gfx::Rect* textRect = new gfx::Rect{0, 0, 50, 30};
		
		addEvent(new gfx::RenderImageEvent(m_fpsCounter, NULL, textRect));
	}
	
	void GameSystem::updateGameState()
	{
		m_space->update();
		
		m_gfxManager.scrollBackground();
		
	}

	void GameSystem::update(double framerate, long delay)
	{

		if (m_running)
			updateGameState();

		
		m_gfxManager.renderBackground();

		m_gfxManager.renderSpace(*m_space);
		//m_gfxManager.renderHitboxes(*m_space);
		
		renderFpsCounter(framerate);
		
	}
	
	
	
}
