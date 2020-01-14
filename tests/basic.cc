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


static int streq(const char* s1, const char* s2, size_t len) {
    if (s1 == s2)
        return 1;

    if (s1 == NULL || s2 == NULL)
        return 0;

    return strncmp(s1, s2, len) == 0;
}

int main() {
    
    unsigned long d1, d2, d3;

    assert(::jnp1::dict_size(::jnp1::dict_global()) == 0);

    d1 = ::jnp1::dict_new();

    ::jnp1::dict_insert(d1, "k0", "a");
    assert(streq(::jnp1::dict_find(d1, "k0"), "a", 2));

    ::jnp1::dict_insert(d1, "k1", "aa");
    assert(streq(::jnp1::dict_find(d1, "k1"), "aa", 3));
    assert(::jnp1::dict_size(d1) == 2);

    ::jnp1::dict_remove(d1, "k1");
    assert(::jnp1::dict_find(d1, "k1") == NULL);
    assert(streq(::jnp1::dict_find(d1, "k0"), "a", 2));
    assert(::jnp1::dict_size(d1) == 1);

    ::jnp1::dict_insert(d1, "k0", NULL);
    assert(streq(::jnp1::dict_find(d1, "k0"), "a", 2));
    assert(::jnp1::dict_size(d1) == 1);

    ::jnp1::dict_insert(d1, NULL, NULL);
    assert(::jnp1::dict_size(d1) == 1);

    ::jnp1::dict_remove(d1, "k1");
    assert(::jnp1::dict_size(d1) == 1);

    ::jnp1::dict_delete(d1);
    ::jnp1::dict_insert(d1, "k0", "b");
    assert(::jnp1::dict_size(d1) == 0);
    assert(::jnp1::dict_find(d1, "k0") == NULL);

    d2 = ::jnp1::dict_new();
    d3 = ::jnp1::dict_new();
    ::jnp1::dict_insert(d2, "k0", "c");
    ::jnp1::dict_insert(d2, "k1", "cc");
    ::jnp1::dict_insert(d2, "k2", "ccc");
    ::jnp1::dict_copy(d2, d3);
    assert(::jnp1::dict_size(d3) == 3);

    ::jnp1::dict_clear(d3);
    assert(::jnp1::dict_size(d3) == 0);

    ::jnp1::dict_insert(::jnp1::dict_global(), "g0", "d");
    assert(::jnp1::dict_size(::jnp1::dict_global()) == 1);
    assert(streq(::jnp1::dict_find(d1, "g0"), "d", 2));

    ::jnp1::dict_delete(::jnp1::dict_global());
    assert(::jnp1::dict_size(::jnp1::dict_global()) == 1);

    ::jnp1::dict_clear(::jnp1::dict_global());
    
    return 0;
}