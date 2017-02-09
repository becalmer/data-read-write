#ifndef __DATA_STRUCT_EBUFFER_H__
#define __DATA_STRUCT_EBUFFER_H__

#include <string.h>

namespace ds
{
    template<size_t N>
    class ebuffer_t
    {
    public:
        ebuffer_t()
        {
            clear();
        }

        ~ebuffer_t()
        {

        }

        void clear()
        {
            m_data[0] = 0;
            m_r_pos = 0;
            m_w_pos = 0;
        }

        char* raddr()
        {
            return (m_data + m_r_pos);
        }

        char* waddr()
        {
            return (m_data + m_w_pos);
        }

        void roffset(size_t size)
        {
            m_r_pos += size;
        }

        void woffset(size_t size)
        {
            m_w_pos += size;
        }

        size_t rsize()
        {
            return (m_w_pos - m_r_pos);
        }

        size_t wsize()
        {
            return N;
        }

        void print()
        {
            printf("[(%s:%s:%d) ++++]\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
            printf("[m_data(%s)]\n", m_data);
            printf("[m_r_pos(%zu)]\n", m_r_pos);
            printf("[m_w_pos(%zu)]\n", m_w_pos);
            printf("[(%s:%s:%d) ----]\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
        }

    private:
        size_t m_r_pos;
        size_t m_w_pos;
        char   m_data[N];
    };
}

#endif
