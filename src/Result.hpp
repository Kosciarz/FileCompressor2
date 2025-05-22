#pragma once

#include <stdexcept>

template <typename T, typename E>
class [[nodiscard]] Result
{
public:
    Result() = delete;

    static Result Ok(const T& value)
    {
        return Result{true, value, E{}};
    }

    static Result Err(const E& error)
    {
        return Result{false, T{}, error};
    }

    bool IsOk() const
    {
        return m_Success;
    }

    bool IsErr() const
    {
        return !m_Success;
    }

    T& Value() &
    {
        if (!m_Success)
            throw std::runtime_error{"Attempted to access value in Err result"};
        return m_Value;
    }

    const T& Value() const&
    {
        if (!m_Success)
            throw std::runtime_error{"Attempted to access value in Err result"};
        return m_Value;
    }

    E& Error()
    {
        if (m_Success)
            throw std::runtime_error{"Attempted to access error in an Ok Result"};
        return m_Error;
    }

    const E& Error() const
    {
        if (m_Success)
            throw std::runtime_error{"Attempted to access error in an Ok Result"};
        return m_Error;
    }

    explicit operator bool() const
    {
        return m_Success;
    }

private:
    Result(bool success, const T& value, const E& error)
        : m_Success{success}, m_Value{value}, m_Error{error}
    {
    }

private:
    bool m_Success;
    T m_Value;
    E m_Error;
};

template <typename E>
class [[nodiscard]] Result<void, E>
{
    public:
    Result() = delete;

    static Result Ok()
    {
        return Result{true, E{}};
    }

    static Result Err(const E& error)
    {
        return Result{false, error};
    }

    bool IsErr() const
    {
        return !m_Success;
    }

    E& Error()
    {
        if (m_Success)
            throw std::runtime_error{"Attempted to access error in an Ok Result"};
        return m_Error;
    }

    const E& Error() const
    {
        if (m_Success)
            throw std::runtime_error{"Attempted to access error in an Ok Result"};
        return m_Error;
    }

    explicit operator bool() const
    {
        return m_Success;
    }

private:
    Result(bool success, const E& error)
        : m_Success{success}, m_Error{error}
    {
    }

private:
    bool m_Success;
    E m_Error;
};