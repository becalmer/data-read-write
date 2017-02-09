#ifndef __DATA_STRUCT_AUX_H__
#define __DATA_STRUCT_AUX_H__

#include <type_1.h>

namespace ds
{
    class aux_t
    {
    public:
        aux_t();

        void clear();

        const value_t& tostring(size_t x);

    private:
        value_t m_value;
    };
}

#endif
