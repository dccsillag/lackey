/*
 * Copyright (C) 2012-2013 Andy Spencer <andy753421@gmail.com>
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

#include <string.h>
#include <ncurses.h>

#include "util.h"
#include "date.h"
#include "cal.h"
#include "view.h"

/* Static data */
static WINDOW *win;

/* Month init */
void month_init(WINDOW *_win)
{
    win = _win;
}

/* Month size */
void month_size(int rows, int cols)
{
}

/* Month draw */
void month_draw(void)
{
    const char *name  = month_to_string(SEL.month);
    const int   start = start_of_month(SEL.year, SEL.month);
    const int   days  = days_in_month(SEL.year, SEL.month);
    const int   weeks = weeks_in_month(SEL.year, SEL.month);
    const int   hdr   = COMPACT ? 3 : 4;
    const float midpt = (float)COLS/2.0 - (strlen(name) + 1 + 4)/2.0;
    const float hstep = (float)(COLS-1)/7.0;
    const float vstep = (float)(LINES-2-hdr+COMPACT)/weeks;

    /* Load cal data */
    cal_load(SEL.year, SEL.month, 0, days);

    /* Print Header */
    if (COMPACT) wattron(win, A_REVERSE | A_BOLD);
    if (COMPACT) mvwhline(win, 0, 0, ' ' | A_REVERSE | A_BOLD, COLS);
    if (COMPACT) mvwhline(win, 1, 0, ' ' | A_REVERSE | A_BOLD, COLS);
    mvwprintw(win, 0, midpt, "%s %d", name, SEL.year);
    for (int d = 0; d < 7; d++) {
        const char *str = hstep >= 10 ? day_to_string(d+SUN) : day_to_str(d+SUN);
        mvwprintw(win, 1, ROUND(1+d*hstep), "%s", str);
    }
    if (COMPACT)  wattroff(win, A_REVERSE | A_BOLD);
    if (!COMPACT) mvwhline(win, 2, 0, ACS_HLINE, COLS);

    /* Print days */
    for (int d = 0; d < days; d++) {
        int row = (start + d) / 7;
        int col = (start + d) % 7;
        int is_selected = d == SEL.day;
        int is_today = SEL.year == NOW.year && SEL.month == NOW.month && d == NOW.day;
        if (is_selected) wattron(win, A_BOLD);
        if (is_today)    wattron(win, A_STANDOUT);
        mvwprintw(win, ROUND(hdr+row*vstep), ROUND(1+col*hstep), "%d", d+1);
        if (is_selected) wattroff(win, A_BOLD);
        if (is_today)    wattroff(win, A_STANDOUT);
    }

    /* Print events */
    event_t *event = EVENTS;
    for (int d = 0; d < days; d++) {
        int y = ROUND(hdr+(((start + d) / 7)  )*vstep);
        int e = ROUND(hdr+(((start + d) / 7)+1)*vstep)-2;
        int x = ROUND(1  +(((start + d) % 7)  )*hstep)+3;
        int w = ROUND(1  +(((start + d) % 7)+1)*hstep)-x-1;
        while (event && before(&event->start, SEL.year, SEL.month, d, 24, 0)) {
            if (!before(&event->start, SEL.year, SEL.month, d, 0, 0)){
                if (y == e) mvwhline(win, y, x-3, ACS_DARROW, 2);
                if (y <= e) event_line(win, event, y, x, w, 0);
                y++;
            }
            event = event->next;
        }
    }

    /* Print lines */
    for (int w = 1; w < weeks; w++)
        mvwhline(win, ROUND(hdr-1+w*vstep), 1, ACS_HLINE, COLS-2);
    for (int d = 1; d < 7; d++) {
        int top = d >=  start             ? 0     : 1;
        int bot = d <= (start+days-1)%7+1 ? weeks : weeks-1;
        mvwvline(win, ROUND(hdr+top*vstep), ROUND(d*hstep),
                ACS_VLINE, (bot-top)*vstep);
        for (int w = 1; w < weeks; w++) {
            int chr = w == top ? ACS_TTEE :
                  w == bot ? ACS_BTEE : ACS_PLUS;
            mvwaddch(win, ROUND(hdr-1+w*vstep), ROUND(d*hstep), chr);
        }
    }

    /* Draw today */
    int col = day_of_week(SEL.year, SEL.month, SEL.day);
    int row = (start+SEL.day) / 7;
    int l = ROUND((col+0)*hstep);
    int r = ROUND((col+1)*hstep);
    int t = ROUND((row+0)*vstep+hdr-1);
    int b = ROUND((row+1)*vstep+hdr-1);
    mvwvline_set(win, t, l, WACS_T_VLINE, b-t);
    mvwvline_set(win, t, r, WACS_T_VLINE, b-t);
    mvwhline_set(win, t, l, WACS_T_HLINE, r-l);
    mvwhline_set(win, b, l, WACS_T_HLINE, r-l);
    mvwadd_wch(win, t, l, WACS_T_ULCORNER);
    mvwadd_wch(win, t, r, WACS_T_URCORNER);
    mvwadd_wch(win, b, l, WACS_T_LLCORNER);
    mvwadd_wch(win, b, r, WACS_T_LRCORNER);
}

/* Month run */
int month_run(int key, mmask_t btn, int row, int col)
{
    wday_t weekday = day_of_week(SEL.year, SEL.month, SEL.day);

    int days = 0, months = 0;
    switch (key)
    {
        case 'h': days   = weekday > 0 ? -1 : 0; break;
        case 'j': days   =  7;                   break;
        case 'k': days   = -7;                   break;
        case 'l': days   = weekday < 6 ?  1 : 0; break;
        case 'i': months = -1;                   break;
        case 'o': months =  1;                   break;
        case 't': SEL = NOW;                     break;
        default:               return 0;
    }

    add_days(&SEL.year, &SEL.month, &SEL.day, days);
    add_months(&SEL.year, &SEL.month, months);
    werase(win);
    month_draw();
    wrefresh(win);

    return 1;
}
