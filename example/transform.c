#include "str.h"

int main() {

    string s = str("Hello, World!");

    // convert to uppercase (allocates a new string)
    string upper = to_upper_str(s);
    printf("%s\n", upper.val); // HELLO, WORLD!

    // convert to lowercase (allocates a new string)
    string lower = to_lower_str(s);
    printf("%s\n", lower.val); // hello, world!

    // clean up heap strings
    destroy_str(&upper);
    destroy_str(&lower);

    return 0;
}