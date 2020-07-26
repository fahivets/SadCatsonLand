#include "stdafx.h"
#include "Animation.h"

void Animation::addFrame(const int& textureID, const SDL_Rect& rect, const float& frameTime)
{
	FrameData data;

	data.id = textureID;
	data.rect = rect;
	data.displayTimeSeconds = frameTime;
	m_frames.emplace_back(std::move(data));
}

const FrameData& Animation::getCurrentFrame() const
{
	return (m_frames.at(m_currentFrameIndex));
}

bool Animation::updateFrame(const float& deltaTime)
{
	if (m_frames.size() > 0)
	{
		m_currentFrameTime += deltaTime;
		if (m_currentFrameTime >= m_frames[m_currentFrameIndex].displayTimeSeconds)
		{
			m_currentFrameTime = 0.0f;
			incrementFrame();
			return (true);
		}
	}
	return (false);
}

void Animation::reset()
{
	m_currentFrameIndex = 0;
	m_currentFrameTime = 0.0f;
}

void Animation::incrementFrame()
{
	m_currentFrameIndex = (m_currentFrameIndex + 1) % m_frames.size();
}