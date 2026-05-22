# str

A small string library for C. It wraps a `char *` with a length and capacity, giving you a value type that knows its own size and can grow when heap-allocated.

## Quick start

Copy `src/str.h` and `src/str.c` into your project.

```c
#include "str.h"

int main() {
    // stack string (no allocation, no cleanup needed)
    string greeting = str("Hello, World!");
    printf("%s\n", greeting.val);  // Hello, World!
    printf("%zu\n", greeting.len); // 13

    // heap string (growable, must be destroyed)
    string buf = create_str(16);
    append_str(&buf, str("Hello"));
    append_str(&buf, str(", "));
    append_str(&buf, str("World!"));
    printf("%s\n", buf.val); // Hello, World!
    destroy_str(&buf);

    return 0;
}
```

## Stack vs heap strings

`str("...")` produces a string that points directly at the string literal. It has zero capacity and cannot be appended to, but it also requires no cleanup.

`create_str(n)` allocates `n` bytes on the heap. You can append to it and it will grow as needed. Call `destroy_str` when you're done.

`clone_str(s)` is a shorthand for allocating a new heap string and copying the contents of an existing one:

```c
string s = clone_str(str("foo"));
// ... use s ...
destroy_str(&s);
```

## API

### Construction and destruction

| Function | Description |
|---|---|
| `str("...")` | Create a stack string from a literal |
| `null_str()` | Create a null string |
| `empty_str()` | Create an empty string (`""`, length 0) |
| `create_str(cap)` | Allocate a heap string with the given capacity |
| `clone_str(s)` | Allocate a copy of `s` |
| `from_file(path)` | Read an entire file into a heap string |
| `destroy_str(&s)` | Free a heap string |

### Query

| Function | Description |
|---|---|
| `s.len` | Length of the string |
| `s.val` | The underlying `char *` |
| `str_eq(a, b)` | String equality |
| `is_null_str(s)` | True if `val` is NULL |
| `is_empty_str(s)` | True if length is 0 |
| `is_allocated_str(s)` | True if the string is heap-allocated |
| `char_at(s, i)` | Character at index, or `'\0'` if out of bounds |
| `contains_str(s, sub)` | Substring search |
| `contains_char(s, c)` | Character search |
| `index_of_str(s, sub)` | Index of first occurrence, or -1 |
| `index_of_char(s, c)` | Index of first occurrence, or -1 |

### Mutation (heap strings only)

| Function | Description |
|---|---|
| `append_str(&s, src)` | Append a string |
| `append_char(&s, c)` | Append a character |

### Transformation (returns a new heap string)

| Function | Description |
|---|---|
| `slice_str(s, start, end)` | Extract a substring |
| `to_upper_str(s)` | Convert to uppercase |
| `to_lower_str(s)` | Convert to lowercase |

### Iteration

```c
string s = str("abc");
for (each_char_in(s, i)) {
    putchar(s.val[i]);
}
```

## License

Public domain.