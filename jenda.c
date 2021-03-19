#include <stdlib.h>
#include <time.h>
#include <curses.h>

#include "calendarmath.h"
#include "calendar.h"
#include "event.h"
#include "ui.h"

int main()
{
	init_current_time();
	determine_leap_year(current_year);
	initscr();
	noecho();
	start_color_pairs();
	init_windows();
	
	int selected_day = current_day;
	
	EVENT *testevent = newevent("Twins bday", 16, 4, 2021);
	
	draw_calendarwin(working_month, working_year);
	draw_eventswin_border();
	draw_eventswin_dates(selected_day, working_month, working_year);
	
	int listwin_height = events_h - calendar_h;
	int listwin_width = calendar_w;
	WINDOW *listwin = newwin(listwin_height, listwin_width, calendar_h, 0);
	box(listwin, 0, 0);
	mvwprintw(listwin, 0, 1, "Calendars");
	
	CALENDAR *calendars[] =
	{
		newcalendar("My Calendar"),
		newcalendar("Work Schedule"),
		newcalendar("English Class"),
		newcalendar("Math Class")
	};

	for(int i = 0; i < 4; i++)
	{
		wattron(listwin, COLOR_PAIR(i + 1));
		mvwprintw(listwin, i + 1, 1, "%s", calendars[i]->name);
		wattroff(listwin, COLOR_PAIR(i + 1));
	}
	
	// WINDOW *promptwin = newwin(1, screen_w, listwin_height + calendar_h, 0);
	// mvwprintw(promptwin, 0, 0, "jenda version 0.01 - type '?' for help");
	
	refresh();
	wrefresh(calendarwin);
	wrefresh(eventswin);
	wrefresh(listwin);
	wrefresh(promptwin);

	int running = 1;
	int key = 0;
	
	while(running)
	{
		draw_eventswin_dates(selected_day, working_month, working_year);
		wrefresh(eventswin);
		echo_promptwin(key);
		key = getch();
		
		switch(key)
		{
			case 100: // d
			selected_day++;
			if(selected_day > days_in_month[working_month])
			{
				set_working_month(1);
				selected_day = 1;
				redraw_eventswin(selected_day, working_month, working_year);
				draw_eventswin_event(testevent);
				redraw_calendarwin(working_month, working_year);
			}
			break;
			case 68: // D
			selected_day--;
			if(selected_day < 1)
			{
				set_working_month(-1);
				selected_day = days_in_month[working_month];
				redraw_eventswin(selected_day, working_month, working_year);
				draw_eventswin_event(testevent);
				redraw_calendarwin(working_month, working_year);
			}
			break;
			case 119: // w
			selected_day += 7;	
			if(selected_day > days_in_month[working_month])
			{
				selected_day -= days_in_month[working_month]; 
				set_working_month(1);
				redraw_eventswin(selected_day, working_month, working_year);
				draw_eventswin_event(testevent);
				redraw_calendarwin(working_month, working_year);
			}
			break;
			case 87: // W
			selected_day -= 7;	
			if(selected_day < 1)
			{
				set_working_month(-1);
				selected_day += days_in_month[working_month];
				redraw_eventswin(selected_day, working_month, working_year);
				draw_eventswin_event(testevent);
				redraw_calendarwin(working_month, working_year);
			}
			break;
			case 113: // q
			running = 0;
			break;
		}
	}

	delwin(eventswin);
	delwin(calendarwin);
	delwin(listwin);
	delwin(promptwin);
	endwin();

	return 0;
}