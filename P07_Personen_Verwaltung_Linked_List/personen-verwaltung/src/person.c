#include <string.h>
#include "person.h"

#define STR_MIN(a,b) (strlen(a)<strlen(b))?strlen(a):strlen(b)

/**
* @brief Compares two persons in this sequence: 1st=name, 2nd=first_name, 3rd=age
* @param a [IN] const reference to 1st person in the comparison
* @param b [IN] const reference to 2nd person in the comparison
* @return =0 if all record fields are the same
* >0 if all previous fields are the same, but for this field, a is greater
* <0 if all previous fields are the same, but for this field, b is greater
* @remark strncmp() is used for producing the result of string field comparisons
* @remark a->age – b->age is used for producing the result of age comparison
*/
int person_compare(const person_t *a, const person_t *b) {

    int compare = 0;

	if((compare = strncmp(a->name, b->name, STR_MIN(a->name, b->name)))) {
		return compare;
	}
	else if((compare = strncmp(a->first_name, b->first_name, STR_MIN(a->first_name, b->first_name)))) {
		return compare;
	}
	else if((compare = a->age - b->age)) {
		return compare;
	}

	return compare; // both people are the same
}
