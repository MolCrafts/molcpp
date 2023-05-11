#pragma once
#include "mplog.h"
#include <exception>

namespace molcpp
{
    class KeyError : public std::exception
    {
    public:
        KeyError(const std::string &message) : m_message(message)
        {
            LOG_ERROR(m_message);
        }

        const char *what() const noexcept override
        {
            return m_message.c_str();
        }

    private:
        std::string m_message;
    };

    class IndexError : public std::exception
    {
    public:
        IndexError(const std::string &message) : m_message(message)
        {
            LOG_ERROR(m_message);
        }

        const char *what() const noexcept override
        {
            return m_message.c_str();
        }

    private:
        std::string m_message;
    };

    class IOError : public std::exception
    {
    public:
        IOError(const std::string &message) : m_message(message)
        {
            LOG_ERROR(m_message);
        }

        const char *what() const noexcept override
        {
            return m_message.c_str();
        }
    private:
        std::string m_message;
    };
}