/**
 * @file
 * @brief  Access to the GCC produced dependency data (via gcc -H command line option).
 */

// begin of include guard
#ifndef DATA_H
#define DATA_H

// includes which are needed in this header file
#include <stdlib.h>


/**
* @brief Directory container for file entries of the dependency file.
*/
typedef struct {
 const char *name; ///< @brief the path name of the directory as given gcc.
} dir_t;


/**
* @brief File container for the file entries of the dependency file.
*/
typedef struct {
 const char *name; ///< @brief The base name of the file as given by gcc.
 size_t dir; ///< @brief The index of the directory entry.
 size_t level; ///< @brief The level as given by gcc.
} file_t;




/**
* @brief Overall container for all directories and all files from gcc.
*/
typedef struct {
 size_t n_dirs; ///< @brief The number of valid entries in the dirs list.
 dir_t *dirs; ///< @brief The list of directories.
 size_t n_files; ///< @brief The number of valid entries in the files list.
 file_t *files; ///< @brief The list of files from the dependency file.
} data_t;




/**
* @brief Entry function to read the dependency data from stdin.
* @param root [IN] The name of the root file.
* @return The container of the read data from stdin.
*/
const data_t data_read_all(const char *root);



// end of include guard
#endif // DATA_H
