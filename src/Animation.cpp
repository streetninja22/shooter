#include "Animation.h"

#include <iostream>

namespace shooter
{

	gfx::Sprite Animation::getNextFrame()
	{
		//First check if the animation is animated at all
		if (m_static)
		{
			return m_track.at(0).sprite;
		}
		
		//Check if previous frame start time + delay <= current time, to go to next frame. If the delay of the frame is equal to 0, the default delay of the animation is used instead
		if (m_prevFrameTime + (getCurrentFrame().delay ? getCurrentFrame().delay : m_defaultFrameDelay) <= m_clock)
		{
			++m_currentFrameIndex;
			
			if (m_currentFrameIndex == m_track.size())
			{
				//loop back to start
				m_currentFrameIndex = 0;
				m_clock = 0;
				m_prevFrameTime = 0;
			}
			else
			{
				m_prevFrameTime = m_clock;
			}
			
		}
		
		++m_clock;
		return getCurrentFrame().sprite;
	}
		
}
