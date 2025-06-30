# GlitchSnitch 🐛

A comprehensive C testing and debugging macro library designed to catch bugs, validate code behavior, and streamline development workflows.

## Features

- **Comprehensive Testing Framework** - Unit testing with detailed reporting
- **Memory Management Tools** - Leak detection and allocation tracking
- **Performance Benchmarking** - Built-in timing and profiling
- **Crash Testing** - Validate expected program failures
- **Debug & Tracing** - Conditional debug output and function tracing
- **Security Checks** - Buffer overflow protection and bounds checking
- **Cross-Platform** - Works on Linux, macOS, and other Unix-like systems

## Quick Start

### Installation

1. Clone the repository:
```bash
git clone https://github.com/yourusername/glitchsnitch.git
cd glitchsnitch
```

2. Include the header in your C project:
```c
#include "src/glitchsnitch.h"
```

3. Compile your tests:
```bash
gcc -o your_test your_test.c
```

### Basic Usage

```c
#include "glitchsnitch.h"

// Your function to test
int add(int a, int b) {
    return a + b;
}

// Test function
int test_addition() {
    TEST_ASSERT_EQ(add(2, 3), 5, "2 + 3 should equal 5");
    TEST_ASSERT(add(0, 0) == 0, "Zero addition test");
    return 1;
}

int main() {
    RUN_TEST(test_addition);
    PRINT_TEST_SUMMARY();
    return 0;
}
```

## Testing Macros

### Basic Assertions

```c
// Basic condition testing
TEST_ASSERT(condition, "message");

// Equality testing with detailed output
TEST_ASSERT_EQ(actual, expected, "message");

// String comparison
TEST_ASSERT_STR_EQ(str1, str2, "message");

// Null pointer checks
TEST_ASSERT_NOT_NULL(ptr, "message");
TEST_ASSERT_NULL(ptr, "message");
```

### Advanced Testing

```c
// Array comparison
int expected[] = {1, 2, 3};
int actual[] = {1, 2, 3};
TEST_ASSERT_ARRAY_EQ(actual, expected, 3, "Arrays should match");

// Floating point comparison
TEST_ASSERT_FLOAT_EQ(3.14159, 3.14160, 0.001, "Pi approximation");

// Range validation
TEST_ASSERT_IN_RANGE(value, 1, 100, "Value should be 1-100");

// File operations
TEST_FILE_EXISTS("/path/to/file", "File should exist");
```

### Crash Testing

```c
void dangerous_function() {
    int *ptr = NULL;
    CHECK_PTR(ptr); // This will crash
}

int test_crash() {
    TEST_EXPECT_CRASH({dangerous_function();}, "Should crash on null pointer");
    return 1;
}
```

## Performance & Benchmarking

```c
int test_performance() {
    BENCHMARK_START();
    
    // Your code to benchmark
    for (int i = 0; i < 1000000; i++) {
        // Some operation
    }
    
    BENCHMARK_END("Million iterations");
    return 1;
}
```

### Stress Testing

```c
int test_stress() {
    // Run test 1000 times
    STRESS_TEST(1000, (add(1, 1) == 2), "Addition stress test");
    
    // Repeat operation multiple times
    REPEAT_TEST(100, {
        int result = add(rand() % 10, rand() % 10);
        // Validate result
    });
    
    return 1;
}
```

## Memory Management

```c
int test_memory() {
    MALLOC_COUNT_START();
    
    char *buffer = malloc(100);
    TRACK_MALLOC(buffer);
    
    // Use buffer...
    
    free(buffer);
    TRACK_FREE(buffer);
    
    CHECK_MEMORY_LEAKS(); // Reports any leaks
    return 1;
}
```

## Error Checking & Validation

### Runtime Checks

```c
void safe_function() {
    char *ptr = malloc(100);
    CHECK_ALLOC(ptr, "Memory allocation");
    
    int index = 5, size = 10;
    CHECK_BOUNDS(index, size, "Array access");
    
    CHECK(ptr != NULL, "Pointer should not be null");
    
    free(ptr);
}
```

### System Call Checking

```c
void file_operations() {
    int fd = open("file.txt", O_RDONLY);
    CHECK_ERRNO(fd, "File open");
    
    // Use file descriptor...
    
    close(fd);
}
```

## Debug & Tracing

### Environment Variables

- `DEBUG=1` - Enable debug output
- `TRACE=1` - Enable function tracing
- `SKIP_SLOW_TESTS=1` - Skip slow tests

### Debug Macros

```c
int debug_example() {
    TRACE_FUNCTION(); // Shows function entry if TRACE=1
    
    int value = 42;
    LOG_VAR(value); // Shows variable value if DEBUG=1
    
    DEBUG_PRINT("Processing item %d", value);
    
    WARN(value > 100, "Value might be too large");
    
    return 1;
}
```

## Test Organization

### Setup and Teardown

```c
int test_with_setup() {
    TEST_SETUP({
        // Initialize test data
        srand(42);
        printf("Setting up test...\n");
    });
    
    // Your test code here
    TEST_ASSERT(1 == 1, "Basic test");
    
    TEST_TEARDOWN({
        // Cleanup
        printf("Cleaning up...\n");
    });
    
    return 1;
}
```

### Conditional Testing

```c
int test_conditional() {
    // Skip test based on condition
    TEST_SKIP(getenv("SKIP_SLOW_TESTS"), "Skipping slow test");
    
    // Continue with test...
    return 1;
}
```

## Complete Example

Here's a full example demonstrating multiple features:

```c
#include "glitchsnitch.h"
#include <string.h>

// Function to test
int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

// Memory allocation function
char* create_buffer(size_t size) {
    return malloc(size);
}

// Test suite
int test_factorial() {
    TRACE_FUNCTION();
    
    TEST_ASSERT_EQ(factorial(0), 1, "0! should be 1");
    TEST_ASSERT_EQ(factorial(5), 120, "5! should be 120");
    TEST_ASSERT_IN_RANGE(factorial(4), 20, 30, "4! should be 24");
    
    return 1;
}

int test_memory_operations() {
    MALLOC_COUNT_START();
    
    char *buffer = create_buffer(100);
    TRACK_MALLOC(buffer);
    CHECK_ALLOC(buffer, "Buffer allocation");
    
    strcpy(buffer, "Hello, World!");
    TEST_ASSERT_STR_EQ(buffer, "Hello, World!", "String copy test");
    
    free(buffer);
    TRACK_FREE(buffer);
    
    CHECK_MEMORY_LEAKS();
    return 1;
}

int test_performance() {
    BENCHMARK_START();
    int result = factorial(10);
    BENCHMARK_END("Factorial calculation");
    
    TEST_ASSERT(result > 0, "Factorial result should be positive");
    return 1;
}

int main() {
    printf("=== GlitchSnitch Example Test Suite ===\n\n");
    
    RUN_TEST(test_factorial);
    RUN_TEST(test_memory_operations);
    RUN_TEST(test_performance);
    
    PRINT_TEST_SUMMARY();
    
    return (tests_failed == 0) ? 0 : 1;
}
```

## Macro Reference

### Testing Macros
| Macro | Description |
|-------|-------------|
| `TEST_ASSERT(cond, msg)` | Basic assertion |
| `TEST_ASSERT_EQ(actual, expected, msg)` | Equality check |
| `TEST_ASSERT_STR_EQ(str1, str2, msg)` | String comparison |
| `TEST_ASSERT_ARRAY_EQ(arr1, arr2, size, msg)` | Array comparison |
| `TEST_ASSERT_FLOAT_EQ(a, b, epsilon, msg)` | Float comparison |
| `TEST_ASSERT_IN_RANGE(val, min, max, msg)` | Range check |
| `TEST_EXPECT_CRASH(code, msg)` | Expected crash test |
| `RUN_TEST(func)` | Execute test function |

### Performance Macros
| Macro | Description |
|-------|-------------|
| `BENCHMARK_START()` | Start timing |
| `BENCHMARK_END(name)` | End timing and report |
| `STRESS_TEST(n, code, msg)` | Stress testing |
| `REPEAT_TEST(n, code)` | Repeat operations |

### Memory Macros
| Macro | Description |
|-------|-------------|
| `MALLOC_COUNT_START()` | Initialize tracking |
| `TRACK_MALLOC(ptr)` | Track allocation |
| `TRACK_FREE(ptr)` | Track deallocation |
| `CHECK_MEMORY_LEAKS()` | Report leaks |

### Validation Macros
| Macro | Description |
|-------|-------------|
| `CHECK(cond, msg)` | Fatal assertion |
| `CHECK_PTR(ptr)` | Null pointer check |
| `CHECK_BOUNDS(idx, size, msg)` | Bounds checking |
| `CHECK_ALLOC(ptr, msg)` | Allocation check |
| `CHECK_ERRNO(call, msg)` | System call check |

### Debug Macros
| Macro | Description |
|-------|-------------|
| `DEBUG_PRINT(fmt, ...)` | Conditional debug output |
| `TRACE_FUNCTION()` | Function entry tracing |
| `LOG_VAR(var)` | Variable logging |
| `WARN(cond, msg)` | Non-fatal warning |

## Building and Running

### Simple Compilation
```bash
gcc -o test_suite your_tests.c
./test_suite
```

### With Debug Output
```bash
DEBUG=1 TRACE=1 ./test_suite
```

## CMake Integration

GlitchSnitch is designed as a modern CMake header-only library with full installation support.

### Method 1: Using find_package() (After Installation)

First, build and install GlitchSnitch:
```bash
git clone https://github.com/yourusername/glitchsnitch.git
cd glitchsnitch
mkdir build && cd build
cmake ..
make install
```

Then use it in your project:
```cmake
cmake_minimum_required(VERSION 3.12)
project(YourProject)

# Find and link GlitchSnitch
find_package(GlitchSnitch REQUIRED)

add_executable(your_tests your_tests.c)
target_link_libraries(your_tests GlitchSnitch::glitchsnitch)
```

### Method 2: Using add_subdirectory()

Add GlitchSnitch as a subdirectory in your project:
```cmake
cmake_minimum_required(VERSION 3.12)
project(YourProject)

# Add GlitchSnitch subdirectory
add_subdirectory(external/glitchsnitch)

add_executable(your_tests your_tests.c)
target_link_libraries(your_tests GlitchSnitch::glitchsnitch)
```

### Method 3: Using FetchContent (CMake 3.14+)

Automatically download and include GlitchSnitch:
```cmake
cmake_minimum_required(VERSION 3.14)
project(YourProject)

include(FetchContent)

FetchContent_Declare(
    glitchsnitch
    GIT_REPOSITORY https://github.com/i-Sage/glitchsnitch.git
    GIT_TAG main
)

FetchContent_MakeAvailable(glitchsnitch)

add_executable(your_tests your_tests.c)
target_link_libraries(your_tests GlitchSnitch::glitchsnitch)
```

### Building GlitchSnitch

```bash
# Basic build
mkdir build && cd build
cmake ..
make

# With testing enabled
cmake -DBUILD_TESTING=ON ..
make
ctest

# Install to system
make install

# Custom install prefix
cmake -DCMAKE_INSTALL_PREFIX=/usr/local ..
make install
```

### CMake Options

| Option | Default | Description |
|--------|---------|-------------|
| `BUILD_TESTING` | `OFF` | Enable building and running tests |
| `CMAKE_INSTALL_PREFIX` | System default | Installation directory |

### Integration Example

Complete example of integrating GlitchSnitch into your project:

```cmake
# CMakeLists.txt
cmake_minimum_required(VERSION 3.12)
project(MyTestSuite VERSION 1.0.0)

# Option 1: If GlitchSnitch is installed
find_package(GlitchSnitch REQUIRED)

# Option 2: If using as subdirectory
# add_subdirectory(external/glitchsnitch)

# Create your test executable
add_executable(my_tests
    src/my_tests.c
    src/functions_to_test.c
)

# Link GlitchSnitch
target_link_libraries(my_tests GlitchSnitch::glitchsnitch)

# Set C standard
target_compile_features(my_tests PRIVATE c_std_99)

# Enable testing
enable_testing()
add_test(NAME my_tests_run COMMAND my_tests)
```

## Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Changelog

### v1.0.0
- Initial release
- Basic testing framework
- Memory management tools
- Performance benchmarking
- Debug and tracing capabilities
- Comprehensive macro library

---

**GlitchSnitch** - Because every bug deserves to be caught! 🐛✨