#include "str.h"

int main() {
    string s = str("Hello, World!\n");

    for (each_char_in(s)) {
        putchar(s.val[i]);
    }

    return 0;
}