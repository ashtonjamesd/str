#include "str.h"

int main() {

    // read an entire file into a string
    string contents = create_str_from_file("example/file.c");

    if (is_null_str(contents)) {
        printf("failed to read file\n");
        return 1;
    }

    printf("file is %zu bytes\n", contents.len);
    printf("%s", contents.val);

    destroy_str(&contents);

    return 0;
}