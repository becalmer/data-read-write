#ifndef __DATA_STRUCT_SBUFFER_H__
#define __DATA_STRUCT_SBUFFER_H__

#include <stdint.h>

namespace ds
{
    class sbuffer_t
    {
    public:
        enum
        {
            SIZE = (1 << 16),
        };

        sbuffer_t();
        ~sbuffer_t();

        bool write(const int8_t& x);
        bool write(const uint8_t& x);
        bool write(const int16_t& x);
        bool write(const uint16_t& x);
        bool write(const int32_t& x);
        bool write(const uint32_t& x);
        bool write(const int64_t& x);
        bool write(const uint64_t& x);
        bool write(const int8_t* x, size_t l);
        bool write(const uint8_t* x, size_t l);

        bool read(int8_t& x);
        bool read(uint8_t& x);
        bool read(int16_t& x);
        bool read(uint16_t& x);
        bool read(int32_t& x);
        bool read(uint32_t& x);
        bool read(int64_t& x);
        bool read(uint64_t& x);
        bool read(int8_t* x, size_t& l);
        bool read(uint8_t* x, size_t& l);

        void print();

    protected:
        uint8_t  m_data[SIZE];
        size_t   m_r_pos;
        size_t   m_w_pos;
    };
}

#endif
