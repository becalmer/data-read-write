#include <stdint.h>
#include <stdio.h>
#include "tstring.h"

namespace ds
{
    tstring_t::tstring_t(const char* s)
    {
        m_data = 0;
        m_len = 0;
        m_capacity = 0;

        append(s);
    }
    
    tstring_t::tstring_t(const tstring_t& s)
    {
        m_data = 0;
        m_len = 0;
        m_capacity = 0;

        append(s.c_str());
    }
    
    tstring_t::~tstring_t()
    {
        if(m_data)
        {
            delete[] m_data;
            m_data = 0;
            m_len = 0;
            m_capacity = 0;
        }
    }
    
    tstring_t& tstring_t::operator = (const char* s)
    {
        m_len = 0;

        append(s);

        return *this;
    }
    
    tstring_t& tstring_t::operator = (const tstring_t& s)
    {
        return (*this = s.c_str());
    }

    bool tstring_t::operator == (const char* s)
    {
        return equal(s);
    }

    bool tstring_t::operator == (const tstring_t& s)
    {
        return equal(s.c_str());
    }

    void tstring_t::clear()
    {
        m_len = 0;
    }

    void tstring_t::resize(size_t n)
    {
        if(m_capacity >= n)
        {
            return;
        }

        size_t l = (n + 1023) / 16 * 16;
        char* data = new char[l];
        if(!data)
        {
            return;
        }

        if(m_data)
        {
            if(m_len > 0)
            {
                strncpy(data, m_data, m_len);
                data[m_len] = 0;
            }
            delete[] m_data;
        }

        m_data = data;

        m_capacity = l;
    }
    
    const char* tstring_t::c_str() const
    {
        return m_data;
    }
    
    char* tstring_t::c_str()
    {
        return m_data;
    }

    const char& tstring_t::operator [] (size_t idx) const
    {
        return m_data[idx];
    }
 
    char& tstring_t::operator [] (size_t idx)
    {
        return m_data[idx];
    }

    size_t tstring_t::append(char c)
    {
        char ch[2] = {c, 0};
        return append(ch);
    }

    size_t tstring_t::append(const char* s)
    {
        if(!s)
        {
            return m_len;
        }

        size_t l = strlen(s);

        if(l >= m_capacity)
        {
            resize(l);
        }

        strncpy(m_data + m_len, s, l);
        m_len += l;

        m_data[m_len] = 0;

        return m_len;
    }

    size_t tstring_t::append(const tstring_t& s)
    {
        return append(s.c_str());
    }

    size_t tstring_t::len() const
    {
        return m_len;
    }

    size_t tstring_t::capacity() const
    {
        return m_capacity;
    }

    bool tstring_t::equal(const char* s)
    {
        return (0 == strncmp(m_data, s, m_len));
    }

    bool tstring_t::equal(const tstring_t& s)
    {
        if(m_len != s.len())
        {
            return false;
        }
        return equal(s.c_str());
    }

    void tstring_t::print()
    {
        printf("[(%s:%s:%d) ++++]\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
        printf("[m_len(%zu)]\n", m_len);
        printf("[m_capacity(%zu)]\n", m_capacity);
        printf("[m_data(%s)]\n", m_data);
        printf("[(%s:%s:%d) ----]\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
    }
}
