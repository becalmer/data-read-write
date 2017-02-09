cmake_minimum_required(VERSION 2.8)

project(data_struct)

message(STATUS "This is binary dir: " ${PROJECT_BINARY_DIR})
message(STATUS "This is source dir: " ${PROJECT_SOURCE_DIR})

#定义目标，一般与所在目录同名
set(TARGET "data_struct")

#原文件路径
#set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/${TARGET}")

#头文件路径
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR})

#添加源文件
#aux_source_directory(${SOURCE_DIR} SOURCES)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR})

SET(BASE_LIB "base")

SET(BASE_SRC
    aux.cpp
    bin.cpp
    buffer.cpp
    buffer_pool.cpp
    file.cpp
    generator.cpp
    info.cpp
    message.cpp
    parser.cpp
    path.cpp
    scaner.cpp
    sbuffer.cpp
    tstring.cpp
    utils.cpp
)

ADD_DEFINITIONS("-g")

ADD_LIBRARY(${BASE_LIB} STATIC ${BASE_SRC})

#目标可执行程序
ADD_EXECUTABLE(${TARGET} data_struct.cpp)

TARGET_LINK_LIBRARIES(${TARGET} ${BASE_LIB})

ADD_SUBDIRECTORY(cpp)
