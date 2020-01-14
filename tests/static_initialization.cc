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

namespace {
    int streq(const char* s1, const char* s2, size_t len) {
        if (s1 == s2)
            return 1;

        if (s1 == NULL || s2 == NULL)
            return 0;

        return strncmp(s1, s2, len) == 0;
    }

    unsigned long test() {
        unsigned long id = ::jnp1::dict_new();
        ::jnp1::dict_insert(id, "k0", "a");
        return id;
    }

    unsigned long id = test();
}

int main() {
    const char* str = ::jnp1::dict_find(id, "k0");
    assert(streq(str, "a", 2));
    ::jnp1::dict_delete(id);
}