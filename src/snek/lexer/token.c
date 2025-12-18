#include "token.h"

#include <stdlib.h>

const token_t keywords[] = {
    {WHISPER, "whisper"},
    {COIL, "coil"},
    {SHED, "shed"}
};
const size_t keyword_count = sizeof(keywords) / sizeof(keywords[0]);

token_t* token_new(const token_type_t type, char* value)
{
    token_t* new_token = malloc(sizeof(token_t));

    if (new_token == NULL) return NULL;

    new_token->type = type;
    new_token->value = value;

    return new_token;
}

void token_debug(const token_t* token)
{
    switch (token->type)
    {
    case EQUAL:
        printf("(EQUAL,'%s')\n", token->value);
        break;
    case L_PAREN:
        printf("(L_PAREN,'%s')\n", token->value);
        break;
    case R_PAREN:
        printf("(R_PAREN,'%s')\n", token->value);
        break;
    case COIL:
        printf("(COIL,'%s')\n", token->value);
        break;
    case SHED:
        printf("(SHED,'%s')\n", token->value);
        break;
    case ID:
        printf("(ID,'%s')\n", token->value);
        break;
    case COMMA:
        printf("(COMMA,'%s')\n", token->value);
        break;
    case PLUS:
        printf("(PLUS,'%s')\n", token->value);
        break;
    case INTEGER_CONST:
        printf("(INT,'%ld')\n", strtol(token->value, NULL, 10));
        break;
    case WHISPER:
        printf("(WHISPER,'%s')\n", token->value);
        break;
    case QUOTE:
        printf("(QUOTE,'%s')\n", token->value);
        break;
    default:
        printf("Unknown token: (%d,'%s')\n", token->type, token->value);
    }
}

void token_free(token_t* token)
{
    if (token)
    {
        free(token->value);
        free(token);
    }
}
