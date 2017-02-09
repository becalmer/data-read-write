#ifndef __DATA_STRUCT_SSTACK_H__
#define __DATA_STRUCT_SSTACK_H__

#include <string.h>

namespace ds
{
    template<typename T, size_t N>
    class sstack_t
    {
    public:
        sstack_t()
        {
            clear();
        }

        sstack_t(const sstack_t& s)
        {
            *this = s;
        }

        ~sstack_t()
        {
        }

        void clear()
        {
            m_top = 0;
        }

        sstack_t& operator = (const sstack_t& s)
        {
            m_top = s.m_top;
            for(size_t x = 0; x < m_top; ++ x)
            {
                m_data[x] = s.m_data[x];
            }

            return *this;
        }

        bool empty()
        {
            return (m_top == 0);
        }

        bool full()
        {
            return (m_top >= N);
        }

        size_t count()
        {
            return m_top;
        }

        T& alloc()
        {
            size_t x = m_top ++;
            return m_data[x];
        }

        T& top()
        {
            return m_data[m_top - 1];
        }

        void pop()
        {
            -- m_top;
        }

        void print()
        {
            printf("[(%s:%s:%d) ++++]\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
            printf("[m_top(%zu)]\n", m_top);
            for (size_t x  = 0; x < m_top; ++ x)
            {
                m_data[x].print();
            }
            printf("[(%s:%s:%d) ----]\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
        }

    private:
        T      m_data[N];
        size_t m_top;
    };
}

#endif
