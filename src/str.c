#include "str.h"

bool is_upper(char c) {
    return c >= 'A' and c <= 'Z';
}

bool is_lower(char c) {
    return c >= 'a' and c <= 'z';
}

char to_upper(char c) {
    if (is_upper(c) or !is_lower(c)) return c;
    return c - 32;
}

char to_lower(char c) {
    if (!is_upper(c) or is_lower(c)) return c;

    return c + 32;
}

string create_str(size_t capacity) {
    const string s = {
        .capacity = capacity,
        .len = 0,
        .val = calloc(capacity, 1),
    };

    s.val[0] = '\0';

    return s;
}

bool append_str(string *dest, string src) {
    if (dest->capacity == 0) return false;
    if (str_eq(src, empty_str())) return true;

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

bool append_char(string *dest, char needle) {
    if (dest->capacity == 0) return false;

    if (dest->len == dest->capacity) {
        dest->capacity *= 2;
        dest->val = realloc(dest->val, dest->capacity);
    }

    dest->val[dest->len] = needle;
    dest->len += 1;

    dest->val[dest->len] = '\0';

    return true;
}

int index_of_char(string haystack, char needle) {
    for (each_char_in(haystack, i)) {
        if (needle == haystack.val[i]) return i;
    }

    return -1;
}

int index_of_str(string haystack, string needle) {
    if (needle.len == 0) return -1;
    if (needle.len > haystack.len) return -1;

    for (size_t i = 0; i <= haystack.len - needle.len; i++) {

        bool contains = true;
        for (each_char_in(needle, j)) {
            if (haystack.val[i + j] != needle.val[j]) {
                contains = false;
                break;
            }
        }

        if (contains) return i;
    }

    return -1;
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

bool is_allocated_str(string s) {
    return s.capacity > 0;
}

bool contains_str(string haystack, string needle) {
    if (needle.len == 0) return true;
    if (needle.len > haystack.len) return false;

    for (size_t i = 0; i <= haystack.len - needle.len; i++) {

        bool contains = true;
        for (each_char_in(needle, j)) {
            if (haystack.val[i + j] != needle.val[j]) {
                contains = false;
                break;
            }
        }

        if (contains) return true;
    }

    return false;
}

bool contains_char(string haystack, char needle) {
    for (each_char_in(haystack, i)) {
        if (needle == haystack.val[i]) return true;
    }

    return false;
}

string clone_str(string s) {
    size_t capacity = s.capacity;
    if (s.capacity == 0) {
        capacity = s.len + 1;
    }

    string new_s = create_str(capacity);
    new_s.len = s.len;

    if (!s.val) {
        s.val = NULL;
        return new_s;
    }

    memcpy(new_s.val, s.val, s.len);

    return new_s;
}

bool is_null_str(string s) {
    return s.val == NULL;
}

bool is_empty_str(string s) {
    return s.len == 0;
}

string slice_str(string s, size_t start, size_t end) {
    if (start == end) return empty_str();
    if (end < start) return null_str();
    if (end > s.len) return null_str();
    if (is_null_str(s)) return null_str();

    string new_s = create_str(end - start + 1);
    
    for (size_t i = start; i < end; i++) {
        append_char(&new_s, s.val[i]);
    }

    return new_s;
}

string to_upper_str(string s) {
    if (is_null_str(s)) return null_str();

    string new_s = create_str(s.len + 1);

    for (each_char_in(s, i)) {
        append_char(&new_s, to_upper(s.val[i]));
    }

    return new_s;
}

string to_lower_str(string s) {
    if (is_null_str(s)) return null_str();

    string new_s = create_str(s.len + 1);

    for (each_char_in(s, i)) {
        append_char(&new_s, to_lower(s.val[i]));
    }

    return new_s;
}

string from_file(char *path) {
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