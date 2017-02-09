#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

namespace ds
{
    template<size_t N>
    class sstring_t
    {
    public:
        sstring_t(const char* s = 0)
        {
            m_len = 0;

            append(s);
        }
        
        sstring_t(const sstring_t<N>& s)
        {
            m_len = 0;

            append(s.c_str());
        }
         
        ~sstring_t()
        {
        }
         
        sstring_t& operator = (const char* s)
        {
            clear();
            append(s);

            return *this;
        }
         
        sstring_t<N>& operator = (const sstring_t<N>& s)
        {
            return (*this = s.c_str());
        }

        bool operator == (const char* s)
        {
            return equal(s);
        }

        bool operator == (const sstring_t<N>& s) const
        {
            return equal(s.c_str());
        }

        bool operator < (const sstring_t<N>& s) const
        {
            return (strncmp(m_data, s.m_data, m_len) < 0);
        }

        void clear()
        {
            m_len = 0;
        }

        const char* c_str() const
        {
            return m_data;
        }
         
        char* c_str()
        {
            return m_data;
        }

        const char& operator [] (size_t idx) const
        {
            return m_data[idx];
        }

        char& operator [] (size_t idx)
        {
            return m_data[idx];
        }

        size_t append(char c)
        {
            char ch[2] = {c, 0};
            return append(ch);
        }

        size_t append(const char* s)
        {
            if(!s)
            {
                return m_len;
            }

            size_t l = strlen(s);

            if((l + m_len) > N)
            {
                return m_len;
            }

            strncpy(m_data + m_len, s, l);
            m_len += l;
            m_data[m_len] = 0;

            return m_len;
        }

        size_t append(const sstring_t& s)
        {
            return append(s.c_str());
        }

        size_t len()
        {
            return m_len;
        }

        size_t len() const
        {
            return m_len;
        }

        size_t capacity()
        {
            return N;
        }

        size_t capacity() const
        {
            return N;
        }

        bool equal(const char* s) const
        {
            return (0 == strncmp(m_data, s, m_len));
        }

        bool equal(const char* s)
        {
            return (0 == strncmp(m_data, s, m_len));
        }

        bool equal(const sstring_t<N>& s) const
        {
            if(m_len != s.len())
            {
                return false;
            }
            return equal(s.c_str());
        }

        bool equal(const sstring_t<N>& s)
        {
            if(m_len != s.len())
            {
                return false;
            }
            return equal(s.c_str());
        }

        const char* substr(size_t from)
        {
            return (m_data + from);
        }

        const char* substr(size_t from) const
        {
            return (m_data + from);
        }

        uint32_t to_uint32() const
        {
            return strtol(m_data, 0, 10);
        }

        int32_t to_int32()
        {
            return strtol(m_data, 0, 10);
        }

        template<typename T>
        bool write(T& t)
        {
            uint16_t l = m_len;

            if(!t.write(l))
            {
                return false;
            }

            return t.write((uint8_t*)m_data, m_len);
        }

        template<typename T>
        bool read(T& t)
        {
            uint16_t l = 0;

            if(!t.read(l))
            {
                return false;
            }

            if(N < l)
            {
                return false;
            }

            m_len = l;

            if(!t.read((uint8_t*)m_data, m_len))
            {
                return false;
            }

            return true;
        }

        void print()
        {
            printf("[(%s:%s:%d) ++++]\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
            printf("[m_len(%zu)]\n", m_len);
            printf("[m_data(%s)]\n", m_data);
            printf("[(%s:%s:%d) ----]\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
        }

    private:
        char   m_data[N];
        size_t m_len;
    };
}
