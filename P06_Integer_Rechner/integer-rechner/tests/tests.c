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
#include "stack.h"

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
static void test_stack_new(void)
{
    // arrange
    const size_t size = 2;
    // act
    stack_t *instance = stack_new(size);
    // assert
    CU_ASSERT_PTR_NOT_NULL_FATAL(instance);
    CU_ASSERT_EQUAL(stack_is_empty(instance), 1);
    // cleanup
    stack_destroy(instance);
}

static void test_stack_push(void)
{
    // arrange
    const size_t size = 2;
    stack_t *instance = stack_new(size);
    CU_ASSERT_PTR_NOT_NULL_FATAL(instance);
    // act & assert
    for(size_t i = 0; i < size; i++) {
        stack_push(instance, i);
        CU_ASSERT_EQUAL(stack_top(instance), i);
    }
    // cleanup
    stack_destroy(instance);
}

static void test_stack_top(void)
{
    // arrange
    const size_t size = 2;
    stack_t *instance = stack_new(size);
    CU_ASSERT_PTR_NOT_NULL_FATAL(instance);
    // act & assert
    CU_ASSERT_EQUAL(stack_is_empty(instance), 1);
    for(size_t i = 0; i < size; i++) {
        CU_ASSERT_EQUAL(stack_is_full(instance), 0);
        stack_push(instance, i);
        CU_ASSERT_EQUAL(stack_is_empty(instance), 0);
        CU_ASSERT_EQUAL(stack_top(instance), i);
    }
    CU_ASSERT_EQUAL(stack_is_full(instance), 1);
    // cleanup
    stack_destroy(instance);
}

static void test_stack_pop(void)
{
    // arrange
    const size_t size = 2;
    stack_t *instance = stack_new(size);
    CU_ASSERT_PTR_NOT_NULL_FATAL(instance);
    for(size_t i = 0; i < size; i++) {
        stack_push(instance, i);
    }
    // act & assert
    for(size_t i = size; i > 0; i--) {
        CU_ASSERT_EQUAL(stack_is_empty(instance), 0);
        CU_ASSERT_EQUAL(stack_pop(instance), i-1);
        CU_ASSERT_EQUAL(stack_is_full(instance), 0);
    }
    // cleanup
    stack_destroy(instance);
}

static void test_stack_is_empty(void)
{
    // arrange
    const size_t size = 2;
    stack_t *instance = stack_new(size);
    CU_ASSERT_PTR_NOT_NULL_FATAL(instance);
    // act & assert
    CU_ASSERT_EQUAL(stack_is_empty(instance), 1);
    for(size_t i = 0; i < size; i++) {
        stack_push(instance, i);
        CU_ASSERT_EQUAL(stack_is_empty(instance), 0);
    }
    for(size_t i = size; i > 0; i--) {
        CU_ASSERT_EQUAL(stack_is_empty(instance), 0);
        stack_pop(instance);
    }
    CU_ASSERT_EQUAL(stack_is_empty(instance), 1);
    // cleanup
    stack_destroy(instance);
}

static void test_stack_is_full(void)
{
    // arrange
    const size_t size = 2;
    stack_t *instance = stack_new(size);
    CU_ASSERT_PTR_NOT_NULL_FATAL(instance);
    // act & assert
    CU_ASSERT_EQUAL(stack_is_full(instance), 0);
    for(size_t i = 0; i < size; i++) {
        CU_ASSERT_EQUAL(stack_is_full(instance), 0);
        stack_push(instance, i);
    }
    CU_ASSERT_EQUAL(stack_is_full(instance), 1);
    for(size_t i = size; i > 0; i--) {
        stack_pop(instance);
        CU_ASSERT_EQUAL(stack_is_full(instance), 0);
    }
    CU_ASSERT_EQUAL(stack_is_full(instance), 0);
    // cleanup
    stack_destroy(instance);
}

static void test_silent(void)
{
    const char *out_txt[] = {
        "--- RESULT ---\n",
        "dec=3\n",
        "hex=0x00000003\n",
        "oct=000000000003\n",
        "bin=0b00000000000000000000000000000011\n",
    };
    const char *err_txt[] = {
        NULL,
    };
    
    // arrange & act & assert
    CU_ASSERT_EQUAL_FATAL(WEXITSTATUS(system("echo '1 + 2' | " XSTR(TARGET) " 0 >" OUTFILE " 2>" ERRFILE)), OK);
    assert_lines(OUTFILE, out_txt, sizeof(out_txt)/sizeof(*out_txt));
    assert_lines(ERRFILE, err_txt, sizeof(err_txt)/sizeof(*err_txt));
    // arrange & act & assert
    CU_ASSERT_EQUAL_FATAL(WEXITSTATUS(system("echo '1 + 2' | " XSTR(TARGET) "   >" OUTFILE " 2>" ERRFILE)), OK);
    assert_lines(OUTFILE, out_txt, sizeof(out_txt)/sizeof(*out_txt));
    assert_lines(ERRFILE, err_txt, sizeof(err_txt)/sizeof(*err_txt));
}

static void test_verbose(void)
{
    const char *out_txt[] = {
        "--- RESULT ---\n",
        "dec=3\n",
        "hex=0x00000003\n",
        "oct=000000000003\n",
        "bin=0b00000000000000000000000000000011\n",
    };
    const char *err_txt[] = {
        "hex=0x00000001\n",
        "hex=0x00000002\n",
        "OP_ADD\n",
    };
    
    
    // arrange & act & assert
    CU_ASSERT_EQUAL_FATAL(WEXITSTATUS(system("echo '1 + 2' | " XSTR(TARGET) " 1 >" OUTFILE " 2>" ERRFILE)), OK);
    assert_lines(OUTFILE, out_txt, sizeof(out_txt)/sizeof(*out_txt));
    assert_lines(ERRFILE, err_txt, sizeof(err_txt)/sizeof(*err_txt));
}

static void test_all(void)
{
    const char *out_txt[] = {
        "--- RESULT ---\n",
        "dec=8\n",
        "hex=0x00000008\n",
        "oct=000000000010\n",
        "bin=0b00000000000000000000000000001000\n",
    };
    const char *err_txt[] = {
        NULL,
    };
    
    
    // arrange & act & assert
    CU_ASSERT_EQUAL_FATAL(WEXITSTATUS(system("echo '(8 | 7 ^ 5) & 4 << 3 + 2 * (~1+(1>>0))' | " XSTR(TARGET) "  >" OUTFILE " 2>" ERRFILE)), OK);
    assert_lines(OUTFILE, out_txt, sizeof(out_txt)/sizeof(*out_txt));
    assert_lines(ERRFILE, err_txt, sizeof(err_txt)/sizeof(*err_txt));
}

static void test_error(void)
{
    const char *out_txt[] = {
        NULL,
    };
    const char *err_txt[] = {
        "ERROR: at or near position 5: number or '(' ... ')' expected\n",
    };
    
    // arrange & act & assert
    CU_ASSERT_EQUAL_FATAL(WEXITSTATUS(system("echo '1 + ' | " XSTR(TARGET) " >" OUTFILE " 2>" ERRFILE)), FAIL);
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
                  , test_stack_new
                  , test_stack_push
                  , test_stack_top
                  , test_stack_pop
                  , test_stack_is_empty
                  , test_stack_is_full
                  , test_silent
                  , test_verbose
                  , test_all
                  , test_error
                  );
}
