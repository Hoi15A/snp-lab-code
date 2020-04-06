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
#include <stdio.h>
#include <stdlib.h>
#include "calc.h"

/**
 * @brief Main entry point.
 * @param[in] argc  The size of the argv array.
 * @param[in] argv  The command line arguments...
 * @returns Returns EXIT_SUCCESS (=0) on success, EXIT_FAILURE (=1) there is an expression syntax error.
 */
int main(int argc, char* argv[])
{
    int verbose = argc > 1 && strtol(argv[1], NULL, 10);
    
    const size_t stack_size = 10;
    stack_t *stack = stack_new(stack_size);
    eval_t  *eval  = eval_new(stack, verbose);
    scan_t  *scan  = scan_new();
    calc_t  *calc  = calc_new(scan, eval);
    
    calc_execute(calc);

    calc_destroy(calc);
    scan_destroy(scan);
    eval_destroy(eval);
    stack_destroy(stack);
    
    return EXIT_SUCCESS;
}
