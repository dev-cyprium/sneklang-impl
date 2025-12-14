#include "munit.h"

#include "snek/lexer/lexer.h"
#include "snek/lexer/token.h"

/*
 * whisper "hi"
 */
static MunitResult
test_whisper_string(const MunitParameter params[], void *data)
{
    sneklang_source_file_t src = lexer_new("whisper \"hi\"");

    token_t *tok;

    // whisper
    tok = lexer_next(&src);
    munit_assert_not_null(tok);
    munit_assert_int(tok->type, ==, WHISPER);
    token_free(tok);

    // "hi"
    tok = lexer_next(&src);
    munit_assert_not_null(tok);
    munit_assert_int(tok->type, ==, QUOTE);
    munit_assert_string_equal(tok->value, "hi");
    token_free(tok);

    // EOF
    tok = lexer_next(&src);
    munit_assert_not_null(tok);
    munit_assert_int(tok->type, ==, TOKEN_EOF);
    token_free(tok);

    return MUNIT_OK;
}

static MunitTest lexer_tests[] = {
    {
        "/lexer/whisper_string",
        test_whisper_string,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL
    },
    { NULL, NULL, NULL, NULL, 0, NULL }
};

static const MunitSuite suite = {
    "/sneklang",
    lexer_tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char *argv[])
{
    return munit_suite_main(&suite, NULL, argc, argv);
}
