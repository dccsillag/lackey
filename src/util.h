/*
 * Copyright (C) 2012 Andy Spencer <andy753421@gmail.com>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef UTIL_H
#define UTIL_H

/* Macros */
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define ROUND(x) ((int)((x)+0.5))
#define N_ELEMENTS(x) (sizeof(x)/sizeof((x)[0]))

/* Time types */
typedef int year_t;
typedef int day_t;

typedef enum {
	JAN =  0,
	FEB =  1,
	MAR =  2,
	APR =  3,
	MAY =  4,
	JUN =  5,
	JUL =  6,
	AUG =  7,
	SEP =  8,
	OCT =  9,
	NOV = 10,
	DEC = 11,
} month_t;

typedef enum {
	SUN = 0,
	MON = 1,
	TUE = 2,
	WED = 3,
	THU = 4,
	FRI = 5,
	SAT = 6,
} wday_t;

/* Time functions */
int is_leap_year(year_t year);
int days_in_year(year_t year);
int days_in_month(year_t year, month_t month);
int weeks_in_month(year_t year, month_t month);
wday_t day_of_week(year_t year, month_t month, day_t day);
wday_t start_of_month(year_t year, month_t month);
day_t start_of_week(year_t year, month_t month, day_t day);
void add_days(year_t *year, month_t *month, day_t *day, int days);
void add_months(year_t *year, month_t *month, int months);

/* Time to string functions */
const char *month_to_str(month_t month);
const char *month_to_string(month_t month);
const char *day_to_st(wday_t day);
const char *day_to_str(wday_t day);
const char *day_to_string(wday_t day);

/* Tests */
void test_time(void);

#endif
