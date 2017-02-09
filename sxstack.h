#ifndef __DATA_STRUCT_SXSTACK_H__
#define __DATA_STRUCT_SXSTACK_H__

#include <stdio.h>
#include <string.h>
#include <typeid.h>

namespace ds
{
    template<typename T, size_t N>
    class sxstack_t
    {
    public:
        sxstack_t()
        {
            clear();
        }

        sxstack_t(const sxstack_t& s)
        {
            *this = s;
        }

        ~sxstack_t()
        {
        }

        void clear()
        {
            m_top = 0;
        }

        sxstack_t& operator = (const sxstack_t& s)
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

        void push(const T& t)
        {
            m_data[m_top ++] = t;
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
                format_t format;
                size_t m = 0;
                if(0 == x)
                {
                    m = format.append("[(%zu:");
                }
                else
                {
                    m = format.append(", [(%zu:");
                }
                APPEND_FMT
                format.append(")]");
                printf(format.c_str(), x, m_data[x]);
            }
            if(0 != m_top)
            {
                printf("\n");
            }
            printf("[(%s:%s:%d) ----]\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
        }

    private:
        T      m_data[N];
        size_t m_top;
    };
}

#endif
