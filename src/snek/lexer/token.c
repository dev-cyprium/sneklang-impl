#include "token.h"

#include <stdlib.h>

const token_t keywords[] = {
    {WHISPER, "whisper"}
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

void token_free(token_t* token)
{
    if (token)
    {
        free(token->value);
        free(token);
    }
}
