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

#include <stdlib.h>
#include <assert.h>
#include "stack.h"
#include "error.h"

/**
 * @brief  The details of the otherwise opaque type.
 */
struct stack {
    stack_value_t *stack; ///< the data container (the instance owns this)
    stack_value_t *top;   ///< the pointer into the container where the current top data resides (has to point initially to stack-1)
    stack_value_t *full;  ///< the pointer to the last entry of the conatainer
};

stack_t *stack_new(size_t max_elements)
{
    stack_t *instance = NULL;
    // 1. allocate a stack_t instance on the heap and set the instance variable to it
    // 2. call error_fatal_errno("stack_new: instance"); if failed to allocate the memory on the heap
    // 3. allocate an array of max_elements value_t's on the heap and store its address in the stack member of the stack_t instance
    // 4. call error_fatal_errno("stack_new: stack"); if failed to allocate the memory on the heap
    // 5. set the top member of the stack_t instance to the address of the "element" before the first stack array element
    // 6. set the full member of the stack_t instance to the address of the last element of the stack array
    // BEGIN-STUDENTS-TO-ADD-CODE










    // END-STUDENTS-TO-ADD-CODE
    return instance;
}

void stack_destroy(stack_t *instance)
{
    assert(instance);
    // 1. free the stack array
    // 2. free the stack_t instance
    // BEGIN-STUDENTS-TO-ADD-CODE




    // END-STUDENTS-TO-ADD-CODE
}

void stack_push(stack_t *instance, stack_value_t value)
{
    assert(instance);
    if (stack_is_full(instance)) error_fatal("stack_push: full");
    // 1. increment by one element the address stored in the top member of the stack_t instance
    // 2. store the received value at the new top location
    // BEGIN-STUDENTS-TO-ADD-CODE



    // END-STUDENTS-TO-ADD-CODE
}

stack_value_t stack_pop(stack_t *instance)
{
    assert(instance);
    if (stack_is_empty(instance)) error_fatal("stack_pop: empty");
    stack_value_t value = 0;
    // 1. set the variable value to the value from the address the top member points to
    // 2. decrement by one element the address stored in the top member of the stack_t instance
    // BEGIN-STUDENTS-TO-ADD-CODE



    // END-STUDENTS-TO-ADD-CODE
    return value;
}

stack_value_t stack_top(stack_t *instance)
{
    assert(instance);
    if (stack_is_empty(instance)) error_fatal("stack_top: empty");
    stack_value_t value = 0;
    // 1. set the variable value to the value from the address the top member points to
    // BEGIN-STUDENTS-TO-ADD-CODE


    
    // END-STUDENTS-TO-ADD-CODE
    return value;
}

int stack_is_empty(stack_t *instance)
{
    assert(instance);
    int is_empty = 1;
    // 1. set is_empty to 1 if the top equals the initial condition as done in stack_new(), otherwise to 0
    // BEGIN-STUDENTS-TO-ADD-CODE


    
    // END-STUDENTS-TO-ADD-CODE
    return is_empty;
}

int stack_is_full(stack_t *instance)
{
    assert(instance);
    int is_full = 1;
    // 1. set is_full to 1 if the top equals the full pointer as set in the stack_new() function, otherwise 0
    // BEGIN-STUDENTS-TO-ADD-CODE


    
    // END-STUDENTS-TO-ADD-CODE
    return is_full;
}
