#include <string>
#include <string.h>
#include <iostream>
#include "cdict"
#include "cdictglobal"

inline bool assert_check(const bool condition, const char *msg, const char *file, int line) {
    if(!condition) {
        std::cout << "FAIL " << std::string(msg) << " AT " << std::string(file) << ", LINE " << line << "\n";
    } else {
        std::cout << "OK " << std::string(msg) << "\n";
    }
    return condition;
}

#define assert(EX) (void)((assert_check ((EX), #EX, __FILE__, __LINE__),0))

int main() {
    
    unsigned long long sumsize = 0;
    for(unsigned long long id=1;id<239127;++id) {
       sumsize += ::jnp1::dict_size(id);
       ::jnp1::dict_delete(id);
       sumsize += ::jnp1::dict_size(id);
       ::jnp1::dict_clear(id);
       sumsize += ::jnp1::dict_size(id);
       ::jnp1::dict_insert(id, "KEY", "VALUE");
       sumsize += ::jnp1::dict_size(id);
       ::jnp1::dict_insert(id, "KEY12", "VALUE2");
       ::jnp1::dict_insert(id, "K", "VA");
       sumsize += ::jnp1::dict_size(id);
       if(::jnp1::dict_find(id, "KEY12")!=nullptr) {
           ++sumsize;
       }
    }
    assert(sumsize == 0);
   
    unsigned long long id = ::jnp1::dict_new();
    unsigned long long fid = id;
    for(int w=0;w<100;++w) {
        id = ::jnp1::dict_new();
    }
    
    assert(::jnp1::dict_find(id, "KEY12") == nullptr);
    assert(::jnp1::dict_find(id, "KEY") == nullptr);
    assert(::jnp1::dict_find(id, "KEY12") == nullptr);
    assert(::jnp1::dict_find(id, "K") == nullptr);
    assert(::jnp1::dict_size(id) == 0);
    
    ::jnp1::dict_delete(id);
    
    ::jnp1::dict_insert(id, "KEY12", "VALUE2");
    ::jnp1::dict_insert(id, "K", "VA");
    ::jnp1::dict_insert(id, "KEY", "VALUE");
   
    assert(::jnp1::dict_find(id, "KEY12") == nullptr);
    assert(::jnp1::dict_find(id, "KEY") == nullptr);
    assert(::jnp1::dict_find(id, "KEY12") == nullptr);
    assert(::jnp1::dict_find(id, "K") == nullptr);
    assert(::jnp1::dict_size(id) == 0);
    
    id = fid;
    assert(::jnp1::dict_find(id, "KEY12") == nullptr);
    assert(::jnp1::dict_find(id, "KEY") == nullptr);
    assert(::jnp1::dict_find(id, "KEY12") == nullptr);
    assert(::jnp1::dict_find(id, "K") == nullptr);
    assert(::jnp1::dict_size(id) == 0);
   
    return 0;
}