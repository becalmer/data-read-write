#ifndef __DATA_STRUCT_TYPE_2_H__
#define __DATA_STRUCT_TYPE_2_H__

#include <svector.h>
#include <type_1.h>
#include <sstack.h>
#include <squeue.h>

namespace ds
{
    typedef svector_t<filename_t, 10000>   filename_list_t;
    typedef svector_t<directory_t, 100>    directory_list_t;
    typedef sstack_t<filename_t, 100>      filename_stack_t;
    typedef squeue_t<filename_t, 100>      filename_queue_t;
}

#endif
