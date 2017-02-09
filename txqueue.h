#ifndef __DATA_STRUCT_TQUEUE_H__
#define __DATA_STRUCT_TQUEUE_H__

#include <stdio.h>
#include <string.h>
#include <typeid.h>

namespace ds
{
    template<typename T>
    class tqueue_t
    {
    public:
        tqueue_t()
        {
            m_tail = 0;
            m_capacity = 0;
            m_head = m_tail = 0;
        }

        tqueue_t(const tqueue_t& s)
        {
            m_tail = 0;
            m_capacity = 0;
            m_head = m_tail = 0;

            *this = s;
        }

        ~tqueue_t()
        {
            if(m_data)
            {
                delete[] m_data;
            }
        }

        void clear()
        {
            m_head = m_tail = 0;
        }

        void resize(size_t n)
        {
            size_t c = (n + 1023) / 16 * 16;
            if(c <= m_capacity)
            {
                return;
            }
            T* data = new T[c];
            for(size_t x = 0; x < m_top; ++ x)
            {
                data[x] = m_data[x];
            }
            if(m_data)
            {
                delete[] m_data;
            }
            m_data = data;
            m_capacity = c;
        }

        tqueue_t& operator = (const tqueue_t& s)
        {
            resize(m_capacity);
            m_head = s.m_head;
            m_tail = s.m_tail;
            for(size_t x = m_head; x < m_tail; ++ x)
            {
                m_data[x] = s.m_data[x];
            }
        }

        bool empty()
        {
            return (m_head == m_tail);
        }

        bool full()
        {
            return (m_head == N);
        }

        size_t count()
        {
            return (m_head - m_tail);
        }

        void push(const T& t)
        {
            resize(m_capacity);
            m_data[m_head ++] = t;
        }

        T& front()
        {
            return m_data[m_tail];
        }

        void pop_front()
        {
            ++ m_tail;
        }

        void print()
        {
            printf("[(%s:%s:%d) ++++]\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
            printf("[m_head(%zu)]\n", m_head);
            printf("[m_tail(%zu)]\n", m_tail);
            printf("[m_capacity(%zu)]\n", m_capacity);
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
        T*     m_data;
        size_t m_capacity;
        size_t m_head;
        size_t m_tail;
    };
}

#endif
