#ifndef __DATA_STRUCT_VMAP_H__
#define __DATA_STRUCT_VMAP_H__

#include <map>

namespace ds
{
    template<typename V>
    class vmap_t : public std::map<size_t, V>
    {
    public:
        vmap_t()
        {
        }
        ~vmap_t()
        {
        }
        void print()
        {
            printf("[(%s:%s:%d) ++++]\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
            printf("[size(%zu)]\n", std::map<size_t, V>::size());
            typename std::map<size_t, V>::iterator iter = std::map<size_t, V>::begin(), end = std::map<size_t, V>::end();
            for(; iter != end; ++ iter)
            {
                printf("[(%zu)]\n", (*iter).first);
                V& v = const_cast<V&>((*iter).second);
                v.print();
            }
            if(0 != std::map<size_t, V>::size())
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
                V v;
                if(!v.read(t))
                {
                    return false;
                }
                insert(std::make_pair<size_t, V>(k, v));
            }
            return true;
        }
        template<typename T>
        bool write(T& t)
        {
            uint16_t c = std::map<size_t, V>::size();
            if(!t.write(c))
            {
                return false;
            }
            typename std::map<size_t, V>::iterator iter = std::map<size_t, V>::begin(), end = std::map<size_t, V>::end();
            for(; iter != end; ++ iter)
            {
                uint32_t k = (*iter).first;
                if(!t.write(k))
                {
                    return false;
                }
                V& v = const_cast<V&>((*iter).second);
                if(!v.write(t))
                {
                    return false;
                }
            }
            return true;
        }
    };
}

#endif
