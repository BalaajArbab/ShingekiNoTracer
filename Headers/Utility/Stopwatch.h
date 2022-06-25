// A class to mimic Stopwatch functionality from System.Diagnostics in C#/.NET.
// This is a Header only class.

#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <chrono>
#include <vector>
#include <cstdint>

class Stopwatch
{
public:

    // Initializes Stopwatch instance.
    Stopwatch();

    // Queries whether the stopwatch is currently running (.Start was called).
    bool IsRunning();

    // Initiates an interval of the stopwatch
    bool Start();

    // Stops the stopwatch, creating a closed interval from the start point.
    bool Stop();

    // Returns elapsed time (in seconds) of currently running interval (After starting the stopwatch, without stopping it.)
    double Elapsed();

    // Returns elapsed time (in seconds) of previous completed interval.
    double LastElapsed();

    // Returns the elapsed time (in seconds) of the specified interval (index of intervals starts at 0).
    double GetIntervalElapsed(std::int32_t intervalIndex);

    // Returns elapsed time (in seconds) of all intervals + the currently running interval if stopwatch is running.
    double TotalElapsed();

    // Erases all intervals.
    void Reset();

private:
    // Type aliases to make accessing nested type easier
    using clock_type = std::chrono::steady_clock;
    using second_type = std::chrono::duration<double>;

    std::vector<std::chrono::time_point<clock_type>> m_startPoints;
    std::vector<std::chrono::time_point<clock_type>> m_stopPoints;

    std::int32_t m_intervals{ 0 };
    bool m_isRunning{ false };

};

inline Stopwatch::Stopwatch()
{
    m_startPoints.reserve(10);
    m_stopPoints.reserve(10);
}

inline bool Stopwatch::IsRunning() { return m_isRunning; }

inline bool Stopwatch::Start()
{
    if (!m_isRunning)
    {
        m_isRunning = true;

        m_startPoints.push_back(clock_type::now());

        return true;
    }

    return false;
}

inline bool Stopwatch::Stop()
{
    if (m_isRunning)
    {
        m_stopPoints.push_back(clock_type::now());

        m_isRunning = false;
        ++m_intervals;

        return true;
    }

    return false;
}

inline double Stopwatch::Elapsed()
{
    if (!m_isRunning) return 0.0;

    return std::chrono::duration_cast<second_type>(clock_type::now() - m_startPoints[m_intervals]).count();
}

inline double Stopwatch::LastElapsed()
{
    if (m_intervals == 0) return 0.0;

    return std::chrono::duration_cast<second_type>(m_stopPoints[m_intervals - 1] - m_startPoints[m_intervals - 1]).count();
}

inline double Stopwatch::GetIntervalElapsed(std::int32_t intervalIndex)
{
    if (m_intervals < 1 || intervalIndex >= m_intervals) return 0.0; // TODO throw exception for negative index

    return std::chrono::duration_cast<second_type>(m_stopPoints[intervalIndex] - m_startPoints[intervalIndex]).count();
}

inline double Stopwatch::TotalElapsed()
{
    double total{ 0.0 };

    for (std::int32_t i{ }; i < m_intervals; ++i)
    {
        total += std::chrono::duration_cast<second_type>(m_stopPoints[i] - m_startPoints[i]).count();
    }

    total += Elapsed();
    
    return total;
}

inline void Stopwatch::Reset()
{
    m_intervals = 0;
    m_isRunning = false;
    m_startPoints.resize(0);
    m_stopPoints.resize(0);
}

#endif

