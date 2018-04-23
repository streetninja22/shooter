#pragma once

#include "GraphicsSystem.h"


namespace gfx
{
	
	
	class LoadTextureEvent : public GraphicsEvent
	{
		std::string m_filepath;
		
	public:
		LoadTextureEvent(std::string filepath) : m_filepath(filepath)
		{
			
		}
		
		std::string getFilepath() { return m_filepath; }
		
		virtual GraphicsEventType getGraphicsEventType() { return GraphicsEventType::LOAD_TEXTURE; }
	};

	//An event which calls for the Graphics System to render an image
	class RenderImageEvent : public RenderEvent
	{
		Texture* m_texture;
		Rect* m_srcRect;
		Rect* m_dstRect;
		
	public:
		RenderImageEvent()
		{
			
		}
		
		/* Creates a RenderImageEvent
			*
			* @param texture the Texture to render
			* @param srcRect The source rectangle which determines what part of the texture will be rendered
			* @param dstRect The destination rectangle, which determins where on the screen the texture will be rendered
			*/
		RenderImageEvent(Texture* texture, Rect* srcRect, Rect* dstRect) : m_texture(texture), m_srcRect(srcRect), m_dstRect(dstRect)
		{
		}
		
		virtual ~RenderImageEvent() override
		{
			delete m_srcRect;
			delete m_dstRect;
		}
		
		Rect* getSrcRect() { return m_srcRect; }
		Rect* getDstRect() { return m_dstRect; }
		Texture* getTexture() { return m_texture; }
		virtual GraphicsEventType getGraphicsEventType() override { return GraphicsEventType::RENDER_IMAGE; }
	};

	class RenderDrawRectEvent : public RenderEvent
	{
		Rect m_rect;
		Color m_color;
		
	public:
		
		/* Creates a RenderRectEvent
		*
		* @param rect The rectangle object which stores the size and position of the rect to draw
		* @param color The color to draw the rectangle in
		*/
		RenderDrawRectEvent(Rect rect, Color color) : m_rect(rect), m_color(color)
		{
		}
		
		virtual ~RenderDrawRectEvent()
		{
		}
		
		Rect& getRect() { return m_rect; } //nerf this scrubs
		Color getColor() { return m_color; }
		virtual GraphicsEventType getGraphicsEventType() override { return GraphicsEventType::RENDER_DRAW_RECT; }
	};

	class RenderFillRectEvent : public RenderEvent
	{
		Rect m_rect;
		Color m_color;
		
	public:
		
		/* Creates a RenderRectEvent
		 *
		 * @param rect The rectangle object which stores the size and position of the rect to draw
		 * @param color The color to draw the rectangle in
		 */
		RenderFillRectEvent(Rect rect, Color color) : m_rect(rect), m_color(color)
		{
		}
		
		virtual ~RenderFillRectEvent()
		{
		}
		
		Rect& getRect() { return m_rect; } //nerf this scrubs
		Color getColor() { return m_color; }
		virtual GraphicsEventType getGraphicsEventType() override { return GraphicsEventType::RENDER_FILL_RECT; }
	};

	




	class LoadTextureReturnType : public GraphicsEventReturnType
	{
		Texture* m_texture;

	public:
		LoadTextureReturnType(Texture* texture) : GraphicsEventReturnType(), m_texture(texture)
		{
		}

		Texture* getTexture() { return m_texture; }

		virtual GraphicsEventType getGraphicsEventType() { return GraphicsEventType::LOAD_TEXTURE; }
	};

}
