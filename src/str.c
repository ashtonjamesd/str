#include "str.h"

String create_str(size_t cap) {
    String s = {
        .cap = cap,
        .len = 0,
        .val = malloc(cap),
    };

    return s;
}

void append_str(String *dest, String src) {
    for (size_t i = 0; i < src.len; i++) {
        dest->val[dest->len] = src.val[i];
        dest->len += 1;

        if (dest->len == dest->cap) {
            const size_t new_cap = (dest->cap * 2) + src.len;

            dest->cap = new_cap;
            dest->val = realloc(dest->val, dest->cap);
        }
    }
}

void destroy_str(String *s) {
    free(s->val);

    s->cap = 0;
    s->len = 0;
    s->val = NULL;
}