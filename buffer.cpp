#include <string.h>
#include <stdio.h>
#include "buffer.h"

namespace ds
{
    buffer_t::buffer_t()
    {
        m_size = (1 << 16);
        m_data = new uint8_t[m_size];
        m_r_pos = 0;
        m_w_pos = 0;
    }

    buffer_t::~buffer_t()
    {
        delete[] m_data;
        m_data = 0;
        m_size = 0;
        m_r_pos = 0;
        m_w_pos = 0;
    }

    bool buffer_t::write(const int8_t& x)
    {
        if((m_w_pos + 1) > m_size)
        {
            size_t   sz = m_size + (1 << 16);
            uint8_t* data = new uint8_t[sz];
            if(!data)
            {
                return false;
            }
            memcpy(data, m_data, m_w_pos);
            delete[] m_data;
            m_size = sz;
            m_data = data;
        }

        memcpy(m_data + m_w_pos, &x, 1);
        m_w_pos += 1;

        return true;
    }

    bool buffer_t::write(const uint8_t& x)
    {
        if((m_w_pos + 1) > m_size)
        {
            size_t   sz = m_size + (1 << 16);
            uint8_t* data = new uint8_t[sz];
            if(!data)
            {
                return false;
            }
            memcpy(data, m_data, m_w_pos);
            delete[] m_data;
            m_size = sz;
            m_data = data;
        }

        memcpy(m_data + m_w_pos, &x, 1);
        m_w_pos += 1;

        return true;
    }

    bool buffer_t::write(const int16_t& x)
    {
        if((m_w_pos + 2) > m_size)
        {
            size_t   sz = m_size + (1 << 16);
            uint8_t* data = new uint8_t[sz];
            if(!data)
            {
                return false;
            }
            memcpy(data, m_data, m_w_pos);
            delete[] m_data;
            m_size = sz;
            m_data = data;
        }

        memcpy(m_data + m_w_pos, &x, 2);
        m_w_pos += 2;

        return true;
    }

    bool buffer_t::write(const uint16_t& x)
    {
        if((m_w_pos + 2) > m_size)
        {
            size_t   sz = m_size + (1 << 16);
            uint8_t* data = new uint8_t[sz];
            if(!data)
            {
                return false;
            }
            memcpy(data, m_data, m_w_pos);
            delete[] m_data;
            m_size = sz;
            m_data = data;
        }

        memcpy(m_data + m_w_pos, &x, 2);
        m_w_pos += 2;

        return true;
    }

    bool buffer_t::write(const int32_t& x)
    {
        if((m_w_pos + 4) > m_size)
        {
            size_t   sz = m_size + (1 << 16);
            uint8_t* data = new uint8_t[sz];
            if(!data)
            {
                return false;
            }
            memcpy(data, m_data, m_w_pos);
            delete[] m_data;
            m_size = sz;
            m_data = data;
        }

        memcpy(m_data + m_w_pos, &x, 4);
        m_w_pos += 4;

        return true;
    }

    bool buffer_t::write(const uint32_t& x)
    {
        if((m_w_pos + 4) > m_size)
        {
            size_t   sz = m_size + (1 << 16);
            uint8_t* data = new uint8_t[sz];
            if(!data)
            {
                return false;
            }
            memcpy(data, m_data, m_w_pos);
            delete[] m_data;
            m_size = sz;
            m_data = data;
        }

        memcpy(m_data + m_w_pos, &x, 4);
        m_w_pos += 4;

        return true;
    }

    bool buffer_t::write(const int64_t& x)
    {
        if((m_w_pos + 8) > m_size)
        {
            size_t   sz = m_size + (1 << 16);
            uint8_t* data = new uint8_t[sz];
            if(!data)
            {
                return false;
            }
            memcpy(data, m_data, m_w_pos);
            delete[] m_data;
            m_size = sz;
            m_data = data;
        }

        memcpy(m_data + m_w_pos, &x, 8);
        m_w_pos += 8;

        return true;
    }

    bool buffer_t::write(const uint64_t& x)
    {
        if((m_w_pos + 8) > m_size)
        {
            size_t   sz = m_size + (1 << 16);
            uint8_t* data = new uint8_t[sz];
            if(!data)
            {
                return false;
            }
            memcpy(data, m_data, m_w_pos);
            delete[] m_data;
            m_size = sz;
            m_data = data;
        }

        memcpy(m_data + m_w_pos, &x, 8);
        m_w_pos += 8;

        return true;
    }

    bool buffer_t::write(const int8_t* x, size_t& l)
    {
        if(l <= 0)
        {
            return true;
        }

        size_t m = l + m_w_pos;

        if(m > m_size)
        {
            size_t   n = (m + 1023) / 16 * 16;
            uint8_t* data = new uint8_t[n];
            if(!data)
            {
                return false;
            }
            memcpy(data, m_data, m_w_pos);
            delete[] m_data;
            m_size = n;
            m_data = data;
        }

        memcpy(m_data + m_w_pos, x, l);
        m_w_pos += l;

        return true;
    }

    bool buffer_t::write(const uint8_t* x, size_t& l)
    {
        if(l <= 0)
        {
            return true;
        }

        size_t m = l + m_w_pos;

        if(m > m_size)
        {
            size_t   n = (m + 1023) / 16 * 16;
            uint8_t* data = new uint8_t[n];
            if(!data)
            {
                return false;
            }
            memcpy(data, m_data, m_w_pos);
            delete[] m_data;
            m_size = n;
            m_data = data;
        }

        memcpy(m_data + m_w_pos, x, l);
        m_w_pos += l;

        return true;
    }

    bool buffer_t::read(int8_t& x)
    {
        if((m_r_pos + 1) > m_w_pos)
        {
            return false;
        }

        memcpy(&x, m_data + m_r_pos, 1);
        m_r_pos += 1;

        return true;
    }

    bool buffer_t::read(uint8_t& x)
    {
        if((m_r_pos + 1) > m_w_pos)
        {
            return false;
        }

        memcpy(&x, m_data + m_r_pos, 1);
        m_r_pos += 1;

        return true;
    }

    bool buffer_t::read(int16_t& x)
    {
        if((m_r_pos + 2) > m_w_pos)
        {
            return false;
        }

        memcpy(&x, m_data + m_r_pos, 2);
        m_r_pos += 2;

        return true;
    }

    bool buffer_t::read(uint16_t& x)
    {
        if((m_r_pos + 2) > m_w_pos)
        {
            return false;
        }

        memcpy(&x, m_data + m_r_pos, 2);
        m_r_pos += 2;

        return true;
    }

    bool buffer_t::read(int32_t& x)
    {
        if((m_r_pos + 4) > m_w_pos)
        {
            return false;
        }

        memcpy(&x, m_data + m_r_pos, 4);
        m_r_pos += 4;

        return true;
    }

    bool buffer_t::read(uint32_t& x)
    {
        if((m_r_pos + 4) > m_w_pos)
        {
            return false;
        }

        memcpy(&x, m_data + m_r_pos, 4);
        m_r_pos += 4;

        return true;
    }

    bool buffer_t::read(int64_t& x)
    {
        if((m_r_pos + 8) > m_w_pos)
        {
            return false;
        }

        memcpy(&x, m_data + m_r_pos, 8);
        m_r_pos += 8;

        return true;
    }

    bool buffer_t::read(uint64_t& x)
    {
        if((m_r_pos + 8) > m_w_pos)
        {
            return false;
        }

        memcpy(&x, m_data + m_r_pos, 8);
        m_r_pos += 8;

        return true;
    }

    bool buffer_t::read(int8_t* x, size_t& l)
    {
        if(l <= 0)
        {
            return true;
        }

        if((m_r_pos + l) > m_w_pos)
        {
            return false;
        }

        memcpy(x, m_data + m_r_pos, l);
        m_r_pos += l;

        return true;
    }

    bool buffer_t::read(uint8_t* x, size_t& l)
    {
        if(l <= 0)
        {
            return true;
        }

        if((m_r_pos + l) > m_w_pos)
        {
            return false;
        }

        memcpy(x, m_data + m_r_pos, l);
        m_r_pos += l;

        return true;
    }

    void buffer_t::print()
    {
        printf("[(%s:%s:%d) ++++]\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
        printf("[m_data(%s)]\n", m_data);
        printf("[m_size(%zu)]\n", m_size);
        printf("[m_r_pos(%zu)]\n", m_r_pos);
        printf("[m_w_pos(%zu)]\n", m_w_pos);
        printf("[(%s:%s:%d) ----]\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
    }

    const uint8_t* buffer_t::raddr()
    {
        return (m_data + m_r_pos);
    }

    size_t buffer_t::rsize()
    {
        return (m_w_pos - m_r_pos);
    }
}
