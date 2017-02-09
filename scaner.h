#ifndef __DATA_STRUCT_SCANER_H__
#define __DATA_STRUCT_SCANER_H__

#include <type_2.h>

namespace ds
{
    class scaner_t
    {
    public:
        scaner_t(const directory_t& directory);
        ~scaner_t();

        void clear();

        bool open(const directory_t& directory);

        bool is_opened();

        size_t count();

        filename_t& operator [] (size_t idx);

        void print();

    private:
        filename_list_t m_filename_list;
    };
}

#endif
