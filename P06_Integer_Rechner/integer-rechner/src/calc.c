/* ----------------------------------------------------------------------------
 * --  _____       ______  _____                                              -
 * -- |_   _|     |  ____|/ ____|                                             -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems              -
 * --   | | | '_ \|  __|  \___ \   Zuercher Hochschule Winterthur             -
 * --  _| |_| | | | |____ ____) |  (University of Applied Sciences)           -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland               -
 * ----------------------------------------------------------------------------
 */
/**
 * @file
 * @brief Lab implementation
 */
#include <stdlib.h>
#include <assert.h>
#include "calc.h"
#include "eval.h"
#include "error.h"

/**
 * @brief  The details of the otherwise opaque type.
 */
struct calc {
    scan_t *scan; ///< DI: the scanner (this instance does not take over ownership)
    eval_t *eval; ///< DI: the evaluator (this instance does not take over ownership)
};

static void parse_expression(calc_t *instance);

static eval_op_t unary_tk2op(int tk) {
    switch(tk) {
    case '~': return OP_INV;
    case '+': return OP_NOP;
    case '-': return OP_CHS;
    default:
        error_fatal("not supported unary op");
        return OP_NOP;
    }
}

static eval_op_t binary_tk2op(int tk) {
    switch(tk) {
    case '|':       return OP_BIT_OR;
    case '^':       return OP_BIT_XOR;
    case '&':       return OP_BIT_AND;
    case TK_LSHIFT: return OP_BIT_LEFT;
    case TK_RSHIFT: return OP_BIT_RIGHT;
    case '+':       return OP_ADD;
    case '-':       return OP_SUB;
    case '*':       return OP_MUL;
    case '/':       return OP_DIV;
    case '%':       return OP_MOD;
    default:
        error_fatal("not supported binary op");
        return OP_NOP;
    }
}


static int parse_optional_op(calc_t *instance, const int ops[])
{
    assert(instance);
    assert(ops);
    const int *op = ops;
    while(*op && *op != scan_curr_token(instance->scan)) op++;
    if (*op) scan_next_token(instance->scan);
    return *op;
}

static void parse_unary_op(calc_t *instance, void (*parse)(calc_t *), const int ops[])
{
    assert(instance);
    int op = parse_optional_op(instance, ops);
    if (op) {
        parse_unary_op(instance, parse, ops);
        eval_op(instance->eval, unary_tk2op(op));
    }
    else {
        (*parse)(instance);
    }
}

static void parse_binary_op(calc_t *instance, void (*parse)(calc_t *), const int ops[])
{
    assert(instance);
    (*parse)(instance);
    int op = parse_optional_op(instance, ops);
    while (op) {
        (*parse)(instance);
        eval_op(instance->eval, binary_tk2op(op));
        op = parse_optional_op(instance, ops);
    }
}

static void parse_nested_expression(calc_t *instance)
{
    assert(instance);
    //  printf("parse_nested\n");
    if ('(' != scan_curr_token(instance->scan)) error_fatal("number or '(' ... ')' expected");
    if (scan_next_token(instance->scan) == TK_EOT) error_fatal("expression expected");
    parse_expression(instance);
    if (scan_curr_token(instance->scan) != ')') error_fatal("closing ')' expected");
    scan_next_token(instance->scan);
}

static void parse_number(calc_t *instance)
{
    assert(instance);
    //  printf("parse_number\n");
    if (scan_curr_token(instance->scan) != TK_NUM) error_fatal("number expected");
    eval_number(instance->eval, scan_curr_value(instance->scan));
    scan_next_token(instance->scan);
}

static void parse_primary(calc_t *instance)
{
    assert(instance);
    //  printf("parse_primary(%d)\n", scan_curr_token(instance->scan));
    int t = scan_curr_token(instance->scan);
    if (t == TK_NUM)   parse_number(instance);
    else if (t == '(') parse_nested_expression(instance);
    else error_fatal("number or '(' ... ')' expected");
}

static void parse_unary(calc_t *instance) { parse_unary_op(instance, parse_primary, (const int[]){ '+', '-', '~', 0 }); }

static void parse_mul(calc_t *instance) { parse_binary_op(instance, parse_unary, (const int[]){ '*', '/', '%', 0 }); }

static void parse_sum(calc_t *instance) { parse_binary_op(instance, parse_mul, (const int[]){ '+', '-', 0 }); }

static void parse_bit_shift(calc_t *instance) { parse_binary_op(instance, parse_sum, (const int[]){ TK_LSHIFT, TK_RSHIFT, 0 }); }

static void parse_bit_and(calc_t *instance) { parse_binary_op(instance, parse_bit_shift, (const int[]){ '&', 0 }); }

static void parse_bit_xor(calc_t *instance) { parse_binary_op(instance, parse_bit_and, (const int[]){ '^', 0 }); }

static void parse_bit_or(calc_t *instance) { parse_binary_op(instance, parse_bit_xor, (const int[]){ '|', 0 }); }

static void parse_expression(calc_t *instance) { parse_bit_or(instance); }


calc_t *calc_new(scan_t *scan, eval_t *eval)
{
    assert(scan);
    assert(eval);
    calc_t *instance = malloc(sizeof(calc_t));
    if (!instance) error_fatal_errno("calc_new: instance");
    instance->scan = scan;
    instance->eval = eval;
    return instance;
}

void calc_destroy(calc_t *instance)
{
    assert(instance);
    free(instance);
}

void calc_execute(calc_t *instance)
{
    assert(instance);
    if (scan_next_token(instance->scan) == TK_EOT) error_fatal("missing expression text");
    parse_expression(instance);
    //  printf("excess = %d\n", scan_curr_token(instance->scan));
    if (scan_curr_token(instance->scan) != TK_EOT) error_fatal("excess expression text found");

    eval_result(instance->eval);
}
