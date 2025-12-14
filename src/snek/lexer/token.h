//
// Created by Stefan Kupresak on 14. 12. 2025.
//

#ifndef SNEKLANG_TOKEN_H
#define SNEKLANG_TOKEN_H

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
    RETURN
} token_type_t;

typedef struct Token
{
    token_type_t type;
    char *value;
} token_t;

#endif //SNEKLANG_TOKEN_H