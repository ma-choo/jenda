#ifndef CALENDARMATH_H
#define CALENDARMATH_H

const char *month_name[12];
const char *mon_name[12];
const char *day_name[7];

int days_in_month[12];
int current_day, current_month, current_year;
int next_month, last_month, working_month;
int next_year, last_year, working_year;
struct tm *current_time;

void init_current_time();
void set_working_month(int i);
void determine_leap_year(int year);
int first_day_offset(int month, int year);
int get_first_day_offset();
int set_first_day_offset();

#endif