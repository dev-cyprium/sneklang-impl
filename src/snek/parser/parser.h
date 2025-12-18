#ifndef SNEKLANG_PARSER_H
#define SNEKLANG_PARSER_H
#include "snek/lexer/lexer.h"

typedef struct Parser
{
    sneklang_source_file_t* source;
    token_t current;
    token_t next;
} parser_t;

typedef enum
{
    AST_INT_LITERAL,
    AST_IDENTIFIER,
    AST_UNARY,
    AST_BINARY,
    AST_GROUPING
} ast_node_type_t;

typedef struct ast_node ast_node_t;

typedef struct
{
    int value;
} ast_int_literal_t;

typedef struct
{
    const char* name;
} ast_identifier_t;

typedef struct
{
    token_type_t op;
    ast_node_t* expr;
} ast_unary_t;

typedef struct
{
    token_type_t op;
    ast_node_t* left;
    ast_node_t* right;
} ast_binary_t;

typedef struct
{
    ast_node_t *expr;
} ast_grouping_t;

struct ast_node
{
    ast_node_type_t type;
    union
    {
        ast_int_literal_t int_lit;
        ast_identifier_t identifier;
        ast_unary_t unary;
        ast_binary_t binary;
        ast_grouping_t grouping;
    } as;
};

parser_t parser_new(sneklang_source_file_t* source);

void parser_advance(parser_t* p);
bool parser_match(parser_t* p, token_type_t type);
void parser_expect(parser_t* p, token_type_t type, const char* message);

ast_node_t* parse_expression(parser_t* p, int min_bp);


#endif //SNEKLANG_PARSER_H
