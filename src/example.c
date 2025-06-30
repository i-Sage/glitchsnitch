#include "glitchsnitch.h"
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <time.h>

/// !=======================================================================================================================
/// !                                                    EXAMPLE FUNCTIONS
/// !=======================================================================================================================

int multiply(int a, int b) {
    return a * b;
}

double calculate_pi_approximation() {
    return 3.14159;
}

void copy_array(int *dest, int *src, int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = src[i];
    }
}

char* allocate_buffer(size_t size) {
    return malloc(size);
}

void deallocate_buffer(char *buffer) {
    free(buffer);
}

int divide_by_zero() {
    int x = 10;
    int y = 0;
    CHECK(y != 0, "Division by zero");
    return x / y;
}

void access_null_pointer() {
    char *ptr = NULL;
    CHECK_PTR(ptr);
    *ptr = 'x';
}

int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n-1) + fibonacci(n-2);
}

void write_to_file(const char *filename) {
    FILE *f = fopen(filename, "w");
    if (f) {
        fprintf(f, "Test content\n");
        fclose(f);
    }
}

/// !=======================================================================================================================
/// !                                                       TEST EXAMPLES
/// !=======================================================================================================================

// Basic assertion examples
int test_basic_assertions() {
    TRACE_FUNCTION();
    
    // Basic condition check
    TEST_ASSERT(5 > 3, "Five is greater than three");
    
    // Equality check with detailed output
    TEST_ASSERT_EQ(multiply(4, 5), 20, "4 * 5 should equal 20");
    
    // String comparison
    char greeting[] = "Hello";
    TEST_ASSERT_STR_EQ(greeting, "Hello", "Greeting should be 'Hello'");
    
    // Null pointer checks
    char *valid_ptr = "test";
    char *null_ptr = NULL;
    TEST_ASSERT_NOT_NULL(valid_ptr, "Valid pointer should not be null");
    TEST_ASSERT_NULL(null_ptr, "Null pointer should be null");
    
    return 1;
}

// Array testing example
int test_array_operations() {
    TRACE_FUNCTION();
    
    int source[] = {1, 2, 3, 4, 5};
    int destination[5] = {0};
    int expected[] = {1, 2, 3, 4, 5};
    
    copy_array(destination, source, 5);
    
    TEST_ASSERT_ARRAY_EQ(destination, expected, 5, "Array copy should match expected values");
    
    return 1;
}

// Floating point comparison example
int test_floating_point() {
    TRACE_FUNCTION();
    
    double pi_approx = calculate_pi_approximation();
    TEST_ASSERT_FLOAT_EQ(pi_approx, 3.14159, 0.00001, "Pi approximation should be close to 3.14159");
    
    // Test with larger epsilon
    TEST_ASSERT_FLOAT_EQ(pi_approx, 3.14, 0.01, "Pi approximation should be close to 3.14 (loose tolerance)");
    
    return 1;
}

// Range testing example
int test_range_checks() {
    TRACE_FUNCTION();
    
    int value = 50;
    TEST_ASSERT_IN_RANGE(value, 1, 100, "Value should be between 1 and 100");
    
    // Test with random values
    srand(time(NULL));
    int random_val = RANDOM_INT(10, 20);
    LOG_VAR(random_val);
    TEST_ASSERT_IN_RANGE(random_val, 10, 20, "Random value should be in specified range");
    
    return 1;
}

// Crash testing examples
int test_crash_scenarios() {
    TRACE_FUNCTION();
    
    // Test expected crash from division by zero check
    TEST_EXPECT_CRASH({divide_by_zero();}, "Division by zero should crash");
    
    // Test expected crash from null pointer access
    TEST_EXPECT_CRASH({access_null_pointer();}, "Null pointer access should crash");
    
    return 1;
}

// Memory management testing
int test_memory_management() {
    TRACE_FUNCTION();
    MALLOC_COUNT_START();
    
    // Allocate some memory
    char *buffer1 = allocate_buffer(100);
    TRACK_MALLOC(buffer1);
    CHECK_ALLOC(buffer1, "Buffer allocation");
    
    char *buffer2 = allocate_buffer(200);
    TRACK_MALLOC(buffer2);
    CHECK_ALLOC(buffer2, "Second buffer allocation");
    
    // Use the buffers
    strcpy(buffer1, "Hello, World!");
    TEST_ASSERT_STR_EQ(buffer1, "Hello, World!", "Buffer content should match");
    
    // Free the memory
    deallocate_buffer(buffer1);
    TRACK_FREE(buffer1);
    deallocate_buffer(buffer2);
    TRACK_FREE(buffer2);
    
    CHECK_MEMORY_LEAKS();
    
    return 1;
}

// File operations testing
int test_file_operations() {
    TRACE_FUNCTION();
    
    const char *test_file = "/tmp/test_file.txt";
    
    // Create a test file
    write_to_file(test_file);
    
    // Test file existence
    TEST_FILE_EXISTS(test_file, "Test file should exist after creation");
    
    // Clean up
    remove(test_file);
    
    return 1;
}

// Performance and benchmarking
int test_performance() {
    TRACE_FUNCTION();
    
    // Simple benchmark
    BENCHMARK_START();
    int result = fibonacci(30);
    BENCHMARK_END("Fibonacci calculation");
    
    LOG_VAR(result);
    TEST_ASSERT(result > 0, "Fibonacci result should be positive");
    
    return 1;
}

// Stress testing example
int test_stress_scenarios() {
    TRACE_FUNCTION();
    
    // Stress test with repeated operations
    STRESS_TEST(1000, (multiply(RANDOM_INT(1, 100), RANDOM_INT(1, 100)) > 0), 
                "Multiplication of positive numbers should always be positive");
    
    // Repeat test multiple times
    REPEAT_TEST(5, {
        int a = RANDOM_INT(1, 10);
        int b = RANDOM_INT(1, 10);
        int product = multiply(a, b);
        if (product != a * b) {
            fprintf(stderr, "Multiplication failed: %d * %d != %d\n", a, b, product);
        }
    });
    
    return 1;
}

// Buffer overflow testing
int test_buffer_security() {
    TRACE_FUNCTION();
    
    char buffer[10];
    int buffer_size = sizeof(buffer);
    
    // Safe write
    TEST_BUFFER_OVERFLOW(buffer, buffer_size, 5, "Writing 5 bytes to 10-byte buffer should be safe");
    
    // This would fail the test (commented out to avoid failure)
    // TEST_BUFFER_OVERFLOW(buffer, buffer_size, 15, "Writing 15 bytes to 10-byte buffer should fail");
    
    return 1;
}

// Conditional testing
int test_conditional_features() {
    TRACE_FUNCTION();
    
    // Skip test based on condition
    TEST_SKIP(getenv("SKIP_SLOW_TESTS"), "Skipping slow test due to environment variable");
    
    // Warning example (non-fatal)
    int value = 5;
    WARN(value > 10, "Value is quite small, might want to increase it");
    
    // Debug output (only shown if DEBUG env var is set)
    DEBUG_PRINT("Debug info: value = %d", value);
    
    return 1;
}

// Setup and teardown example
int test_with_setup_teardown() {
    TRACE_FUNCTION();
    
    TEST_SETUP({
        printf("  Initializing test data...\n");
        srand(42); // Fixed seed for reproducible tests
    });
    
    // The actual test
    int random1 = RANDOM_INT(1, 100);
    int random2 = RANDOM_INT(1, 100);
    TEST_ASSERT(random1 >= 1 && random1 <= 100, "First random number in valid range");
    TEST_ASSERT(random2 >= 1 && random2 <= 100, "Second random number in valid range");
    
    TEST_TEARDOWN({
        printf("  Cleaning up test data...\n");
    });
    
    return 1;
}

// Bounds checking example
int test_bounds_checking() {
    TRACE_FUNCTION();
    
    int array[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int size = 10;
    
    // Safe access
    int index = 5;
    CHECK_BOUNDS(index, size, "Array access");
    TEST_ASSERT_EQ(array[index], 5, "Array element should match index");
    
    return 1;
}

/// !=======================================================================================================================
/// !                                                       TEST RUNNER
/// !=======================================================================================================================

int main() {
    printf("=== GLITCHSNITCH MACRO EXAMPLES ===\n\n");
    
    printf("Environment variables you can set:\n");
    printf("  DEBUG=1     - Enable debug output\n");
    printf("  TRACE=1     - Enable function tracing\n");
    printf("  SKIP_SLOW_TESTS=1 - Skip slow tests\n\n");
    
    // Overall benchmark
    BENCHMARK_START();
    
    // Run all test examples
    RUN_TEST(test_basic_assertions);
    RUN_TEST(test_array_operations);
    RUN_TEST(test_floating_point);
    RUN_TEST(test_range_checks);
    RUN_TEST(test_crash_scenarios);
    RUN_TEST(test_memory_management);
    RUN_TEST(test_file_operations);
    RUN_TEST(test_performance);
    RUN_TEST(test_stress_scenarios);
    RUN_TEST(test_buffer_security);
    RUN_TEST(test_conditional_features);
    RUN_TEST(test_with_setup_teardown);
    RUN_TEST(test_bounds_checking);
    
    BENCHMARK_END("All tests");
    
    // Print final summary
    PRINT_TEST_SUMMARY();
    
    printf("\n=== EXAMPLE COMPLETE ===\n");
    
    return (tests_failed == 0) ? 0 : 1;
}

/// !=======================================================================================================================
/// !                                            MACRO REFERENCE SUMMARY
/// !=======================================================================================================================

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
