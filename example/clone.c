#include "str.h"

int main() {

    // you can create and initialise a heap-allocated string like so.
    // however, this method requires you to specify the initial capacity
    // and then append the string value later.
    string s = create_str(14);
    append_str(&s, str("Hello, World!"));


    // this is a more concise way to make a heap-allocated string with a value
    string s = clone_str(str("Hello, World!\n"));


    // clean up
    destroy_str(&s);

    return 0;
}