/**
 * @file
 * @brief  Provides output functions for various file formats.
 */
// define proper header file here, with include gaurd, etc.
#ifndef OUTPUT_H
#define OUTPUT_H

#include "data.h"

/**
* @brief Produces DOT output of the dependencies given in data.
* @param data [IN] Container of the dependency data.
*/
void output_dot(const data_t data);


#endif // OUTPUT_H

