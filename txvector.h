#ifndef __DATA_STRUCT_TXVECTOR_H__
#define __DATA_STRUCT_TXVECTOR_H__

#include <string.h>
#include <buffer.h>
#include <stdint.h>
#include <typeid.h>

namespace ds
{
    // uint16_t uint32_t等基础数据使用的堆(在堆上分配内存)上的vector
    template<typename T>
    class txvector_t
    {
    public:
        txvector_t()
        {
            m_data = 0;
            m_capacity = 0;
            clear();
        }

        ~txvector_t()
        {
            if(m_data)
            {
                delete[] m_data;
            }
        }

        txvector_t(const txvector_t& s)
        {
            *this = s;
        }

        void clear()
        {
            m_count = 0;
        }

        txvector_t& operator = (const txvector_t& s)
        {
            if(m_data)
            {
                delete[] m_data;
            }

            m_capacity = s.capacity();
            m_count = s.count();

            m_data = new T[m_capacity];

            for(size_t x = 0; x < m_count; ++ x)
            {
                m_data[x] = s[x];
            }

            return *this;
        }

        void resize(size_t n)
        {
            if(n < m_capacity)
            {
                return;
            }

            size_t l = (n + 15) / 16 * 16;

            T* data = new T[l];

            if(!data)
            {
                return;
            }

            for(size_t x = 0; x < m_count; ++ x)
            {
                m_data[x] = data[x];
            }

            if(m_data)
            {
                delete[] m_data;
            }

            m_data = data;
            m_capacity = l;
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
            resize(m_capacity);
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
            return (m_count >= m_capacity);
        }

        bool full()
        {
            return (m_count >= m_capacity);
        }

        void inc()
        {
            ++ m_count;
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

            resize((size_t)l);

            if(m_capacity < l)
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
            printf("[m_capacity(%zu)]\n", m_capacity);
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
        T*     m_data;
        size_t m_count;
        size_t m_capacity;
    };
}

#endif
