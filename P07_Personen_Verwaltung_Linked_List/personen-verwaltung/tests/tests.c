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
#include "../src/person.h"
#include "../src/list.h"

#ifndef TARGET // must be given by the make file --> see test target
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
static const char* first_name = "Stefan";
static const char* name = "Holzer";
static const int age = 18;
static size_t first_name_len;
static size_t name_len;

// setup & cleanup
static int setup(void)
{
	first_name_len = strlen(first_name) + 1; 
	name_len = strlen(name) + 1;
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
static void test_person_compare(void)
{
	// BEGIN-STUDENTS-TO-ADD-CODE
	int d;

	person_t p1, p2;
	strncpy(p1.first_name, first_name, first_name_len);
	strncpy(p2.first_name, first_name, first_name_len);
	strncpy(p1.name, name, name_len);
	strncpy(p2.name, name, name_len);
	p1.age=age;
	p2.age=age;
	// arrange
	d = person_compare(&p2, &p1);
	// act
	CU_ASSERT(d == 0);
	
	// assert
	
	// END-STUDENTS-TO-ADD-CODE
}

static void test_list_insert(void)
{
	// BEGIN-STUDENTS-TO-ADD-CODE
	// arrange
	person_t person1, person2;
	node_t list;
	list.next = NULL;

	strncpy(person1.first_name, name, name_len);
	strncpy(person1.name, first_name, first_name_len);
	person1.age = age + 5;

	strncpy(person2.first_name, first_name, first_name_len);
	strncpy(person2.name, name, name_len);
	person2.age = age;

	// act
	list_insert(&list, person2);
	list_insert(&list, person1);

	list_remove(&list, person2);

	// assert
	// Make sure person 2 is not there anymore
	CU_ASSERT(person_compare(&(list.next->content), &person1) == 0); 
	// END-STUDENTS-TO-ADD-CODE
}

static void test_list_remove(void)
{
	// BEGIN-STUDENTS-TO-ADD-CODE
	// arrange
	person_t person1, person2;
	node_t list;
	list.next = NULL;

	// Two differently named people (non equivalent!, name and first name swapped
	// and different age)
	strncpy(person1.first_name, name, name_len);
	strncpy(person1.name, first_name, first_name_len);
	person1.age = age + 5;

	strncpy(person2.first_name, first_name, first_name_len);
	strncpy(person2.name, name, name_len);
	person2.age = age;

	// act
	list_insert(&list, person2);
	list_insert(&list, person1);

	list_remove(&list, person2);

	// assert
	// Make sure person 2 is not there anymore
	CU_ASSERT(person_compare(&(list.next->content), &person1) == 0); 
	
	// END-STUDENTS-TO-ADD-CODE
}

static void test_list_clear(void)
{
    // BEGIN-STUDENTS-TO-ADD-CODE
    // arrange
    person_t person;
    node_t list;
	list.next = NULL;

    strncpy(person.first_name, first_name, first_name_len);
    strncpy(person.name, name, name_len);
    person.age=age;

    // Add 4 more elements to the list
    for(size_t i = 1; i <= 3; i++) 
    {
    list_insert(&list, person);
    }

    // act
    list_clear(&list);
	
    // assert
    CU_ASSERT(list.next == NULL);
	
	// END-STUDENTS-TO-ADD-CODE
}

/**
 * @brief Registers and runs the tests.
 * @returns success (0) or one of the CU_ErrorCode (>0)
 */
int main(void)
{
    // setup, run, teardown
    TestMainBasic("lab test", setup, teardown
                  , test_person_compare
                  , test_list_insert
                  , test_list_remove
                  , test_list_clear
                  );
}
