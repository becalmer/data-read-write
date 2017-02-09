#ifndef __DATA_STRUCT_INFO_H__
#define __DATA_STRUCT_INFO_H__

#include <type_1.h>
#include <svector.h>
#include <kmap.h>
#include <vmap.h>
#include <kvmap.h>

namespace ds
{
    struct unit_info_t
    {
        unit_info_t();

        size_t       m_index;
        typeinfo_t   m_typeinfo;
        identifier_t m_identifier;
    };

    struct enum_info_t
    {
        bool operator == (const enum_info_t& info) const;
        bool operator < (const enum_info_t& info) const;

        bool add(const identifier_t& identifier, const number_t& number);

        identifier_t         m_identifier;
        kmap_t<identifier_t> m_identifier_id_map;
        vmap_t<identifier_t> m_id_identifier_map;
    };

    struct struct_info_t
    {
        bool operator == (const struct_info_t& info) const;
        bool operator < (const struct_info_t& info) const;

        void add_unit_info(const unit_info_t& info);

        identifier_t                m_identifier;
        svector_t<unit_info_t, 128> m_unit_vec;
    };

    struct info_t
    {
        void clear();

        bool is_intersect(const info_t& info);

        bool add_message_info(const identifier_t& identifier, const number_t& number);

        bool add_struct_info(const struct_info_t& info);

        bool add_enum_info(const enum_info_t& info);

        void print();

        bool empty();

        svector_t<identifier_t, 16> m_include_vec;
        kmap_t<identifier_t>      m_identifier_id_map;
        vmap_t<identifier_t>      m_id_identifier_map;
        svector_t<identifier_t, 1024> m_identifier_vec;
        kvmap_t<identifier_t, struct_info_t> m_struct_info_map;
        kvmap_t<identifier_t, enum_info_t>   m_enum_info_map;
    };

    struct info_mgr_t
    {
        void add(const filename_t& filename, const info_t& info);

        void print();

        kvmap_t<filename_t, info_t> m_filename_info_map;
    };

    extern info_mgr_t g_info_mgr;
}

#endif
