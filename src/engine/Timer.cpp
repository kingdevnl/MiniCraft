
#include <iostream>
#include "Timer.hpp"

Timer::Timer(const char *name) {
    this->m_Name = name;
    this->m_StartTime = std::chrono::high_resolution_clock::now();
}

void Timer::Stop() {
    auto endTime = std::chrono::high_resolution_clock::now();
    long long start = std::chrono::time_point_cast<std::chrono::milliseconds>(m_StartTime).time_since_epoch().count();
    long long end = std::chrono::time_point_cast<std::chrono::milliseconds>(endTime).time_since_epoch().count();

    m_Stopped = true;

    std::cout << m_Name << ": " << ( end - start) << "ms" << std::endl;
}

Timer::~Timer() {
    if(!m_Stopped) {
        Stop();
    }
}
