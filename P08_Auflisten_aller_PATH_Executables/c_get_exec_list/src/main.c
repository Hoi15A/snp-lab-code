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
 * @brief Lab implementation
 */

#include <linux/limits.h> // PATH_MAX
#include <stdlib.h>   // getenv, malloc, free, EXIT_SUCCESS, NULL
#include <string.h>   // strchr
#include <stdio.h>    // printf, sprintf
#include <sys/stat.h> // struct stat, S_ISDIR, S_ISREG
#include <unistd.h>   // stat, access
#include <dirent.h>   // opendir, closedir, readdir, DIR, struct dirent

/**
 * @brief  Creates a copy of the string on the heap.
 * @param  s [IN]  The original string.
 * @return Returns the allocated copy or NULL if s is NULL or if malloc failed.
 * @remark Suggestion: Use the functions malloc(), strcpy().
 */
static char *malloc_copy(const char *s)
{
    char *p = NULL;
    // BEGIN-STUDENTS-TO-ADD-CODE
    if (s == NULL) return NULL;

    int len = strlen(s);
    p = malloc(sizeof(char) * len);

    if (p) {
        strcpy(p, s);
    } else {
        printf("Memory allocation failed");
        return NULL;
    }

    // END-STUDENTS-TO-ADD-CODE
    return p;       
}

/**
 * @brief  Replaces inplace in the buffer all occurances of sep by '\0'.
 * @param  buffer [INOUT] The string which gets searched and modified.
 * @param  sep    [IN]    The separator for which all instances in buffer get replaced by '\0'.
 * @return Returns the number of fields which are separated by sep, or 0 if buffer is NULL.
 * @remark Empty fields are allowed and to be supported, i.e. given by ":..." or by "...::..." or by "...:".
 * @remark Suggestion: Use the function strchr() to search for the separator.
 */
static size_t split_buffer_inplace(char buffer[], char sep)
{
    size_t n = 0;
    // BEGIN-STUDENTS-TO-ADD-CODE
    if(!buffer) {
        return 0;
    }
    char rep = '\0', *temp = buffer;
	while(temp = strchr(temp, sep)) {
		*temp = rep;
		n++;
		temp++;
	};

	// END-STUDENTS-TO-ADD-CODE
    return n;
}

/**
 * @brief  If path is an executable directory, list all executable files located directly in that directory - each such file as i:path:file.
 * @param  i [IN]    The number of the path to report.
 * @param  path [IN] The directory path to search for executables.
 * @remark Suggestion: Use the function is_accessible_dir(), is_executable_file(), opendir(), readdir(), closedir().
 */
static void list_executables(size_t i, const char *path)
{
    // bash:
    //   [ -n "$p" ] || p="."
    //   if [ -d "$p" ] && [ -x "$p" ]
    //   then
    //      find -L "$p" -maxdepth 1 -type f -executable -printf "$i:%h:%f\n"
    //   fi
    const char *p = path && strlen(path) ? path : "."; // replace an empty path by "." as current directory to allow for appending /name
    // BEGIN-STUDENTS-TO-ADD-CODE
    struct stat sb;
    char tmp_path[PATH_MAX];

    if (access(p, F_OK) == -1) {
        return;
    }

    if (stat(p, &sb) == -1) {
        fprintf(stderr, __FILE__ ": Failed to stat file (%s).\n", p);
    }

    if (S_ISDIR(sb.st_mode)) {
        DIR *dir = opendir(p);
        if (dir != NULL) {
            struct dirent *entry;
            while ((entry = readdir(dir))) {
                size_t len = (strlen(p) + 1) + 1 + strlen(entry->d_name);
                snprintf(tmp_path, len, "%s/%s", p, entry->d_name);

                if (entry->d_type == DT_REG && access(tmp_path, X_OK) == 0) {
                    printf("%ld:%s:%s\n", i, p, entry->d_name);
                }
            }
            closedir(dir);
        }
    }
    // END-STUDENTS-TO-ADD-CODE
}

// # from lab P01_Bash
// paths="$1"
// [ -n "$paths" ] || paths="$PATH"
// 
// # input-field-separator: tells the shell to split in the 'for' loop the $var by ":"
// IFS=":"
// 
// for p in $paths
// do
//   i=$((i+1))
//   [ -n "$p" ] || p="."
//   if [ -d "$p" ] && [ -x "$p" ]
//   then
//      find -L "$p" -maxdepth 1 -type f -executable -printf "$i:%h:%f\n" 2>/dev/null
//   fi
// done

int main(int argc, const char *argv[])
{
    char *paths = malloc_copy(argc > 1 && argv[1][0] ? argv[1] : getenv("PATH"));
    size_t n = split_buffer_inplace(paths, ':'); // replaces all ':' by '\0' and returns the number of the resulting fields
    char *p = paths;
    for(size_t i = 1; i <= n; i++) { // 1...n
        list_executables(i, p);
        p += strlen(p) + 1; // readover the field and the trailing '\0' to get to the next field
    }
    free(paths);
    return EXIT_SUCCESS;
}
