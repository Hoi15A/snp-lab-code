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
#ifndef _EVAL_H_
#define _EVAL_H_

#include "stack.h"

/**
 * @brief  All RPN Operators.
 */
typedef enum {
    OP_NOP,          ///< no operation
    OP_PRINT_HEX,    ///< print as hex
    OP_PRINT_DEC,    ///< print as dec
    OP_PRINT_OCT,    ///< print as oct
    OP_PRINT_BIN,    ///< print as bin
    OP_BIT_OR,       ///< unsigned integer bit or
    OP_BIT_XOR,      ///< unsigned integer bit xor
    OP_BIT_AND,      ///< unsigned integer bit and
    OP_BIT_LEFT,     ///< unsigned integer shift-left
    OP_BIT_RIGHT,    ///< unsigned integer shift-right
    OP_ADD,          ///< unsigned integer addition
    OP_SUB,          ///< unsigned integer subtraction
    OP_MUL,          ///< unsigned integer multiplication
    OP_DIV,          ///< unsigned integer division
    OP_MOD,          ///< unsigned integer modulo
    OP_CHS,          ///< unsigned integer twos-complement
    OP_INV,          ///< unsigned integer ones-complement
} eval_op_t;

/**
 * @brief  Opaque type - detailed in the implementation only.
 */
typedef struct eval eval_t;

/**
 * @brief                     Construcor.
 * @param  stack [IN]         Dependency Injection: the serving stack.
 * @param  verbose [IN]       Cointrol debug output (stderr): 0 = no output, 1 = additional output.
 * @return                    The newly created and initialized instance
 * @remark In case of error, the program terminates with EXIT_FAILURE and an appropriate error message.
 * @remark Does not take over ownership of the injected dependencies.
 */
eval_t *eval_new(stack_t *stack, int verbose);

/**
 * @brief  Frees the instances memory and the data it owns.
 * @param  instance [INOUT]  The affected instance.
 * @remark assert(instance) is performed, i.e. it is considered a programming error if instance is NULL.
 */
void eval_destroy(eval_t *instance);

/**
 * @brief  Feeds the value in RPN sequence to the evaluator.
 * @param  instance [INOUT]  The affected instance.
 * @param  value [IN]        The value to stack on the RPN calculator.
 * @remark assert(instance) is performed, i.e. it is considered a programming error if instance is NULL.
 */
void eval_number(eval_t *instance, unsigned int value);

/**
 * @brief  Feeds the operation in RPN sequence to the evaluator.
 * @param  instance [INOUT]  The affected instance.
 * @param  op [IN]           The operator to evaluate.
 * @remark assert(instance) is performed, i.e. it is considered a programming error if instance is NULL.
 */
void eval_op(eval_t *instance, eval_op_t op);

/**
 * @brief  Prints the top entry of the stack.
 * @param  instance [INOUT]  The affected instance.
 * @remark assert(instance) is performed, i.e. it is considered a programming error if instance is NULL.
 */
void eval_result(eval_t *instance);

#endif // _EVAL_H_
