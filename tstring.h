#ifndef __DATA_STRUCT_TSTRING_H__
#define __DATA_STRUCT_TSTRING_H__

#include <string.h>
#include <buffer.h>

namespace ds
{
    class tstring_t
    {
    public:
        tstring_t(const char* s = 0);
        tstring_t(const tstring_t& s);
        ~tstring_t();

        tstring_t& operator = (const char* s);
        tstring_t& operator = (const tstring_t& s);

        bool operator == (const char* s);
        bool operator == (const tstring_t& s);

        void clear();

        void resize(size_t n);

        const char* c_str() const;
        char* c_str();

        const char& operator [] (size_t idx) const;
        char& operator [] (size_t idx);

        size_t append(char c);
        size_t append(const char* s);
        size_t append(const tstring_t& s);

        size_t len() const;
        size_t capacity() const;

        bool equal(const char* s);
        bool equal(const tstring_t& s);

        template<typename T>
        bool write(T& t)
        {
            uint16_t l = m_len;
    
            if(!t.write(l))
            {
                return false;
            }
    
            size_t lt = l;
    
            return t.write((int8_t*)m_data, lt);
        }
   
        template<typename T>
        bool read(T& t)
        {
            uint16_t l = 0;
    
            if(!t.read(l))
            {
                return false;
            }
    
            resize((size_t)l);
    
            if(m_capacity < l)
            {
                return false;
            }
    
            size_t lt = l;
    
            return t.read((int8_t*)m_data, lt);
        }

        void print();

    private:
        char*   m_data;
        size_t  m_len;
        size_t  m_capacity;
    };
}

#endif
