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
 * @brief Test suite for the given package.
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <assert.h>
#include <CUnit/Basic.h>
#include "test_utils.h"

#ifndef TARGET // must be given by the make file --> see test target
#error missing TARGET define
#endif

/// @brief alias for EXIT_SUCCESS
#define OK   EXIT_SUCCESS
/// @brief alias for EXIT_FAILURE
#define FAIL EXIT_FAILURE

/// @brief The name of the STDOUT text file.
#define OUTFILE "stdout.txt"
/// @brief The name of the STDERR text file.
#define ERRFILE "stderr.txt"

#define TRACE_INDENT "\n                " ///< allow for better stdout formatting in case of error

#define PATH_SIZE 256

// setup & cleanup
static int setup(void)
{
    remove_file_if_exists(OUTFILE);
    remove_file_if_exists(ERRFILE);
    return 0; // success
}

static int teardown(void)
{
    // Do nothing.
    // Especially: do not remove result files - they are removed in int setup(void) *before* running a test.
    return 0; // success
}

// tests
static void test_paths(void)
{
    // arrange
    const char *name = strrchr(XSTR(TARGET), '/');
    name = name ? name+1 : XSTR(TARGET);

    char buf[PATH_SIZE] = { 0 };
    snprintf(buf, PATH_SIZE, "4:../bin:%s\n", name);
    
    const char *out_txt[] =
        { "1:.:runtest\n"
          , buf
        };
    const char *err_txt[] = { NULL };
    // act
    int exit_code = system(XSTR(TARGET) " .::..:../bin 1>" OUTFILE " 2>" ERRFILE);
    // assert
    CU_ASSERT_EQUAL(WEXITSTATUS(exit_code), EXIT_SUCCESS);
    assert_lines(OUTFILE, out_txt, sizeof(out_txt)/sizeof(*out_txt));
    assert_lines(ERRFILE, err_txt, sizeof(err_txt)/sizeof(*err_txt));
}

/**
 * @brief Registers and runs the tests.
 * @returns success (0) or one of the CU_ErrorCode (>0)
 */
int main(void)
{
    // setup, run, teardown
    TestMainBasic("lab test", setup, teardown
                  , test_paths
                  );
}
