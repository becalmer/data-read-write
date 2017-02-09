#include "login/login.h"
#include "buffer_pool.h"
#include "bin.h"
#include "sbuffer.h"

int main()
{
    ds::g_buffer_pool.init(10, (1 << 20));

    ds::entry entry;

    entry.set_m(1);

    entry.set_n(2);

    ds::user_login_info_t& info = entry.alloc_user_login_info();
    
    ds::user_t& user = info.alloc_user();
    user = "Game";

    ds::password_t& password = info.alloc_password();
    password = "Develop";

    entry.print();

    ds::buffer_t buffer;

    entry.write(buffer);

    ds::bin_t bin;

    bin.copy(buffer.raddr(), buffer.rsize());

    ds::loginp login;

    ds::chat chat;

    ds::sbuffer_t sbuffer;

    chat.write(sbuffer);

    /*
    ds::user_login_info_t login;

    ds::user_t& user = login.alloc_user();
    user = "Hello";

    ds::password_t& password = login.alloc_password();
    password = "World";

    login.print();
    */
    return 0;
}
