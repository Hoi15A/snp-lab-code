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
 * @brief Infix calculator
 */

#ifndef _CALC_H_
#define _CALC_H_

#include "scan.h"
#include "eval.h"

/**
 * @brief  Opaque type - detailed in the implementation only.
 */
typedef struct calc calc_t;

/**
 * @brief                     Construcor.
 * @param  scan [IN]          Dependency Injection: the serving scanner.
 * @param  eval [IN]          Dependency Injection: the serving evaluator.
 * @return                    The newly created and initialized instance
 * @remark In case of error, the program terminates with EXIT_FAILURE and an appropriate error message.
 * @remark Does not take over ownership of the injected dependencies.
 */
calc_t *calc_new(scan_t *scan, eval_t *eval);

/**
 * @brief  Frees the instances memory and the data it owns.
 * @param  instance [INOUT]  The affected instance.
 * @remark assert(instance) is performed, i.e. it is considered a programming error if instance is NULL.
 */
void calc_destroy(calc_t *instance);

/**
 * @brief  Entry point for processing the expression from stdin.
 * @param  instance [INOUT]  The affected instance.
 * @remark assert(instance) is performed, i.e. it is considered a programming error if instance is NULL.
 */
void calc_execute(calc_t *instance);

#endif // _CALC_H_
