#pragma once
#include <chrono>


class Timer {
public:
    Timer(const char* name);
    ~Timer();

    void Stop();


private:
    const char* m_Name;
    std::chrono::time_point<std::chrono::steady_clock> m_StartTime;
    bool m_Stopped = false;
};

