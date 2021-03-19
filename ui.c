#include <curses.h>

#include "event.h"
#include "calendarmath.h"

int screen_h, screen_w;
int	calendar_h, calendar_w;
int events_h, events_w, events_hfactor, events_wfactor;
WINDOW *calendarwin, *eventswin, *promptwin;

void start_color_pairs()
{
	start_color();
	init_pair(1, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_CYAN, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_YELLOW, COLOR_BLACK);
	init_pair(6, COLOR_GREEN, COLOR_BLACK);
	init_pair(7, COLOR_WHITE, COLOR_BLUE);
}

void init_windows()
{
	getmaxyx(stdscr, screen_h, screen_w);
	
	calendar_h = 9;
	calendar_w = 22;
	events_hfactor = (screen_h - 2) / 6;
	events_wfactor = ((screen_w - calendar_w) - 2) / 7;
	events_h = (events_hfactor * 6) + 1;
	events_w = (events_wfactor * 7) + 1;
	
	calendarwin = newwin(calendar_h, calendar_w, 0, 0);
	eventswin = newwin(events_h, events_w, 0, calendar_w);
	promptwin = newwin(1, screen_w, events_h, 0);
}

void draw_calendarwin(int working_month, int working_year)
{
	box(calendarwin, 0, 0);
	mvwprintw(calendarwin, 0, 1, "%s %d", month_name[working_month], working_year);
	mvwprintw(calendarwin, 1, 2, "S  M  T  W  T  F  S");
	
	for(int d = 1, y = 2, x = first_day_offset(working_month, working_year); d <= days_in_month[working_month]; d++)
	{
		if(d == current_day && working_month == current_month)
			wattron(calendarwin, COLOR_PAIR(7));
		else
			wattroff(calendarwin, COLOR_PAIR(7));
		
		mvwprintw(calendarwin, y, x * 3 + 1, "%2d", d);
		if(++x > 6)
		{
			y++;
			x=0;
		}
	}
}

void redraw_calendarwin(int working_month, int working_year)
{
	wclear(calendarwin);
	draw_calendarwin(working_month, working_year);
	wrefresh(calendarwin);
}

void draw_eventswin_border()
{
	for(int y = 1; y < 6; y++)
	{	
		mvwhline(eventswin, events_hfactor * y, 0, ACS_HLINE, events_w);
	}
	for(int x = 1; x < 7; x++)
	{
		mvwvline(eventswin, 0, events_wfactor * x, ACS_VLINE, events_h);
	}
	box(eventswin, 0, 0);
	for (int x = 0; x < 7; x++)
	{
		mvwprintw(eventswin, 0, x * events_wfactor + 1, "%s", day_name[x]);
	}
}

void draw_eventswin_dates(int selected_day, int month, int year)
{
	for(int day = 1, y = 1, x = first_day_offset(month, year); day <= days_in_month[month]; day++)
	{
		if(day == selected_day)
			wattron(eventswin, A_REVERSE);
		else if(day == current_day && working_month == current_month)
			wattron(eventswin, COLOR_PAIR(7));
		
		mvwprintw(eventswin, y, 1 + x * events_wfactor, "%*d", events_wfactor - 1, day);
		if(day == 1) mvwprintw(eventswin, y, x * events_wfactor + 1, "%*s", events_wfactor - 3, mon_name[month]); // make simpler?
		
		if(++x > 6)
		{
			y += events_hfactor;
			x = 0;
		}
		wattroff(eventswin, A_REVERSE);
		wattroff(eventswin, COLOR_PAIR(7));
	}
}

void draw_eventswin_event(EVENT *ev)
{
	if(ev->month != working_month + 1) return; // normalize month on check
	char *eventname = ev->name;
	int day_pos = ev->day - 1 + first_day_offset(working_month, working_year);;
	
	// day_pos = y * 7 + x 
	// solve for y and x
	// translate y and x coordinates in the print function
	int y = day_pos / 7;
	int x = day_pos % 7;
	mvwprintw(eventswin, y * events_hfactor + 2, x * events_wfactor + 1, "%s", eventname);
}

void redraw_eventswin(int selected_day, int month, int year)
{
	wclear(eventswin);
	draw_eventswin_border();
	draw_eventswin_dates(selected_day, month, year);
}

void echo_promptwin(int key)
{
	mvwprintw(promptwin, 0, 0, "%c - ", key);
	switch(key)
	{
		case 100: // d
		mvwprintw(promptwin, 0, 4, "next-day");
		break;
		case 68: // D
		mvwprintw(promptwin, 0, 4, "prev-day");
		break;
		case 119: // w
		mvwprintw(promptwin, 0, 4, "next-week");
		break;                
		case 87: // W         
		mvwprintw(promptwin, 0, 4, "prev-week");
		break;               
		case 110: // n
		mvwprintw(promptwin, 0, 4, "new: [c]alendar, [e]vent");
		break;
		case 113: // q        
		mvwprintw(promptwin, 0, 4, "Are you sure?");
		break;               
		default:             
		mvwprintw(promptwin, 0, 0, "%*jenda version 0.01 - type '?' for help");
	}
	wclrtoeol(promptwin);
	wrefresh(promptwin);
}