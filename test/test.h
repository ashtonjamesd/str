#ifndef test_h
#define test_h

#include <stdio.h>
#include <stdbool.h>

static struct {
    size_t ran;
    size_t failed;

    size_t assertions;
    size_t assertions_failed;
} runner = {
    .failed = 0,
    .ran = 0,
};

int conclude_test_runner() {
    printf("\ntest summary:\n");

    printf("  %zu test%s ran\n", runner.ran, runner.ran != 1 ? "s" : "");
    printf("  %zu test%s failed\n", runner.failed, runner.failed != 1 ? "s" : "");

    return (runner.failed > 0)? 1 : 0;
}

#define should(name) void name()

#define run_test(fn) do { \
    size_t prev_assertions_failed = runner.assertions_failed; \
    fn(); \
    runner.ran += 1; \
    \
    if (prev_assertions_failed != runner.assertions_failed) { \
        runner.failed += 1; \
        printf("test failed '%s'\n\n", #fn); \
    } \
} while (0); 

#define expect(expr) if (!(expr)) { \
    runner.assertions_failed += 1; \
    printf("assertion failed (%s:%d): '%s'\n", __FILE__, __LINE__, #expr); \
}

#define expect_not(expr) if ((expr)) { \
    runner.assertions_failed += 1; \
    printf("assertion failed (%s:%d): '%s'\n", __FILE__, __LINE__, #expr); \
}

#define expect_null(expr) expect((expr) == NULL)
#define expect_not_null(expr) expect((expr) != NULL)
#define expect_str_eq(a, b) expect(strcmp((a ? a : ""), (b ? b : "")) == 0)

#endif