#pragma once

#include "includeSDL.h"


Uint32 getTicks()
{
	return SDL_GetTicks();
}


void delay(Uint32 time)
{
	SDL_Delay(time);
}
