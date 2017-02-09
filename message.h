#ifndef __DATA_STRUCT_MESSAGE_H__
#define __DATA_STRUCT_MESSAGE_H__

namespace ds
{
    class message_t
    {
    public:
        message_t();
        virtual ~message_t();

    protected:
        uint8_t* m_data;
        uint32_t m_r_pos;
        uint32_t m_w_pos;
    };
}

#endif
