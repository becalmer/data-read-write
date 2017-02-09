#include <unistd.h>

#include "path.h"
#include <type_2.h>

namespace ds
{
    path_t::path_t()
    {
    }

    void path_t::parse(const directory_t& s)
    {
        if(!is_valid(s))
        {
            return;
        }

        filename_queue_t queue;

        split_to_queue(s, queue);

        //queue.print();

        directory_t directory;

        getcwd(directory.c_str(), 240);

        if(!is_valid(directory))
        {
            return;
        }

        //directory.print();

        filename_stack_t stack;

        split_to_stack(directory, stack);

        //stack.print();

        while(1)
        {
            const directory_t& dir = queue.front();

            //printf("[---(%s)---]\n", dir.c_str());

            if(dir.equal("../"))
            {
                stack.pop();
                queue.pop_front();
            }
            else
            {
                break;
            }
        }

        filename_stack_t stack_1;

        while(!stack.empty())
        {
            filename_t& filename = stack_1.alloc();
            filename = stack.top();
            stack.pop();
        }

        while(!stack_1.empty())
        {
            m_directory.append(stack_1.top());
            stack_1.pop();
        }

        while((!queue.empty()))
        {
            m_directory.append(queue.front());
            queue.pop_front();
        }

        m_directory.print();
    }

    path_t::~path_t()
    {

    }

    directory_t& path_t::absolute_directory(const directory_t& directory)
    {
        m_directory.clear();

        parse(directory);

        return m_directory;
    }

    bool path_t::is_valid(const directory_t& directory)
    {
        size_t  len = directory.len();

        for(size_t x = 0; x < len; ++ x)
        {
            if(!(((directory[x] >= '0') && (directory[x] <= '9')) ||
                ((directory[x] >= 'a') && (directory[x] <= 'z'))  ||
                ((directory[x] >= 'A') && (directory[x] <= 'Z'))  ||
                (directory[x] == '/') ||
                (directory[x] == '_') ||
                (directory[x] == '.')))
            {
                printf("[(%s:%s:%d) \'%c\' = 0X%X]\n", __FILE__, __PRETTY_FUNCTION__, __LINE__, directory[x], directory[x]);
                return false;
            }
        }

        const char *p = 0;

        if(strstr(directory.c_str(), "//"))
        {
            printf("[(%s:%s:%d) %s]\n", __FILE__, __PRETTY_FUNCTION__, __LINE__, directory.c_str());
            return false;
        }

        if(p = strstr(directory.c_str(), "./"))
        {
            size_t x = p - directory.c_str();
            if(x <= 0)
            {
                printf("[(%s:%s:%d) \'%c\' = 0X%X]\n", __FILE__, __PRETTY_FUNCTION__, __LINE__, directory[x], directory[x]);
                return false;
            }

            if('.' != p[x - 1])
            {
                printf("[(%s:%s:%d) \'%c\' = 0X%X]\n", __FILE__, __PRETTY_FUNCTION__, __LINE__, directory[x], directory[x]);
                return false;
            }
        }

        if(p = strstr(directory.c_str(), "/."))
        {
            size_t x = p - directory.c_str();
            if((x + 2) >= len)
            {
                printf("[(%s:%s:%d) \'%c\' = 0X%X]\n", __FILE__, __PRETTY_FUNCTION__, __LINE__, directory[x], directory[x]);
                return false;
            }

            if('.' != p[2])
            {
                printf("[(%s:%s:%d) \'%c\' = 0X%X]\n", __FILE__, __PRETTY_FUNCTION__, __LINE__, directory[x], directory[x]);
                return false;
            }
        }

        printf("[(%s:%s:%d)]\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
        return true;
    }

    void path_t::split_to_stack(const directory_t& s, filename_stack_t& stack)
    {
        directory_t directory;
        size_t x = 0;
        while(s[x])
        {
            directory.append(s[x]);
            if('/' == s[x])
            {
                if((x + 1) == s.len())
                {
                    break;
                }

                directory_t& dir = stack.alloc();
                dir = directory;

                directory.clear();
            }
            ++ x;
        }

        if(directory.len() > 0)
        {
            directory_t& dir = stack.alloc();
            dir = directory;
        }
    }

    void path_t::split_to_queue(const directory_t& s, filename_queue_t& queue)
    {
        directory_t directory;
        size_t x = 0;
        while(s[x])
        {
            directory.append(s[x]);
            if('/' == s[x])
            {
                if((x + 1) == s.len())
                {
                    break;
                }

                directory_t& dir = queue.alloc();
                dir = directory;

                directory.clear();
            }
            ++ x;
        }

        if(directory.len() > 0)
        {
            directory_t& dir = queue.alloc();
            dir = directory;
        }
    }
}
