#include "test.h"
#include "../src/str.h"

should(create_a_full_slice) {
    string s = str("Hello, World!");
    string sliced = slice_str(s, 0, 13);

    expect_str_eq(sliced.val, "Hello, World!");
}

should(slice_single_char) {
    string s = str("Hello, World!");
    string sliced = slice_str(s, 0, 1);

    expect_str_eq(sliced.val, "H");
}

should(create_empty_slice_if_end_is_too_large) {
    string s = str("Hello, World!");
    string sliced = slice_str(s, 0, 500);

    expect_null(sliced.val);
}

should(create_empty_slice_when_start_is_same_as_end) {
    string s = str("Hello, World!");
    string sliced = slice_str(s, 5, 5);

    expect_str_eq(sliced.val, "");
}

should(not_create_slice_when_start_is_larger_than_end) {
    string s = str("Hello, World!");
    string sliced = slice_str(s, 10, 9);

    expect_null(sliced.val);
}

should(create_a_slice) {
    string s = str("Hello, World!");
    string sliced = slice_str(s, 7, 12);

    expect_not_null(sliced.val);
    expect_str_eq(sliced.val, "World");
}

should(not_find_index_of_char) {
    string s1 = str("Hello, World!");

    int index = index_of_char(s1, 'X');
    expect(index == -1);
}

should(find_index_of_char) {
    string s1 = str("Hello, World!");

    int index = index_of_char(s1, ',');
    expect(index == 5);
}

should(not_find_index_of_string) {
    string s1 = str("Hello, World!");
    string s2 = str("x");

    int index = index_of_str(s1, s2);
    expect(index == -1);
}

should(find_index_of_string) {
    string s1 = str("Hello, World!");
    string s2 = str("Wor");

    int index = index_of_str(s1, s2);
    expect(index == 7);
}

should(not_be_an_allocated_string) {
    expect(
        !is_allocated_str(str("Hello, World!"))
    )
}

should(be_an_allocated_string) {
    expect(
        is_allocated_str(clone_str(str("Hello, World!")))
    )
}

should(not_contain_chars) {
    string haystack = str("Hello, World!");

    bool contains = contains_char(haystack, 'X');
    expect(!contains);

    contains = contains_char(haystack, 'Y');
    expect(!contains);

    contains = contains_char(haystack, 'Z');
    expect(!contains);
}

should(contain_chars) {
    string haystack = str("Hello, World!");

    bool contains = contains_char(haystack, 'H');
    expect(contains);

    contains = contains_char(haystack, ' ');
    expect(contains);

    contains = contains_char(haystack, '!');
    expect(contains);

    contains = contains_char(haystack, 'l');
    expect(contains);

    contains = contains_char(haystack, ',');
    expect(contains);
}

should(contain_another_string) {
    string haystack = str("Hello, World!");
    string needle = str("lo, Wor");

    bool contains = contains_str(haystack, needle);
    expect(contains);
}

should(clone_a_null_string) {
    string s = null_str();
    string cloned = clone_str(s);

    expect(s.capacity == 0);
    expect(s.len == 0);
    expect_null(s.val);

    bool destroyed = destroy_str(&cloned);
    expect(destroyed);
}

should(clone_a_heap_allocated_string) {
    string s = create_str(13);
    append_str(&s, str("Hello, World!"));

    string cloned = clone_str(s);

    expect_str_eq(s.val, cloned.val);
    expect(s.val != cloned.val);

    bool destroyed = destroy_str(&cloned);
    expect(destroyed);

    destroyed = destroy_str(&s);
    expect(destroyed);
}

should(clone_a_non_heap_allocated_string) {
    string s = str("Hello, World!");
    string cloned = clone_str(s);

    expect(cloned.len == 13);
    expect(cloned.capacity == 14);
    expect_str_eq(s.val, cloned.val);

    bool destroyed = destroy_str(&cloned);
    expect(destroyed);
}

should(not_append_empty_string) {
    string s = create_str(3);

    bool appended = append_str(&s, str("123"));
    expect(appended);

    appended = append_str(&s, empty_str());
    expect(appended);

    expect_str_eq(s.val, (str("123")).val);

    bool destroyed = destroy_str(&s);
    expect(destroyed);
}

should(create_zero_capacity_string) {
    string s = create_str(0);

    expect(s.len == 0);
    expect(s.capacity == 0);
    expect_str_eq(s.val, "");
}

should(not_append_on_non_allocated_string) {
    string s = str("Hello, World!");

    bool appended = append_str(&s, str("Oops!"));
    expect(!appended);
}

should(not_append_char_on_non_allocated_string) {
    string s = str("Hello, World!");

    bool appended = append_char(&s, 'a');
    expect(!appended);
}

should(not_destroy_destroyed_string) {
    string s = create_str(200);
    
    bool destroyed = destroy_str(&s);
    expect(destroyed);

    bool destroyed_again = destroy_str(&s);
    expect(!destroyed_again);

    expect(s.capacity == 0);
    expect(s.len == 0);
    expect_null(s.val);
}

should(not_destroy_non_heap_allocated_string) {
    string s1 = str("Hello, World!");
    expect(!destroy_str(&s1));

    string s2 = empty_str();
    expect(!destroy_str(&s2));

    string s3 = null_str();
    expect(!destroy_str(&s3));

    string s4 = from_str(s1);
    expect(!destroy_str(&s4));
}

should(append_multiple_strings) {
    string s = create_str(1);

    bool appended = append_str(&s, str("Hello, World!"));
    expect(appended);

    expect(s.len == 13);

    appended = append_str(&s, str("Hello, World!"));
    expect(appended);
    expect(s.len == 26);

    appended = append_str(&s, str("Hello, World!"));
    expect(appended);
    expect(s.len == 39);

    bool destroyed = destroy_str(&s);
    expect(destroyed);

    expect(s.len == 0);
    expect(s.capacity == 0);
    expect_null(s.val);
}

should(be_equal_to_another_null_string) {
    string s1 = null_str();
    string s2 = null_str();

    expect(str_eq(s1, s2));
}

should(not_be_equal_to_a_null_string) {
    string s1 = create_str(14);
    append_str(&s1, str("Hello, World!"));

    string s2 = null_str();

    expect(!str_eq(s1, s2));
}

should(not_be_equal_strings) {
    string s1 = create_str(3);
    append_str(&s1, str("foo"));

    string s2 = create_str(3);
    append_str(&s2, str("bar"));

    expect(!str_eq(s1, s2));
}

should(be_equal_strings) {
    string s1 = create_str(14);
    append_str(&s1, str("Hello, World!"));

    string s2 = create_str(14);
    append_str(&s2, str("Hello, World!"));

    expect(str_eq(s1, s2));
}

should(append_char_to_string) {
    string s = create_str(5);
    bool appended = append_str(&s, str("1234"));
    expect(appended);

    appended = append_char(&s, '5');
    expect(appended);

    expect_str_eq(s.val, (str("12345")).val);

    string s2 = create_str(1);
    appended = append_char(&s2, 'a');
    expect(appended);

    expect_str_eq(s2.val, (str("a")).val);
}

should(append_to_string) {
    string s = create_str(14);

    bool appended = append_str(&s, str("Hello, World!"));
    expect(appended);

    expect(s.len == 13);
    expect(s.capacity == 14);

    bool destroyed = destroy_str(&s);
    expect(destroyed);

    expect(s.len == 0);
    expect(s.capacity == 0);
    expect_null(s.val);
}

should(create_and_destroy_string) {
    string s = create_str(10);

    expect(s.len == 0);
    expect(s.capacity == 10);

    bool destroyed = destroy_str(&s);
    expect(destroyed);

    expect(s.len == 0);
    expect(s.capacity == 0);
    expect_null(s.val);
}

should(create_a_null_string) {
    string s = null_str();

    expect(s.capacity == 0);
    expect(s.len == 0);
    expect_null(s.val);
}

should(create_a_string_from_another_string) {
    string s1 = str("Hello, World!");
    string s2 = from_str(s1);

    expect_str_eq(s1.val, s2.val);
}

should(create_an_empty_string) {
    string s = empty_str();

    expect(s.len == 0);
    expect(s.capacity == 0);
    expect_str_eq(s.val, "");
}

should(read_string_from_file) {
    string s = from_file("test/fixtures/hello.txt");

    expect(s.len == 13);
    expect(s.capacity == 14);
    expect_str_eq(s.val, "Hello, World!");

    bool destroyed = destroy_str(&s);
    expect(destroyed);
}

should(return_null_string_from_nonexistent_file) {
    string s = from_file("test/fixtures/nonexistent.txt");

    expect(s.len == 0);
    expect(s.capacity == 0);
    expect_null(s.val);
}

should(create_a_string) {
    string s = str("Hello, World!");

    expect(s.len == 13);
    expect(s.capacity == 0);
    expect_str_eq(s.val, "Hello, World!");
}

int main() {
    run_test(create_and_destroy_string);
    run_test(append_to_string);
    run_test(create_a_string);
    run_test(create_an_empty_string);
    run_test(create_a_string_from_another_string);
    run_test(create_a_null_string);
    run_test(be_equal_strings);
    run_test(not_be_equal_strings);
    run_test(not_destroy_non_heap_allocated_string);
    run_test(not_destroy_destroyed_string);
    run_test(not_be_equal_to_a_null_string);
    run_test(not_append_char_on_non_allocated_string);
    run_test(not_append_on_non_allocated_string);
    run_test(create_zero_capacity_string);
    run_test(append_char_to_string);
    run_test(be_equal_to_another_null_string);
    run_test(append_multiple_strings);
    run_test(not_append_empty_string);
    run_test(read_string_from_file);
    run_test(return_null_string_from_nonexistent_file);
    run_test(clone_a_non_heap_allocated_string);
    run_test(clone_a_heap_allocated_string);
    run_test(clone_a_null_string);
    run_test(contain_another_string);
    run_test(contain_chars);
    run_test(not_contain_chars);
    run_test(be_an_allocated_string);
    run_test(not_be_an_allocated_string);
    run_test(find_index_of_string);
    run_test(not_find_index_of_string);
    run_test(find_index_of_char);
    run_test(not_find_index_of_char);
    run_test(create_a_slice);
    run_test(not_create_slice_when_start_is_larger_than_end);
    run_test(create_empty_slice_when_start_is_same_as_end);
    run_test(create_empty_slice_if_end_is_too_large);
    run_test(slice_single_char);
    run_test(create_a_full_slice);

    return conclude_test_runner();
}