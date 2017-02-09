#include "utils.h"

namespace ds
{
    bool is_alpha(char c)
    {
       return (((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')));
    }
    bool is_backslash(char c)
    {
        return (c == '/');
    }
}
