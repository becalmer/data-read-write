#ifndef __DATA_STRUCT_BUFFER_POOL_H__
#define __DATA_STRUCT_BUFFER_POOL_H__

#include <stdint.h>
#include <string.h>

namespace ds
{
    struct pool_t
    {
        pool_t();

        uint8_t*  m_data;
        size_t    m_row;
        size_t    m_col;
    };
    class buffer_pool_t
    {
    public:
        buffer_pool_t();
        ~buffer_pool_t();

        bool init(size_t row, size_t col);

        bool alloc(pool_t& pool);
        bool free(pool_t& pool);

    private:
        uint8_t** m_data;
        size_t    m_col;
        size_t    m_row;
        size_t    m_mask;
    };

    extern buffer_pool_t g_buffer_pool;
}

#endif
