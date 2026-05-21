#ifndef str_h
#define str_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <iso646.h>

/*
* a struct representing a string data type.
*/
typedef struct {

    /*
    *   the internal c-string representation.
    */
    char *val;

    /*
    *   the length of the string.
    *   this is managed internally and external modification should be prohibited.
    */
    size_t len;

    /*
    *   the number of heap-allocated bytes for this string.
    *   this is managed internally and external modification should be prohibited.
    */
    size_t capacity;

} string;

// typedef'd String
typedef string string;

#define make_str(_val, _len) (string) { .val = _val, .len = _len, .capacity = 0 }

#define str(s)      make_str(s, sizeof(s) - 1)
#define null_str()  make_str(NULL, 0)
#define from_str(s) make_str(s.val, s.len)
#define empty_str() make_str("", 0)

#define each_char_in(s, i) size_t i = 0; i < s.len; i++

string from_file(char *path);

string create_str(size_t capacity);
bool destroy_str(string *s);
bool is_allocated_str(string s);

string clone_str(string s);
string slice_str(string s, size_t start, size_t end);

bool contains_str(string haystack, string needle);
bool contains_char(string haystack, char needle);

bool append_str(string *dest, string src);
bool append_char(string *dest, char needle);

int index_of_char(string haystack, char needle);
int index_of_str(string haystack, string needle);

bool str_eq(string a, string b);
bool is_null_str(string s);
bool is_empty_str(string s);
bool is_upper(char c);
bool is_lower(char c);

string to_upper_str(string s);
string to_lower_str(string s);

#endif