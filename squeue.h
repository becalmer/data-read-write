#ifndef __DATA_STRUCT_QUEUE_H__
#define __DATA_STRUCT_QUEUE_H__

namespace ds
{
    template<typename T, size_t N>
    class squeue_t
    {
    public:
        squeue_t()
        {
            m_head = m_tail = 0;
        }

        squeue_t(const squeue_t& s)
        {
            *this = s;
        }

        ~squeue_t()
        {

        }

        void clear()
        {
            m_head = m_tail = 0;
        }

        squeue_t& operator = (const squeue_t& s)
        {
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

        T& alloc()
        {
            size_t x = m_head ++;
            return m_data[x];
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
            for (size_t x  = m_tail; x < m_head; ++ x)
            {
                m_data[x].print();
            }
            printf("[(%s:%s:%d) ----]\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);

        }

    private:
        T      m_data[N];
        size_t m_head;
        size_t m_tail;
    };
}

#endif
