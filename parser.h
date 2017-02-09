#ifndef __DATA_STRUCT_PARSER_H__
#define __DATA_STRUCT_PARSER_H__

#include <type_1.h>
#include <info.h>

namespace ds
{
    class parser_t
    {
    public:
        parser_t();
        ~parser_t();

        void clear();

        void handle(content_t& content);

        bool handle_message(const char* p, content_t& content);
        bool handle_struct(const char* p, content_t& content);
        bool handle_enum(const char* p, content_t& content);
        bool handle_include(const char* p, content_t& content);

        void set_filename(const filename_t& filename);

    private:
        filename_t m_filename;
        info_t     m_info;
    };
}

#endif
