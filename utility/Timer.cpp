#include "stdafx.h"
#include "Timer.h"

Timer::Timer() : m_timePrev(std::chrono::high_resolution_clock::now())
{}

float Timer::getDelta()
{
    auto timeCurrent = std::chrono::high_resolution_clock::now();
    auto elapsedTime(timeCurrent - m_timePrev);
    m_timePrev = std::chrono::high_resolution_clock::now();
    return (std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(elapsedTime).count());
}

float Timer::getFPS(const float deltaTime) const
{
    auto ftSeconds(deltaTime / 1000.0f);
    auto fps(1.0f / ftSeconds);
    return (fps);
}
