#ifndef __SERVER_DATASTRUCT_CPP_LOGIN_LOGIN_H__
#define __SERVER_DATASTRUCT_CPP_LOGIN_LOGIN_H__

#include <bit.h>
#include "type_1.h"
#include "kmap.h"
#include "bmap.h"
#include "kvmap.h"
#include "vmap.h"
#include "svector.h"
#include "stset.h"
#include "tset.h"

namespace message
{
  extern const uint32_t login;
  extern const uint32_t chat;
}

namespace ds
{
  class user_login_info_t
  {
  public:
    user_login_info_t();
    ~user_login_info_t();
    void clear();
    template<typename T>
    bool write(T& t)
    {
      if(!bit.write(t))
      {
        return false;
      }
      if(bit.has(0))
      {
        if(!user.write(t))
        {
          return false;
        }
      }
      if(bit.has(1))
      {
        if(!password.write(t))
        {
          return false;
        }
      }
      return true;
    }
    template<typename T>
    bool read(T& t)
    {
      if(!bit.read(t))
      {
        return false;
      }
      if(bit.has(0))
      {
        if(!user.read(t))
        {
          return false;
        }
      }
      if(bit.has(1))
      {
        if(!password.read(t))
        {
          return false;
        }
      }
      return true;
    }
    void print();

    user_t& alloc_user();
    void clear_user();
    bool has_user();

    password_t& alloc_password();
    void clear_password();
    bool has_password();

  private:
    typedef bit_t<1>                bit_s;
    bit_s                           bit;
    user_t                          user;
    password_t                      password;
  };
  class loginp
  {
  public:
    loginp();
    ~loginp();
    void clear();
    template<typename T>
    bool write(T& t)
    {
      if(!bit.write(t))
      {
        return false;
      }
      if(bit.has(0))
      {
        if(!t.write(lu))
        {
          return false;
        }
      }
      if(bit.has(1))
      {
        if(!t.write(lm))
        {
          return false;
        }
      }
      if(bit.has(3))
      {
        if(!user_login_info.write(t))
        {
          return false;
        }
      }
      return true;
    }
    template<typename T>
    bool read(T& t)
    {
      if(!bit.read(t))
      {
        return false;
      }
      if(bit.has(0))
      {
        if(!t.read(lu))
        {
          return false;
        }
      }
      if(bit.has(1))
      {
        if(!t.read(lm))
        {
          return false;
        }
      }
      if(bit.has(3))
      {
        if(!user_login_info.read(t))
        {
          return false;
        }
      }
      return true;
    }
    void print();

    void set_lu(uint32_t _lu);
    void clear_lu();
    bool has_lu();

    void set_lm(uint32_t _lm);
    void clear_lm();
    bool has_lm();

    user_login_info_t& alloc_user_login_info();
    void clear_user_login_info();
    bool has_user_login_info();

  private:
    typedef bit_t<3>                bit_s;
    bit_s                           bit;
    uint32_t                        lu;
    uint32_t                        lm;
    user_login_info_t               user_login_info;
  };
  class chat
  {
  public:
    chat();
    ~chat();
    void clear();
    template<typename T>
    bool write(T& t)
    {
      if(!bit.write(t))
      {
        return false;
      }
      if(bit.has(0))
      {
        if(!t.write(lu))
        {
          return false;
        }
      }
      if(bit.has(1))
      {
        if(!t.write(lm))
        {
          return false;
        }
      }
      if(bit.has(3))
      {
        if(!user_login_info.write(t))
        {
          return false;
        }
      }
      return true;
    }
    template<typename T>
    bool read(T& t)
    {
      if(!bit.read(t))
      {
        return false;
      }
      if(bit.has(0))
      {
        if(!t.read(lu))
        {
          return false;
        }
      }
      if(bit.has(1))
      {
        if(!t.read(lm))
        {
          return false;
        }
      }
      if(bit.has(3))
      {
        if(!user_login_info.read(t))
        {
          return false;
        }
      }
      return true;
    }
    void print();

    void set_lu(uint32_t _lu);
    void clear_lu();
    bool has_lu();

    void set_lm(uint32_t _lm);
    void clear_lm();
    bool has_lm();

    user_login_info_t& alloc_user_login_info();
    void clear_user_login_info();
    bool has_user_login_info();

  private:
    typedef bit_t<3>                bit_s;
    bit_s                           bit;
    uint32_t                        lu;
    uint32_t                        lm;
    user_login_info_t               user_login_info;
  };
  class entry
  {
  public:
    entry();
    ~entry();
    void clear();
    template<typename T>
    bool write(T& t)
    {
      if(!bit.write(t))
      {
        return false;
      }
      if(bit.has(0))
      {
        if(!t.write(m))
        {
          return false;
        }
      }
      if(bit.has(1))
      {
        if(!t.write(n))
        {
          return false;
        }
      }
      if(bit.has(2))
      {
        if(!t.write(c))
        {
          return false;
        }
      }
      if(bit.has(5))
      {
        if(!user_login_info.write(t))
        {
          return false;
        }
      }
      if(bit.has(6))
      {
        if(!user_map.write(t))
        {
          return false;
        }
      }
      if(bit.has(8))
      {
        if(!id_map.write(t))
        {
          return false;
        }
      }
      if(bit.has(10))
      {
        if(!user_password_map.write(t))
        {
          return false;
        }
      }
      if(bit.has(12))
      {
        if(!password_map.write(t))
        {
          return false;
        }
      }
      if(bit.has(14))
      {
        if(!user_vec.write(t))
        {
          return false;
        }
      }
      if(bit.has(16))
      {
        if(!user_id_set.write(t))
        {
          return false;
        }
      }
      if(bit.has(18))
      {
        if(!user_set.write(t))
        {
          return false;
        }
      }
      return true;
    }
    template<typename T>
    bool read(T& t)
    {
      if(!bit.read(t))
      {
        return false;
      }
      if(bit.has(0))
      {
        if(!t.read(m))
        {
          return false;
        }
      }
      if(bit.has(1))
      {
        if(!t.read(n))
        {
          return false;
        }
      }
      if(bit.has(2))
      {
        if(!t.read(c))
        {
          return false;
        }
      }
      if(bit.has(5))
      {
        if(!user_login_info.read(t))
        {
          return false;
        }
      }
      if(bit.has(6))
      {
        if(!user_map.read(t))
        {
          return false;
        }
      }
      if(bit.has(8))
      {
        if(!id_map.read(t))
        {
          return false;
        }
      }
      if(bit.has(10))
      {
        if(!user_password_map.read(t))
        {
          return false;
        }
      }
      if(bit.has(12))
      {
        if(!password_map.read(t))
        {
          return false;
        }
      }
      if(bit.has(14))
      {
        if(!user_vec.read(t))
        {
          return false;
        }
      }
      if(bit.has(16))
      {
        if(!user_id_set.read(t))
        {
          return false;
        }
      }
      if(bit.has(18))
      {
        if(!user_set.read(t))
        {
          return false;
        }
      }
      return true;
    }
    void print();

    void set_m(uint32_t _m);
    void clear_m();
    bool has_m();

    void set_n(uint32_t _n);
    void clear_n();
    bool has_n();

    void set_c(uint32_t _c);
    void clear_c();
    bool has_c();

    user_login_info_t& alloc_user_login_info();
    void clear_user_login_info();
    bool has_user_login_info();

    kmap_t<user_t>& alloc_user_map();
    void clear_user_map();
    bool has_user_map();

    bmap_t& alloc_id_map();
    void clear_id_map();
    bool has_id_map();

    kvmap_t<user_t,password_t>& alloc_user_password_map();
    void clear_user_password_map();
    bool has_user_password_map();

    vmap_t<password_t>& alloc_password_map();
    void clear_password_map();
    bool has_password_map();

    svector_t<user_t,32>& alloc_user_vec();
    void clear_user_vec();
    bool has_user_vec();

    stset_t& alloc_user_id_set();
    void clear_user_id_set();
    bool has_user_id_set();

    tset_t<user_t>& alloc_user_set();
    void clear_user_set();
    bool has_user_set();

  private:
    typedef bit_t<18>               bit_s;
    bit_s                           bit;
    uint32_t                        m;
    uint32_t                        n;
    uint32_t                        c;
    user_login_info_t               user_login_info;
    kmap_t<user_t>                  user_map;
    bmap_t                          id_map;
    kvmap_t<user_t,password_t>      user_password_map;
    vmap_t<password_t>              password_map;
    svector_t<user_t,32>            user_vec;
    stset_t                         user_id_set;
    tset_t<user_t>                  user_set;
  };
  enum state
  {
    scene            = 1,
    login            = 2,
  };
}

#endif