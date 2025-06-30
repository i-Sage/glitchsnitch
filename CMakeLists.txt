cmake_minimum_required(VERSION 3.12)
project(GlitchSnitch 
    VERSION 1.0.0
    DESCRIPTION "A comprehensive C testing and debugging macro library"
    LANGUAGES C
)

# Set C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Create header-only library
add_library(glitchsnitch INTERFACE)

# Add alias for consistent naming
add_library(GlitchSnitch::glitchsnitch ALIAS glitchsnitch)

# Set target properties
target_include_directories(glitchsnitch 
    INTERFACE 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:include>
)

# Required system libraries for the macros
target_link_libraries(glitchsnitch INTERFACE m)

# Compiler-specific options
target_compile_features(glitchsnitch INTERFACE c_std_99)

# Optional: Enable testing if this is the main project
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
    
    if(BUILD_TESTING)
        # Check if test template exists before building
        if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/test_template.c")
            add_executable(test_template src/test_template.c)
            target_link_libraries(test_template glitchsnitch)
            
            # Add test
            add_test(NAME test_template_run COMMAND test_template)
            
            # Set test properties
            set_tests_properties(test_template_run PROPERTIES
                PASS_REGULAR_EXPRESSION "TEST SUMMARY"
            )
        endif()
    endif()
endif()

# Installation
include(GNUInstallDirs)

# Install header file
install(FILES src/glitchsnitch.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Install targets
install(TARGETS glitchsnitch
    EXPORT GlitchSnitchTargets
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Create and install config files
install(EXPORT GlitchSnitchTargets
    FILE GlitchSnitchTargets.cmake
    NAMESPACE GlitchSnitch::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/GlitchSnitch
)

# Create basic config files
include(CMakePackageConfigHelpers)

# Create a simple config file content
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/GlitchSnitchConfig.cmake" "
include(CMakeFindDependencyMacro)
include(\"\${CMAKE_CURRENT_LIST_DIR}/GlitchSnitchTargets.cmake\")
")

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/GlitchSnitchConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/GlitchSnitchConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/GlitchSnitchConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/GlitchSnitch
)

# Print summary
message(STATUS "")
message(STATUS "GlitchSnitch Configuration Summary:")
message(STATUS "  Version: ${PROJECT_VERSION}")
message(STATUS "  C Standard: C${CMAKE_C_STANDARD}")
message(STATUS "  Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  Install prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "  Testing: ${BUILD_TESTING}")
message(STATUS "")
