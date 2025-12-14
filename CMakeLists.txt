cmake_minimum_required(VERSION 3.24)
project(sneklang C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# ------------------------
# Core library (shared by snek + tests)
# ------------------------
add_library(snekcore
        src/snek/lexer/lexer.c
        src/snek/lexer/token.c
)

target_compile_options(snekcore PRIVATE
        -Wall -Wextra -Wpedantic
)

target_include_directories(snekcore PUBLIC
        src
)

# ------------------------
# Main executable
# ------------------------
add_executable(snek
        src/main.c
)

target_link_libraries(snek PRIVATE snekcore)

target_compile_options(snek PRIVATE
        -Wall -Wextra -Wpedantic
)

# ------------------------
# Tests (Munit submodule)
# ------------------------
enable_testing()

add_executable(snek_tests
        tests/test_lexer.c
        third_party/munit/munit.c
)

target_include_directories(snek_tests PRIVATE
        third_party/munit
        src
)

target_compile_options(snek_tests PRIVATE
        -Wall -Wextra -Wpedantic
)

target_link_libraries(snek_tests PRIVATE snekcore)

add_test(NAME snek_tests COMMAND snek_tests)
