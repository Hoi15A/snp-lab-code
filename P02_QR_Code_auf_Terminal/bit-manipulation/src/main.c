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
 * @brief Lab P02 bit Manipulation
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define USAGE "usage: %s value [bitnr]\n value in the range 0..255\n bitnr in the range 0..7\n"

/**
 * @brief   main function
 * @returns always success (0)
 */
int main(int argc, const char* argv[]) {

	if (argc < 2) {
		(void)printf(USAGE, argv[0]);
		return EXIT_FAILURE;
	}

	char *ignored_text;
	// string scanf instead
	uint8_t num = strtol(argv[1], &ignored_text, 10);
	

	if (num < 0 || num > 255) {
		(void)printf(USAGE, argv[0]);
		return EXIT_FAILURE;
	}
	
	if (argc == 2) {
		
		(void)printf("unsigned: %4u (%#04x)\n", num, num);
		(void)printf("  signed: %4d (%#04x)\n", num, num);
		uint8_t added = num + 255;
		(void)printf("    +255: %4u (%#04x)\n", added, added);

		(void)printf("   one's: %4d (%#04x)\n", ~num, ~num);
		(void)printf("   two's: %4d (%#04x)\n", ~num + 1, ~num + 1);

	} else if (argc == 3) {
		
		uint8_t bit = strtol(argv[2], &ignored_text, 10);
		if (bit < 0 || bit > 7) {
			(void)printf(USAGE, argv[0]);
			return EXIT_FAILURE;
		}


		(void)printf("               dec   hex   oct\n");
		(void)printf("your input   : %3d  0x%02x  %#04o\n", num, num, num);

		if (num & (1<<(bit))) {
			(void)printf("bit %d is set.\n", bit);
		} else {
			(void)printf("bit %d is not set.\n", bit);
		}
		
		uint8_t cleared = num & ~(1UL << bit);
		(void)printf("bit %d cleared: %3d  0x%02x  %#04o\n", bit, cleared, cleared, cleared);

		uint8_t set = num | 1UL << bit;
		(void)printf("bit %d set    : %3d  0x%02x  %#04o\n", bit, set, set, set);

		uint8_t flip = num ^ 1UL << bit;
		(void)printf("bit %d flipped: %3d  0x%02x  %#04o\n", bit, flip, flip, flip);
	} else {
		return EXIT_FAILURE;
	}
	
	
	return EXIT_SUCCESS;
}
