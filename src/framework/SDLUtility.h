#pragma once
#include <string>
#include "includeSDL.h"
#include <iostream>


namespace SDLUtil
{
	/**
	* Get the resource path
	* It's assumed that the executable is in the same folder as the Resources folder
	*
	* @param subDir input which represents the wanted subdirectory within Resources, such as textures
	*/
	std::string getResourcePath(const std::string &subDir = "")
	{

#ifdef _WIN32 //Windows uses different path seperators than most operating systems (fucking microsoft why are you such a hipster)
		const char PATH_SEP = '\\';
#else
		const char PATH_SEP = '/';
#endif
		static std::string baseRes;
		if (baseRes.empty())
		{
			char *basePath = SDL_GetBasePath();
			if (basePath)
			{
				baseRes = basePath;
				SDL_free(basePath);
			}
			else
			{
				std::cerr << "SDL Error: " << SDL_GetError() << '\n';
				return "";
			}


		}
		return subDir.empty() ? baseRes : baseRes + subDir + PATH_SEP;


	}

	/**
	* Log an SDL error with an error message to the output stream of our choice
	*
	* @param outstream Chosen output stream to log the error to
	* @param msg The error message to write, format is msg error: SDL_GetError();
	*/
	void logSDLError(std::ostream &outstream, const std::string &msg)
	{
		outstream << msg << " error: " << SDL_GetError() << "\n";
	}

	/**
	* Renders a texture
	*
	* @param texture The texture to load
	* @param renderer The renderer to load to
	* @param x The X coordinate on the window to render at
	* @param y the Y coordinate on the window to render at
	*/
	void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, const int x, const int y)
	{
		//Setup the destination rectangle to the position we want to render the texture
		SDL_Rect dstRect;
		dstRect.x = x;
		dstRect.y = y;
		//Query the texture to get it's height and width to use
		SDL_QueryTexture(texture, NULL, NULL, &dstRect.w, &dstRect.h);
		SDL_RenderCopy(renderer, texture, NULL, &dstRect);

	}

	/**
	* Renders a texture
	*
	* @param texture The texture to load
	* @param renderer The renderer to load to
	* @param x The X coordinate on the window to render at
	* @param y the Y coordinate on the window to render at
	* @param w The width to render the image
	* @param h The height to render the image
	*/
	void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, const int x, const int y, const int w, const int h)
	{
		//Setup the destination rectangle which the texture will be rendered at
		SDL_Rect dstRect;
		dstRect.x = x;
		dstRect.y = y;
		dstRect.w = w;
		dstRect.h = h;
		SDL_RenderCopy(renderer, texture, NULL, &dstRect);
	}
}
