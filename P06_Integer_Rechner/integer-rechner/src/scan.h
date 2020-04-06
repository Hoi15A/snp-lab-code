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
 * @brief Infix calculator tokenizer
 */

#ifndef _SCAN_H_
#define _SCAN_H_

/**
 * @brief  Opaque type - detailed in the implementation only.
 */
typedef struct scan scan_t;

/**
 * @brief  Specific token enum values beside the ones provided as plain characters.
 * @remark The last enum value must be below printable ascii code
 */
typedef enum {
    TK_ERROR = 0,   ///< error or end mark for arrays of tokens (must be 0)
    TK_EOT,         ///< end of text, i.e. when EOF is recognized
    TK_LSHIFT,      ///< left-shift operator (2-char token)
    TK_RSHIFT,      ///< right-shift operator (2-char token)
    TK_NUM,         ///< number token (e.g. 3, 0x1F, etc.)
} scan_tk_t;

/**
 * @brief  Construcor.
 * @return The newly created and initialized instance
 * @remark In case of error, the program terminates with EXIT_FAILURE and an appropriate error message.
 */
scan_t *scan_new();

/**
 * @brief  Frees the instances memory and the data it owns.
 * @param  instance [INOUT]  The affected instance.
 * @remark assert(instance) is performed, i.e. it is considered a programming error if instance is NULL.
 */
void scan_destroy(scan_t *instance);

/**
 * @brief  Moves to the next token.
 * @param  instance [INOUT]  The affected instance.
 * @return Returns the next recognized token (single character token or scan_tk_t enum value).
 * @remark assert(instance) is performed, i.e. it is considered a programming error if instance is NULL.
 * @remark If the token is a TK_NUM, the scan_curr_value() function returns the associated value.
 */
int scan_next_token(scan_t *instance);

/**
 * @brief  Gets the token which mas found with the last scan_next_token() call.
 * @param  instance [INOUT]  The affected instance.
 * @return Returns the currently recognized token (single character token or scan_tk_t enum value).
 * @remark assert(instance) is performed, i.e. it is considered a programming error if instance is NULL.
 */
int scan_curr_token(scan_t *instance);

/**
 * @brief  Gets the value associated with the TK_NUM token.
 * @param  instance [INOUT]  The affected instance.
 * @return  Returns the value associated with the current TK_NUM.
 * @remark assert(instance) is performed, i.e. it is considered a programming error if instance is NULL.
 * @remark This only gives valid values if the scan_curr_token() equals TK_NUM.
 */
unsigned int scan_curr_value(scan_t *instance);

#endif // _SCAN_H_
