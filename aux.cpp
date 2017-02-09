#include "aux.h"

namespace ds
{
    aux_t::aux_t()
    {
        clear();
    }

    void aux_t::clear()
    {
        m_value.clear();
    }

    const value_t& aux_t::tostring(size_t x)
    {
        char buff[m_value.capacity()];
        snprintf(buff, m_value.capacity() - 1, "%zu", x);
        m_value = buff;
        return m_value;
    }
}
