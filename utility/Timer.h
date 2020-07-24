#ifndef TIMER_H_INCLUDE
#define TIMER_H_INCLUDE
#include "NonCopyable.h"
#include "NonMovable.h"

class Timer : public NonCopyable, public NonMovable
{
public:
    Timer();
    ~Timer() = default;

    float getDelta();
    float getFPS(const float deltaTime) const;

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_timePrev;
};

#endif