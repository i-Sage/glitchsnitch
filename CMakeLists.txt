cmake_minimum_required(VERSION 3.12)
project(GlitchSnitch 
    VERSION 1.0.0
    DESCRIPTION "A comprehensive C testing and debugging macro library"
    LANGUAGES C
)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_library(glitchsnitch INTERFACE)

add_library(GlitchSnitch::glitchsnitch ALIAS glitchsnitch)

target_include_directories(glitchsnitch
    INTERFACE 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(glitchsnitch INTERFACE m)
target_compile_features(glitchsnitch INTERFACE c_std_99)