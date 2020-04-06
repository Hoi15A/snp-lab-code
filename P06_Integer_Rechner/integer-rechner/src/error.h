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
 * @brief Error handling
 */

#ifndef _ERROR_H_
#define _ERROR_H_

/**
 * @brief  Sets the context of the current token for potential error reports.
 * @param  pos [IN] The current input start position of the token which is currently processed.
 */
void error_set_pos(size_t pos);

/**
 * @brief  Issues on stderr an error message and terminates the program with EXIT_FAILURE.
 * @param  message [IN] Context information.
 */
void error_fatal(const char message[]);

/**
 * @brief  Issues on stderr an error message (includeing the errno text) and terminates the program with EXIT_FAILURE.
 * @param  message [IN] Context information.
 */
void error_fatal_errno(const char message[]);

#endif // _ERROR_H_
