#include "InputSystem.h"
#include "Keycode.h"
#include <iostream>


namespace inpt
{
	
	
	InputEvent* InputSystem::mouseInput(SDL_Event& inputEvent)
	{
		MouseEvent* outputEvent = new MouseEvent(inputEvent.button.x, inputEvent.button.y, MouseEventType::LEFTMOUSEDOWN);
		switch (inputEvent.type)
		{
			case (SDL_MOUSEBUTTONDOWN):
			{
				//don't need case for leftmousedown, it is default
				
				if (inputEvent.button.button == SDL_BUTTON_RIGHT)
					outputEvent->setType(MouseEventType::RIGHTMOUSEDOWN);
				else if (inputEvent.button.button == SDL_BUTTON_MIDDLE)
					outputEvent->setType(MouseEventType::MIDDLEMOUSEDOWN);
			}
				
			case (SDL_MOUSEBUTTONUP):
			{
				if (inputEvent.button.button == SDL_BUTTON_LEFT)
					outputEvent->setType(MouseEventType::LEFTMOUSEUP);
				else if (inputEvent.button.button == SDL_BUTTON_RIGHT)
					outputEvent->setType(MouseEventType::RIGHTMOUSEUP);
				else if (inputEvent.button.button == SDL_BUTTON_MIDDLE)
					outputEvent->setType(MouseEventType::MIDDLEMOUSEUP);
			
			}
				
			case (SDL_MOUSEMOTION):
			{
				outputEvent->setType(MouseEventType::MOUSEMOTION);
			}
		}
		
		return outputEvent;
	}
	
	
	InputEvent* InputSystem::keyboardInput(SDL_Event& inputEvent)
	{
		KeyCode code = scancodeToKeycode(inputEvent.key.keysym.scancode);
		KeyEventType type;
		
		if (inputEvent.type == SDL_KEYDOWN)
			type = KeyEventType::KEYDOWN;
		else
			type = KeyEventType::KEYUP;
		
		return new KeyboardEvent(type, code);
	}

	void InputSystem::updateInput()
	{
		SDL_Event inputEvent;

		while (SDL_PollEvent(&inputEvent))
		{
			switch (inputEvent.type)
			{
			
			case (SDL_MOUSEMOTION):
			case (SDL_MOUSEBUTTONUP):
			case (SDL_MOUSEBUTTONDOWN):
			{
				InputEvent* output = mouseInput(inputEvent);
				addEvent(output);
			}

			case (SDL_KEYDOWN):
			case (SDL_KEYUP):
			{
				InputEvent* output = keyboardInput(inputEvent);
				addEvent(output);
			}
					
			}
		}
	}
}
