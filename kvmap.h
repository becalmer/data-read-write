#ifndef __DATA_STRUCT_KVMAP_H__
#define __DATA_STRUCT_KVMAP_H__

#include <map>

namespace ds
{
    template<typename K, typename V>
    class kvmap_t : public std::map<K, V>
    {
    public:
        kvmap_t()
        {
        }
        ~kvmap_t()
        {
        }
        void print()
        {
            printf("[(%s:%s:%d) ++++]\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
            printf("[size(%zu)]\n", std::map<K, V>::size());
            typename std::map<K, V>::iterator iter = std::map<K, V>::begin(), end = std::map<K, V>::end();
            for(; iter != end; ++ iter)
            {
                K& k = const_cast<K&>((*iter).first);
                k.print();
                V& v = const_cast<V&>((*iter).second);
                v.print();
            }
            if(0 != std::map<K, V>::size())
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
                V v;
                if(!v.read(t))
                {
                    return false;
                }
                insert(std::make_pair<K, V>(k, v));
            }
            return true;
        }
        template<typename T>
        bool write(T& t)
        {
            uint16_t c = std::map<K, V>::size();
            if(!t.write(c))
            {
                return false;
            }
            typename std::map<K, V>::iterator iter = std::map<K, V>::begin(), end = std::map<K, V>::end();
            for(; iter != end; ++ iter)
            {
                K& k = const_cast<K&>((*iter).first);
                if(!k.write(t))
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
