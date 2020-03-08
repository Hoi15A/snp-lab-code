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
		printf("No arguments passed\n");
		return EXIT_FAILURE;
	}

	char *ignored_text;
	uint8_t num = strtol(argv[1], &ignored_text, 10);
	

	if (num < 1 || num > 255) {
		printf("Input out of range 1-255: %s\n", argv[1]);
		return EXIT_FAILURE;
	}
	
	if (argc == 2) {
		
		printf("unsigned: %4u (%#04x)\n", num, num);
		printf("  signed: %4d (%#04x)\n", num, num); // How tf do you print signed hex
		uint8_t added = num + 255;
		printf("    +255: %4u (%#04x)\n", added, added);

		// Pretty sure is wrong but dunno why
		uint8_t ones = ~num;
		printf("   one's: %4u (%#04x)\n", ones, ones);
		uint8_t twos = ~(num + 1);
		printf("   two's: %4u (%#04x)\n", twos, twos);

	} else if (argc == 3) {
		
		uint8_t bit = strtol(argv[2], &ignored_text, 10);
		if (bit < 0 || bit > 7) {
			printf("Input out of range 0-7: %s\n", argv[1]);
			return EXIT_FAILURE;
		}


		printf("               dec   hex   oct\n");
		printf("your input   : %3d   %#04x   %#04o\n", num, num, num);

		if (num & (1<<(bit))) {
			printf("bit %d is set.\n", bit);
		} else {
			printf("bit %d is not set.\n", bit);
		}
		
		uint8_t cleared = num & ~(1UL << bit);
		printf("bit 2 cleared: %3d   %#04x   %#04o\n", cleared, cleared, cleared);

		uint8_t set = num | 1UL << bit;
		printf("bit 2 set    : %3d   %#04x   %#04o\n", set, set, set);

		uint8_t flip = num ^ 1UL << bit;
		printf("bit 2 flipped: %3d   %#04x   %#04o\n", flip, flip, flip);
	} else {
		return EXIT_FAILURE;
	}
	
	
	return EXIT_SUCCESS;
}
