#ifndef __DATA_STRUCT_BIT_H__
#define __DATA_STRUCT_BIT_H__

#include <string.h>
#include <stdint.h>

namespace ds
{
    template<size_t N>
    class bit_t
    {
    public:
        bit_t()
        {
            clear();
        }

        ~bit_t()
        {

        }

        void clear()
        {
            m_len = 0;
            memset(m_data, 0, sizeof(m_data));
        }

        void set(size_t x)
        {
            if(x >= (sizeof(m_data) * 8))
            {
                return;
            }

            m_data[x / 8] |= (1 << (x % 8));

            size_t y = (x + 8) / 8;
            if(y > m_len)
            {
                m_len = y;
            }
        }

        void clr(size_t x)
        {
            if(x >= (sizeof(m_data) * 8))
            {
                return;
            }

            m_data[x / 8] &= (1 << (x % 8));
        }

        bool has(size_t x)
        {
            if(x >= (sizeof(m_data) * 8))
            {
                return false;
            }

            return (0 != (m_data[x / 8] & (1 << (x % 8))));
        }

        template<typename T>
        bool write(T& t)
        {
            uint8_t x = m_len;
            if(!t.write(x))
            {
                return false;
            }
            if(m_len == 0)
            {
                return true;
            }
            if(!t.write((uint8_t*)m_data, m_len))
            {
                return false;
            }
            return true;
        }

        template<typename T>
        bool read(T& t)
        {
            uint8_t x = 0;
            if(!t.read(x))
            {
                return false;
            }
            m_len = x;
            if(m_len == 0)
            {
                return true;
            }
            if(!t.read((uint8_t*)m_data, m_len))
            {
                return false;
            }
            return true;
        }

    private:
        size_t m_len;
        char   m_data[(N + 63) / 64 * 8];
    };
}

#endif
