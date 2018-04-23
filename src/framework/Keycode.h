#pragma once

#include "includeSDL.h"


namespace inpt
{
	enum KeyCode
	{
        KEYCODE_DEFAULT,
		KEYCODE_0,
		KEYCODE_1,
		KEYCODE_2,
		KEYCODE_3,
		KEYCODE_4,
		KEYCODE_5,
		KEYCODE_6,
		KEYCODE_7,
		KEYCODE_8,
		KEYCODE_9,

		KEYCODE_Q,
		KEYCODE_W,
		KEYCODE_E,
		KEYCODE_R,
		KEYCODE_T,
		KEYCODE_Y,
		KEYCODE_U,
		KEYCODE_I,
		KEYCODE_O,
		KEYCODE_P,
		KEYCODE_A,
		KEYCODE_S,
		KEYCODE_D,
		KEYCODE_F,
		KEYCODE_G,
		KEYCODE_H,
		KEYCODE_J,
		KEYCODE_K,
		KEYCODE_L,
		KEYCODE_Z,
		KEYCODE_X,
		KEYCODE_C,
		KEYCODE_V,
		KEYCODE_B,
		KEYCODE_N,
		KEYCODE_M,
		
		KEYCODE_SPACE,
		KEYCODE_MINUS,
		KEYCODE_EQUALS,
		KEYCODE_BRACKET_LEFT,
		KEYCODE_BRACKET_RIGHT,
		KEYCODE_BACKSLASH,
		KEYCODE_SEMICOLON,
		KEYCODE_APOSTROPHE,
		KEYCODE_COMMA,
		KEYCODE_PERIOD,
		KEYCODE_SLASH,
		KEYCODE_TILDE,
		
		KEYCODE_ESCAPE,
		KEYCODE_TAB,
		KEYCODE_CAPS_LOCK,
		KEYCODE_SHIFT_RIGHT,
		KEYCODE_SHIFT_LEFT,
		KEYCODE_CONTROL_RIGHT,
		KEYCODE_CONTROL_LEFT,
		KEYCODE_ALT_RIGHT,
		KEYCODE_ALT_LEFT,
		KEYCODE_BACKSPACE,
		KEYCODE_RETURN,
		
		KEYCODE_ARROW_UP,
		KEYCODE_ARROW_DOWN,
		KEYCODE_ARROW_LEFT,
		KEYCODE_ARROW_RIGHT,
		
		KEYCODE_F1,
		KEYCODE_F2,
		KEYCODE_F3,
		KEYCODE_F4,
		KEYCODE_F5,
		KEYCODE_F6,
		KEYCODE_F7,
		KEYCODE_F8,
		KEYCODE_F9,
		KEYCODE_F10,
		KEYCODE_F11,
		KEYCODE_F12,
		
		//layout specific
		
		KEYCODE_WINDOWS,
		
		KEYCODE_FUNCTION,
		KEYCODE_COMMAND_LEFT,
		KEYCODE_COMMAND_RIGHT,
		
		KEYCODE_MAX
		//TODO finish inputting keycodes(stopped at letters)
	};

	//compiler whines if we don't have this static

	/* Converts an SDL_Scancode value to our KeyCode enum
	*
	* @param scancode the SDL_Scancode to convert
	*/
	static KeyCode scancodeToKeycode(SDL_Scancode scancode)
	{
		switch (scancode)
		{
			//ugh, tedious
			case (SDL_SCANCODE_0):
				return KeyCode::KEYCODE_0;

			case (SDL_SCANCODE_1):
				return KeyCode::KEYCODE_1;

			case (SDL_SCANCODE_2):
				return KeyCode::KEYCODE_2;

			case (SDL_SCANCODE_3):
				return KeyCode::KEYCODE_3;

			case (SDL_SCANCODE_4):
				return KeyCode::KEYCODE_4;

			case (SDL_SCANCODE_5):
				return KeyCode::KEYCODE_4;

			case (SDL_SCANCODE_6):
				return KeyCode::KEYCODE_6;

			case (SDL_SCANCODE_7):
				return KeyCode::KEYCODE_7;

			case (SDL_SCANCODE_8):
				return KeyCode::KEYCODE_8;

			case (SDL_SCANCODE_9):
				return KeyCode::KEYCODE_9;

			case (SDL_SCANCODE_A):
				return KeyCode::KEYCODE_A;

			case (SDL_SCANCODE_B):
				return KeyCode::KEYCODE_B;

			case (SDL_SCANCODE_C):
				return KeyCode::KEYCODE_C;

			case (SDL_SCANCODE_D):
				return KeyCode::KEYCODE_D;

			case (SDL_SCANCODE_E):
				return KeyCode::KEYCODE_E;

			case (SDL_SCANCODE_F):
				return KeyCode::KEYCODE_F;

			case (SDL_SCANCODE_G):
				return KeyCode::KEYCODE_G;

			case (SDL_SCANCODE_H):
				return KeyCode::KEYCODE_H;

			case (SDL_SCANCODE_I):
				return KeyCode::KEYCODE_I;

			case (SDL_SCANCODE_J):
				return KeyCode::KEYCODE_J;

			case (SDL_SCANCODE_K):
				return KeyCode::KEYCODE_K;

			case (SDL_SCANCODE_L):
				return KeyCode::KEYCODE_L;

			case (SDL_SCANCODE_M):
				return KeyCode::KEYCODE_M;

			case (SDL_SCANCODE_N):
				return KeyCode::KEYCODE_N;

			case (SDL_SCANCODE_O):
				return KeyCode::KEYCODE_O;

			case (SDL_SCANCODE_P):
				return KeyCode::KEYCODE_P;

			case (SDL_SCANCODE_Q):
				return KeyCode::KEYCODE_Q;

			case (SDL_SCANCODE_R):
				return KeyCode::KEYCODE_R;

			case (SDL_SCANCODE_S):
				return KeyCode::KEYCODE_S;

			case (SDL_SCANCODE_T):
				return KeyCode::KEYCODE_T;

			case (SDL_SCANCODE_U):
				return KeyCode::KEYCODE_U;

			case (SDL_SCANCODE_V):
				return KeyCode::KEYCODE_V;

			case (SDL_SCANCODE_W):
				return KeyCode::KEYCODE_W;

			case (SDL_SCANCODE_Y):
				return KeyCode::KEYCODE_Y;

			case (SDL_SCANCODE_X):
				return KeyCode::KEYCODE_X;

			case (SDL_SCANCODE_Z):
				return KeyCode::KEYCODE_Z;
					
					
			case (SDL_SCANCODE_ESCAPE):
				return KeyCode::KEYCODE_ESCAPE;
				
			case (SDL_SCANCODE_MINUS):
				return KeyCode::KEYCODE_MINUS;
				
			case (SDL_SCANCODE_EQUALS):
				return KeyCode::KEYCODE_EQUALS;
				
			case (SDL_SCANCODE_LEFTBRACKET):
				return KeyCode::KEYCODE_BRACKET_LEFT;
				
			case (SDL_SCANCODE_RIGHTBRACKET):
				return KeyCode::KEYCODE_BRACKET_RIGHT;
				
			case (SDL_SCANCODE_BACKSLASH):
				return KeyCode::KEYCODE_BACKSLASH;
				
			case (SDL_SCANCODE_SEMICOLON):
				return KeyCode::KEYCODE_SEMICOLON;
				
			case (SDL_SCANCODE_APOSTROPHE):
				return KeyCode::KEYCODE_APOSTROPHE;
				
			case (SDL_SCANCODE_COMMA):
				return KeyCode::KEYCODE_COMMA;
				
			case (SDL_SCANCODE_PERIOD):
				return KeyCode::KEYCODE_PERIOD;
				
			case (SDL_SCANCODE_SLASH):
				return KeyCode::KEYCODE_SLASH;
				
			case (SDL_SCANCODE_SPACE):
				return KeyCode::KEYCODE_SPACE;
					
					
			case (SDL_SCANCODE_TAB):
				return KeyCode::KEYCODE_TAB;
				
			case (SDL_SCANCODE_CAPSLOCK):
				return KeyCode::KEYCODE_CAPS_LOCK;
				
			case (SDL_SCANCODE_LSHIFT):
				return KeyCode::KEYCODE_SHIFT_LEFT;
				
			case (SDL_SCANCODE_RSHIFT):
				return KeyCode::KEYCODE_SHIFT_RIGHT;
				
			case (SDL_SCANCODE_LCTRL):
				return KeyCode::KEYCODE_CONTROL_LEFT;
				
			case (SDL_SCANCODE_RCTRL):
				return KeyCode::KEYCODE_CONTROL_RIGHT;
				
			case (SDL_SCANCODE_LALT):
				return KeyCode::KEYCODE_ALT_LEFT;
				
			case (SDL_SCANCODE_RALT):
				return KeyCode::KEYCODE_ALT_RIGHT;
				
			case (SDL_SCANCODE_BACKSPACE):
				return KeyCode::KEYCODE_BACKSPACE;
				
			case (SDL_SCANCODE_RETURN):
				return KeyCode::KEYCODE_RETURN;
				
				
			case (SDL_SCANCODE_UP):
				return KeyCode::KEYCODE_ARROW_UP;
				
			case (SDL_SCANCODE_DOWN):
				return KeyCode::KEYCODE_ARROW_DOWN;
				
			case (SDL_SCANCODE_LEFT):
				return KeyCode::KEYCODE_ARROW_LEFT;
				
			case (SDL_SCANCODE_RIGHT):
				return KeyCode::KEYCODE_ARROW_RIGHT;
				
				
			case (SDL_SCANCODE_F1):
				return KeyCode::KEYCODE_F1;
				
			case (SDL_SCANCODE_F2):
				return KeyCode::KEYCODE_F2;
				
			case (SDL_SCANCODE_F3):
				return KeyCode::KEYCODE_F3;
				
			case (SDL_SCANCODE_F4):
				return KeyCode::KEYCODE_F4;
				
			case (SDL_SCANCODE_F5):
				return KeyCode::KEYCODE_F5;
				
			case (SDL_SCANCODE_F6):
				return KeyCode::KEYCODE_F6;
				
			case (SDL_SCANCODE_F7):
				return KeyCode::KEYCODE_F7;
				
			case (SDL_SCANCODE_F8):
				return KeyCode::KEYCODE_F8;
				
			case (SDL_SCANCODE_F9):
				return KeyCode::KEYCODE_F9;
				
			case (SDL_SCANCODE_F10):
				return KeyCode::KEYCODE_F10;
				
			case (SDL_SCANCODE_F11):
				return KeyCode::KEYCODE_F11;
				
			case (SDL_SCANCODE_F12):
				return KeyCode::KEYCODE_F12;
				
		}

        return KEYCODE_DEFAULT;
	}

}
