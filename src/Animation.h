#pragma once
#include "framework/GraphicsSystem.h"
#include <vector>

namespace shooter
{

	//A single frame of an animation. Contains both the sprite to be rendered and the delay until the next frame
	struct AnimationFrame
	{
		gfx::Sprite sprite;
		
		//The number of frames to delay before going to the next frame. Setting to 0 will cause a delay set to the default value for the animation
		Uint32 delay;
	};



	class Animation
	{
		std::vector<AnimationFrame> m_track;
		
		Uint32 m_clock;
		Uint32 m_prevFrameTime;
		Uint32 m_defaultFrameDelay;
		
		unsigned int m_currentFrameIndex;
		
		//Determines whether the animation is running or stopped. If true, then getNextFrame() just returns the first frame
		bool m_static;
		
	public:
		//Initialize empty Animation
		Animation() : m_clock(0), m_prevFrameTime(0), m_currentFrameIndex(0), m_static(false)
		{
		}
		
		Animation(std::vector<AnimationFrame> animationTrack, Uint32 defaultFrameDelay = 1, bool staticAnimation = false) : m_track(animationTrack), m_defaultFrameDelay(defaultFrameDelay), m_clock(0), m_prevFrameTime(0), m_currentFrameIndex(0), m_static(staticAnimation)
		{
		}
		
		AnimationFrame getCurrentFrame()
		{
			return m_track.at(m_currentFrameIndex);
		}
		
		gfx::Sprite getNextFrame();
		
		void setStatic(bool state)
		{
			m_static = state;
		}
		
	};
		
}
