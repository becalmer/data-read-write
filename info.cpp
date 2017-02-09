/*************************************************************************
	> File Name: /data/home/liujinqiao/server/data_struct/src/info.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 18 Jan 2017 08:53:12 PM CST
 ************************************************************************/

#include <info.h>

namespace ds
{
    info_mgr_t g_info_mgr;

    unit_info_t::unit_info_t() : m_index(0)
    {
    }

    bool enum_info_t::operator == (const enum_info_t& info) const
    {
        return (m_identifier == info.m_identifier);
    }

    bool enum_info_t::operator < (const enum_info_t& info) const
    {
        return (m_identifier < info.m_identifier);
    }

    bool enum_info_t::add(const identifier_t& identifier, const number_t& number)
    {
        if(m_id_identifier_map.size() > 0)
        {
            vmap_t<identifier_t>::iterator iter = m_id_identifier_map.end();
            -- iter;
            if(number.to_uint32() <= (*iter).first)
            {
                printf("[%s:%s:%d] identifier(%s) id(%s) <= max id(%zu)\n", __FILE__, __PRETTY_FUNCTION__, __LINE__, identifier.c_str(), number.c_str(), (*iter).first);
                return false;
            }
        }
        kmap_t<identifier_t>::iterator kiter = m_identifier_id_map.find(identifier);
        if(kiter == m_identifier_id_map.end())
        {
            m_identifier_id_map[identifier] = number.to_uint32();
        }
        else
        {
            printf("[%s:%s:%d] identifier(%s) exist id(%zu), new id(%s)\n", __FILE__, __PRETTY_FUNCTION__, __LINE__, identifier.c_str(), (*kiter).second, number.c_str());
            return false;
        }
        vmap_t<identifier_t>::iterator titer = m_id_identifier_map.find(number.to_uint32());
        if(titer == m_id_identifier_map.end())
        {
            m_id_identifier_map[number.to_uint32()] = identifier;
        }
        else
        {
            printf("[%s:%s:%d] id(%s) exist identifier(%s), new identifier(%s)\n", __FILE__, __PRETTY_FUNCTION__, __LINE__, number.c_str(), (*titer).second.c_str(), identifier.c_str());
            return false;
        }

        return true;
    }

    bool struct_info_t::operator == (const struct_info_t& info) const
    {
        return (m_identifier == info.m_identifier);
    }

    bool struct_info_t::operator < (const struct_info_t& info) const
    {
        return (m_identifier < info.m_identifier);
    }

    void struct_info_t::add_unit_info(const unit_info_t& info)
    {
        size_t count = m_unit_vec.count();
        size_t x = 0;
        for(; x < count; ++ x)
        {
            if(info.m_identifier == m_unit_vec[x].m_identifier)
            {
                printf("[%s:%s:%d] identifier(%s) exist index(%zu) typeinfo(%s), new index(%zu) typeinfo(%s)\n", __FILE__, __PRETTY_FUNCTION__, __LINE__, m_unit_vec[x].m_identifier.c_str(), m_unit_vec[x].m_index, m_unit_vec[x].m_typeinfo.c_str(), info.m_index, info.m_typeinfo.c_str());
            }
            if(info.m_index == m_unit_vec[x].m_index)
            {
                printf("[%s:%s:%d] index(%zu) exist identifier(%s) typeinfo(%s), new identifier(%s) typeinfo(%s)\n", __FILE__, __PRETTY_FUNCTION__, __LINE__, m_unit_vec[x].m_index, m_unit_vec[x].m_identifier.c_str(), m_unit_vec[x].m_typeinfo.c_str(), info.m_identifier.c_str(), info.m_typeinfo.c_str());
            }
        }

        if(x == count)
        {
            unit_info_t& rinfo = m_unit_vec.alloc();
            rinfo = info;
        }
    }

    void info_t::clear()
    {
        m_identifier_id_map.clear();
        m_id_identifier_map.clear();
        m_struct_info_map.clear();
        m_enum_info_map.clear();
        m_identifier_vec.clear();
        m_include_vec.clear();
    }

    bool info_t::is_intersect(const info_t& info)
    {
        kmap_t<identifier_t>::iterator iter1 = m_identifier_id_map.begin(), end1 = m_identifier_id_map.end();
        for(; iter1 != end1; ++ iter1)
        {
            if(info.m_identifier_id_map.end() != info.m_identifier_id_map.find((*iter1).first))
            {
                return true;
            }
        }
        vmap_t<identifier_t>::iterator iter2 = m_id_identifier_map.begin(), end2 = m_id_identifier_map.end();
        for(; iter2 != end2; ++ iter2)
        {
            if(info.m_id_identifier_map.end() != info.m_id_identifier_map.find((*iter2).first))
            {
                return true;
            }
        }
        kvmap_t<identifier_t, struct_info_t>::iterator iter3 = m_struct_info_map.begin(), end3 = m_struct_info_map.end();
        for(; iter3 != end3; ++ iter3)
        {
            if(info.m_struct_info_map.end() != info.m_struct_info_map.find((*iter3).first))
            {
                return true;
            }
        }
        kvmap_t<identifier_t, enum_info_t>::iterator iter4 = m_enum_info_map.begin(), end4 = m_enum_info_map.end();
        for(; iter4 != end4; ++ iter4)
        {
            if(info.m_enum_info_map.end() != info.m_enum_info_map.find((*iter4).first))
            {
                return true;
            }
        }
        return false;
    }

    bool info_t::add_message_info(const identifier_t& identifier, const number_t& number)
    {
        if(m_id_identifier_map.size() > 0)
        {
            vmap_t<identifier_t>::iterator iter = m_id_identifier_map.end();
            -- iter;
            if(number.to_uint32() <= (*iter).first)
            {
                printf("[%s:%s:%d] identifier(%s) id(%s) <= max id(%zu)\n", __FILE__, __PRETTY_FUNCTION__, __LINE__, identifier.c_str(), number.c_str(), (*iter).first);
                return false;
            }
        }
        kmap_t<identifier_t>::iterator kiter = m_identifier_id_map.find(identifier);
        if(kiter == m_identifier_id_map.end())
        {
            m_identifier_id_map[identifier] = number.to_uint32();
        }
        else
        {
            printf("[%s:%s:%d] identifier(%s) exist id(%zu), new id(%s)\n", __FILE__, __PRETTY_FUNCTION__, __LINE__, identifier.c_str(), (*kiter).second, number.c_str());
            return false;
        }
        vmap_t<identifier_t>::iterator titer = m_id_identifier_map.find(number.to_uint32());
        if(titer == m_id_identifier_map.end())
        {
            m_id_identifier_map[number.to_uint32()] = identifier;
        }
        else
        {
            printf("[%s:%s:%d] id(%s) exist identifier(%s), new identifier(%s)\n", __FILE__, __PRETTY_FUNCTION__, __LINE__, number.c_str(), (*titer).second.c_str(), identifier.c_str());
            return false;
        }

        return true;
    }

    bool info_t::add_struct_info(const struct_info_t& info)
    {
        kvmap_t<identifier_t, struct_info_t>::iterator iter = m_struct_info_map.find(info.m_identifier);
        if(iter == m_struct_info_map.end())
        {
            m_struct_info_map[info.m_identifier] = info;
        }
        else
        {
            printf("[%s:%s:%d] identifier(%s) exist]\n", __FILE__, __PRETTY_FUNCTION__, __LINE__, (*iter).first.c_str());
            return false;
        }

        identifier_t& name = m_identifier_vec.alloc();
        name = info.m_identifier;

        return true;
    }

    bool info_t::add_enum_info(const enum_info_t& info)
    {
        kvmap_t<identifier_t, enum_info_t>::iterator iter = m_enum_info_map.find(info.m_identifier);
        if(iter == m_enum_info_map.end())
        {
            m_enum_info_map[info.m_identifier] = info;
        }
        else
        {
            printf("[%s:%s:%d] identifier(%s) exist]\n", __FILE__, __PRETTY_FUNCTION__, __LINE__, (*iter).first.c_str());
            return false;
        }

        identifier_t& name = m_identifier_vec.alloc();
        name = info.m_identifier;

        return true;
    }

    void info_t::print()
    {
        printf("[%s:%s:%d] message info ----------------------------\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
        vmap_t<identifier_t>::iterator miiter = m_id_identifier_map.begin(), miend = m_id_identifier_map.end();
        for(; miiter != miend; ++ miiter)
        {
            printf("[message(%s), id(%zu)]\n", (*miiter).second.c_str(), (*miiter).first);
        }
        printf("[%s:%s:%d] message info ----------------------------\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
        printf("[%s:%s:%d] struct info ++++++++++++++++++++++++++++\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
        kvmap_t<identifier_t, struct_info_t>::iterator isiter = m_struct_info_map.begin(), isend = m_struct_info_map.end();
        for(; isiter != isend; ++ isiter)
        {
            printf("[struct(%s)]\n", (*isiter).first.c_str());
            struct_info_t& siinfo = (*isiter).second;
            size_t count = siinfo.m_unit_vec.count();
            for(size_t x = 0; x < count; ++ x)
            {
                unit_info_t& uiinfo = siinfo.m_unit_vec[x];
                printf("[index(%zu), typeinfo(%s), identifier(%s)]\n", uiinfo.m_index, uiinfo.m_typeinfo.c_str(), uiinfo.m_identifier.c_str());
            }
        }
        printf("[%s:%s:%d] struct info ++++++++++++++++++++++++++++\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
        printf("[%s:%s:%d] enum info @@@@@@@@@@@@@@@@@@@@@@@@@@@@\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
        kvmap_t<identifier_t, enum_info_t>::iterator ieiter = m_enum_info_map.begin(), ieend = m_enum_info_map.end();
        for(; ieiter != ieend; ++ ieiter)
        {
            printf("[enum(%s)]\n", (*ieiter).first.c_str());
            enum_info_t& eiinfo = (*ieiter).second;
            vmap_t<identifier_t>::iterator eiiter = eiinfo.m_id_identifier_map.begin(), eiend = eiinfo.m_id_identifier_map.end();
            for(; eiiter != eiend; ++ eiiter)
            {
                printf("[id(%zu), identifier(%s)]\n", (*eiiter).first, (*eiiter).second.c_str());
            }
        }
        printf("[%s:%s:%d] enum info @@@@@@@@@@@@@@@@@@@@@@@@@@@@\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
        printf("[%s:%s:%d] identifier info *************************\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
        for(size_t x = 0; x < m_identifier_vec.count(); ++ x)
        {
            printf("[%s)]\n", m_identifier_vec[x].c_str());
        }
        printf("[%s:%s:%d] identifier info *************************\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
        printf("[%s:%s:%d] include info &&&&&&&&&&&&&&&&&&&&&&&&&&\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
        for(size_t x = 0; x < m_include_vec.count(); ++ x)
        {
            printf("[%s)]\n", m_include_vec[x].c_str());
        }
        printf("[%s:%s:%d] include info &&&&&&&&&&&&&&&&&&&&&&&&&&&\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
    }

    bool info_t::empty()
    {
        return ((m_identifier_id_map.size() == 0) && (m_struct_info_map.size() == 0) && (m_enum_info_map.size() == 0));
    }

    void info_mgr_t::add(const filename_t& filename, const info_t& info)
    {
        kvmap_t<filename_t, info_t>::iterator iter = m_filename_info_map.find(filename);
        if(iter == m_filename_info_map.end())
        {
            kvmap_t<filename_t, info_t>::iterator iiter = m_filename_info_map.begin(), iend = m_filename_info_map.end();
            for(; iiter != iend; ++ iiter)
            {
                info_t& rinfo = (*iiter).second;
                if(rinfo.is_intersect(info))
                {
                    return;
                }
            }
            m_filename_info_map[filename] = info;
        }
        else
        {
            printf("[%s:%s:%d] filename(%s), exist\n", __FILE__, __PRETTY_FUNCTION__, __LINE__, filename.c_str());
        }
    }

    void info_mgr_t::print()
    {
        printf("[%s:%s:%d] info mgr &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
        kvmap_t<filename_t, info_t>::iterator iter = m_filename_info_map.begin(), end = m_filename_info_map.end();
        for(;iter != end; ++ iter)
        {
            printf("[filename(%s)]\n", (*iter).first.c_str());
            info_t& info = (*iter).second;
            info.print();
        }
        printf("[%s:%s:%d] info mgr &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
    }
}
