#include "str.h"

int main() {

    // allocate a string
    string s = clone_str(str("Hello, World!"));

    // allocate a new string based on a slice of another
    string slice = slice_str(s, 7, 12);

    printf("%s", slice.val); // 'World'

    // clean up
    destroy_str(&s);
    destroy_str(&slice);

    return 0;
}