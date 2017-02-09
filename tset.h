#ifndef __DATA_STRUCT_TSET_H__
#define __DATA_STRUCT_TSET_H__

#include <set>

namespace ds
{
    template<typename T>
    class tset_t : public std::set<T>
    {
    public:
        tset_t()
        {
        }
        ~tset_t()
        {
        }
        void print()
        {
            printf("[(%s:%s:%d) ++++]\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
            printf("[size(%zu)]\n", std::set<T>::size());
            typename std::set<T>::iterator iter = std::set<T>::begin(), end = std::set<T>::end();
            for(; iter != end; ++ iter)
            {
                T& t = const_cast<T&>(*iter);
                t.print();
            }
            if(0 != std::set<T>::size())
            {
                printf("\n");
            }
            printf("[(%s:%s:%d) ----]\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
        }
        template<typename V>
        bool read(V& v)
        {
            uint16_t c = 0;
            if(!v.read(c))
            {
                return false;
            }
            for(size_t x = 0; x < c; ++ x)
            {
                T t;
                if(!t.read(v))
                {
                    return false;
                }
                insert(t);
            }
            return true;
        }
        template<typename V>
        bool write(V& v)
        {
            uint16_t c = std::set<T>::size();
            if(!v.write(c))
            {
                return false;
            }
            typename std::set<T>::iterator iter = std::set<T>::begin(), end = std::set<T>::end();
            for(; iter != end; ++ iter)
            {
                T& t = const_cast<T&>((*iter));
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
