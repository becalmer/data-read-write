#include <string.h>
#include <stdio.h>
#include "sbuffer.h"

namespace ds
{
    sbuffer_t::sbuffer_t()
    {
        m_r_pos = 0;
        m_w_pos = 0;
    }

    sbuffer_t::~sbuffer_t()
    {
        m_r_pos = 0;
        m_w_pos = 0;
    }

    bool sbuffer_t::write(const int8_t& x)
    {
        if((m_w_pos + 1) > SIZE)
        {
            return false;
        }

        memcpy(m_data + m_w_pos, &x, 1);
        m_w_pos += 1;

        return true;
    }

    bool sbuffer_t::write(const uint8_t& x)
    {
        if((m_w_pos + 1) > SIZE)
        {
            return false;
        }

        memcpy(m_data + m_w_pos, &x, 1);
        m_w_pos += 1;

        return true;
    }

    bool sbuffer_t::write(const int16_t& x)
    {
        if((m_w_pos + 2) > SIZE)
        {
            return false;
        }

        memcpy(m_data + m_w_pos, &x, 2);
        m_w_pos += 2;

        return true;
    }

    bool sbuffer_t::write(const uint16_t& x)
    {
        if((m_w_pos + 2) > SIZE)
        {
            return false;
        }

        memcpy(m_data + m_w_pos, &x, 2);
        m_w_pos += 2;

        return true;
    }

    bool sbuffer_t::write(const int32_t& x)
    {
        if((m_w_pos + 4) > SIZE)
        {
            return false;
        }

        memcpy(m_data + m_w_pos, &x, 4);
        m_w_pos += 4;

        return true;
    }

    bool sbuffer_t::write(const uint32_t& x)
    {
        if((m_w_pos + 4) > SIZE)
        {
            return false;
        }

        memcpy(m_data + m_w_pos, &x, 4);
        m_w_pos += 4;

        return true;
    }

    bool sbuffer_t::write(const int64_t& x)
    {
        if((m_w_pos + 8) > SIZE)
        {
            return false;
        }

        memcpy(m_data + m_w_pos, &x, 8);
        m_w_pos += 8;

        return true;
    }

    bool sbuffer_t::write(const uint64_t& x)
    {
        if((m_w_pos + 8) > SIZE)
        {
            return false;
        }

        memcpy(m_data + m_w_pos, &x, 8);
        m_w_pos += 8;

        return true;
    }

    bool sbuffer_t::write(const int8_t* x, size_t l)
    {
        uint32_t n = l;
        if(!write(n))
        {
            return false;
        }

        size_t m = l + m_w_pos;

        if((l + m_w_pos) > SIZE)
        {
            return false;
        }

        memcpy(m_data + m_r_pos, x, l);
        m_w_pos += l;

        return true;
    }

    bool sbuffer_t::write(const uint8_t* x, size_t l)
    {
        uint32_t n = l;
        if(!write(n))
        {
            return false;
        }

        if((l + m_w_pos) > SIZE)
        {
            return false;
        }

        memcpy(m_data + m_w_pos, x, l);
        m_w_pos += l;

        return true;
    }

    bool sbuffer_t::read(int8_t& x)
    {
        if((m_r_pos + 1) > m_w_pos)
        {
            return false;
        }

        memcpy(&x, m_data + m_r_pos, 1);
        m_r_pos += 1;

        return true;
    }

    bool sbuffer_t::read(uint8_t& x)
    {
        if((m_r_pos + 1) > m_w_pos)
        {
            return false;
        }

        memcpy(&x, m_data + m_r_pos, 1);
        m_r_pos += 1;

        return true;
    }

    bool sbuffer_t::read(int16_t& x)
    {
        if((m_r_pos + 2) > m_w_pos)
        {
            return false;
        }

        memcpy(&x, m_data + m_r_pos, 2);
        m_r_pos += 2;

        return true;
    }

    bool sbuffer_t::read(uint16_t& x)
    {
        if((m_r_pos + 2) > m_w_pos)
        {
            return false;
        }

        memcpy(&x, m_data + m_r_pos, 2);
        m_r_pos += 2;

        return true;
    }

    bool sbuffer_t::read(int32_t& x)
    {
        if((m_r_pos + 4) > m_w_pos)
        {
            return false;
        }

        memcpy(&x, m_data + m_r_pos, 4);
        m_r_pos += 4;

        return true;
    }

    bool sbuffer_t::read(uint32_t& x)
    {
        if((m_r_pos + 4) > m_w_pos)
        {
            return false;
        }

        memcpy(&x, m_data + m_r_pos, 4);
        m_r_pos += 4;

        return true;
    }

    bool sbuffer_t::read(int64_t& x)
    {
        if((m_r_pos + 8) > m_w_pos)
        {
            return false;
        }

        memcpy(&x, m_data + m_r_pos, 8);
        m_r_pos += 8;

        return true;
    }

    bool sbuffer_t::read(uint64_t& x)
    {
        if((m_r_pos + 8) > m_w_pos)
        {
            return false;
        }

        memcpy(&x, m_data + m_r_pos, 8);
        m_r_pos += 8;

        return true;
    }

    bool sbuffer_t::read(int8_t* x, size_t& l)
    {
        uint32_t n = 0;
        if(!read(n))
        {
            return false;
        }

        if((m_r_pos + n) > m_w_pos)
        {
            return false;
        }

        l = n;

        memcpy(x, m_data + m_r_pos, n);
        m_r_pos += n;

        return true;
    }

    bool sbuffer_t::read(uint8_t* x, size_t& l)
    {
        uint32_t n = 0;
        if(!read(n))
        {
            return false;
        }

        if((m_r_pos + n) > m_w_pos)
        {
            return false;
        }

        l = n;

        memcpy(x, m_data + m_r_pos, n);
        m_r_pos += n;

        return true;
    }

    void sbuffer_t::print()
    {
        printf("[(%s:%s:%d) ++++]\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
        printf("[m_data(%s)]\n", m_data);
        printf("[m_r_pos(%zu)]\n", m_r_pos);
        printf("[m_w_pos(%zu)]\n", m_w_pos);
        printf("[(%s:%s:%d) ----]\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
    }
}
