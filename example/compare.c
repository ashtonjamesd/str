#include "str.h"

int main() {

    string a = str("Hello");
    string b = str("Hello");
    string c = str("World");

    if (str_eq(a, b)) {
        printf("a and b are equal\n");
    }

    if (!str_eq(a, c)) {
        printf("a and c are not equal\n");
    }

    // check prefix and suffix
    string path = str("/usr/local/bin");

    if (starts_with_str(path, str("/usr"))) {
        printf("path starts with /usr\n");
    }

    if (ends_with_str(path, str("/bin"))) {
        printf("path ends with /bin\n");
    }

    return 0;
}