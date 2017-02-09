#ifndef __DATA_STRUCT_BUFFER_H__
#define __DATA_STRUCT_BUFFER_H__

#include <stdint.h>
#include <string.h>

namespace ds
{
    class buffer_t
    {
    public:
        buffer_t();
        virtual ~buffer_t();

        bool write(const int8_t& x);
        bool write(const uint8_t& x);
        bool write(const int16_t& x);
        bool write(const uint16_t& x);
        bool write(const int32_t& x);
        bool write(const uint32_t& x);
        bool write(const int64_t& x);
        bool write(const uint64_t& x);
        bool write(const int8_t* x, size_t& l);
        bool write(const uint8_t* x, size_t& l);

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

        const uint8_t* raddr();
        size_t rsize();

    protected:
        uint8_t* m_data;
        size_t   m_size;
        size_t   m_r_pos;
        size_t   m_w_pos;
    };
}

#endif
