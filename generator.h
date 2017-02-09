#ifndef __DATA_STRUCT_GENERATOR_H__
#define __DATA_STRUCT_GENERATOR_H__

#include <type_1.h>
#include <info.h>

namespace ds
{
    class generator_t
    {
    public:
        generator_t();

        void clear();

        void handle(const filename_t& filename, const directory_t& directory_in, const directory_t& directory_out);

    private:
        void generate_header(const filename_t& filename, const info_t& info);
        void generate_cpp(const filename_t& filename, const info_t& info);
        void write(const filename_t& filename, const text_t& text);
        void parse_header_name(const filename_t& filename, filename_t& filename_out);
        size_t m_last_struct_index;
    };
}

#endif
