#include "login.h"

namespace message
{
  const uint32_t login                            = 1;
  const uint32_t chat                             = 2;
}

namespace ds
{
  user_login_info_t::user_login_info_t()
  {
    clear();
  }
  user_login_info_t::~user_login_info_t()
  {
  }
  void user_login_info_t::clear()
  {
    bit.clear();
    user.clear();
    password.clear();
  }
  void user_login_info_t::print()
  {
    if(bit.has(0))
    {
      user.print();
    }
    if(bit.has(1))
    {
      password.print();
    }
  }
  user_t& user_login_info_t::alloc_user()
  {
    bit.set(0);
    return user;
  }
  void user_login_info_t::clear_user()
  {
    bit.clr(0);
    user.clear();
  }
  bool user_login_info_t::has_user()
  {
    return bit.has(0);
  }
  password_t& user_login_info_t::alloc_password()
  {
    bit.set(1);
    return password;
  }
  void user_login_info_t::clear_password()
  {
    bit.clr(1);
    password.clear();
  }
  bool user_login_info_t::has_password()
  {
    return bit.has(1);
  }
  loginp::loginp()
  {
    clear();
  }
  loginp::~loginp()
  {
  }
  void loginp::clear()
  {
    bit.clear();
    lu = 0;
    lm = 0;
    user_login_info.clear();
  }
  void loginp::print()
  {
    if(bit.has(0))
    {
      printf("lu = %u\n");
    }
    if(bit.has(1))
    {
      printf("lm = %u\n");
    }
    if(bit.has(3))
    {
      user_login_info.print();
    }
  }
  void loginp::set_lu(uint32_t _lu)
  {
    lu = _lu;
    bit.set(0);
  }
  void loginp::clear_lu()
  {
    lu = 0;
    bit.clr(0);
  }
  bool loginp::has_lu()
  {
    return bit.has(0);
  }
  void loginp::set_lm(uint32_t _lm)
  {
    lm = _lm;
    bit.set(1);
  }
  void loginp::clear_lm()
  {
    lm = 0;
    bit.clr(1);
  }
  bool loginp::has_lm()
  {
    return bit.has(1);
  }
  user_login_info_t& loginp::alloc_user_login_info()
  {
    bit.set(3);
    return user_login_info;
  }
  void loginp::clear_user_login_info()
  {
    bit.clr(3);
    user_login_info.clear();
  }
  bool loginp::has_user_login_info()
  {
    return bit.has(3);
  }
  chat::chat()
  {
    clear();
  }
  chat::~chat()
  {
  }
  void chat::clear()
  {
    bit.clear();
    lu = 0;
    lm = 0;
    user_login_info.clear();
  }
  void chat::print()
  {
    if(bit.has(0))
    {
      printf("lu = %u\n");
    }
    if(bit.has(1))
    {
      printf("lm = %u\n");
    }
    if(bit.has(3))
    {
      user_login_info.print();
    }
  }
  void chat::set_lu(uint32_t _lu)
  {
    lu = _lu;
    bit.set(0);
  }
  void chat::clear_lu()
  {
    lu = 0;
    bit.clr(0);
  }
  bool chat::has_lu()
  {
    return bit.has(0);
  }
  void chat::set_lm(uint32_t _lm)
  {
    lm = _lm;
    bit.set(1);
  }
  void chat::clear_lm()
  {
    lm = 0;
    bit.clr(1);
  }
  bool chat::has_lm()
  {
    return bit.has(1);
  }
  user_login_info_t& chat::alloc_user_login_info()
  {
    bit.set(3);
    return user_login_info;
  }
  void chat::clear_user_login_info()
  {
    bit.clr(3);
    user_login_info.clear();
  }
  bool chat::has_user_login_info()
  {
    return bit.has(3);
  }
  entry::entry()
  {
    clear();
  }
  entry::~entry()
  {
  }
  void entry::clear()
  {
    bit.clear();
    m = 0;
    n = 0;
    c = 0;
    user_login_info.clear();
    user_map.clear();
    id_map.clear();
    user_password_map.clear();
    password_map.clear();
    user_vec.clear();
    user_id_set.clear();
    user_set.clear();
  }
  void entry::print()
  {
    if(bit.has(0))
    {
      printf("m = %u\n");
    }
    if(bit.has(1))
    {
      printf("n = %u\n");
    }
    if(bit.has(2))
    {
      printf("c = %u\n");
    }
    if(bit.has(5))
    {
      user_login_info.print();
    }
    if(bit.has(6))
    {
      user_map.print();
    }
    if(bit.has(8))
    {
      id_map.print();
    }
    if(bit.has(10))
    {
      user_password_map.print();
    }
    if(bit.has(12))
    {
      password_map.print();
    }
    if(bit.has(14))
    {
      user_vec.print();
    }
    if(bit.has(16))
    {
      user_id_set.print();
    }
    if(bit.has(18))
    {
      user_set.print();
    }
  }
  void entry::set_m(uint32_t _m)
  {
    m = _m;
    bit.set(0);
  }
  void entry::clear_m()
  {
    m = 0;
    bit.clr(0);
  }
  bool entry::has_m()
  {
    return bit.has(0);
  }
  void entry::set_n(uint32_t _n)
  {
    n = _n;
    bit.set(1);
  }
  void entry::clear_n()
  {
    n = 0;
    bit.clr(1);
  }
  bool entry::has_n()
  {
    return bit.has(1);
  }
  void entry::set_c(uint32_t _c)
  {
    c = _c;
    bit.set(2);
  }
  void entry::clear_c()
  {
    c = 0;
    bit.clr(2);
  }
  bool entry::has_c()
  {
    return bit.has(2);
  }
  user_login_info_t& entry::alloc_user_login_info()
  {
    bit.set(5);
    return user_login_info;
  }
  void entry::clear_user_login_info()
  {
    bit.clr(5);
    user_login_info.clear();
  }
  bool entry::has_user_login_info()
  {
    return bit.has(5);
  }
  kmap_t<user_t>& entry::alloc_user_map()
  {
    bit.set(6);
    return user_map;
  }
  void entry::clear_user_map()
  {
    bit.clr(6);
    user_map.clear();
  }
  bool entry::has_user_map()
  {
    return bit.has(6);
  }
  bmap_t& entry::alloc_id_map()
  {
    bit.set(8);
    return id_map;
  }
  void entry::clear_id_map()
  {
    bit.clr(8);
    id_map.clear();
  }
  bool entry::has_id_map()
  {
    return bit.has(8);
  }
  kvmap_t<user_t,password_t>& entry::alloc_user_password_map()
  {
    bit.set(10);
    return user_password_map;
  }
  void entry::clear_user_password_map()
  {
    bit.clr(10);
    user_password_map.clear();
  }
  bool entry::has_user_password_map()
  {
    return bit.has(10);
  }
  vmap_t<password_t>& entry::alloc_password_map()
  {
    bit.set(12);
    return password_map;
  }
  void entry::clear_password_map()
  {
    bit.clr(12);
    password_map.clear();
  }
  bool entry::has_password_map()
  {
    return bit.has(12);
  }
  svector_t<user_t,32>& entry::alloc_user_vec()
  {
    bit.set(14);
    return user_vec;
  }
  void entry::clear_user_vec()
  {
    bit.clr(14);
    user_vec.clear();
  }
  bool entry::has_user_vec()
  {
    return bit.has(14);
  }
  stset_t& entry::alloc_user_id_set()
  {
    bit.set(16);
    return user_id_set;
  }
  void entry::clear_user_id_set()
  {
    bit.clr(16);
    user_id_set.clear();
  }
  bool entry::has_user_id_set()
  {
    return bit.has(16);
  }
  tset_t<user_t>& entry::alloc_user_set()
  {
    bit.set(18);
    return user_set;
  }
  void entry::clear_user_set()
  {
    bit.clr(18);
    user_set.clear();
  }
  bool entry::has_user_set()
  {
    return bit.has(18);
  }
}