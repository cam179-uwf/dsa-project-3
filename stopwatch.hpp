#ifndef STOPWATCH
#define STOPWATCH

#include <chrono>
#include <stdexcept>

using time_point = std::chrono::_V2::system_clock::time_point;

/**
 * Christian Marcellino
 * COP4534 Project 3
 * 10/20/2024
 * 
 * Helper class for keeping track of detailed time.
 */
class Stopwatch 
{
    time_point* begin;
    time_point* end;

public:
    Stopwatch()
    {
        begin = nullptr;
        end = nullptr;
    }

    ~Stopwatch()
    {
        if (begin != nullptr)
            delete begin;

        if (end != nullptr)
            delete end;
    }

    Stopwatch(Stopwatch& other) = delete;
    Stopwatch& operator=(Stopwatch& other) = delete;

    /**
     * Start the stopwatch.
     */
    void start()
    {
        if (begin != nullptr)
            delete begin;

        begin = new time_point(std::chrono::high_resolution_clock::now());
    }

    /**
     * Stop the stopwatch.
     */
    void stop()
    {
        if (begin == nullptr)
        {
            throw std::runtime_error("Stopwatch was never started.");
        }

        if (end != nullptr)
            delete end;

        end = new time_point(std::chrono::high_resolution_clock::now());
    }

    /**
     * Retrieve elapsed time in milliseconds.
     */
    int64_t elapsed_milliseconds()
    {
        if (begin == nullptr)
        {
            throw std::runtime_error("Stopwatch was never started.");
        }

        if (end == nullptr)
        {
            throw std::runtime_error("Stopwatch was never stopped.");
        }

        if (*end < *begin)
        {
            throw std::runtime_error("Stopwatch start time should be before the stop time.");
        }

        return std::chrono::duration_cast<std::chrono::milliseconds>(*end - *begin).count();
    }

    /**
     * Retrieve elapsed time in microseconds.
     */
    int64_t elapsed_microseconds()
    {
        if (begin == nullptr)
        {
            throw std::runtime_error("Stopwatch was never started.");
        }

        if (end == nullptr)
        {
            throw std::runtime_error("Stopwatch was never stopped.");
        }

        if (*end < *begin)
        {
            throw std::runtime_error("Stopwatch start time should be before the stop time.");
        }

        return std::chrono::duration_cast<std::chrono::microseconds>(*end - *begin).count();
    }
};

#endif