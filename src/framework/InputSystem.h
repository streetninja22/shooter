#pragma once

#include "System.h"
#include "Event.h"
#include "Keycode.h"
#include "includeSDL.h"

namespace inpt
{

	enum InputEventType
	{
		MOUSE,
		KEYBOARD,
	};

	enum KeyEventType
	{
		KEYDOWN,
		KEYUP
	};

	enum MouseEventType
	{
		MOUSEMOTION,
		LEFTMOUSEDOWN,
		RIGHTMOUSEDOWN,
		MIDDLEMOUSEDOWN,
		LEFTMOUSEUP,
		RIGHTMOUSEUP,
		MIDDLEMOUSEUP
	};

	class InputEvent : public Event
	{
		InputEventType m_inputType;

	public:
		InputEvent(InputEventType inputType) : m_inputType(inputType), Event(EventType::INPUT)
		{

		}

		InputEventType getInputType()
		{
			return m_inputType;
		}
	};

	class KeyboardEvent : public InputEvent
	{
		KeyEventType m_type;
		KeyCode m_keyCode;

	public:
		KeyboardEvent(KeyEventType type, KeyCode keyCode) : m_type(type), m_keyCode(keyCode), InputEvent(InputEventType::KEYBOARD)
		{
		}

		KeyEventType getType()
		{
			return m_type;
		}

		KeyCode getKeyCode()
		{
			return m_keyCode;
		}
	};


	class MouseEvent : public InputEvent
	{
		int m_posX;
		int m_posY;

		MouseEventType m_type;

	public:
		MouseEvent(int posX, int posY, MouseEventType type) : m_posX(posX), m_posY(posY), m_type(type), InputEvent(InputEventType::MOUSE)
		{

		}

        /* Returns the X coordinate of the mouse
        */
		int getX()
		{
			return m_posX;
		}

        /* Returns the Y coordinate of the mouse
         */
		int getY()
		{
			return m_posY;
		}

        /* Returns the type of mouse input (left click, right click, mmb, etc)
         */
		MouseEventType getType()
		{
			return m_type;
		}

        /* Sets the type of mouse input
         * @param type The type
         */
		void setType(MouseEventType type)
		{
			m_type = type;
		}
	};

	class InputSystem : public System
	{


	public:
		InputSystem(EventBus* bus) : System(bus)
		{

		}

		void updateInput();
		
		InputEvent* mouseInput(SDL_Event &inputEvent);
		
		InputEvent* keyboardInput(SDL_Event &inputEvent);

	};

	//TODO finish input system
}
