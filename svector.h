#ifndef __DATA_STRUCT_SVECTOR_H__
#define __DATA_STRUCT_SVECTOR_H__

#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <buffer.h>
#include <typeid.h>
#include <type_1.h>

namespace ds
{
    // 非uint16_t uint32_t等基础数据使用的栈(不在堆上分配内存)上的vector
    template<typename T, size_t N>
    class svector_t
    {
    public:
        svector_t()
        {
            clear();
        }

        svector_t(const svector_t& s)
        {
            *this = s;
        }

        ~svector_t()
        {
            clear();
        }

        void clear()
        {
            m_count = 0;
        }

        svector_t& operator = (const svector_t& s)
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

        T& alloc()
        {
            size_t x = m_count ++;
            return m_data[x];
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
                if(!m_data[x].write(v))
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
                if(!m_data[x].read(v))
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
                m_data[x].print();
            }
            printf("[(%s:%s:%d) ----]\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
        }

    private:
        T      m_data[N];
        size_t m_count;
    };
}

#endif
