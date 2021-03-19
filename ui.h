#ifndef UI_H
#define UI_H

int screen_h, screen_w;
int	calendar_h, calendar_w;
int events_h, events_w, events_hfactor, events_wfactor;
int longmonth;
WINDOW *calendarwin, *eventswin, *promptwin;

void start_color_pairs();
void init_windows();
void draw_calendarwin(int working_month, int working_year);
void redraw_calendarwin(int working_month, int working_year);
void draw_eventswin_border();
void draw_eventswin_dates(int selected_day, int month, int year);
void draw_eventswin_event(EVENT *ev);
void redraw_eventswin(int selected_day, int month, int year);
void factor_eventswin(); // if days_in_month(working_month) + first_day_offset > 35 { factor_eventswin }
void echo_promptwin(int key);

#endif