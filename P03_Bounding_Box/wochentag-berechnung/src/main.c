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
 * @brief Lab P03 weekday
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

 // *** TASK1: typedef enum types for month_t (Jan=1,...Dec} ***
typedef enum {
    Jan = 1,
    Feb,
    Mar,
    Apr,
    Mai,
    Jun,
    Jul,
    Aug,
    Sep,
    Oct,
    Nov,
    Dec,
} month_t;


// *** TASK1: typedef struct for date_t ***
typedef struct {
    int day;
    int month;
    int year;
} date_t;

// *** TASK2: typedef enum weekday_t (Sun=0, Mon, ...Sat) ***
typedef enum {
    Sun = 0,
    Mon,
    Tue,
    Wed,
    Thu,
    Fri,
    Sat,
} weekday_t;

/**
 * @brief   TASK1: Checks if the given date is a leap year.
 * @return 0 = is not leap year, 1 = is leap year
 */
int checkLeapYear(int checkyear) {
    if (checkyear % 4 == 0) {
        if (checkyear % 100 == 0) {
            if (checkyear % 400 == 0)
                return 1;
            else
                return 0;
        }
        else
            return 1;
    }
    else
        return 0;
}

/**
 * @brief   TASK1: Calculates the length of the month given by the data parameter
 * @return 28, 29, 30, 31 if a valid month, else 0
 */
int lengthOfMonth(date_t date) {
    if (date.month == Apr || date.month == Jun || date.month == Sep || date.month == Nov) {
        return 30;
    }
    else if (date.month == Jan || date.month == Mar || date.month == Mai || date.month == Jul || date.month == Aug || date.month == Oct || date.month == Dec) {
        return 31;
    }
    else if (date.month == Feb && !checkLeapYear(date.year)) {
        return 28;
    }
    else if (date.month == Feb && checkLeapYear(date.year)) {
        return 29;
    }
    else {
        return 0;
    }
}

/**
 * @brief   TASK1: Checks if the given date is in the gregorian date range
 * @return 0 = no, 1 = yes
 */
int isGregorian(date_t date) {
    if ((date.year > 1582) && (date.year < 10000)) {
        return 1;
    }
    else if (date.year == 1582) {
        if (date.month > 10) {
            return 1;
        }
        else if (date.month == 10 && date.day >= 15) {
            return 1;
        }
        else {
            return 0;
        }
    }
    else {
        return 0;
    }
}

/**
 * @brief   TASK1: Checks if the given date is a valid date.
 * @return 0 = is not valid date, 1 = is valid date
 */
int  is_valid_date(date_t date) {
    if ((13 > date.month) && (lengthOfMonth(date) >= date.day) && (date.year < 10000) && (date.month > 0) && isGregorian(date) && (date.day > 0)) {
        return 1;
    }
    else {
        return 0;
    }
}


/**
 * @brief   TASK2: calculated from a valid date the weekday
 * @return return a weekday in the range Sun...Sat
 */
weekday_t calculateWeekday(date_t date) {
    assert(is_valid_date(date));
    int a = 0;
    int m = 1 + (date.month + 9) % 12;
    if (date.month < 3) {
        a = date.year - 1;
    }
    else {
        a = date.year;
    }
    int y = a % 100;
    int c = a / 100;
    int weekday = ((date.day + (13 * m - 1) / 5 + y + y / 4 + c / 4 - 2 * c) % 7 + 7) % 7;
    return weekday;
}

/**
 * @brief   TASK2: print weekday as 3-letter abreviated English day name
 */
void print_weekday(weekday_t day) {
    switch (day) {
    case Sun: printf("Sun"); break;
    case Mon: printf("Mon"); break;
    case Tue: printf("Tue"); break;
    case Wed: printf("Wed"); break;
    case Thu: printf("Thu"); break;
    case Fri: printf("Fri"); break;
    case Sat: printf("Sat"); break;
    default: assert(!"day is out-of-range");
    }
}

/**
 * @brief   main function
 * @param   argc [in] number of entries in argv
 * @param   argv [in] program name plus command line arguments
 * @return return success if valid date is given, failure otherwise
 */
int main(int argc, const char* argv[]) {
    // TASK1: parse the mandatory argument into a date_t variable and check if the date is valid
    date_t date;
    int ints;

    if (argc < 2) {
        fprintf(stderr, "date is not valid in format yyyy-mm-dd\n");
        return EXIT_FAILURE;
    }

    ints = sscanf(argv[1], "%d-%d-%d", &date.year, &date.month, &date.day);

    if (ints != 3 || !is_valid_date(date)) {
        fprintf(stderr, "date is not valid\n");
        return EXIT_FAILURE;
    }

    // TASK2: calculate the weekday and print it in this format: "%04d-%02d-%02d is a %s\n"
    isGregorian(date);
    weekday_t weekday = calculateWeekday(date);
    printf("%04d-%02d-%02d is a ", date.year, date.month, date.day);
    print_weekday(weekday);
    printf("\n");


    return EXIT_SUCCESS;
}
