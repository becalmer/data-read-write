#include "file.h"
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

namespace ds
{
    file_t::file_t()
    {
        m_file = NULL;
    }
    
    file_t::~file_t()
    {
        close();
    }

    bool file_t::create(const filename_t& filename)
    {
        filename_t name;
        size_t index = 1;
        while(index < filename.len())
        {
            if('/' == filename[index])
            {
                name = filename;
                name[index] = 0;
                if(!is_exist(name))
                {
                    if(0 != mkdir(name.c_str(), 0775))
                    {
                        printf("[%s:%s:%d] mkdir name(%s) failed!\n", __FILE__, __PRETTY_FUNCTION__, __LINE__, name.c_str());
                        return false;
                    }
                }
            }
            ++ index;
        }

        return open(filename, "wb");
    }
    
    bool file_t::open(const filename_t& filename, const char* mode)
    {
        return ((m_file = fopen(filename.c_str(), mode)) != NULL);
    }

    void file_t::close()
    {
        if(m_file != NULL)
        {
            fclose(m_file);
            m_file = NULL;
        }
    }
    
    bool file_t::is_opened() const
    {
        return (m_file != NULL);
    }

    bool file_t::is_exist(const filename_t& filename)
    {
        if(0 == access(filename.c_str(), F_OK))
        {
            return true;
        }
        return false;
    }
    
    void file_t::read(content_t& content)
    {
        fseek(m_file, 0, SEEK_END);
        size_t size = ftell(m_file);
        fseek(m_file, 0, SEEK_SET);

        if(size == 0)
        {
            return;
        }

        if(size >= content.wsize())
        {
            return;
        }

        if(size != fread(content.raddr(), 1, size, m_file))
        {
            printf("[%s:%s:%d] fread size(%zu) failed\n", __FILE__, __PRETTY_FUNCTION__, __LINE__, size);
            return;
        }

        content.woffset(size);

        char* p = (char*)content.waddr();
        *p = 0;
    }

    void file_t::write(const text_t& text)
    {
        if(text.len() != fwrite(text.c_str(), 1, text.len(), m_file))
        {
            printf("[%s:%s:%d] fwrite failed, content(%s), len(%zu)\n", __FILE__, __PRETTY_FUNCTION__, __LINE__, text.c_str(), text.len());
        }
    }
}
