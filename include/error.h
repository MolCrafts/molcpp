#pragma once
#include "log.h"
#include <exception>

namespace molcpp
{

    class MolCppError : public std::exception
    {
    public:
        MolCppError(const std::string &message) : m_message(message)
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

    class FileStatusError : public MolCppError 
    {
    public:
        FileStatusError(const std::string &message) : MolCppError(message)
        {
        }
    };

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

    class TypeError : public std::exception
    {
    public:
        TypeError(const std::string &message) : m_message(message)
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

    class ValueError : public std::exception
    {
    public:
        ValueError(const std::string &message) : m_message(message)
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

    class NotImplementedError : public std::exception
    {
    public:
        NotImplementedError(const std::string &message) : m_message(message)
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

    class AttributeError : public std::exception
    {
    public:
        AttributeError(const std::string &message) : m_message(message)
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

    class InternalError : public std::exception
    {
    public:
        InternalError(const std::string &message) : m_message(message)
        {
            LOG_ERROR(m_message);
        }

        const char *what() const noexcept override
        {   
            std::string msg = "Internal Error: " + m_message + "\n---!Please report this error to the developers!---";
            return m_message.c_str();
        }

    private:
        std::string m_message;
    };
}
