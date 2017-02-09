#ifndef __DATA_STRUCT_TYPEID_H__
#define __DATA_STRUCT_TYPEID_H__

#include <typeinfo>
#include <string.h>

#if 0

#undef CMP_TYPE
#define CMP_TYPE(T,V) if(strcmp(typeid(T).name(), typeid(V).name()) == 0)

#define APPEND_FMT \
    CMP_TYPE(T,int8_t) \
    { \
        format.append("%d"); \
    } \
    else CMP_TYPE(T,uint8_t) \
    { \
        format.append("%u"); \
    } \
    else CMP_TYPE(T,int16_t) \
    { \
        format.append("%d"); \
    } \
    else CMP_TYPE(T,uint16_t) \
    { \
        format.append("%u"); \
    } \
    else CMP_TYPE(T,int32_t) \
    { \
        format.append("%d"); \
    } \
    else CMP_TYPE(T,uint32_t) \
    { \
        format.append("%u"); \
    } \
    else CMP_TYPE(T,int64_t) \
    { \
        format.append("%lld"); \
    } \
    else CMP_TYPE(T,uint64_t) \
    { \
        format.append("%llu"); \
    }

#undef CMP_TYPE

#else

#define APPEND_FMT \
    if(strcmp(typeid(T).name(), typeid(int8_t).name()) == 0) \
    { \
        format.append("%d"); \
    } \
    else if(strcmp(typeid(T).name(), typeid(uint8_t).name()) == 0) \
    { \
        format.append("%u"); \
    } \
    else if(strcmp(typeid(T).name(), typeid(int16_t).name()) == 0) \
    { \
        format.append("%d"); \
    } \
    else if(strcmp(typeid(T).name(), typeid(uint16_t).name()) == 0) \
    { \
        format.append("%u"); \
    } \
    else if(strcmp(typeid(T).name(), typeid(int32_t).name()) == 0) \
    { \
        format.append("%d"); \
    } \
    else if(strcmp(typeid(T).name(), typeid(uint32_t).name()) == 0) \
    { \
        format.append("%u"); \
    } \
    else if(strcmp(typeid(T).name(), typeid(int64_t).name()) == 0) \
    { \
        format.append("%lld"); \
    } \
    else if(strcmp(typeid(T).name(), typeid(uint64_t).name()) == 0) \
    { \
        format.append("%llu"); \
    }

#endif

#endif
