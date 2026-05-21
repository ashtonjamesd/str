#include "str.h"

int main() {
    string s = create_str(14);
    append_str(&s, str("Hello, World!"));

    for (each_char_in(s)) {
        putchar(s.val[i]);
    }

    destroy_str(&s);

    return 0;
}