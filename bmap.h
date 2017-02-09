#ifndef __DATA_STRUCT_BMAP_H__
#define __DATA_STRUCT_BMAP_H__

#include <map>

namespace ds
{
    class bmap_t : public std::map<size_t, size_t>
    {
    public:
        bmap_t()
        {
        }
        ~bmap_t()
        {
        }
        void print()
        {
            printf("[(%s:%s:%d) ++++]\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
            printf("[size(%zu)]\n", std::map<size_t, size_t>::size());
            std::map<size_t, size_t>::iterator iter = std::map<size_t, size_t>::begin(), end = std::map<size_t, size_t>::end();
            for(; iter != end; ++ iter)
            {
                printf("[(%zu:%zu)]\n", (*iter).first, (*iter).second);
            }
            if(0 != std::map<size_t, size_t>::size())
            {
                printf("\n");
            }
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
            for(size_t x  = 0; x < c; ++ x)
            {
                uint32_t k = 0;
                if(!t.read(k))
                {
                    return false;
                }
                uint32_t v = 0;
                if(!t.read(v))
                {
                    return false;
                }
                insert(std::make_pair<size_t, size_t>(k, v));
            }
            return true;
        }
        template<typename T>
        bool write(T& t)
        {
            uint16_t c = std::map<size_t, size_t>::size();
            if(!t.write(c))
            {
                return false;
            }
            typename std::map<size_t, size_t>::iterator iter = std::map<size_t, size_t>::begin(), end = std::map<size_t, size_t>::end();
            for(; iter != end; ++ iter)
            {
                uint32_t k = (*iter).first;
                if(!t.write(k))
                {
                    return false;
                }
                uint32_t v = (*iter).second;
                if(!t.write(v))
                {
                    return false;
                }
            }
            return true;
        }
    };
}

#endif
