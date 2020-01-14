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
    
    for(unsigned long long i = 0; i < 2000; ++i) {
        ::jnp1::dict_delete(i);
        ::jnp1::dict_size(i);
        ::jnp1::dict_insert(i, nullptr, nullptr);
        ::jnp1::dict_insert(i, "ALA", nullptr);
        ::jnp1::dict_insert(i, nullptr, "MA KOTA");
        assert(::jnp1::dict_find(i, "ALA") == nullptr);
        ::jnp1::dict_clear(i);
        assert(::jnp1::dict_find(i, "ALA") == nullptr);
        assert(::jnp1::dict_find(i, nullptr) == nullptr);
    }
    
    unsigned long long id = ::jnp1::dict_new();
    assert(::jnp1::dict_size(id) == 0);
    ::jnp1::dict_insert(id, nullptr, nullptr);
    ::jnp1::dict_insert(id, "ALA", nullptr);
    ::jnp1::dict_insert(id, nullptr, "MA KOTA");
    assert(::jnp1::dict_size(id) == 0);
    
    assert(::jnp1::dict_find(id, "ALA") == nullptr);
    assert(::jnp1::dict_find(id, nullptr) == nullptr);
    
    ::jnp1::dict_insert(id, "ALA", "MA KOTA");
    assert(::jnp1::dict_size(id) == 1);
    
    return 0;
}