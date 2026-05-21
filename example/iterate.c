#include "str.h"

int main() {

    // declares a non-heap-allocated string
    string s = str("Hello, World!\n");

    // iterates through each character in the string
    for (each_char_in(s, i)) {
        putchar(s.val[i]);
    }

    return 0;
}