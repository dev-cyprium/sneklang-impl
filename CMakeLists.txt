cmake_minimum_required(VERSION 3.24)
project(sneklang C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(snek
        src/main.c
        src/snek/lexer/lexer.c
        src/snek/lexer/token.c
)

target_compile_options(snek PRIVATE
        -Wall -Wextra -Wpedantic
)
