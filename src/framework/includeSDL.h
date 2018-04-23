#pragma once


//  This header is intended to increase portability, since Xcode/MacOS puts SDL under SDL2/SDL.h, while on Windows/Visual Studio it will simply be SDL.h
#ifdef __APPLE__

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#else

#include <SDL.h>
#include <SDL_image.h>

#endif
