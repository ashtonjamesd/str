#include "str.h"

int main() {

    // build up a string piece by piece
    string s = create_str(64);

    append_str(&s, str("name"));
    append_char(&s, '=');
    append_str(&s, str("value"));
    append_char(&s, '&');
    append_str(&s, str("key"));
    append_char(&s, '=');
    append_str(&s, str("other"));

    printf("%s\n", s.val); // name=value&key=other

    destroy_str(&s);

    return 0;
}