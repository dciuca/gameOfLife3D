// include/utils/Utils.h
#pragma once

#include <string>
#include <iostream>
#include <chrono>

namespace Utils
{

    // ============================================
    // LOGGING
    // ============================================

    enum class LogLevel
    {
        INFO,
        WARNING,
        ERROR,
        DEBUG
    };

    inline void log(const std::string &message, LogLevel level = LogLevel::INFO)
    {
        switch (level)
        {
        case LogLevel::INFO:
            std::cout << "[INFO] " << message << std::endl;
            break;
        case LogLevel::WARNING:
            std::cout << "[WARNING] " << message << std::endl;
            break;
        case LogLevel::ERROR:
            std::cerr << "[ERROR] " << message << std::endl;
            break;
        case LogLevel::DEBUG:
            std::cout << "[DEBUG] " << message << std::endl;
            break;
        }
    }

    // ============================================
    // TIMER
    // ============================================

    class Timer
    {
    private:
        std::chrono::high_resolution_clock::time_point m_start;
        std::chrono::high_resolution_clock::time_point m_end;
        bool m_stopped = false;

    public:
        Timer() { start(); }

        void start()
        {
            m_start = std::chrono::high_resolution_clock::now();
            m_stopped = false;
        }

        void stop()
        {
            m_end = std::chrono::high_resolution_clock::now();
            m_stopped = true;
        }

        double elapsedMilliseconds() const
        {
            auto end = m_stopped ? m_end : std::chrono::high_resolution_clock::now();
            return std::chrono::duration<double, std::milli>(end - m_start).count();
        }

        double elapsedMicroseconds() const
        {
            auto end = m_stopped ? m_end : std::chrono::high_resolution_clock::now();
            return std::chrono::duration<double, std::micro>(end - m_start).count();
        }

        double elapsedSeconds() const
        {
            return elapsedMilliseconds() / 1000.0;
        }

        void reset() { start(); }

        void logElapsed(const std::string &label, LogLevel level = LogLevel::DEBUG)
        {
            log(label + " | " + std::to_string(elapsedMilliseconds()) + " ms", level);
        }
    };
}