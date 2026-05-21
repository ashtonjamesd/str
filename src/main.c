#include "str.h"

int main() {
    string s = create_str(4);

    for (each_char_in(s, i)) {
        putchar(s.val[i]);
    }

    destroy_str(&s);

    return 0;
}