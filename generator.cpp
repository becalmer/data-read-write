#include <generator.h>
#include <info.h>
#include <pwd.h>
#include <unistd.h>
#include <utils.h>
#include <aux.h>
#include <file.h>

namespace ds
{
    generator_t::generator_t()
    {
        clear();
    }

    void generator_t::clear()
    {
        m_last_struct_index = 9999999;
    }

    bool is_base_type(const typeinfo_t& info)
    {
        if(info.equal("uint32_t"))
        {
            return true;
        }
        if(info.equal("uint16_t"))
        {
            return true;
        }
        if(info.equal("uint8_t"))
        {
            return true;
        }
        return false;
    }

    bool is_base64_type(const typeinfo_t& info)
    {
        if(info.equal("uint64_t"))
        {
            return true;
        }
        return false;
    }

    void generate_header_macro(const filename_t& filename, value_t& value)
    {
        struct passwd* pwd = getpwuid(getuid());
        const char* p = strstr(filename.c_str(), pwd->pw_name);
        if(!p)
        {
            printf("[%s:%s:%d] filename(%s) cant find user(%s)!\n", __FILE__, __PRETTY_FUNCTION__, __LINE__, filename.c_str(), pwd->pw_name);
            return;
        }

        p += strlen(pwd->pw_name);

        ++ p;

        value.append("__");
        while(*p)
        {
            if(is_alpha(*p))
            {
                value.append(*p & (~0X20));
            }
            else if(is_backslash(*p))
            {
                value.append('_');
            }
            ++ p;
        }
        value.append("_H__");

        //printf("macro(%s)\n", value.c_str());
    }

    void generator_t::write(const filename_t& name, const text_t& text)
    {
        file_t file;

        if(file.is_exist(name))
        {
            if(file.open(name, "rb"))
            {
                content_t content;

                file.read(content);

                if(!text.equal(content.raddr()))
                {
                    file.close();
                    if(file.open(name, "wb"))
                    {
                        file.write(text);
                    }
                }
            }
        }
        else
        {
            if(file.create(name))
            {
                file.write(text);
            }
            else
            {
                printf("[%s:%s:%d] name(%s), open failed!\n", __FILE__, __PRETTY_FUNCTION__, __LINE__, name.c_str());
            }
        }
    }

    bool try_handle_enum_header(const identifier_t& identifier, const info_t& info, text_t& text)
    {
       kvmap_t<identifier_t, enum_info_t>::const_iterator iter1 = info.m_enum_info_map.find(identifier);
       if(iter1 == info.m_enum_info_map.end())
       {
           return false;
       }

       aux_t aux;

       text.append("\n  enum ");
       text.append((*iter1).first.c_str());
       text.append("\n  {");
       const enum_info_t& einfo = (*iter1).second;
       vmap_t<identifier_t>::const_iterator iter2 = einfo.m_id_identifier_map.begin(), end2 = einfo.m_id_identifier_map.end();
       for(; iter2 != end2; ++ iter2)
       {
           text.append("\n    ");
           text.append((*iter2).second.c_str());
           for(size_t x = (*iter2).second.len(); x < 16; ++ x)
           {
               text.append(' ');
           }
           text.append(" = ");
           text.append(aux.tostring((*iter2).first).c_str());
           text.append(",");
       }
       text.append("\n  };");

       return true;
    }

    bool try_handle_struct_header(const identifier_t& identifier, const info_t& info, text_t& text)
    {
        kvmap_t<identifier_t, struct_info_t>::const_iterator iter1 = info.m_struct_info_map.find(identifier);
        if(iter1 == info.m_struct_info_map.end())
        {
            return false;
        }

        aux_t aux;

        text.append("\n  class ");
        text.append((*iter1).first.c_str());
        text.append("\n  {");
        text.append("\n  public:\n    ");
        text.append((*iter1).first.c_str());
        text.append("();\n    ~");
        text.append((*iter1).first.c_str());
        text.append("();\n    void clear();");
        text.append("\n    template<typename T>");
        text.append("\n    bool write(T& t)\n    {");
        text.append("\n      if(!bit.write(t))\n      {\n        return false;\n      }");
        const struct_info_t& sinfo = (*iter1).second;
        size_t count = sinfo.m_unit_vec.count();
        for(size_t x = 0; x < count; ++ x)
        {
            const unit_info_t& uiinfo = sinfo.m_unit_vec[x];
            text.append("\n      if(bit.has(");
            text.append(aux.tostring(uiinfo.m_index).c_str());
            text.append("))\n      {\n        ");
            if(is_base_type(uiinfo.m_typeinfo))
            {
                text.append("if(!t.write(");
                text.append(uiinfo.m_identifier.c_str());
                text.append("))\n        {\n          ");
                text.append("return false;\n        }");
            }
            else
            {
                text.append("if(!");
                text.append(uiinfo.m_identifier.c_str());
                text.append(".write(t))\n        {\n          ");
                text.append("return false;\n        }");
            }
            text.append("\n      }");
        }
        text.append("\n      return true;");
        text.append("\n    }");
        text.append("\n    template<typename T>");
        text.append("\n    bool read(T& t)\n    {");
        text.append("\n      if(!bit.read(t))\n      {\n        return false;\n      }");
        for(size_t x = 0; x < count; ++ x)
        {
            const unit_info_t& uiinfo = sinfo.m_unit_vec[x];
            text.append("\n      if(bit.has(");
            text.append(aux.tostring(uiinfo.m_index).c_str());
            text.append("))\n      {\n        ");
            if(is_base_type(uiinfo.m_typeinfo))
            {
                text.append("if(!t.read(");
                text.append(uiinfo.m_identifier.c_str());
                text.append("))\n        {\n          ");
                text.append("return false;\n        }");
            }
            else
            {
                text.append("if(!");
                text.append(uiinfo.m_identifier.c_str());
                text.append(".read(t))\n        {\n          ");
                text.append("return false;\n        }");
            }
            text.append("\n      }");
        }
        text.append("\n      return true;");
        text.append("\n    }");
        text.append("\n    void print();\n");
        for(size_t x = 0; x < count; ++ x)
        {
            const unit_info_t& uiinfo = sinfo.m_unit_vec[x];
            text.append("\n    ");
            if(is_base_type(uiinfo.m_typeinfo))
            {
                text.append("void set_");
                text.append(uiinfo.m_identifier.c_str());
                text.append("(");
                text.append(uiinfo.m_typeinfo.c_str());
                text.append(" _");
                text.append(uiinfo.m_identifier.c_str());
                text.append(");");
                text.append("\n    ");
                text.append("void clear_");
                text.append(uiinfo.m_identifier.c_str());
                text.append("(");
                text.append(");");
                text.append("\n    ");
                text.append("bool has_");
                text.append(uiinfo.m_identifier.c_str());
                text.append("(");
                text.append(");\n");
            }
            else
            {
                text.append(uiinfo.m_typeinfo.c_str());
                text.append("& alloc_");
                text.append(uiinfo.m_identifier.c_str());
                text.append("(");
                text.append(");");
                text.append("\n    ");
                text.append("void clear_");
                text.append(uiinfo.m_identifier.c_str());
                text.append("(");
                text.append(");");
                text.append("\n    ");
                text.append("bool has_");
                text.append(uiinfo.m_identifier.c_str());
                text.append("(");
                text.append(");\n");
            }
        }
        text.append("\n");
        value_t value("typedef bit_t<");
        value.append(aux.tostring(sinfo.m_unit_vec[sinfo.m_unit_vec.count() - 1].m_index).c_str());
        value.append("> ");
        text.append("  private:\n    ");
        text.append(value.c_str());
        for(size_t x = value.len(); x < 32; ++ x)
        {
            text.append(' ');
        }
        text.append("bit_s;\n    bit_s");
        for(size_t y = 5; y < 32; ++ y)
        {
            text.append(' ');
        }
        text.append("bit;");
        for(size_t x = 0; x < count; ++ x)
        {
            const unit_info_t& uiinfo = sinfo.m_unit_vec[x];
            text.append("\n    ");
            text.append(uiinfo.m_typeinfo.c_str());
            for(size_t y = uiinfo.m_typeinfo.len(); y < 32; ++ y)
            {
                text.append(' ');
            }
            text.append(uiinfo.m_identifier.c_str());
            text.append(';');
        }
        text.append("\n  };");
        return true;
    }

    void generator_t::generate_header(const filename_t& filename, const info_t& info)
    {
        value_t value;

        generate_header_macro(filename, value);

        text_t text;

        text.append("#ifndef ");
        text.append(value.c_str());
        text.append("\n#define ");
        text.append(value.c_str());
        text.append("\n\n#include <bit.h>\n");
        for(size_t x = 0; x < info.m_include_vec.count(); ++ x)
        {
            text.append("#include \"");
            text.append(info.m_include_vec[x].c_str());
            text.append(".h\"\n");
        }

        aux_t aux;

        if(info.m_id_identifier_map.size() > 0)
        {
            text.append("\nnamespace message\n{");
            vmap_t<identifier_t>::const_iterator iter2 = info.m_id_identifier_map.begin(), end2 = info.m_id_identifier_map.end();
            for(; iter2 != end2; ++ iter2)
            {
                text.append("\n  extern const uint32_t ");
                text.append((*iter2).second.c_str());
                text.append(";");
            }
            text.append("\n}");
        }

        text.append("\n\nnamespace ds\n{");

        if(info.m_identifier_vec.count() > 0)
        {
            size_t cnt = info.m_identifier_vec.count();
            for(size_t x = 0; x < cnt; ++ x)
            {
                if(!try_handle_enum_header(info.m_identifier_vec[x], info, text))
                {
                    if(!try_handle_struct_header(info.m_identifier_vec[x], info, text))
                    {
                        printf("[%s:%s:%d] enum identifier(%s), cant found!\n", __FILE__, __PRETTY_FUNCTION__, __LINE__, info.m_identifier_vec[x].c_str());
                    }
                    else
                    {
                        m_last_struct_index = x;
                    }
                }
            }
        }

        text.append("\n}\n\n#endif");

        // printf("%s\n", text.c_str());

        // printf("------(%s)-----\n", filename.c_str());

        filename_t name = filename;
        name.append(".h");

        write(name, text);
    }

    bool try_handle_struct_cpp(const identifier_t& identifier, const info_t& info, text_t& text)
    {
        kvmap_t<identifier_t, struct_info_t>::const_iterator iter1 = info.m_struct_info_map.find(identifier);
        if(iter1 == info.m_struct_info_map.end())
        {
            return false;
        }

        aux_t aux;

        text.append("  ");
        text.append((*iter1).first.c_str());
        text.append("::");
        text.append((*iter1).first.c_str());
        text.append("()\n  {\n    clear();\n  }\n  ");
        text.append((*iter1).first.c_str());
        text.append("::~");
        text.append((*iter1).first.c_str());
        text.append("()\n  {\n  }");
        text.append("\n  void ");
        text.append((*iter1).first.c_str());
        text.append("::clear()\n  {\n    bit.clear();");
        const struct_info_t& sinfo = (*iter1).second;
        size_t count = sinfo.m_unit_vec.count();
        for(size_t x = 0; x < count; ++ x)
        {
            const unit_info_t& uiinfo = sinfo.m_unit_vec[x];
            text.append("\n    ");
            if(is_base_type(uiinfo.m_typeinfo))
            {
                text.append(uiinfo.m_identifier.c_str());
                text.append(" = 0;");
            }
            else
            {
                text.append(uiinfo.m_identifier.c_str());
                text.append(".clear();");
            }
        }
        text.append("\n  }");
        text.append("\n  void ");
        text.append((*iter1).first.c_str());
        text.append("::print()\n  {");
        for(size_t x = 0; x < count; ++ x)
        {
            const unit_info_t& uiinfo = sinfo.m_unit_vec[x];
            text.append("\n    if(bit.has(");
            text.append(aux.tostring(uiinfo.m_index).c_str());
            text.append("))\n    {\n      ");
            if(is_base_type(uiinfo.m_typeinfo))
            {
                text.append("printf(\"");
                text.append(uiinfo.m_identifier.c_str());
                text.append(" = %u\\n\");");
            }
            else if(is_base64_type(uiinfo.m_typeinfo))
            {
                text.append("printf(\"");
                text.append(uiinfo.m_identifier.c_str());
                text.append(" = %llu\\n\");");
            }
            else
            {
                text.append(uiinfo.m_identifier.c_str());
                text.append(".print();");
            }
            text.append("\n    }");
        }
        text.append("\n  }");
        for(size_t x = 0; x < count; ++ x)
        {
            const unit_info_t& uiinfo = sinfo.m_unit_vec[x];
            text.append("\n  ");
            if(is_base_type(uiinfo.m_typeinfo))
            {
                text.append("void ");
                text.append((*iter1).first.c_str());
                text.append("::set_");
                text.append(uiinfo.m_identifier.c_str());
                text.append("(");
                text.append(uiinfo.m_typeinfo.c_str());
                text.append(" _");
                text.append(uiinfo.m_identifier.c_str());
                text.append(")\n  {\n    ");
                text.append(uiinfo.m_identifier.c_str());
                text.append(" = _");
                text.append(uiinfo.m_identifier.c_str());
                text.append(";\n    bit.set(");
                text.append(aux.tostring(uiinfo.m_index).c_str());
                text.append(");\n  }\n  ");
                text.append("void ");
                text.append((*iter1).first.c_str());
                text.append("::clear_");
                text.append(uiinfo.m_identifier.c_str());
                text.append("(");
                text.append(")\n  {\n    ");
                text.append(uiinfo.m_identifier.c_str());
                text.append(" = 0;");
                text.append("\n    bit.clr(");
                text.append(aux.tostring(uiinfo.m_index).c_str());
                text.append(");\n  }\n  ");
                text.append("bool ");
                text.append((*iter1).first.c_str());
                text.append("::has_");
                text.append(uiinfo.m_identifier.c_str());
                text.append("(");
                text.append(")");
                text.append("\n  {");
                text.append("\n    return bit.has(");
                text.append(aux.tostring(uiinfo.m_index).c_str());
                text.append(");\n  }");
            }
            else
            {
                text.append(uiinfo.m_typeinfo.c_str());
                text.append("& ");
                text.append((*iter1).first.c_str());
                text.append("::alloc_");
                text.append(uiinfo.m_identifier.c_str());
                text.append("(");
                text.append(")\n  {\n    bit.set(");
                text.append((aux.tostring(uiinfo.m_index)).c_str());
                text.append(");\n    return ");
                text.append(uiinfo.m_identifier.c_str());
                text.append(";\n  }\n  ");
                text.append("void ");
                text.append((*iter1).first.c_str());
                text.append("::clear_");
                text.append(uiinfo.m_identifier.c_str());
                text.append("(");
                text.append(")\n  {\n    bit.clr(");
                text.append((aux.tostring(uiinfo.m_index)).c_str());
                text.append(");\n    ");
                text.append(uiinfo.m_identifier.c_str());
                text.append(".clear();\n  }\n  ");
                text.append("bool ");
                text.append((*iter1).first.c_str());
                text.append("::has_");
                text.append(uiinfo.m_identifier.c_str());
                text.append("()");
                text.append("\n  {");
                text.append("\n    return bit.has(");
                text.append(aux.tostring(uiinfo.m_index).c_str());
                text.append(");\n  }");
            }
        }
        return true;
    }

    void generator_t::generate_cpp(const filename_t& filename, const info_t& info)
    {
        text_t text;

        aux_t aux;

        text.append("#include \"");

        filename_t filename_out;

        parse_header_name(filename, filename_out);

        printf("****************[%s:%s:%d](%s:%s)******************\n", __FILE__, __PRETTY_FUNCTION__, __LINE__, filename.c_str(), filename_out.c_str());

        text.append(filename_out.c_str());

        text.append(".h\"");
        text.append("\n");

        if(info.m_id_identifier_map.size() > 0)
        {
            text.append("\nnamespace message\n{");
            vmap_t<identifier_t>::const_iterator iter2 = info.m_id_identifier_map.begin(), end2 = info.m_id_identifier_map.end();
            for(; iter2 != end2; ++ iter2)
            {
                text.append("\n  const uint32_t ");
                text.append((*iter2).second.c_str());
                for(size_t x = (*iter2).second.len(); x < 32; ++ x)
                {
                    text.append(' ');
                }
                text.append(" = ");
                text.append(aux.tostring((*iter2).first).c_str());
                text.append(";");
            }
            text.append("\n}\n");
        }

        text.append("\nnamespace ds\n{\n");

        if(info.m_struct_info_map.size() > 0)
        {
            size_t cnt = info.m_identifier_vec.count();
            for(size_t x = 0; x < cnt; ++ x)
            {
                if(try_handle_struct_cpp(info.m_identifier_vec[x], info, text) &&
                  (x != m_last_struct_index))
                {
                    text.append("\n");
                }
            }
        }

        text.append("\n}");

        //printf("%s\n", text.c_str());

        filename_t name = filename;
        name.append(".cpp");

        write(name, text);
    }

    void generator_t::handle(const filename_t& filename, const directory_t& directory_in, const directory_t& directory_out)
    {
        clear();

        printf("[%s][%s][%s]\n", filename.c_str(), directory_in.c_str(), directory_out.c_str());

        filename_t filename_out = directory_out;
        filename_out.append(filename.substr(directory_in.len()));

        if(filename_out.len() < 3)
        {
            printf("[%s:%s:%d] filename(%s) err!\n", __FILE__, __PRETTY_FUNCTION__, __LINE__, filename_out.c_str());
            return;
        }

        filename_t suf = filename_out.substr(filename_out.len() - 3);

        if(!suf.equal(".ds"))
        {
            printf("[%s:%s:%d] filename(%s) err!\n", __FILE__, __PRETTY_FUNCTION__, __LINE__, filename_out.c_str());
            return;
        }

        kvmap_t<filename_t, info_t>::iterator iter1 = g_info_mgr.m_filename_info_map.find(filename);
        if(iter1 == g_info_mgr.m_filename_info_map.end())
        {
            printf("[%s:%s:%d] filename(%s) inexist!\n", __FILE__, __PRETTY_FUNCTION__, __LINE__, filename.c_str());
            return;
        }

        filename_out[filename_out.len() - 3] = 0;

        filename_t name = filename_out.c_str();

        printf("++++++++++++[%s]++++++++++++\n", filename_out.c_str());

        generate_header(name, (*iter1).second);
        generate_cpp(name, (*iter1).second);
    }

    void generator_t::parse_header_name(const filename_t& filename, filename_t& filename_out)
    {
        int32_t index = filename.len() - 1;
        while(index >= 0)
        {
            if('/' == filename[index])
            {
                break;
            }
            -- index;
        }
        ++ index;

        while(index < filename.len())
        {
            filename_out.append(filename[index]);
            ++ index;
        }
    }
}
