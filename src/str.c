#include "str.h"

string create_str(size_t capacity) {
    string s = {
        .capacity = capacity,
        .len = 0,
        .val = calloc(capacity, 1),
    };

    s.val[0] = '\0';

    return s;
}

bool append_str(string *dest, string src) {
    if (dest->capacity == 0) return false;

    for (size_t i = 0; i < src.len; i++) {
        if (dest->len == dest->capacity) {
            const size_t new_cap = (dest->capacity * 2) + src.len;

            dest->capacity = new_cap;
            dest->val = realloc(dest->val, dest->capacity);
        }

        dest->val[dest->len] = src.val[i];
        dest->len += 1;
    }
    
    dest->val[dest->len] = '\0';

    return true;
}

bool append_char(string *dest, char c) {
    if (dest->capacity == 0) return false;

    if (dest->len == dest->capacity) {
        dest->capacity *= 2;
        dest->val = realloc(dest->val, dest->capacity);
    }

    dest->val[dest->len] = c;
    dest->len += 1;

    dest->val[dest->len] = '\0';

    return true;
}

bool str_eq(string a, string b) {
    if (!a.val and !b.val) return true;
    
    if (!a.val) return false;
    if (!b.val) return false;
    
    return strcmp(a.val, b.val) == 0;
}

bool destroy_str(string *s) {
    if (s->capacity == 0) return false;

    free(s->val);

    s->capacity = 0;
    s->len = 0;
    s->val = NULL;

    return true;
}

static string from_file(char *path) {
    FILE *fptr = fopen(path, "r");
    if (!fptr) {
        return null_str();
    }

    fseek(fptr, 0, SEEK_END);
    long sz = ftell(fptr);
    if (sz < 0) {
        fclose(fptr);
        return null_str();
    }
    rewind(fptr);

    char *buf = malloc(sz + 1);
    if (!buf) {
        fclose(fptr);
        return null_str();
    }

    size_t amount_read = fread(buf, 1, sz, fptr);
    if ((long)amount_read != sz) {
        fclose(fptr);
        free(buf);
        return null_str();
    }

    buf[sz] = '\0';
    fclose(fptr);

    string s = {
        .val = buf,
        .len = amount_read,
        .capacity = sz + 1,
    };

    return s;
}