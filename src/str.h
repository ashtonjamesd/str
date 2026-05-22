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

// constructs a new string instance
#define str(s)      make_str(s, sizeof(s) - 1)

// constructs a null string
#define null_str()  make_str(NULL, 0)

// constructs a string from another string
#define from_str(s) make_str(s.val, s.len)

// constructs an empty string
#define empty_str() make_str("", 0)

// macro for looping through strings
#define each_char_in(s, i) size_t i = 0; i < s.len; i++



/*
*  core construction and destruction functions
*/

// allocates a string on the heap
string create_str(size_t capacity);

// reads a file and allocates a new string on the heap, storing the file content
string create_str_from_file(char *path);

// deallocates a heap-allocated string
bool destroy_str(string *s);



/*
*  functions that allocate and return a new string on the heap
*/

// allocates a new string, copying the contents of 's'
string clone_str(string s);

// allocates a new string from a substring within 's'
string slice_str(string s, size_t start, size_t end);

// allocates a new string that is 's' converted to uppercase
string to_upper_str(string s);

// allocates a new string that is 's' converted to lowercase
string to_lower_str(string s);

// allocates a new string with leading and trailing whitespace removed
string trim_str(string s);

// allocates a new string with leading whitespace removed
string trim_left_str(string s);

// allocates a new string with trailing whitespace removed
string trim_right_str(string s);



/*
*  functions that append and may reallocate
*/

// appends a strings content to another, it may reallocate
bool append_str(string *dest, string src);

// appends a character to a string, it may reallocate
bool append_char(string *dest, char c);



/*
*  functions to retrieve information about strings
*/

// returns the index occurrence of a character or -1 if not found
int index_of_char(string haystack, char needle);

// returns the index occurrence of a string or -1 if not found
int index_of_str(string haystack, string needle);

// returns the character at the specified index or '\0' if out of bounds
char char_at(string s, size_t idx);



/*
*  string predicate functions
*/

// true if a string contains a substring of another string
bool contains_str(string haystack, string needle);

// true if a string contains a specific character
bool contains_char(string haystack, char needle);

// true if a string starts with a string
bool starts_with_str(string haystack, string s);

// true if a string starts with a character
bool starts_with_char(string haystack, char needle);

// true if a string ends with a string
bool ends_with_str(string haystack, string s);

// true if a string ends with a character
bool ends_with_char(string haystack, char needle);

// true if a string is equal to another string
bool str_eq(string a, string b);

// true if a string contains 'NULL'
bool is_null_str(string s);

// true if a string is allocated on the heap
bool is_allocated_str(string s);

// true if a string is ""
bool is_empty_str(string s);

// true if a character is an uppercase letter
bool is_upper(char c);

// true if a character is an lowercase letter
bool is_lower(char c);

#endif