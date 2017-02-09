#include "bin.h"

namespace ds
{
    bin_t::bin_t()
    {
        m_data = 0;
        m_len = 0;
        g_buffer_pool.alloc(m_pool);
        m_data = m_pool.m_data;
    }

    bin_t::~bin_t()
    {
        g_buffer_pool.free(m_pool);
    }

    void bin_t::copy(const uint8_t* data, size_t len)
    {
        if(m_pool.m_col < len)
        {
            return;
        }
        memcpy(m_data, data, len);
        m_len = len;
    }
}
