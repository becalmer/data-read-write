#ifndef __DATA_STRUCT_FILE_H__
#define __DATA_STRUCT_FILE_H__

#include <stdio.h>
#include <type_1.h>

namespace ds
{
    class file_t
    {
    public:
        file_t();
        ~file_t();

        bool open(const filename_t& filename, const char* mode);

        bool create(const filename_t& filename);

        void close();

        bool is_opened() const;

        bool is_exist(const filename_t& filename);

        void read(content_t& content);
        void write(const text_t& text);

    private:
        FILE* m_file;
    };
}

#endif
