#pragma once

#include "includeSDL.h"


Uint32 getTicks()
{
	return SDL_GetTicks();
}


Uint32 delay(long time)
{
	SDL_Delay(time);
}
