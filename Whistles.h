#ifndef WHISTLES_H
#define WHISTLES_H

#include <string.h>
#include "py/compile.h"
#include "py/runtime.h"

///https://github.com/micropython/micropython/blob/master/ports/bare-arm/main.c

class whistles
{
public:
    whistles() : input_kind(MP_PARSE_SINGLE_INPUT) { mp_init(); }
    ~whistles() { mp_deinit(); } //TODO: Pass in instance to deinit instead of global
    void eval(const char* code)
    {
        nlr_buf_t nlr;
        if (nlr_push(&nlr) == 0)
        {
            mp_lexer_t* lex = mp_lexer_new_from_str_len(MP_QSTR__lt_stdin_gt_, code, strlen(code), 0);
            qstr source_name = lex->source_name;
            mp_parse_tree_t parse_tree = mp_parse(lex, input_kind); // <-- All that's really needed
            mp_obj_t module_fun = mp_compile(&parse_tree, source_name, true);
            mp_call_function_0(module_fun);
            nlr_pop();
        }
        else { mp_obj_print_exception(&mp_plat_print, (mp_obj_t)nlr.ret_val); }
    }
    mp_parse_input_kind_t input_kind;
};

static whistles Whistles;

#endif//WHISTLES_H

#ifndef WHISTLES_C
#define WHISTLES_C

#include "py/compile.c"
#include "py/runtime.c"

#endif//WHISTLES_C