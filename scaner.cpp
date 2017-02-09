#include "scaner.h"
#include <sys/types.h>
#include <dirent.h>

namespace ds
{
    scaner_t::scaner_t(const directory_t& directory)
    {
        open(directory);
    }

    scaner_t::~scaner_t()
    {

    }

    void scaner_t::clear()
    {
        m_filename_list.clear();
    }

    bool scaner_t::open(const directory_t& directory)
    {
        DIR* pDIR = opendir(directory.c_str());
        if(!pDIR)
        {
            return false;
        }

        directory_list_t list;

        struct dirent* pDirect = 0;

        while(0 != (pDirect = readdir(pDIR)))
        {
            if(DT_REG == pDirect->d_type)
            {
                filename_t& filename = m_filename_list.alloc();

                filename.append(directory);
                filename.append("/");
                filename.append(pDirect->d_name);
            }
            else if(DT_DIR == pDirect->d_type)
            {
                if((strcmp(pDirect->d_name, ".") == 0) ||
                   (strcmp(pDirect->d_name, "..") == 0))
                {
                    continue;
                }

                directory_t dir(directory);

                dir.append("/");

                dir.append(pDirect->d_name);

                filename_t& filename = list.alloc();
                filename = dir.c_str();
            }
        }

        closedir(pDIR);

        size_t c = list.count();

        for(size_t x = 0; x < c; ++ x)
        {
            open(list[x]);
        }

        return true;
    }

    bool scaner_t::is_opened()
    {
        return (m_filename_list.count() > 0);
    }

    size_t scaner_t::count()
    {
        return m_filename_list.count();
    }

    filename_t& scaner_t::operator [] (size_t idx)
    {
        return m_filename_list[idx];
    }

    void scaner_t::print()
    {
        printf("[(%s:%s:%d) ++++]\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
        m_filename_list.print();
        printf("[(%s:%s:%d) ----]\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
    }
}
