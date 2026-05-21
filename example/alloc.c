#include "str.h"

int main() {
    // creates a heap-allocated string
    string s = create_str(14);

    // appends another string to the allocated string
    append_str(&s, str("Hello, World!"));

    // frees the string allocation
    destroy_str(&s);

    return 0;
}