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
 * @brief RPN Evaluator
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "eval.h"
#include "error.h"

/**
 * @brief  The details of the otherwise opaque type.
 */
struct eval {
    stack_t *stack;   ///< DI: the stack (this instance does not take over ownership)
    int      verbose; ///< verbosity control (0 = silent, 1 = verbose)
};

static void write_op(FILE *fd, eval_op_t op)
{
    switch(op) {
    case OP_NOP:       fprintf(fd, "OP_NOP\n");       break; 
    case OP_PRINT_HEX: fprintf(fd, "OP_PRINT_HEX\n"); break;
    case OP_PRINT_DEC: fprintf(fd, "OP_PRINT_DEC\n"); break;
    case OP_PRINT_OCT: fprintf(fd, "OP_PRINT_OCT\n"); break;
    case OP_PRINT_BIN: fprintf(fd, "OP_PRINT_BIN\n"); break;
    case OP_BIT_OR:    fprintf(fd, "OP_BIT_OR\n");    break;
    case OP_BIT_XOR:   fprintf(fd, "OP_BIT_XOR\n");   break;
    case OP_BIT_AND:   fprintf(fd, "OP_BIT_AND\n");   break;
    case OP_BIT_LEFT:  fprintf(fd, "OP_BIT_LEFT\n");  break;
    case OP_BIT_RIGHT: fprintf(fd, "OP_BIT_RIGHT\n"); break;
    case OP_ADD:       fprintf(fd, "OP_ADD\n");       break;
    case OP_SUB:       fprintf(fd, "OP_SUB\n");       break;
    case OP_MUL:       fprintf(fd, "OP_MUL\n");       break;
    case OP_DIV:       fprintf(fd, "OP_DIV\n");       break;
    case OP_MOD:       fprintf(fd, "OP_MOD\n");       break;
    case OP_CHS:       fprintf(fd, "OP_CHS\n");       break;
    case OP_INV:       fprintf(fd, "OP_INV\n");       break;
    }
}

static void write_value(FILE *fd, eval_op_t op, unsigned int value)
{
    const unsigned int top_bit = 1 << (sizeof(unsigned int) * 8 - 1);
    switch(op) {
    case OP_PRINT_HEX:
        fprintf(fd, "hex=0x%0*x\n", (int)(sizeof(unsigned int)*2), value);
        break;
    case OP_PRINT_DEC:
        fprintf(fd, "dec=%d\n", value);
        break;
    case OP_PRINT_OCT:
        fprintf(fd, "oct=0%0*o\n", (int)((sizeof(unsigned int)*8+2)/3), value);
        break;
    case OP_PRINT_BIN:
        fprintf(fd, "bin=0b");
        for(size_t i = 0; i < sizeof(unsigned int)*8; i++) {
            fputc((value & top_bit) ? '1' : '0', fd);
            value <<= 1;
        }
        fputc('\n', fd);
        break;
    default:
        break;
    }
}

static int eval_top(eval_t *instance, eval_op_t op)
{
    assert(instance);
    assert(instance->stack);
    
    switch(op) {
    case OP_NOP:
        return 1;
    case OP_PRINT_HEX:
    case OP_PRINT_DEC:
    case OP_PRINT_OCT:
    case OP_PRINT_BIN:
        write_value(stdout, op, stack_top(instance->stack));
        return 1;
    default:
        break;
    }
    return 0;
}

static int eval_unary(eval_t *instance, eval_op_t op)
{
    assert(instance);
    assert(instance->stack);

    unsigned int v;
    switch(op) {
    case OP_CHS:
        v = stack_pop(instance->stack);
        stack_push(instance->stack, -v);
        return 1;
    case OP_INV:
        // 1. implement the ~ operator analogous to the - sign operator above
        v = stack_pop(instance->stack);
        stack_push(instance->stack, ~v);
        return 1;
    default:
        break;
    }
    return 0;
}

static int eval_binary(eval_t *instance, eval_op_t op)
{
    assert(instance);
    assert(instance->stack);

    unsigned int a;
    unsigned int b;

    switch(op) {
    case OP_ADD:
        b = stack_pop(instance->stack);
        a = stack_pop(instance->stack);
        stack_push(instance->stack, a + b);
        return 1;
    case OP_SUB:
        b = stack_pop(instance->stack);
        a = stack_pop(instance->stack);
        stack_push(instance->stack, a - b);
        return 1;
    case OP_MUL:
        b = stack_pop(instance->stack);
        a = stack_pop(instance->stack);
        stack_push(instance->stack, a * b);
        return 1;
    case OP_DIV:
        b = stack_pop(instance->stack);
        a = stack_pop(instance->stack);
        stack_push(instance->stack, a / b);
        return 1;
    case OP_MOD:
        b = stack_pop(instance->stack);
        a = stack_pop(instance->stack);
        stack_push(instance->stack, a % b);
        return 1;
    case OP_BIT_OR:
        // 1. implement the | operator analogous to the * operator above
        b = stack_pop(instance->stack);
        a = stack_pop(instance->stack);
        stack_push(instance->stack, a | b);
        return 1;
    case OP_BIT_XOR:
        // 1. implement the ^ operator analogous to the * operator above
        b = stack_pop(instance->stack);
        a = stack_pop(instance->stack);
        stack_push(instance->stack, a ^ b);
        return 1;
    case OP_BIT_AND:
        // 1. implement the & operator analogous to the * operator above
        b = stack_pop(instance->stack);
        a = stack_pop(instance->stack);
        stack_push(instance->stack, a & b);
        return 1;
    case OP_BIT_LEFT:
        // 1. implement the << operator analogous to the * operator above
        b = stack_pop(instance->stack);
        a = stack_pop(instance->stack);
        stack_push(instance->stack, a << b);
        return 1;
    case OP_BIT_RIGHT:
        // 1. implement the >> operator analogous to the * operator above
        b = stack_pop(instance->stack);
        a = stack_pop(instance->stack);
        stack_push(instance->stack, a >> b);
        return 1;
    default:
        break;
    }
    return 0;
}

eval_t *eval_new(stack_t *stack, int verbose)
{
    assert(stack);
    eval_t *instance = malloc(sizeof(eval_t));
    if (!instance) error_fatal_errno("eval_new: instance");
    instance->stack = stack;
    instance->verbose = verbose;
    return instance;
}

void eval_destroy(eval_t *instance)
{
    assert(instance);
    free(instance);
}

void eval_number(eval_t *instance, unsigned int value)
{
    assert(instance);
    stack_push(instance->stack, value);
    if (instance->verbose) write_value(stderr, OP_PRINT_HEX, value);
}

void eval_op(eval_t *instance, eval_op_t op)
{
    if (eval_top(instance, op) || eval_unary(instance, op) || eval_binary(instance, op)) {
        // successfully evaluated
        if (instance->verbose) write_op(stderr, op);
    } else {
        error_fatal("eval_op: unknown op");
    }
}

void eval_result(eval_t *instance)
{
    assert(instance);
    unsigned int v = stack_top(instance->stack);
    printf("--- RESULT ---\n");
    write_value(stdout, OP_PRINT_DEC, v);
    write_value(stdout, OP_PRINT_HEX, v);
    write_value(stdout, OP_PRINT_OCT, v);
    write_value(stdout, OP_PRINT_BIN, v);
}
