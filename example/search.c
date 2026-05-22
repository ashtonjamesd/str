#include "str.h"

int main() {

    string s = str("Hello, World!");

    // check if a string contains a substring
    if (contains_str(s, str("World"))) {
        printf("found 'World'\n");
    }

    // check if a string contains a character
    if (contains_char(s, '!')) {
        printf("found '!'\n");
    }

    // find the position of a substring
    int idx = index_of_str(s, str("World"));
    printf("'World' starts at index %d\n", idx);

    // find the position of a character
    idx = index_of_char(s, ',');
    printf("',' is at index %d\n", idx);

    return 0;
}