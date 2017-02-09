#ifndef __DATA_STRUCT_TSTACK_H__
#define __DATA_STRUCT_TSTACK_H__

namespace ds
{
    template<typename T>
    class tstack_t
    {
    public:
        tstack_t()
        {
            m_data = 0;
            m_capacity = 0;
            clear();
        }

        tstack_t(const tstack_t& s)
        {
            m_data = 0;
            m_capacity = 0;
            m_top = 0;
            *this = s;
        }

        ~tstack_t()
        {
            if(m_data)
            {
                delete[] m_data;
            }
        }

        void clear()
        {
            m_top = 0;
        }

        tstack_t& operator = (const tstack_t& s)
        {
            if(s.m_top <= 0)
            {
                return *this;
            }
            resize(s.m_capacity);
            m_top = s.m_top;
            for(size_t x = 0; x < m_top; ++ x)
            {
                m_data[x] = s.m_data[x];
            }

            return *this;
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

        size_t count()
        {
            return m_top;
        }

        bool empty()
        {
            return (m_top == 0);
        }

        bool full()
        {
            return (m_top >= m_capacity);
        }

        T& alloc()
        {
            resize(m_capacity);
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
            printf("[m_bottom(%zu)]\n", m_bottom);
            for (size_t x  = 0; x < m_top; ++ x)
            {
                m_data[x].print();
            }
            printf("[(%s:%s:%d) ----]\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
        }

    private:
        T*     m_data;
        size_t m_top;
        size_t m_capacity;
    };
}

#endif
