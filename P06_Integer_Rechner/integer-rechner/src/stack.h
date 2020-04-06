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
 * @brief Stack
 */

#ifndef _STACK_H_
#define _STACK_H_

/**
 * @brief  Convenience alias.
 */
typedef unsigned int stack_value_t;

/**
 * @brief  Opaque type - detailed in the implementation only.
 */
typedef struct stack stack_t;

/**
 * @brief                     Construcor.
 * @param  max_elements [IN]  Gives the size of the stack.
 * @return                    The newly created and initialized instance
 * @remark In case of error, the program terminates with EXIT_FAILURE and an appropriate error message.
 */
stack_t *stack_new(size_t max_elements);

/**
 * @brief  Frees the instances memory and the data it owns (i.e. the stack container).
 * @param  instance [INOUT]  The affected instance.
 * @remark assert(instance) is performed, i.e. it is considered a programming error if instance is NULL.
 */
void stack_destroy(stack_t *instance);

/**
 * @brief  Pushes the value to the stack.
 * @param  instance [INOUT]  The affected instance.
 * @param  value [IN]        The value to pus.
 * @remark In case of error, the program terminates with EXIT_FAILURE and an appropriate error message.
 * @remark assert(instance) is performed, i.e. it is considered a programming error if instance is NULL.
 */
void stack_push(stack_t *instance, stack_value_t value);

/**
 * @brief  Removes the top stack entry and returns it.
 * @param  instance [INOUT]  The affected instance.
 * @return  Returns the top most entry.
 * @remark In case of error, the program terminates with EXIT_FAILURE and an appropriate error message.
 * @remark assert(instance) is performed, i.e. it is considered a programming error if instance is NULL.
 */
stack_value_t stack_pop(stack_t *instance);

/**
 * @brief  Gets the top stack entry.
 * @param  instance [INOUT]  The affected instance.
 * @return  Returns the top most entry.
 * @remark In case of error, the program terminates with EXIT_FAILURE and an appropriate error message.
 * @remark assert(instance) is performed, i.e. it is considered a programming error if instance is NULL.
 */
stack_value_t stack_top(stack_t *instance);

/**
 * @brief  Queries if the stack is empty - i.e. if a pop operation is possible.
 * @param  instance [INOUT]  The affected instance.
 * @return  Returns 1 if empry, 0 otherwise.
 * @remark assert(instance) is performed, i.e. it is considered a programming error if instance is NULL.
 */
int stack_is_empty(stack_t *instance);

/**
 * @brief  Queries if the stack is full - i.e. if a push operation is possible.
 * @param  instance [INOUT]  The affected instance.
 * @return  Returns 1 if full, 0 otherwise.
 * @remark assert(instance) is performed, i.e. it is considered a programming error if instance is NULL.
 */
int stack_is_full(stack_t *instance);

#endif // _STACK_H_
