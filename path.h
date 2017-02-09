#ifndef __DATA_STRUCT_PATH_H__
#define __DATA_STRUCT_PATH_H__

#include <type_2.h>

namespace ds
{
    class path_t
    {
    public:
        path_t();
        ~path_t();

        static bool is_valid(const directory_t& directory);

        static void split_to_stack(const directory_t& directory, filename_stack_t& stack);
        static void split_to_queue(const directory_t& directory, filename_queue_t& queue);

        directory_t& absolute_directory(const directory_t& directory);

    private:
        void parse(const directory_t& director);

        directory_t      m_directory;
    };
}

#endif
