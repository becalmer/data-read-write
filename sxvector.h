#ifndef __DATA_STRUCT_SXVECTOR_H__
#define __DATA_STRUCT_SXVECTOR_H__

#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <buffer.h>
#include <typeid.h>
#include <type_1.h>

namespace ds
{
    // uint16_t uint32_t等基础数据使用的栈(不在堆上分配内存)上的vector
    template<typename T, size_t N>
    class sxvector_t
    {
    public:
        sxvector_t()
        {
            clear();
        }

        sxvector_t(const sxvector_t& s)
        {
            *this = s;
        }

        ~sxvector_t()
        {
            clear();
        }

        void clear()
        {
            m_count = 0;
        }

        sxvector_t& operator = (const sxvector_t& s)
        {
            m_count = s.count();
            for(size_t x = 0; x < m_count; ++ x)
            {
                m_data[x] = s[x];
            }

            return *this;
        }

        size_t count() const
        {
            return m_count;
        }

        size_t count()
        {
            return m_count;
        }

        void push(const T& t)
        {
            m_data[m_count ++] = t;
        }

        T& operator [] (size_t idx)
        {
            return m_data[idx];
        }

        const T& operator [] (size_t idx) const
        {
            return m_data[idx];
        }

        bool full() const
        {
            return (m_count >= N);
        }

        bool full()
        {
            return (m_count >= N);
        }

        template<typename V>
        bool write(V& v)
        {
            uint16_t l = m_count;

            if(!v.write(l))
            {
                return false;
            }

            for(size_t x = 0; x < m_count; ++ x)
            {
                if(!v.write(m_data[x]))
                {
                    return false;
                }
            }

            return true;
        }

        template<typename V>
        bool read(V& v)
        {
            uint16_t l = 0;

            if(!v.read(l))
            {
                return false;
            }

            for(size_t x = 0; x < l; ++ x)
            {
                if(!v.read(m_data[x]))
                {
                    return false;
                }
            }

            m_count = l;

            return true;
        }

        void print()
        {
            printf("[(%s:%s:%d) ++++]\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
            printf("[m_count(%zu)]\n", m_count);
            for(size_t x = 0; x < m_count; ++ x)
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
            if(0 != m_count)
            {
                printf("\n");
            }
            printf("[(%s:%s:%d) ----]\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
        }

    private:
        T      m_data[N];
        size_t m_count;
    };
}

#endif
