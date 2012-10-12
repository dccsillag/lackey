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

#ifndef EVENT_H
#define EVENT_H

#include "util.h"

/* Calendar types */
typedef struct {
	char *name;
	char *desc;
	void *data;
} cal_t;

/* Event types */
typedef struct {
	year_t  year;
	month_t month;
	day_t   day;
	hour_t  hour;
	min_t   min;
} datetime_t;

typedef struct event_t {
	const cal_t    *cal;
	datetime_t      start;
	datetime_t      end;
	const char     *name;
	const char     *desc;
	struct event_t *next;
} event_t;

/* Event functions */
event_t *event_get(year_t year, month_t month, day_t day, int days);

/* Calendar implementation functions */
event_t *dummy_get(cal_t *cal, year_t year, month_t month, day_t day, int days);

#endif