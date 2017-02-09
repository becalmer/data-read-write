#ifndef __DATA_STRUCT_BIN_H__
#define __DATA_STRUCT_BIN_H__

#include <string.h>
#include "buffer_pool.h"

namespace ds
{
    class bin_t
    {
    public:
        bin_t();
        ~bin_t();

        template<typename T>
        bool write(T& t)
        {
            if(!t.write(m_len))
            {
                return false;
            }
            if(!t.write(m_data, m_len))
            {
                return false;
            }
            return true;
        }

        template<typename T>
        bool read(T& t)
        {
            if(!t.read(m_len))
            {
                return false;
            }
            if(!t.read(m_data, m_len))
            {
                return false;
            }
            return true;
        }

        void copy(const uint8_t* data, size_t len);

    private:
        pool_t   m_pool;
        uint8_t* m_data;
        uint32_t m_len;
    };
}

#endif
