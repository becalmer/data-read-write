auto define *.ds file, use data_struct to generate .h,.cpp file
1. git clone复制代码
2. mkdir build建立编译中间文件目录
3. cd build，cmake ..，make生成data_struct应用程序
4. data_struct目录是数据结构源文件如源文件login/login.ds

*.ds 文件编码规则
message用于定义协议id
struct用于定义struct结构体
enum用于定义enum枚举
include用于包含头文件
/**/和//用于注释

5. 在build下面执行./data_struct就会在cpp/目录下生成协议.h和.cpp文件

bmap_t key和value为基础数据类型uint32_t的map
kmap_t key为模板类型，value为uint32_t类型
vmap_t key为uint32_t类型，value为模板类型
bmap_t key和value为模板的map

其他类set、queue也是类似这样

理由：便于打包和解包

string,vector,queue,stack提供栈和堆版本

buffer类也提供栈和堆版本
