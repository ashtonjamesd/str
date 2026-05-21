#ifndef str_h
#define str_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    // the internal c-string representation
    char *val;
    size_t len;

    // the number of heap-allocated bytes for this string
    size_t cap;
} String;

#define _make_str(_val, _len) (String) { .val = _val, .len = _len, .cap = 0 }

#define str(s)      _make_str(s, sizeof(s) - 1)
#define nullstr()   _make_str(NULL, 0)
#define str_from(s) _make_str(s.val, s.len)
#define str_empty() _make_str("", 0)

#define each_char_in(s) size_t i = 0; i < s.len; i++
#define print_str(s) printf("%s", s.val)

String create_str(size_t cap);
void destroy_str(String *s);

void append_str(String *dest, String src);
bool str_eq(String a, String b);

#endif