#ifndef SNEKLANG_LEXER_H
#define SNEKLANG_LEXER_H

#include <stdbool.h>
#include <stdio.h>

#include "token.h"

typedef struct SneklangSourceFile
{
    char *file_buffer;
    char current_char;
    bool error_state;
    size_t current_pos;
    size_t total_len;
} sneklang_source_file_t;


sneklang_source_file_t lexer_new(char *file_buffer);
token_t* lexer_next(sneklang_source_file_t *source_file);

#endif //SNEKLANG_LEXER_H