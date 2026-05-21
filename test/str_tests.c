#include "test.h"
#include "../src/str.h"

should(create_zero_capacity_string) {
    string s = create_str(0);

    expect(s.len == 0);
    expect(s.cap == 0);
    expect_str_eq(s.val, "");
}

should(append_on_non_allocated_string) {
    string s = str("Hello, World!");

    bool appended = append_str(&s, str("Oops!"));
    expect(!appended);
}

should(not_destroy_destroyed_string) {
    string s = create_str(200);
    
    bool destroyed = destroy_str(&s);
    expect(destroyed);

    bool destroyed_again = destroy_str(&s);
    expect(!destroyed_again);

    expect(s.cap == 0);
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

should(be_equal_string) {
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
    expect(s.cap == 14);

    destroy_str(&s);

    expect(s.len == 0);
    expect(s.cap == 0);
    expect_null(s.val);
}

should(create_and_destroy_string) {
    string s = create_str(10);

    expect(s.len == 0);
    expect(s.cap == 10);

    destroy_str(&s);

    expect(s.len == 0);
    expect(s.cap == 0);
    expect_null(s.val);
}

should(create_a_nullstr) {
    string s = null_str();

    expect(s.cap == 0);
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
    expect(s.cap == 0);
    expect_str_eq(s.val, "");
}

should(create_a_str) {
    string s = str("Hello, World!");

    expect(s.len == 13);
    expect(s.cap == 0);
    expect_str_eq(s.val, "Hello, World!");
}

int main() {
    run_test(create_and_destroy_string);
    run_test(append_to_string);
    run_test(create_a_str);
    run_test(create_an_empty_string);
    run_test(create_a_string_from_another_string);
    run_test(create_a_nullstr);
    run_test(be_equal_string);
    run_test(not_destroy_non_heap_allocated_string);
    run_test(not_destroy_destroyed_string);
    run_test(not_be_equal_to_a_null_string);
    run_test(append_on_non_allocated_string);
    run_test(create_zero_capacity_string);
    run_test(append_char_to_string);
    run_test(be_equal_to_another_null_string);
    
    return conclude_test_runner();
}