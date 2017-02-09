#include "parser.h"
#include "keyword.h"
#include <string.h>
#include "info.h"
#include <utils.h>

namespace ds
{
    parser_t::parser_t()
    {

    }

    parser_t::~parser_t()
    {

    }

    void parser_t::clear()
    {
        m_filename.clear();
        m_info.clear();
    }

    bool handle_single_line_comment(const char* p, content_t& content)
    {
        p = strstr(p + 2, KW_NEWLINE);
        if(!p)
        {
            return false;
        }
        content.roffset(p + 1 - content.raddr());
        //printf("----[%s] content(%s)----\n", __PRETTY_FUNCTION__, content.raddr());
        return true;
    }

    bool handle_multi_line_comment(const char* p, content_t& content)
    {
        p = strstr(p + 2, KW_COMMENT_22);
        if(!p)
        {
            return false;
        }
        content.roffset(p + 2 - content.raddr());
        //printf("----[%s] content(%s)----\n", __PRETTY_FUNCTION__, content.raddr());
        return true;
    }

    bool get_message_body_data(const char* p, content_t& content, const char*& pb, const char*& pe)
    {
        if(p >= content.waddr())
        {
            printf("----[%s][%d] pointer invalid!----\n", __PRETTY_FUNCTION__, __LINE__);
            return false;
        }
        if(*p != '\n')
        {
            printf("----[%s][%d] c = \'%c\'----\n", __PRETTY_FUNCTION__, __LINE__, *p);
            return false;
        }
        ++ p;
        if(p >= content.waddr())
        {
            printf("----[%s][%d] pointer invalid!----\n", __PRETTY_FUNCTION__, __LINE__);
            return false;
        }
        if(*p != '\{')
        {
            printf("----[%s][%d] c = \'%c\'----\n", __PRETTY_FUNCTION__, __LINE__, *p);
            return false;
        }
        ++ p;
        if(p >= content.waddr())
        {
            printf("----[%s][%d] pointer invalid!----\n", __PRETTY_FUNCTION__, __LINE__);
            return false;
        }
        if(*p != '\n')
        {
            printf("----[%s][%d] c = \'%c\'----\n", __PRETTY_FUNCTION__, __LINE__, *p);
            return false;
        }
        ++ p;
        if(p >= content.waddr())
        {
            printf("----[%s][%d] pointer invalid!----\n", __PRETTY_FUNCTION__, __LINE__);
            return false;
        }
        pb = p;
        while(1)
        {
            if(p >= content.waddr())
            {
                printf("----[%s][%d] pointer invalid!----\n", __PRETTY_FUNCTION__, __LINE__);
                return false;
            }
            if(*p == '}')
            {
                break;
            }
            ++ p;
        }
        const char* pp = p - 1;
        if('\n' != *pp)
        {
            printf("----[%s][%d] expect \'\\n\'!----\n", __PRETTY_FUNCTION__, __LINE__);
            return false;
        }
        pe = pp;
        content.roffset(pe + 2 - content.raddr());
        //printf("----[%s] content(%s)----\n", __PRETTY_FUNCTION__, content.raddr());
        return true;
    }

    bool get_body_data(const char* p, content_t& content, const char*& pb, const char*& pe)
    {
        if(p >= content.waddr())
        {
            printf("----[%s][%d] pointer invalid!----\n", __PRETTY_FUNCTION__, __LINE__);
            return false;
        }
        if(*p != '\n')
        {
            printf("----[%s][%d] c = \'%c\'----\n", __PRETTY_FUNCTION__, __LINE__, *p);
            return false;
        }
        ++ p;
        if(p >= content.waddr())
        {
            printf("----[%s][%d] pointer invalid!----\n", __PRETTY_FUNCTION__, __LINE__);
            return false;
        }
        if(*p != '\{')
        {
            printf("----[%s][%d] c = \'%c\'----\n", __PRETTY_FUNCTION__, __LINE__, *p);
            return false;
        }
        ++ p;
        if(p >= content.waddr())
        {
            printf("----[%s][%d] pointer invalid!----\n", __PRETTY_FUNCTION__, __LINE__);
            return false;
        }
        if(*p != '\n')
        {
            printf("----[%s][%d] c = \'%c\'----\n", __PRETTY_FUNCTION__, __LINE__, *p);
            return false;
        }
        ++ p;
        if(p >= content.waddr())
        {
            printf("----[%s][%d] pointer invalid!----\n", __PRETTY_FUNCTION__, __LINE__);
            return false;
        }
        pb = p;
        while(1)
        {
            if(p >= content.waddr())
            {
                printf("----[%s][%d] pointer invalid!----\n", __PRETTY_FUNCTION__, __LINE__);
                return false;
            }
            if(*p == '}')
            {
                break;
            }
            ++ p;
        }
        const char* pp = p - 1;
        if('\n' != *pp)
        {
            printf("----[%s][%d] expect \'\\n\'!----\n", __PRETTY_FUNCTION__, __LINE__);
            return false;
        }
        pe = pp;
        content.roffset(pe + 2 - content.raddr());
        //printf("----[%s] content(%s)----\n", __PRETTY_FUNCTION__, content.raddr());
        return true;
    }

    bool is_num(char c)
    {
        return ((c >= '0') && (c <= '9'));
    }

    bool is_underline(char c)
    {
        return (c == '_');
    }

    bool is_space(char c)
    {
        return (c == ' ');
    }

    bool is_less(char c)
    {
        return (c == '<');
    }

    bool is_great(char c)
    {
        return (c == '>');
    }

    bool is_equal(char c)
    {
        return (c == '=');
    }

    bool is_semicolon(char c)
    {
        return (c == ';');
    }

    bool is_comma(char c)
    {
        return (c == ',');
    }

    bool walk_to_label(const char*& pb, const char* pe)
    {
        if(is_alpha(*pb) || is_underline(*pb))
        {
            return true;
        }

        while(pb < pe)
        {
            if(!((is_num(*pb)) ||
                (is_alpha(*pb)) ||
                (is_underline(*pb)) ||
                (is_space(*pb))))
            {
                printf("[%s][%d] c = \'%c\'\n", __PRETTY_FUNCTION__, __LINE__, *pb);
                return false;
            }
            if(!is_space(*pb))
            {
                break;
            }
            ++ pb;
        }
        if(pb >= pe)
        {
            printf("[%s][%d] c = \'%c\'\n", __PRETTY_FUNCTION__, __LINE__, *pb);
            return false;
        }
        if(!(is_alpha(*pb) || (is_underline(*pb))))
        {
            printf("[%s][%d] c = \'%c\'\n", __PRETTY_FUNCTION__, __LINE__, *pb);
            return false;
        }
        return true;
    }

    bool walk_label(const char*& pb, const char* pe)
    {
        if(!(is_alpha(*pb) || is_underline(*pb)))
        {
            printf("[%s][%d] c = \'%c\' invalid!\n", __PRETTY_FUNCTION__, __LINE__, *pb);
            return false;
        }

        while(pb < pe)
        {
            if(!((is_num(*pb)) ||
                (is_alpha(*pb)) ||
                (is_underline(*pb)) ||
                (is_less(*pb)) ||
                (is_great(*pb)) ||
                (is_comma(*pb)) ||
                (is_space(*pb))))
            {
                printf("[%s][%d] c = \'%c\'\n", __PRETTY_FUNCTION__, __LINE__, *pb);
                return false;
            }
            if(is_space(*pb))
            {
                break;
            }
            ++ pb;
        }
        if(pb > pe)
        {
            printf("[%s][%d] c = \'%c\'\n", __PRETTY_FUNCTION__, __LINE__, *pb);
            return false;
        }
        return true;
    }

    bool walk_to_equal(const char*& pb, const char* pe)
    {
        while(pb < pe)
        {
            if(!((is_space(*pb)) ||
                (is_equal(*pb))))
            {
                printf("[%s][%d] c = \'%c\'\n", __PRETTY_FUNCTION__, __LINE__, *pb);
                return false;
            }
            if(is_equal(*pb))
            {
                break;
            }
            ++ pb;
        }
        if(pb >= pe)
        {
            printf("[%s][%d] c = \'%c\'\n", __PRETTY_FUNCTION__, __LINE__, *pb);
            return false;
        }
        return true;
    }

    bool walk_to_num(const char*& pb, const char* pe)
    {
        while(pb < pe)
        {
            if(!((is_space(*pb)) ||
                (is_num(*pb))))
            {
                printf("[%s][%d] c = \'%c\'\n", __PRETTY_FUNCTION__, __LINE__, *pb);
                return false;
            }
            if(is_num(*pb))
            {
                break;
            }
            ++ pb;
        }
        if(pb >= pe)
        {
            printf("[%s][%d] c = \'%c\'\n", __PRETTY_FUNCTION__, __LINE__, *pb);
            return false;
        }
        return true;
    }

    bool walk_num(const char*& pb, const char* pe)
    {
        while(pb < pe)
        {
            if(!((is_num(*pb)) || (is_semicolon(*pb))))
            {
                printf("[%s][%d] c = \'%c\'\n", __PRETTY_FUNCTION__, __LINE__, *pb);
                return false;
            }
            if(is_semicolon(*pb))
            {
                break;
            }
            ++ pb;
        }
        if(pb > pe)
        {
            printf("[%s][%d] c = \'%c\'\n", __PRETTY_FUNCTION__, __LINE__, *pb);
            return false;
        }
        return true;
    }

    bool walk_num_1(const char*& pb, const char* pe)
    {
        while(pb < pe)
        {
            if(!((is_num(*pb)) || (is_space(*pb))))
            {
                printf("[%s][%d] c = \'%c\'\n", __PRETTY_FUNCTION__, __LINE__, *pb);
                return false;
            }
            if(is_space(*pb))
            {
                break;
            }
            ++ pb;
        }
        if(pb > pe)
        {
            printf("[%s][%d] c = \'%c\'\n", __PRETTY_FUNCTION__, __LINE__, *pb);
            return false;
        }
        return true;
    }

    bool walk_to_semicolon(const char*& pb, const char* pe)
    {
        while(1)
        {
            if(pb > pe)
            {
                return false;
            }

            if(*pb == ';')
            {
                break;
            }

            ++ pb;
        }

        return true;
    }

    bool walk_to_newline(const char*& pb, const char* pe)
    {
        while(1)
        {
            if(pb > pe)
            {
                return false;
            }

            if(*pb == '\n')
            {
                break;
            }

            ++ pb;
        }

        return true;
    }

    const char* find_newline(const char* p, const char* e)
    {
        while(p < e)
        {
            if(*p == '\n')
            {
                return p;
            }
            ++ p;
        }

        return NULL;
    }

    bool parse_name(const char*& p, content_t& content, identifier_t& identifier)
    {
        if(!walk_to_label(p, content.waddr()))
        {
            printf("[%s][%d] walk to label failed!\n", __PRETTY_FUNCTION__, __LINE__);
            return false;
        }
        if(!((is_alpha(*p) || is_underline(*p))))
        {
            printf("[%s][%d] label start \'%c\', invalid!\n", __PRETTY_FUNCTION__, __LINE__, *p);
            return false;
        }
        //printf("p = %s\n", p);
        const char* q = p;
        const char* pe = p;
        if(!walk_to_newline(pe, content.waddr()))
        {
            printf("[%s][%d] walk label failed!\n", __PRETTY_FUNCTION__, __LINE__);
            return false;
        }
        while(p < pe)
        {
            if(!(is_num(*p) || is_alpha(*p) || is_underline(*p)))
            {
                printf("[%s][%d] label start \'%c\', invalid!\n", __PRETTY_FUNCTION__, __LINE__, *p);
                return false;
            }
            identifier.append(*p);
            ++ p;
        }
        char* s = (char*)q;
        *s = 0;
        //printf("q = %s\n", q);
        //printf("identifier = %s\n", identifier.c_str());
        return true;
    }

    bool parser_t::handle_message(const char* p, content_t& content)
    {
        const char* pb = 0;
        const char* pe = 0;
        if(!get_message_body_data(p + 7, content, pb, pe))
        {
            return false;
        }
        while(pb < pe)
        {
            const char* sc = pb;
            if(!walk_to_semicolon(sc, pe))
            {
                printf("[%s][%d] cant find \';\'\n", __PRETTY_FUNCTION__, __LINE__);
                return false;
            }

            const char* nc = pb;
            if(!walk_to_newline(nc, pe))
            {
                printf("[%s][%d] cant find \'\\n\'\n", __PRETTY_FUNCTION__, __LINE__);
                return false;
            }

            if(sc >= nc)
            {
                printf("[%s][%d] \';\' appear after \'\n\'\n", __PRETTY_FUNCTION__, __LINE__);
                return false;
            }

            if(!walk_to_label(pb, sc))
            {
                printf("[%s][%d] exception!\n", __PRETTY_FUNCTION__, __LINE__);
                return false;
            }

            const char* q = pb;

            if(!walk_label(pb, sc))
            {
                printf("[%s][%d] exception!\n", __PRETTY_FUNCTION__, __LINE__);
                return false;
            }

            char* ep = (char*)pb;
            *ep = 0;
            //printf("[%s][%d][%s]\n", __PRETTY_FUNCTION__, __LINE__, q);
            ++ pb;

            identifier_t identifier = q;

            if(!walk_to_equal(pb, sc))
            {
                printf("[%s][%d] exception!\n", __PRETTY_FUNCTION__, __LINE__);
                return false;
            }

            ++ pb;

            if(!walk_to_num(pb, sc))
            {
                printf("[%s][%d] exception!\n", __PRETTY_FUNCTION__, __LINE__);
                return false;
            }

            q = pb;
            if(!walk_num(pb, sc))
            {
                printf("[%s][%d] exception!\n", __PRETTY_FUNCTION__, __LINE__);
                return false;
            }

            ep = (char*)pb;
            *ep = 0;

            number_t number = q;

            //printf("[%s][%d][%s]\n", __PRETTY_FUNCTION__, __LINE__, q);

            //printf("[%s][%d][%p-%p]\n", __PRETTY_FUNCTION__, __LINE__, pb, pe);

            if(!m_info.add_message_info(identifier, number))
            {
                return false;
            }

            pb = ++ nc;
        }
        content.roffset(pe + 2 - content.raddr());

        return true;
    }

    bool parser_t::handle_struct(const char* p, content_t& content)
    {
        const char* pb = 0;
        const char* pe = 0;
        p += 6;
        struct_info_t struct_info;
        if(!parse_name(p, content, struct_info.m_identifier))
        {
            return false;
        }
        //printf("identifier = %s, p = %s\n", struct_info.m_identifier.c_str(), p);
        if(!get_body_data(p, content, pb, pe))
        {
            return false;
        }
        while(pb < pe)
        {
            unit_info_t unit_info;

            const char* sc = pb;
            if(!walk_to_semicolon(sc, pe))
            {
                printf("[%s][%d] cant find \';\'\n", __PRETTY_FUNCTION__, __LINE__);
                return false;
            }

            const char* nc = pb;
            if(!walk_to_newline(nc, pe))
            if(!nc)
            {
                printf("[%s][%d] cant find \'\\n\'\n", __PRETTY_FUNCTION__, __LINE__);
                return false;
            }

            if(sc >= nc)
            {
                printf("[%s][%d] \';\' appear after \'\n\'\n", __PRETTY_FUNCTION__, __LINE__);
                return false;
            }

            if(!walk_to_num(pb, sc))
            {
                printf("[%s][%d] exception!\n", __PRETTY_FUNCTION__, __LINE__);
                return false;
            }

            const char* q = pb;
            //printf("pb = %s\n", pb);

            if(!walk_num_1(pb, sc))
            {
                printf("[%s][%d] exception!\n", __PRETTY_FUNCTION__, __LINE__);
                return false;
            }

            char* ep = (char*)pb;
            *ep = 0;

            number_t num = q;

            ssize_t member_index = num.to_uint32();

            for(size_t x = 0; x < struct_info.m_unit_vec.count(); ++ x)
            {
                if(struct_info.m_unit_vec[x].m_index >= member_index)
                {
                    printf("[%s][%d] new index(%zu) <= identifier(%s), index(%zu)!\n", __PRETTY_FUNCTION__, __LINE__, member_index, struct_info.m_unit_vec[x].m_identifier.c_str(), struct_info.m_unit_vec[x].m_index);
                    return false;
                }
            }

            unit_info.m_index = member_index;

            //printf("num = %s, pb = %s\n", q, pb);

            ++ pb;

            if(!walk_to_label(pb, sc))
            {
                printf("[%s][%d] exception!\n", __PRETTY_FUNCTION__, __LINE__);
                return false;
            }

            q = pb;

            if(!walk_label(pb, sc))
            {
                printf("[%s][%d] exception!\n", __PRETTY_FUNCTION__, __LINE__);
                return false;
            }

            ep = (char*)pb;
            *ep = 0;
            //printf("[%s][%d][%s]\n", __PRETTY_FUNCTION__, __LINE__, q);
            ++ pb;

            unit_info.m_typeinfo = q;

            if(!walk_to_label(pb, sc))
            {
                printf("[%s][%d] exception!\n", __PRETTY_FUNCTION__, __LINE__);
                return false;
            }

            //printf("[%s][%d][%s]\n", __PRETTY_FUNCTION__, __LINE__, pb);

            q = pb;

            if(!walk_label(pb, sc))
            {
                printf("[%s][%d] exception!\n", __PRETTY_FUNCTION__, __LINE__);
                return false;
            }

            ep = (char*)pb;
            *ep = 0;

            unit_info.m_identifier = q;

            unit_info_t& uiinfo = struct_info.m_unit_vec.alloc();
            uiinfo = unit_info;

            //printf("[%s][%d][%s]\n", __PRETTY_FUNCTION__, __LINE__, q);

            //printf("[%s][%d][%p-%p]\n", __PRETTY_FUNCTION__, __LINE__, pb, pe);

            pb = ++ nc;
        }

        content.roffset(pe + 2 - content.raddr());

        m_info.add_struct_info(struct_info);

        return true;
    }

    bool parser_t::handle_enum(const char* p, content_t& content)
    {
        const char* pb = 0;
        const char* pe = 0;
        p += 4;
        enum_info_t enum_info;
        if(!parse_name(p, content, enum_info.m_identifier))
        {
            return false;
        }
        //printf("identifier = %s, p = %s\n", enum_info.m_identifier.c_str(), p);
        if(!get_body_data(p, content, pb, pe))
        {
            return false;
        }
        while(pb < pe)
        {
            const char* sc = pb;
            if(!walk_to_semicolon(sc, pe))
            {
                printf("[%s][%d] cant find \';\'\n", __PRETTY_FUNCTION__, __LINE__);
                return false;
            }

            const char* nc = pb;
            if(!walk_to_newline(nc, pe))
            {
                printf("[%s][%d] cant find \'\\n\'\n", __PRETTY_FUNCTION__, __LINE__);
                return false;
            }

            if(sc >= nc)
            {
                printf("[%s][%d] \';\' appear after \'\n\'\n", __PRETTY_FUNCTION__, __LINE__);
                return false;
            }

            if(!walk_to_label(pb, sc))
            {
                printf("[%s][%d] exception!\n", __PRETTY_FUNCTION__, __LINE__);
                return false;
            }

            const char* q = pb;

            if(!walk_label(pb, sc))
            {
                printf("[%s][%d] exception!\n", __PRETTY_FUNCTION__, __LINE__);
                return false;
            }

            char* ep = (char*)pb;
            *ep = 0;
            //printf("[%s][%d][%s]\n", __PRETTY_FUNCTION__, __LINE__, q);
            ++ pb;

            identifier_t identifier = q;

            if(!walk_to_equal(pb, sc))
            {
                printf("[%s][%d] exception!\n", __PRETTY_FUNCTION__, __LINE__);
                return false;
            }

            ++ pb;

            if(!walk_to_num(pb, sc))
            {
                printf("[%s][%d] exception!\n", __PRETTY_FUNCTION__, __LINE__);
                return false;
            }

            q = pb;
            if(!walk_num(pb, sc))
            {
                printf("[%s][%d] exception!\n", __PRETTY_FUNCTION__, __LINE__);
                return false;
            }

            ep = (char*)pb;
            *ep = 0;

            number_t number = q;

            enum_info.add(identifier, number);

            //printf("[%s][%d][%s]\n", __PRETTY_FUNCTION__, __LINE__, q);

            //printf("[%s][%d][%p-%p]\n", __PRETTY_FUNCTION__, __LINE__, pb, pe);

            pb = ++ nc;
        }

        content.roffset(pe + 2 - content.raddr());

        if(!m_info.add_enum_info(enum_info))
        {
            return false;
        }

        return true;
    }

    bool parser_t::handle_include(const char* p, content_t& content)
    {
        const char* pb = 0;
        const char* pe = find_newline(p, content.waddr());

        if(!pe)
        {
            printf("[%s][%d] err!\n", __PRETTY_FUNCTION__, __LINE__);
            return false;
        }

        if(!walk_label(p, pe))
        {
            printf("[%s][%d] err!\n", __PRETTY_FUNCTION__, __LINE__);
            return false;
        }

        ++ p;
        pb = p;

        //printf("+++(%s)---\n", p);

        if(!walk_label(p, pe))
        {
            printf("[%s][%d] err!\n", __PRETTY_FUNCTION__, __LINE__);
            return false;
        }

        char* ac = (char*)p;
        *ac = 0;

        //printf("[%s][%d][%s]\n", __PRETTY_FUNCTION__, __LINE__, pb);

        identifier_t& identifier = m_info.m_include_vec.alloc();
        identifier = pb;

        content.roffset(pe + 1 - content.raddr());

        //printf("[%s][%d][%s]\n", __PRETTY_FUNCTION__, __LINE__, content.raddr());

        return true;
    }

    const char* compare(const char* p1, const char* p2)
    {
        if(p1 == 0)
        {
            return p2;
        }
        else if(p2 == 0)
        {
            return p1;
        }

        if(p1 < p2)
        {
            return p1;
        }

        return p2;
    }

    const char* compare(const char* p1, const char* p2, const char* p3, const char* p4, const char* p5, const char* p6)
    {
        const char* p = compare(p1, p2);

        p = compare(p, p3);
        p = compare(p, p4);
        p = compare(p, p5);
        p = compare(p, p6);

        return p;
    }

    void parser_t::handle(content_t& content)
    {
        while(content.rsize() > 0)
        {
            const char* p1 = strstr(content.raddr(), KW_COMMENT_1);
            const char* p2 = strstr(content.raddr(), KW_COMMENT_2);
            const char* p3 = strstr(content.raddr(), KW_MESSAGE);
            const char* p4 = strstr(content.raddr(), KW_STRUCT);
            const char* p5 = strstr(content.raddr(), KW_ENUM);
            const char* p6 = strstr(content.raddr(), KW_INCLUDE);

            const char* p = compare(p1, p2, p3, p4, p5, p6);

            //printf("[%s][%d][%s]\n", __PRETTY_FUNCTION__, __LINE__, p);

            if(!p)
            {
                break;
            }

            if(p == p1)
            {
                if(!handle_single_line_comment(p, content))
                {
                    break;
                }
            }
            else if(p == p2)
            {
                if(!handle_multi_line_comment(p, content))
                {
                    break;
                }
            }
            else if(p == p3)
            {
                if(!handle_message(p, content))
                {
                    break;
                }
            }
            else if(p == p4)
            {
                if(!handle_struct(p, content))
                {
                    break;
                }
            }
            else if(p == p5)
            {
                if(!handle_enum(p, content))
                {
                    break;
                }
            }
            else if(p == p6)
            {
                if(!handle_include(p, content))
                {
                    break;
                }
            }
        }

        if(!m_info.empty())
        {
            g_info_mgr.add(m_filename, m_info);
        }
    }

    void parser_t::set_filename(const filename_t& filename)
    {
        m_filename = filename;
    }
}
