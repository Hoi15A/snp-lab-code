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
 * @brief Lab P02 QR Code
 * @remark prerequisite: sudo apt install qrencode
 */
#include <stdio.h>
#include <stdlib.h>

// define local macros
#define RESET "\033[0m\n"
#define BLACK "\033[40m "
#define WHITE "\033[47m "

/**
 * @brief   main function
 * @returns always success (0)
 */
int main() {
	(void)printf(RESET);
	char c;

	while ((c = fgetc(stdin)) != EOF) {
		if (c == '\n') {
			(void)printf(RESET);
		} else if (c == ' ') {
			(void)printf(WHITE);
		} else {
			(void)printf(BLACK);
		}
	}
	
	(void)printf(RESET);
	return EXIT_SUCCESS;
}
