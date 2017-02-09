#ifndef __DATA_STRUCT_STSET_H__
#define __DATA_STRUCT_STSET_H__

#include <set>

#include <string.h>
#include <stdint.h>
#include <typeid.h>

namespace ds
{
    class stset_t : public std::set<size_t>
    {
    public:
        stset_t()
        {
        }
        ~stset_t()
        {
        }
        void print()
        {
            printf("[(%s:%s:%d) ++++]\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
            printf("[size(%zu)]\n", std::set<size_t>::size());
            printf("[");
            size_t c = 0;
            std::set<size_t>::iterator iter = std::set<size_t>::begin(), end = std::set<size_t>::end();
            for(; iter != end; ++ iter)
            {
                size_t t = (*iter);
                printf("%zu", t);
                if((c + 1) != std::set<size_t>::size())
                {
                    printf(":");
                }
            }
            printf("]\n");
            printf("[(%s:%s:%d) ----]\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
        }
        template<typename T>
        bool read(T& t)
        {
            uint16_t c = 0;
            if(!t.read(c))
            {
                return false;
            }
            for(size_t x = 0; x < c; ++ x)
            {
                uint32_t z = 0;
                if(!t.read(z))
                {
                    return false;
                }
                insert(z);
            }
            return true;
        }
        template<typename T>
        bool write(T& t)
        {
            uint16_t c = std::set<size_t>::size();
            if(!t.write(c))
            {
                return false;
            }
            std::set<size_t>::iterator iter = std::set<size_t>::begin(), end = std::set<size_t>::end();
            for(; iter != end; ++ iter)
            {
                uint32_t x = (*iter);
                if(!t.write(x))
                {
                    return false;
                }
            }
            return true;
        }
    };
}

#endif
