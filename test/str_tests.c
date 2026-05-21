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

should(convert_string_to_upper) {
    string s = str("Hello, World!");
    string upper = to_upper_str(s);

    expect_str_eq(upper.val, "HELLO, WORLD!");

    destroy_str(&upper);
}

should(convert_string_to_lower) {
    string s = str("Hello, World!");
    string lower = to_lower_str(s);

    expect_str_eq(lower.val, "hello, world!");

    destroy_str(&lower);
}

should(convert_null_string_to_upper) {
    string s = null_str();
    string upper = to_upper_str(s);

    expect_null(upper.val);
}

should(convert_null_string_to_lower) {
    string s = null_str();
    string lower = to_lower_str(s);

    expect_null(lower.val);
}

should(convert_empty_string_to_upper) {
    string s = str("");
    string upper = to_upper_str(s);

    expect_str_eq(upper.val, "");

    destroy_str(&upper);
}

should(detect_upper_chars) {
    expect(is_upper('A'));
    expect(is_upper('Z'));
    expect(is_upper('M'));
}

should(not_detect_non_upper_chars) {
    expect(!is_upper('a'));
    expect(!is_upper('z'));
    expect(!is_upper('5'));
    expect(!is_upper('!'));
}

should(read_empty_file) {
    string s = from_file("test/fixtures/empty.txt");

    expect(s.len == 0);
    expect_str_eq(s.val, "");

    destroy_str(&s);
}

should(to_upper_preserves_non_alpha) {
    string s = str("abc 123 !@#");
    string upper = to_upper_str(s);

    expect_str_eq(upper.val, "ABC 123 !@#");

    destroy_str(&upper);
}

should(to_lower_preserves_non_alpha) {
    string s = str("ABC 123 !@#");
    string lower = to_lower_str(s);

    expect_str_eq(lower.val, "abc 123 !@#");

    destroy_str(&lower);
}

should(to_upper_already_upper) {
    string s = str("HELLO");
    string upper = to_upper_str(s);

    expect_str_eq(upper.val, "HELLO");

    destroy_str(&upper);
}

should(to_lower_already_lower) {
    string s = str("hello");
    string lower = to_lower_str(s);

    expect_str_eq(lower.val, "hello");

    destroy_str(&lower);
}

should(not_slice_null_string) {
    string s = null_str();
    string sliced = slice_str(s, 0, 5);

    expect_null(sliced.val);
}

should(clone_an_empty_string) {
    string s = str("");
    string cloned = clone_str(s);

    expect(cloned.len == 0);
    expect(cloned.capacity == 1);
    expect_str_eq(cloned.val, "");

    destroy_str(&cloned);
}

should(be_equal_empty_strings) {
    expect(str_eq(empty_str(), empty_str()));
}

should(not_find_index_of_empty_needle) {
    string s = str("Hello, World!");
    expect(index_of_str(s, empty_str()) == -1);
}

should(not_find_index_of_longer_needle) {
    string s = str("Hi");
    expect(index_of_str(s, str("Hello, World!")) == -1);
}

should(find_index_of_string_at_start) {
    string s = str("Hello, World!");
    expect(index_of_str(s, str("Hello")) == 0);
}

should(find_index_of_string_at_end) {
    string s = str("Hello, World!");
    expect(index_of_str(s, str("World!")) == 7);
}

should(contain_empty_needle) {
    string haystack = str("Hello, World!");
    expect(contains_str(haystack, empty_str()));
}

should(not_contain_longer_needle) {
    string haystack = str("Hi");
    string needle = str("Hello, World!");
    expect(!contains_str(haystack, needle));
}

should(contain_string_at_start) {
    string haystack = str("Hello, World!");
    string needle = str("Hello");
    expect(contains_str(haystack, needle));
}

should(contain_string_at_end) {
    string haystack = str("Hello, World!");
    string needle = str("World!");
    expect(contains_str(haystack, needle));
}

should(contain_full_string) {
    string haystack = str("Hello, World!");
    string needle = str("Hello, World!");
    expect(contains_str(haystack, needle));
}

should(detect_lower_chars) {
    expect(is_lower('a'));
    expect(is_lower('z'));
    expect(is_lower('m'));
}

should(not_detect_non_lower_chars) {
    expect(!is_lower('A'));
    expect(!is_lower('Z'));
    expect(!is_lower('5'));
    expect(!is_lower('!'));
}

should(be_empty_str) {
    expect(is_empty_str(empty_str()));
    expect(is_empty_str(null_str()));
}

should(not_be_empty_str) {
    expect(!is_empty_str(str("Hello")));
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
    run_test(convert_string_to_upper);
    run_test(convert_string_to_lower);
    run_test(convert_null_string_to_upper);
    run_test(convert_null_string_to_lower);
    run_test(convert_empty_string_to_upper);
    run_test(read_empty_file);
    run_test(to_upper_preserves_non_alpha);
    run_test(to_lower_preserves_non_alpha);
    run_test(to_upper_already_upper);
    run_test(to_lower_already_lower);
    run_test(not_slice_null_string);
    run_test(clone_an_empty_string);
    run_test(be_equal_empty_strings);
    run_test(not_find_index_of_empty_needle);
    run_test(not_find_index_of_longer_needle);
    run_test(find_index_of_string_at_start);
    run_test(find_index_of_string_at_end);
    run_test(contain_empty_needle);
    run_test(not_contain_longer_needle);
    run_test(contain_string_at_start);
    run_test(contain_string_at_end);
    run_test(contain_full_string);
    run_test(detect_lower_chars);
    run_test(not_detect_non_lower_chars);
    run_test(detect_upper_chars);
    run_test(not_detect_non_upper_chars);
    run_test(be_empty_str);
    run_test(not_be_empty_str);

    return conclude_test_runner();
}