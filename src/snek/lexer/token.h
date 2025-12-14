#ifndef SNEKLANG_TOKEN_H
#define SNEKLANG_TOKEN_H
#include <stdio.h>

typedef enum TokenType
{
    SHED,
    COIL,
    HISS,
    UNHISS,
    WHISPER,
    SLITHER,
    THROUGH,
    IF,
    ELIF,
    ELSE,
    RETURN,
    ID,
    QUOTE,
    EQUAL,
    TOKEN_EOF
} token_type_t;

typedef struct Token
{
    token_type_t type;
    char *value;
} token_t;

extern const token_t keywords[];
extern const size_t keyword_count;

token_t* token_new(token_type_t type, char* value);
void token_free(token_t* token);

#endif //SNEKLANG_TOKEN_H
