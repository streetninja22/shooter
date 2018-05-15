#pragma once

#include "GraphicsSystem.h"

namespace gfx
{

	enum class GraphicsEventType
	{
		DEFAULT,
		RENDER_IMAGE,
		RENDER_ROTATE_IMAGE,
		RENDER_DRAW_RECT,
		RENDER_FILL_RECT,
		LOAD_TEXTURE,
		LOAD_FONT,
		LOAD_TEXT,
		SET_VIEWPORT,
	};

	
	
	enum RenderFlipMode
	{
		FLIP_NONE,
		FLIP_HORIZONTAL,
		FLIP_VERTICAL,
	};
}
