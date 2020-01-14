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
    
    for(int i=0;i<42;++i) {
        std::string key = "key";
        std::string value = "value";
        for(int j=0;j<i;++j) {
            key += "X";
            value += "_";
            value[j%3] = (char)((j%10) + 'a');
            value[value.size()-1] = (char) (((j+2)%7)+'5');
        }
        ::jnp1::dict_insert(::jnp1::dict_global(), key.c_str(), value.c_str());
    }
    assert(::jnp1::dict_size(::jnp1::dict_global()) == 42);
    
    
    for(int k=0;k<100;++k) {
        std::string key = "key";
        std::string value = "value";
        for(int j=0;j<k;++j) {
            key += "X";
            value += "_";
            value[j%3] = (char)((j%10) + 'a');
            value[value.size()-1] = (char) (((j+2)%7)+'5');
        }
        if(k % 3 == 0) key += "#";
        ::jnp1::dict_insert(::jnp1::dict_global(), key.c_str(), value.c_str());
    }
    assert(::jnp1::dict_size(::jnp1::dict_global()) == 42);
    
    for(int k=0;k<42;++k) {
        std::string key = "key";
        std::string value = "value";
        for(int j=0;j<k;++j) {
            key += "X";
            value += "_";
            value[j%3] = (char)((j%10) + 'a');
            value[value.size()-1] = (char) (((j+2)%7)+'5');
        }
        assert( std::string(::jnp1::dict_find(::jnp1::dict_global(), key.c_str())) == value );
    }
    
    return 0;
}