#ifndef __DATA_STRUCT_TYPE_1_H__
#define __DATA_STRUCT_TYPE_1_H__

#include <sstring.h>
#include <ebuffer.h>

namespace ds
{
    typedef sstring_t<256>                format_t;
    typedef sstring_t<256>                filename_t;
    typedef sstring_t<256>                directory_t;
    typedef ebuffer_t<524288>             content_t;
    typedef sstring_t<64>                 identifier_t;
    typedef sstring_t<16>                 number_t;
    typedef sstring_t<64>                 typeinfo_t;
    typedef sstring_t<256>                value_t;
    typedef sstring_t<524288>             text_t;
    typedef sstring_t<16>                 user_t;
    typedef sstring_t<16>                 password_t;
}

#endif
