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

/* Cal status types */
typedef enum {
	NEW  = 0,
	DONE = 100,
} status_t;

/* Calendar type */
typedef struct {
	char *name;
	char *desc;
	void *data;
} cal_t;

/* Calendar item types */
typedef struct event_t {
	const char     *name;
	const char     *desc;
	const char     *loc;
	const char     *cat;
	date_t          start;
	date_t          end;
	const cal_t    *cal;
	struct event_t *next;
} event_t;

typedef struct todo_t {
	const char    *name;
	const char    *desc;
	const char    *cat;
	status_t       status;
	date_t         start;
	date_t         due;
	cal_t         *cal;
	struct todo_t *next;
} todo_t;

/* Global data */
extern event_t *EVENTS;
extern todo_t  *TODOS;

/* Calendar functions */
void cal_init(void);

/* Test fuctions */
void ical_test(void);
