// MIT License

// Copyright © 2025 i-Sage

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the “Software”), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.




/*
SETTING ENVIRONMENTAL VARIABLES
- DEBUG=1 TRACE=1 ./example

BASIC TESTING MACROS:
- TEST_ASSERT(condition, message)                    - Basic assertion
- TEST_ASSERT_EQ(actual, expected, message)          - Equality with detailed output
- TEST_ASSERT_STR_EQ(actual, expected, message)      - String comparison
- TEST_ASSERT_NOT_NULL(ptr, message)                 - Null pointer check
- TEST_ASSERT_NULL(ptr, message)                     - Verify pointer is null
- RUN_TEST(test_func)                                - Run test and track results
- TEST_EXPECT_CRASH(code, message)                   - Test for expected crashes

ADVANCED TESTING MACROS:
- TEST_ASSERT_ARRAY_EQ(actual, expected, size, msg)  - Array comparison
- TEST_ASSERT_FLOAT_EQ(actual, expected, epsilon, msg) - Float comparison
- TEST_ASSERT_IN_RANGE(value, min, max, message)     - Range validation
- TEST_SETUP(code) / TEST_TEARDOWN(code)             - Test initialization/cleanup
- TEST_SKIP(condition, message)                      - Conditional test skipping
- TEST_FILE_EXISTS(filepath, message)                - File existence check
- TEST_BUFFER_OVERFLOW(buffer, size, write_size, msg) - Buffer overflow check

PERFORMANCE MACROS:
- BENCHMARK_START() / BENCHMARK_END(name)            - Performance measurement
- REPEAT_TEST(n, code)                               - Repeat test operations
- STRESS_TEST(iterations, code, message)             - Stress testing

MEMORY MACROS:
- MALLOC_COUNT_START()                               - Initialize memory tracking
- TRACK_MALLOC(ptr) / TRACK_FREE(ptr)               - Track allocations
- CHECK_MEMORY_LEAKS()                              - Check for leaks

CHECKING MACROS:
- CHECK(condition, msg)                              - Fatal assertion
- CHECK_PTR(ptr)                                     - Null pointer check (fatal)
- CHECK_BOUNDS(index, size, msg)                     - Array bounds check
- CHECK_ERRNO(call, msg)                             - System call error check
- CHECK_ALLOC(ptr, msg)                              - Memory allocation check
- ERROR_CHECK(call, expected)                        - Function return check

DEBUGGING MACROS:
- DEBUG_PRINT(fmt, ...)                              - Conditional debug output
- TRACE_FUNCTION()                                   - Function entry tracing
- LOG_VAR(var)                                       - Variable value logging
- WARN(condition, msg)                               - Non-fatal warnings

UTILITY MACROS:
- RANDOM_INT(min, max)                               - Random integer generation
- RANDOM_FLOAT()                                     - Random float generation
- PRINT_TEST_SUMMARY()                               - Test results summary
- ASSERT_UNREACHABLE(msg)                            - Mark unreachable code
- STATIC_ASSERT(condition, msg)                      - Compile-time assertion
*/


#pragma once

#include <stdio.h>
#include <error.h>  
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>


/*
? TEST FUNCTION STRUCTURE
* A test function has the structure:
*
*      int TEST_FUNCTION_NAME(void) {
*
*           TEST_SETUP({
*               /// Initialize test data here
*           });

*           /// Test body goes here

*           return 1
*      }
*/


/*
? RUNNING A TEST
*      int main() {
*           RUN_TEST(TEST_FUNCTION_NAME);
*           PRINT_TEST_SUMMARY();
*      }
*/



/*
? compherensive tests examples
In your test file
int test_advanced_features() {
    TEST_SETUP({
        Initialize test data
        srand(time(NULL));
    });
    
    Array testing
    int expected[] = {1, 2, 3, 4, 5};
    int actual[] = {1, 2, 3, 4, 5};
    TEST_ASSERT_ARRAY_EQ(actual, expected, 5, "Arrays should match");
    
    Float comparison
    TEST_ASSERT_FLOAT_EQ(3.14159, 3.14160, 0.001, "Pi approximation");
    
    Range testing
    int random_val = RANDOM_INT(1, 100);
    TEST_ASSERT_IN_RANGE(random_val, 1, 100, "Random value in range");
    
    Stress testing
    STRESS_TEST(1000, (RANDOM_INT(1, 6) >= 1), "Random dice roll");
    
    TEST_TEARDOWN({
        Cleanup
    });
    
    return 1;
}

Memory leak testing
int test_memory() {
    MALLOC_COUNT_START();
    
    char *buf = malloc(100);
    TRACK_MALLOC(buf);
    
    free(buf);
    TRACK_FREE(buf);
    
    CHECK_MEMORY_LEAKS();
    return 1;
}
*/



static int tests_passed = 0;
static int tests_failed = 0;
static int total_tests  = 0;


typedef enum
{
    /// ? Err values
    ERR        = -1,
    ERR_0      =  0,
    ERR_1      =  1,
    ERR_2      =  2,
    ERR_3      =  3,
    ERR_4      =  4,
    ERR_5      =  5,

    /// ? Expected values
    EXPECTED   =  0,
    EXPECTED_1 =  1,
    EXPECTED_2 =  2,
    EXPECTED_3 =  3,
    EXPECTED_4 =  4,
    EXPECTED_5 =  5,
} err_type_t;


#define TEST_ASSERT(condition, message)                                                                \
    do {                                                                                               \
        if (!(condition)) {                                                                            \
            fprintf(stderr, "FAIL: %s\n", message);                                                    \
            return 0;                                                                                  \
        } else {                                                                                       \
            printf("PASS: %s\n", message);                                                             \
        }                                                                                              \
    } while(0)



#define RUN_TEST(test_func)                                                                            \
    do {                                                                                               \
        printf("Running %s...\n", #test_func);                                                         \
        if (test_func()) {                                                                             \
            printf("✓ %s passed\n\n", #test_func);                                                     \
            tests_passed++;                                                                            \
        } else {                                                                                       \
            printf("✗ %s failed\n\n", #test_func);                                                     \
            tests_failed++;                                                                            \
        }                                                                                              \
        total_tests++;                                                                                 \
    } while(0)



#define TEST_EXPECT_CRASH(test_code, message)                                                          \
    do {                                                                                               \
        pid_t pid = fork();                                                                            \
        if (pid == 0) {                                                                                \
            test_code;                                                                                 \
            exit(0);                                                                                   \
        } else if (pid > 0) {                                                                          \
            int status;                                                                                \
            waitpid(pid, &status, 0);                                                                  \
            if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {                                       \
                fprintf(stderr, "FAIL: %s (expected crash but didn't crash)\n", message);              \
                return 0;                                                                              \
            } else {                                                                                   \
                printf("PASS: %s (crashed as expected)\n", message);                                   \
            }                                                                                          \
        } else {                                                                                       \
            fprintf(stderr, "FAIL: fork() failed for crash test\n");                                   \
            return 0;                                                                                  \
        }                                                                                              \
    } while(0)


#define CHECK_PTR(ptr)                                                                                 \
    do {                                                                                               \
        if ((ptr) == NULL) {                                                                           \
            fprintf(stderr, "ERROR: NULL POINTER DETECTED: %s AT %s:%d\n", #ptr, __FILE__, __LINE__);  \
            exit(EXIT_FAILURE);                                                                        \
        }                                                                                              \
} while(0)   



#define CHECK(condition, msg)                                                                          \
    do                                                                                                 \
    {                                                                                                  \
        if (!(condition))                                                                              \
        {                                                                                              \
            fprintf(stderr, "ERROR: %s (%s:%d)\n", msg, __FILE__, __LINE__);                           \
            exit(EXIT_FAILURE);                                                                        \
        }                                                                                              \
} while (0)


#define ERROR_CHECK(call, expected)                                                                    \
    do {                                                                                               \
        int _ret = (call);                                                                             \
        if (_ret != (expected)) {                                                                      \
            fprintf(stderr, "ERROR: call '%s' returned %d, expected %d\n", #call, _ret, expected);     \
            exit(EXIT_FAILURE);                                                                        \
        }                                                                                              \
} while(0)


#define TEST_ASSERT_EQ(actual, expected, message)                                                           \
    do {                                                                                                    \
        if ((actual) != (expected)) {                                                                       \
            fprintf(stderr, "FAIL: %s - Expected: %d, Got: %d\n", message, (int)(expected), (int)(actual)); \
            return 0;                                                                                       \
        } else {                                                                                            \
            printf("PASS: %s\n", message);                                                                  \
        }                                                                                                   \
    } while(0)

#define TEST_ASSERT_STR_EQ(actual, expected, message)                                                       \
    do {                                                                                                    \
        if (strcmp((actual), (expected)) != 0) {                                                            \
            fprintf(stderr, "FAIL: %s - Expected: \"%s\", Got: \"%s\"\n", message, expected, actual);       \
            return 0;                                                                                       \
        } else {                                                                                            \
            printf("PASS: %s\n", message);                                                                  \
        }                                                                                                   \
    } while(0)

#define TEST_ASSERT_NOT_NULL(ptr, message)                                                                  \
    do {                                                                                                    \
        if ((ptr) == NULL) {                                                                                \
            fprintf(stderr, "FAIL: %s - Pointer is NULL\n", message);                                       \
            return 0;                                                                                       \
        } else {                                                                                            \
            printf("PASS: %s\n", message);                                                                  \
        }                                                                                                   \
    } while(0)

#define TEST_ASSERT_NULL(ptr, message)                                                                      \
    do {                                                                                                    \
        if ((ptr) != NULL) {                                                                                \
            fprintf(stderr, "FAIL: %s - Expected NULL pointer\n", message);                                 \
            return 0;                                                                                       \
        } else {                                                                                            \
            printf("PASS: %s\n", message);                                                                  \
        }                                                                                                   \
    } while(0)

#define BENCHMARK_START()                                                                                   \
    clock_t _start_time = clock()

#define BENCHMARK_END(operation_name)                                                                       \
    do {                                                                                                    \
        clock_t _end_time = clock();                                                                        \
        double _cpu_time = ((double)(_end_time - _start_time)) / CLOCKS_PER_SEC;                            \
        printf("BENCHMARK: %s took %f seconds\n", operation_name, _cpu_time);                               \
    } while(0)

#define PRINT_TEST_SUMMARY()                                                                                \
    do {                                                                                                    \
        printf("\n=== TEST SUMMARY ===\n");                                                                 \
        printf("Total tests: %d\n", total_tests);                                                           \
        printf("Passed: %d\n", tests_passed);                                                               \
        printf("Failed: %d\n", tests_failed);                                                               \
        printf("Success rate: %.1f%%\n", total_tests > 0 ? (tests_passed * 100.0) / total_tests : 0.0);     \
        printf("==================\n");                                                                     \
    } while(0)


#define CHECK_BOUNDS(index, size, msg)                                                                      \
    do {                                                                                                    \
        if ((index) < 0 || (index) >= (size)) {                                                             \
            fprintf(stderr, "ERROR: BOUNDS CHECK FAILED: %s - index %d out of bounds [0, %d) at %s:%d\n",   \
                    msg, (int)(index), (int)(size), __FILE__, __LINE__);                                    \
            exit(EXIT_FAILURE);                                                                             \
        }                                                                                                   \
    } while(0)

#define CHECK_ERRNO(call, msg)                                                                              \
    do {                                                                                                    \
        if ((call) == -1) {                                                                                 \
            fprintf(stderr, "ERROR: %s failed: %s (%s:%d)\n", msg, strerror(errno), __FILE__, __LINE__);    \
            exit(EXIT_FAILURE);                                                                             \
        }                                                                                                   \
    } while(0)

#define CHECK_ALLOC(ptr, msg)                                                                               \
    do {                                                                                                    \
        if ((ptr) == NULL) {                                                                                \
            fprintf(stderr, "ERROR: MEMORY ALLOCATION FAILED: %s at %s:%d\n", msg, __FILE__, __LINE__);     \
            exit(EXIT_FAILURE);                                                                             \
        }                                                                                                   \
    } while(0)

#define WARN(condition, msg)                                                                                \
    do {                                                                                                    \
        if (!(condition)) {                                                                                 \
            fprintf(stderr, "WARNING: %s (%s:%d)\n", msg, __FILE__, __LINE__);                              \
        }                                                                                                   \
    } while(0)

#define DEBUG_PRINT(fmt, ...)                                                                               \
    do {                                                                                                    \
        if (getenv("DEBUG")) {                                                                              \
            fprintf(stderr, "DEBUG (%s:%d): " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__);                 \
        }                                                                                                   \
    } while(0)

#define ASSERT_UNREACHABLE(msg)                                                                             \
    do {                                                                                                    \
        fprintf(stderr, "ERROR: UNREACHABLE CODE REACHED: %s at %s:%d\n", msg, __FILE__, __LINE__);         \
        exit(EXIT_FAILURE);                                                                                 \
    } while(0)

#define STATIC_ASSERT(condition, msg) typedef char static_assertion_##__LINE__[(condition) ? 1 : -1]

// Test setup and teardown
#define TEST_SETUP(setup_code)                                                                             \
    do {                                                                                                   \
        printf("Setting up test...\n");                                                                    \
        setup_code;                                                                                        \
    } while(0)

#define TEST_TEARDOWN(teardown_code)                                                                       \
    do {                                                                                                   \
        printf("Tearing down test...\n");                                                                  \
        teardown_code;                                                                                     \
    } while(0)

// Array testing
#define TEST_ASSERT_ARRAY_EQ(actual, expected, size, message)                                              \
    do {                                                                                                   \
        int _arrays_equal = 1;                                                                             \
        for (int _i = 0; _i < (size); _i++) {                                                              \
            if ((actual)[_i] != (expected)[_i]) {                                                          \
                _arrays_equal = 0;                                                                         \
                break;                                                                                     \
            }                                                                                              \
        }                                                                                                  \
        if (!_arrays_equal) {                                                                              \
            fprintf(stderr, "FAIL: %s - Arrays differ\n", message);                                        \
            return 0;                                                                                      \
        } else {                                                                                           \
            printf("PASS: %s\n", message);                                                                 \
        }                                                                                                  \
    } while(0)

// Floating point comparisons
#define TEST_ASSERT_FLOAT_EQ(actual, expected, epsilon, message)                                           \
    do {                                                                                                   \
        double _diff = (actual) - (expected);                                                              \
        if (_diff < 0) _diff = -_diff;                                                                     \
        if (_diff > (epsilon)) {                                                                           \
            fprintf(stderr, "FAIL: %s - Expected: %f, Got: %f (diff: %f)\n",                               \
                    message, (double)(expected), (double)(actual), _diff);                                 \
            return 0;                                                                                      \
        } else {                                                                                           \
            printf("PASS: %s\n", message);                                                                 \
        }                                                                                                  \
    } while(0)

// Range testing
#define TEST_ASSERT_IN_RANGE(value, min, max, message)                                                     \
    do {                                                                                                   \
        if ((value) < (min) || (value) > (max)) {                                                          \
            fprintf(stderr, "FAIL: %s - Value %d not in range [%d, %d]\n",                                 \
                    message, (int)(value), (int)(min), (int)(max));                                        \
            return 0;                                                                                      \
        } else {                                                                                           \
            printf("PASS: %s\n", message);                                                                 \
        }                                                                                                  \
    } while(0)

// Skip test conditionally
#define TEST_SKIP(condition, message)                                                                      \
    do {                                                                                                   \
        if (condition) {                                                                                   \
            printf("SKIP: %s\n", message);                                                                 \
            return 1;                                                                                      \
        }                                                                                                  \
    } while(0)

// Memory leak detection helpers
#define MALLOC_COUNT_START()                                                                               \
    static int _malloc_count = 0;                                                                          \
    static int _free_count =   0

#define TRACK_MALLOC(ptr)                                                                                  \
    do {                                                                                                   \
        if (ptr) _malloc_count++;                                                                          \
    } while(0)

#define TRACK_FREE(ptr)                                                                                    \
    do {                                                                                                   \
        if (ptr) _free_count++;                                                                            \
    } while(0)

#define CHECK_MEMORY_LEAKS()                                                                               \
    do {                                                                                                   \
        if (_malloc_count != _free_count) {                                                                \
            fprintf(stderr, "MEMORY LEAK: %d mallocs, %d frees\n", _malloc_count, _free_count);            \
        } else {                                                                                           \
            printf("MEMORY: All allocations freed (%d mallocs, %d frees)\n", _malloc_count, _free_count);  \
        }                                                                                                  \
    } while(0)

// Performance and profiling
#define REPEAT_TEST(n, test_code)                                                                          \
    do {                                                                                                   \
        printf("Running test %d times...\n", n);                                                           \
        for (int _rep = 0; _rep < (n); _rep++) {                                                           \
            test_code;                                                                                     \
        }                                                                                                  \
    } while(0)

// File operations testing
#define TEST_FILE_EXISTS(filepath, message)                                                                \
    do {                                                                                                   \
        FILE *_f = fopen(filepath, "r");                                                                   \
        if (_f == NULL) {                                                                                  \
            fprintf(stderr, "FAIL: %s - File '%s' does not exist\n", message, filepath);                   \
            return 0;                                                                                      \
        } else {                                                                                           \
            fclose(_f);                                                                                    \
            printf("PASS: %s\n", message);                                                                 \
        }                                                                                                  \
    } while(0)

// Random testing helpers
#define RANDOM_INT(min, max) ((rand() % ((max) - (min) + 1)) + (min))
#define RANDOM_FLOAT() ((float)rand() / RAND_MAX)

// Stress testing
#define STRESS_TEST(iterations, test_code, message)                                                        \
    do {                                                                                                   \
        printf("STRESS TEST: %s (%d iterations)\n", message, iterations);                                  \
        int _failures = 0;                                                                                 \
        for (int _i = 0; _i < (iterations); _i++) {                                                        \
            if (!(test_code)) {                                                                            \
                _failures++;                                                                               \
            }                                                                                              \
        }                                                                                                  \
        if (_failures > 0) {                                                                               \
            fprintf(stderr, "STRESS TEST FAIL: %d/%d iterations failed\n", _failures, iterations);         \
            return 0;                                                                                      \
        } else {                                                                                           \
            printf("STRESS TEST PASS: All %d iterations passed\n", iterations);                            \
        }                                                                                                  \
    } while(0)

// Enhanced debugging
#define TRACE_FUNCTION()                                                                                   \
    do {                                                                                                   \
        if (getenv("TRACE")) {                                                                             \
            fprintf(stderr, "TRACE: Entering %s (%s:%d)\n", __func__, __FILE__, __LINE__);                 \
        }                                                                                                  \
    } while(0)

#define LOG_VAR(var)                                                                                       \
    do {                                                                                                   \
        if (getenv("DEBUG")) {                                                                             \
            fprintf(stderr, "DEBUG: %s = %d (%s:%d)\n", #var, (int)(var), __FILE__, __LINE__);             \
        }                                                                                                  \
    } while(0)

// Buffer overflow protection testing
#define TEST_BUFFER_OVERFLOW(buffer, size, write_size, message)                                            \
    do {                                                                                                   \
        if ((write_size) > (size)) {                                                                       \
            fprintf(stderr, "FAIL: %s - Buffer overflow detected (writing %d bytes to %d byte buffer)\n",  \
                    message, (int)(write_size), (int)(size));                                              \
            return 0;                                                                                      \
        } else {                                                                                           \
            printf("PASS: %s\n", message);                                                                 \
        }                                                                                                  \
    } while(0)