#include "lexer.h"

#include <assert.h>
#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static void advance(sneklang_source_file_t* source_file);
static void skip_whitespace(sneklang_source_file_t* source_file);
static token_t* id(sneklang_source_file_t *source_file);
static token_t* quote(sneklang_source_file_t *source_file);

sneklang_source_file_t lexer_new(char *file_buffer)
{
    if (file_buffer)
    {
        const sneklang_source_file_t t = {
            .file_buffer = file_buffer,
            .current_char = file_buffer[0] ? file_buffer[0] : '\0',
            .current_pos = 0,
            .total_len = strlen(file_buffer)
        };

        return t;
    }

    return (sneklang_source_file_t) {.error_state = true};
}


token_t* lexer_next(sneklang_source_file_t *source_file)
{
    if (!source_file) return NULL;

    char curr;
    while ((curr = source_file->current_char) != '\0')
    {
        if (isspace(curr))
        {
            skip_whitespace(source_file);
            continue;
        }

        if (isalpha(curr))
        {
            return id(source_file);
        }

        switch (curr)
        {
            case '"':
                return quote(source_file);
            case '=':
                advance(source_file);
                return token_new(EQUAL, "=");
            default:
                printf("token %c no matches", curr);
                return NULL;
        }
    }

    return token_new(TOKEN_EOF, NULL);
}

static token_t* quote(sneklang_source_file_t *sf)
{
    advance(sf); // skip opening quote
    const size_t start = sf->current_pos;

    while (sf->current_char != '"' && sf->current_char != '\0') {
        advance(sf);
    }

    if (sf->current_char == '\0') {
        return NULL;
    }

    const size_t end = sf->current_pos;
    size_t len = end - start;

    char *buffer = malloc(len + 1);
    if (!buffer) return NULL;

    memcpy(buffer, sf->file_buffer + start, len);
    buffer[len] = '\0';

    advance(sf);

    return token_new(QUOTE, buffer);
}

static token_t* id(sneklang_source_file_t *source_file)
{
    const size_t start_offset = source_file->current_pos;
    size_t end_offset = source_file->current_pos;

    char curr;
    while ((curr = source_file->current_char) != '\0' && isalnum(curr))
    {
        end_offset++;
        advance(source_file);
    }

    const size_t len = end_offset - start_offset;
    char *buffer = malloc(len+1);
    if (!buffer) return NULL;

    memcpy(buffer, source_file->file_buffer + start_offset, len);
    buffer[len] = '\0';

    for (size_t i=0; i < keyword_count; i++)
    {
        if (strcmp(buffer, keywords[i].value) == 0)
        {
            return token_new(keywords[i].type, buffer);
        }
    }
    return token_new(ID, buffer);
}

static void skip_whitespace(sneklang_source_file_t *source_file)
{
    while (source_file->current_char != '\0' && isspace(source_file->current_char))
    {
        advance(source_file);
    }
}

static void advance(sneklang_source_file_t *source_file)
{
    if (source_file)
    {
        source_file->current_pos++;
        if (source_file->current_pos > strlen(source_file->file_buffer) -1 )
        {
            source_file->current_char = '\0';
        } else
        {
            source_file->current_char = source_file->file_buffer[source_file->current_pos];
        }
    }
}
