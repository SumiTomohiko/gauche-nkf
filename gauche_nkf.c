/*
 * gauche_nkf.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gauche.h>
#include "gauche_nkf.h"

#define INIT_INCREASE_SIZE  (32)

static unsigned int input_len = 0;
static const char* input_str = "";
static unsigned int input_pos = 0;
static unsigned int output_len = 0;
static char* output_str = "";
static unsigned int output_pos = 0;
static unsigned int increase_size = INIT_INCREASE_SIZE;

#undef getc
#define getc nkf_getc
int nkf_getc(FILE* _)
{
    if (input_pos < input_len) {
        int c = input_str[input_pos] & 0xff;
        input_pos++;
        return c;
    }
    else {
        return EOF;
    }
}

#undef ungetc
#define ungetc nkf_ungetc
int nkf_ungetc(int c, FILE* _)
{
    if (0 < input_pos) {
        input_pos--;
        return c;
    }
    else {
        return EOF;
    }
}

#undef putchar
#define putchar nkf_putchar
int nkf_putchar(int c)
{
    if (output_len <= output_pos) {
        output_len += increase_size;
        output_str = realloc(output_str, output_len);
        if (output_str == NULL) {
            return EOF;
        }
        increase_size *= 2;
    }

    output_str[output_pos++] = c;

    return c;
}

#undef TRUE
#define PERL_XS
#include "nkf/nkf.c"
#include "nkf/utf8tbl.c"

ScmObj Scm_Nkf(ScmObj opts, const char* s) 
{
    reinit();

    ScmObj cp;
    SCM_FOR_EACH(cp, opts) {
        if (!SCM_STRINGP(SCM_CAR(cp))) {
            Scm_Error("string required, but got %S\n", SCM_CAR(cp));
        }
        const ScmStringBody* b = SCM_STRING_BODY(SCM_CAR(cp));
        const char* opt = SCM_STRING_BODY_START(b);
        options((unsigned char*)opt);
    }

    input_len = strlen(s);
    input_str = s;
    input_pos = 0;

    /* Following line comes from Ruby 1.9.0's NKF module */
    output_len = (input_len * 3 + 10) * sizeof(char);
    output_str = malloc(output_len);
    output_pos = 0;

    increase_size = INIT_INCREASE_SIZE;

    kanji_convert(NULL);

    ScmObj result = Scm_MakeString(output_str, output_pos, output_pos, SCM_STRING_COPYING);

    free(output_str);
    output_str = "";

    return result;
}

/*
 * Module initialization function.
 */
extern void Scm_Init_gauche_nkflib(ScmModule*);

void Scm_Init_gauche_nkf(void)
{
    ScmModule *mod;

    /* Register this DSO to Gauche */
    SCM_INIT_EXTENSION(gauche_nkf);

    /* Create the module if it doesn't exist yet. */
    mod = SCM_MODULE(SCM_FIND_MODULE("nkf", TRUE));

    /* Register stub-generated procedures */
    Scm_Init_gauche_nkflib(mod);
}

/**
 * vim: tabstop=4 shiftwidth=4 expandtab softtabstop=4 
 */
