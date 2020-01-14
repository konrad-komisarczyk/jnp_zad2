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
    
    for(int i=0;i<100;++i) {
        std::string key = "key";
        std::string value = "value";
        for(int j=0;j<i;++j) {
            key += "X";
        }
        ::jnp1::dict_insert(::jnp1::dict_global(), key.c_str(), value.c_str());
    }
    assert(::jnp1::dict_size(::jnp1::dict_global()) == 42);
    
    ::jnp1::dict_copy(::jnp1::dict_global(), 1);
    ::jnp1::dict_copy(::jnp1::dict_global(), 2);
    ::jnp1::dict_copy(::jnp1::dict_global(), 3);
    
    assert(::jnp1::dict_size(::jnp1::dict_global()) == 42);
    assert(::jnp1::dict_size(1) == 0);
    assert(::jnp1::dict_size(2) == 0);
    assert(::jnp1::dict_size(3) == 0);
    
    ::jnp1::dict_copy(::jnp1::dict_global(), ::jnp1::dict_global());
    ::jnp1::dict_copy(::jnp1::dict_global(), ::jnp1::dict_global());
    ::jnp1::dict_copy(::jnp1::dict_global(), ::jnp1::dict_global());
    assert(::jnp1::dict_size(::jnp1::dict_global()) == 42);
    
    ::jnp1::dict_copy(1, ::jnp1::dict_global());
    ::jnp1::dict_copy(2, ::jnp1::dict_global());
    ::jnp1::dict_copy(3, ::jnp1::dict_global());
    ::jnp1::dict_copy(4, ::jnp1::dict_global());
    ::jnp1::dict_copy(5, ::jnp1::dict_global());
    ::jnp1::dict_copy(2, 4);
    ::jnp1::dict_copy(4, 2);
    
    assert(::jnp1::dict_size(::jnp1::dict_global()) == 42);
    assert(::jnp1::dict_size(1) == 0);
    assert(::jnp1::dict_size(2) == 0);
    assert(::jnp1::dict_size(3) == 0);
    
    unsigned long long id = ::jnp1::dict_new();
    ::jnp1::dict_copy(::jnp1::dict_global(), id);
    assert(::jnp1::dict_size(id) == 42);
    
    for(int i=0;i<42;++i) {
        std::string key = "key";
        std::string value = "value";
        for(int j=0;j<i;++j) {
            key += "X";
        }
        assert(std::string(::jnp1::dict_find(id, key.c_str())) == value);
    }
    
    ::jnp1::dict_clear(::jnp1::dict_global());
    assert(::jnp1::dict_size(::jnp1::dict_global()) == 0);
    assert(::jnp1::dict_size(id) == 42);
    
    for(int i=0;i<100;++i) {
        std::string key = "#key";
        std::string value = "#value";
        for(int j=0;j<i;++j) {
            key += "X";
        }
        ::jnp1::dict_insert(id, key.c_str(), value.c_str());
    }
    
    assert(::jnp1::dict_size(id) == 142);
    ::jnp1::dict_copy(id, ::jnp1::dict_global());
    ::jnp1::dict_delete(id);
    
    assert(::jnp1::dict_size(id) == 0);
    
    // We copy dict of size > 42 into global dict
    // we assume it should contain no more than 42 in any situation
    assert(::jnp1::dict_size(::jnp1::dict_global()) == 42);
    
    return 0;
}