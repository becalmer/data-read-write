#include "buffer_pool.h"

namespace ds
{
    buffer_pool_t g_buffer_pool;

    pool_t::pool_t()
    {
        m_data = 0;
        m_row = 0;
        m_col = 0;
    }

    buffer_pool_t::buffer_pool_t()
    {
        m_data = 0;
        m_col = 0;
        m_row = 0;
        m_mask = 0;
    }

    buffer_pool_t::~buffer_pool_t()
    {
        if(m_row > 0)
        {
            if(m_col > 0)
            {
                for(size_t x = 0; x < m_row; ++ x)
                {
                    delete[] m_data[x];
                }
                delete[] m_data;
            }
        }

        m_data = 0;
        m_row = 0;
        m_col = 0;
        m_mask = 0;
    }

    bool buffer_pool_t::init(size_t row, size_t col)
    {
        if(row == 0 || row > 32 || col == 0)
        {
            return false;
        }

        m_data = new uint8_t*[row];

        for(size_t x = 0; x < row; ++ x)
        {
            m_data[x] = new uint8_t[col];
        }

        m_row = row;
        m_col = col;

        return true;
    }

    bool buffer_pool_t::alloc(pool_t& pool)
    {
        size_t x = 0;
        for(; x < 32; ++ x)
        {
            if(!((1 << x) & m_mask))
            {
                break;
            }
        }
        if(x == 32)
        {
            return false;
        }
        pool.m_data = m_data[x];
        pool.m_row = x;
        pool.m_col = m_col;

        m_mask |= (1 << x);
        return true;
    }

    bool buffer_pool_t::free(pool_t& pool)
    {
        if(pool.m_row > 32)
        {
            return false;
        }

        m_mask &= ~(1 << (pool.m_row));
        return true;
    }
}
