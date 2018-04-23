#pragma once
#include "includeSDL.h"


namespace SDLUtil
{
	/*
	* Clean up multiple SDL objects
	*
	* @param t The first object to clean up
	*
	* @param args The other objects to clean up
	*/
	template<typename T, typename... Args>
	void cleanup(T *t, Args&&... args)
	{
		cleanup(t);
		cleanup(std::forward<Args>(args)...);
	}

	/*
	* Overloaded cleanup functions to handle specific types
	*/
	template<>
	inline void cleanup<SDL_Window>(SDL_Window *window)
	{
		if (!window)
			return;
		SDL_DestroyWindow(window);
	}

	template<>
	inline void cleanup<SDL_Renderer>(SDL_Renderer *renderer)
	{
		if (!renderer)
			return;
		SDL_DestroyRenderer(renderer);
	}

	template<>
	inline void cleanup<SDL_Texture>(SDL_Texture *texture)
	{
		if (!texture)
			return;
		SDL_DestroyTexture(texture);
	}

	template<>
	inline void cleanup<SDL_Surface>(SDL_Surface *surface)
	{
		if (!surface)
			return;
		SDL_FreeSurface(surface);
	}
}
