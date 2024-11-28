#ifndef SLIDINGBUFFER_H
#define SLIDINGBUFFER_H
#include <cstdint>
#include <cstring>

namespace DroneTool
{
    template<typename T, size_t Size>
    class SlidingBuffer
    {
    public:

        void clear(T val)
        {
            memset(m_buffer, val, sizeof(T) * Size);
        }

        void update(T rhs)
        {
            for (int i = 1; i < Size; i++)
            {
                m_buffer[i-1] = m_buffer[i];
            }
            m_buffer[Size - 1] = rhs;
        }

        T* data()
        {
            return &m_buffer[0];
        }

        [[nodiscard]] constexpr size_t size() const
        {
            return Size;
        }
    private:
        T m_buffer[Size];
    };
}

#endif
