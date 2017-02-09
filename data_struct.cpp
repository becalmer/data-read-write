#include <stdio.h>
#include <stdint.h>
#include <typeinfo>
#include <iostream>
#include <sxvector.h>
#include <scaner.h>
#include <path.h>
#include <type_1.h>
#include <file.h>
#include <parser.h>
#include <info.h>
#include <generator.h>

int main(int argc, const char* argv[])
{
    ds::path_t path;

    ds::directory_t directory_in("../data_struct");

    directory_in = path.absolute_directory(directory_in);

    directory_in.print();

    ds::scaner_t scaner(directory_in);

    if(!scaner.is_opened())
    {
        return -1;
    }

    scaner.print();

    ds::directory_t directory_out("../cpp");

    directory_out = path.absolute_directory(directory_out);

    directory_out.print();

    ds::file_t file;

    ds::content_t content;

    ds::parser_t parser;

    size_t count = scaner.count();

    for(size_t x = 0; x < count; ++ x)
    {
        ds::filename_t& filename = scaner[x];
        if(!file.open(filename, "rb"))
        {
            continue;
        }
        if(!file.is_opened())
        {
            continue;
        }
        file.read(content);
        if(content.rsize() > 0)
        {
            parser.set_filename(filename);
            parser.handle(content);
        }
        //content.print();
        parser.clear();
        content.clear();
        file.close();
    }

    ds::g_info_mgr.print();

    ds::generator_t generator;

    for(size_t x = 0; x < count; ++ x)
    {
        ds::filename_t& filename = scaner[x];

        generator.handle(filename, directory_in, directory_out);
    }

    return 0;
}
