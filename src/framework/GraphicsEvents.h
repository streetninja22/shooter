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
	
	
	
	
	class LoadFontEvent : public GraphicsEvent
	{
		std::string m_filepath;
		int m_psize;
		
	public:
		LoadFontEvent(std::string filepath, int psize) : m_filepath(filepath), m_psize(psize)
		{
		}
		
		std::string getFilepath() { return m_filepath; }
		int getPsize() { return m_psize; }
		
		virtual GraphicsEventType getGraphicsEventType() override { return GraphicsEventType::LOAD_FONT; }
	};
	
	
	
	
	class LoadTextEvent : public GraphicsEvent
	{
		std::string m_text;
		Font* m_font;
		Color m_color;
		
	public:
		LoadTextEvent(std::string text, Font* font, Color color) : m_text(text), m_font(font), m_color(color)
		{
		}
		
		std::string getText() { return m_text; }
		Font* getFont() { return m_font; }
		Color getColor() { return m_color; }
		
		virtual GraphicsEventType getGraphicsEventType() override { return GraphicsEventType::LOAD_TEXT; }
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
		
		/* Creates a RenderImageEvent
		 *
		 * @param sprite The sprite to be rendered
		 * @param dstRect The destination rectangle, which determins where on the screen the texture will be rendered
		 */
		RenderImageEvent(Sprite sprite, Rect* dstRect) : m_dstRect(dstRect)
		{
			if (isSpriteValid(sprite))
			{
				m_srcRect = new Rect;
				*m_srcRect = *(sprite.sourceRect);
				
				m_texture = sprite.texture;
			}
			else
			{
				m_srcRect = nullptr;
				m_texture = nullptr;
			}
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
	
	
	//An event which calls for the Graphics System to render an image
	class RenderRotateImageEvent : public RenderImageEvent
	{
		double m_angle;
		Pair* m_center;
		RenderFlipMode m_flipMode;
		
	public:
		RenderRotateImageEvent()
		{
			
		}
		
		/* Creates a RenderImageEvent
			*
			* @param texture the Texture to render
			* @param srcRect The source rectangle which determines what part of the texture will be rendered
			* @param dstRect The destination rectangle, which determins where on the screen the texture will be rendered
		 	* @param angle The angle by which to rotate the image
		 	* @param center The center of rotation to rotate by
		 	* @param flipMode The mode to flip the image, NONE does not flip the image
			*/
		RenderRotateImageEvent(Texture* texture, Rect* srcRect, Rect* dstRect, double angle, Pair* center, RenderFlipMode flipMode = RenderFlipMode::FLIP_NONE) : RenderImageEvent(texture, srcRect, dstRect), m_angle(angle), m_center(center), m_flipMode(flipMode)
		{
		}
		
		/* Creates a RenderImageEvent
		 *
		 * @param texture the Texture to render
		 * @param srcRect The source rectangle which determines what part of the texture will be rendered
		 * @param dstRect The destination rectangle, which determins where on the screen the texture will be rendered
		 * @param angle The angle by which to rotate the image
		 * @param center The center of rotation to rotate by
		 * @param flipMode The mode to flip the image, NONE does not flip the image
		 */
		RenderRotateImageEvent(Sprite sprite, Rect* dstRect, double angle, Pair* center, RenderFlipMode flipMode = RenderFlipMode::FLIP_NONE) : RenderImageEvent(sprite, dstRect), m_angle(angle), m_center(center), m_flipMode(flipMode)
		{
		}
		
		virtual ~RenderRotateImageEvent() override
		{
			delete m_center;
		}
		
		Pair* getCenter() { return m_center; }
		double getAngle() { return m_angle; }
		RenderFlipMode getFlipMode() { return m_flipMode; }
		
		virtual GraphicsEventType getGraphicsEventType() override { return GraphicsEventType::RENDER_ROTATE_IMAGE; }
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

	
	
	
	
	class SetViewportEvent : public GraphicsEvent
	{
		Rect* m_area;
		
	public:
		SetViewportEvent(Rect* area) : m_area(area)
		{
		}
		
		~SetViewportEvent()
		{
			delete m_area;
		}
		
		
		Rect* getArea() { return m_area; }
		
		virtual GraphicsEventType getGraphicsEventType() override { return GraphicsEventType::SET_VIEWPORT; }
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
	
	
	
	
	
	
	
	
	class LoadFontReturnType : public GraphicsEventReturnType
	{
		Font* m_font;
		
	public:
		LoadFontReturnType(Font* font) : GraphicsEventReturnType(), m_font(font)
		{
		}
		
		Font* getFont() { return m_font; }
		
		virtual GraphicsEventType getGraphicsEventType() override { return GraphicsEventType::LOAD_FONT; }
	};

}
