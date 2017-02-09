#ifndef __DATA_STRUCT_KMAP_H__
#define __DATA_STRUCT_KMAP_H__

#include <map>

namespace ds
{
    template<typename K>
    class kmap_t : public std::map<K, size_t>
    {
    public:
        kmap_t()
        {
        }
        ~kmap_t()
        {
        }
        void print()
        {
            printf("[(%s:%s:%d) ++++]\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
            printf("[size(%zu)]\n", std::map<K, size_t>::size());
            typename std::map<K, size_t>::iterator iter = std::map<K, size_t>::begin(), end = std::map<K, size_t>::end();
            for(; iter != end; ++ iter)
            {
                K& k = const_cast<K&>((*iter).first);
                k.print();
                printf("[(%zu)]\n", (*iter).second);
            }
            if(0 != std::map<K, size_t>::size())
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
                K k;
                if(!k.read(t))
                {
                    return false;
                }
                uint32_t v = 0;
                if(!t.read(v))
                {
                    return false;
                }
                insert(std::make_pair<K, size_t>(k, v));
            }
            return true;
        }
        template<typename T>
        bool write(T& t)
        {
            uint16_t c = std::map<K, size_t>::size();
            if(!t.write(c))
            {
                return false;
            }
            typename std::map<K, size_t>::iterator iter = std::map<K, size_t>::begin(), end = std::map<K, size_t>::end();
            for(; iter != end; ++ iter)
            {
                K& k = const_cast<K&>((*iter).first);
                if(!k.write(t))
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
