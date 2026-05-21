#include "test.h"
#include "../src/str.h"

void test_append_to_string() {
    String s = create_str(14);
    append_str(&s, str("Hello, World!"));

    expect(s.len == 13);
    expect(s.cap == 14);

    destroy_str(&s);

    expect(s.len == 0);
    expect(s.cap == 0);
    expect_null(s.val);
}

void test_create_and_destroy_string() {
    String s = create_str(10);

    expect(s.len == 0);
    expect(s.cap == 10);

    destroy_str(&s);

    expect(s.len == 0);
    expect(s.cap == 0);
    expect_null(s.val);
}

void test_nullstr() {
    String s = nullstr();

    expect(s.cap == 0);
    expect(s.len == 0);
    expect_null(s.val);
}

void test_str_from() {
    String s1 = str("Hello, World!");
    String s2 = str_from(s1);

    expect_str_eq(s1.val, s2.val);
}

void test_str_empty() {
    String s = str_empty();

    expect(s.len == 0);
    expect(s.cap == 0);
    expect_str_eq(s.val, "");
}

void test_str() {
    String s = str("Hello, World!");

    expect(s.len == 13);
    expect(s.cap == 0);
    expect_str_eq(s.val, "Hello, World!");
}

int main() {
    run_test(test_create_and_destroy_string);
    run_test(test_append_to_string);
    run_test(test_str);
    run_test(test_str_empty);
    run_test(test_str_from);
    run_test(test_nullstr);

    return conclude_test_runner();
}