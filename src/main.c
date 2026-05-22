#include "str.h"

int main() {
    // stack string (no allocation, no cleanup needed)
    string greeting = str("Hello, World!");
    printf("%s\n", greeting.val);  // Hello, World!
    printf("%zu\n", greeting.len); // 13

    // heap string (growable, must be destroyed)
    string buf = create_str(16);
    append_str(&buf, str("Hello"));
    append_str(&buf, str(", "));
    append_str(&buf, str("World!"));
    printf("%s\n", buf.val); // Hello, World!
    destroy_str(&buf);

    return 0;
}