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

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include "scan.h"
#include "error.h"

/**
 * @brief  The details of the otherwise opaque type.
 */
struct scan {
    size_t count;       ///< counts the read characters (used for error reporting)
    int la;             ///< look-ahead-1 character
    int token;          ///< the currently recognized token
    unsigned int value; ///< the current TK_NUM value
};


static int next_char(scan_t *instance)
{
    assert(instance);
    instance->la = getc(stdin);
    if (instance->la != EOF) instance->count++;
    return instance->la;
}

static int curr_char(scan_t *instance)
{
    assert(instance);
    return instance->la;
}

static int skip_chars(scan_t *instance)
{
    assert(instance);
    while(instance->la != EOF && isspace(instance->la)) next_char(instance);
    return instance->la;
}

static int eof(scan_t *instance)
{
    assert(instance);
    //  printf("eof?\n");
    if (curr_char(instance) == EOF) {
        instance->token = TK_EOT;
        return 1;
    }
    return 0;
}

static int op1(scan_t *instance, const char ops[])
{
    assert(instance);
    //  printf("op1?\n");
    assert(ops);
    if (strchr(ops, curr_char(instance))) {
        instance->token = curr_char(instance);
        next_char(instance);
        return 1;
    }
    return 0;
}

static int op2(scan_t *instance, const char *op, int t)
{
    assert(instance);
    //  printf("op2?\n");
    assert(op);
    assert(strlen(op) == 2);
    if (curr_char(instance) == op[0] && next_char(instance) == op[1]) {
        instance->token = t;
        next_char(instance);
        return 1;
    }
    return 0;
}

static int number(scan_t *instance)
{
    assert(instance);
    //  printf("number\n");
    int c = curr_char(instance);
    if (c == '0') {
        instance->value = 0;
        instance->token = TK_NUM;
        c = next_char(instance);
        if (strchr("xX", c)) {
            instance->token = TK_ERROR;
            c = next_char(instance);
            while(isxdigit(c) || c == '_') {
                if (c != '_') {
                    instance->value *= 16;
                    instance->token = TK_NUM;
                    if (isdigit(c)) {
                        instance->value += c - '0';
                    } else {
                        instance->value += 10 + c - (isupper(c) ? 'A' : 'a');
                    }
                }
                c = next_char(instance);
            }
        } else if (strchr("bB", c)) {
            instance->token = TK_ERROR;
            c = next_char(instance);
            while(strchr("01_", c)) {
                if (c != '_') {
                    instance->value *= 2;
                    instance->value += c - '0';
                    instance->token = TK_NUM;
                }
                c = next_char(instance);
            }
        } else if (strchr("01234567_", c)) {
            while(strchr("01234567_", c)) {
                if (c != '_') {
                    instance->value *= 8;
                    instance->value += c - '0';
                }
                c = next_char(instance);
            }
        }
        return 1;
    } else if (isdigit(c)) {
        instance->value = 0;
        while(isdigit(c) || c == '_') {
            if (c != '_') {
                instance->value *= 10;
                instance->value += c - '0';
                c = next_char(instance);
            }
        }
        instance->token = TK_NUM;
        return 1;
    }
    return 0;
}



scan_t *scan_new()
{
    scan_t *instance = malloc(sizeof(scan_t));
    if (!instance) error_fatal_errno("scan_new: instance");
    instance->count = 0;
    instance->la    = EOF;
    instance->token = TK_EOT;
    instance->value = 0;
    return instance;
}

void scan_destroy(scan_t *instance)
{
    assert(instance);
    free(instance);
}

int scan_next_token(scan_t *instance)
{
    assert(instance);
    //  printf("next...\n");
    int c = curr_char(instance);
    if (c == EOF) c = next_char(instance); // initial (or final) situation
    c = skip_chars(instance);
    error_set_pos(instance->count);
    
    instance->token = TK_ERROR;
    instance->value = 0;
    
    if (eof(instance) || op1(instance, "+-*%/|^&~()") || op2(instance, "<<", TK_LSHIFT) || op2(instance, ">>", TK_RSHIFT) || number(instance)) {
        // one of the above was found
        skip_chars(instance);
    }

    //  printf("next = %d\n", token);
    return instance->token;
}

int scan_curr_token(scan_t *instance)
{
    assert(instance);
    return instance->token;
}

unsigned int scan_curr_value(scan_t *instance)
{
    assert(instance);
    if (scan_curr_token(instance) != TK_NUM) error_fatal_errno("scan_curr_value: wrong token");
    return instance->value;
}
