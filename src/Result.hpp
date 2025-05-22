#pragma once

#include <string>

namespace compressor {

    template <typename T, typename E = std::string>
    class Result
    {
    public:
        Result() = delete;

        static Result<T, E> Ok(T&& value)
        {
            return Result<T, E>{true, value, E{}};
        }

        static Result<T, E> Error(E&& error)
        {
            return Result<T, E>{false, T{}, error};
        }

        bool IsOk() const
        {
            return m_Success;
        }

        bool IsErr() const
        {
            return !m_Success;
        }

        T&& Value() const
        {
            return m_Value;
        }

        explicit operator bool()()
        {
            return IsOk();
        }

    private:
        Result(bool success, T&& value, E&& error)
            : m_Success{success}, m_Value{value}, m_Error{error}
        {
        }

    private:
        bool m_Success;
        T m_Value;
        E m_Error;
    };

}