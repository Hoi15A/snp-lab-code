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
 * @brief Errors
 */
#include <stdio.h>
#include <stdlib.h>
#include "error.h"

static size_t context = 0;
void error_set_pos(size_t pos)
{
    context = pos;
}

void error_fatal(const char message[])
{
    fprintf(stderr, "ERROR: at or near position %zd: %s\n", context, message);
    exit(EXIT_FAILURE);
}

void error_fatal_errno(const char message[])
{
    fprintf(stderr, "ERROR: at or near position %zd: ", context);
    perror(message);
    exit(EXIT_FAILURE);
}

