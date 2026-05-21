#include "str.h"

int main() {


    char val[] = "Hello, World!";
    
    String s = create_str(sizeof(val));

    append_str(&s, str(val));
    append_str(&s, str(val));

    for (each_char_in(s)) {
        putc(s.val[i], stdout);
    }

    destroy_str(&s);

    return 0;
}