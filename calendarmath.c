#include <time.h>

const char *month_name[] =
{
	"January",   "February", "March",    "April",
	"May",       "June",     "July",     "August",
	"September", "October",  "November", "December"
};

const char *mon_name[] =
{
	"Jan", "Feb", "Mar", "Apr",
	"May", "Jun", "Jul", "Aug",
	"Sep", "Oct", "Nov", "Dec"
};

const char *day_name[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

int days_in_month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
int current_day, current_month, current_year;
int next_month, last_month, working_month;
int next_year, last_year, working_year;
struct tm *current_time;

void init_current_time()
{
	time_t s, val = 1;
	s = time(NULL);
	current_time = localtime(&s);
	
	current_day = current_time->tm_mday;
	current_month = current_time->tm_mon;
	current_year = current_time->tm_year + 1900;
	
	working_month = current_month;
	working_year = current_year;
	next_month = current_month + 1;
	next_year = current_year + 1;
	last_month = current_month - 1;
	last_year = current_year - 1;
}

void set_working_month(int i)
{
	working_month += i;
	next_month += i;
	last_month += i;
}

void determine_leap_year(int year)
{
	if((year % 4 == 0 && year % 100 != 0) || year % 400 ==0) days_in_month[1] = 29;
	else days_in_month[1] = 28;
}

int first_day_offset(int month, int year)
{
	month++; // Normalize month for Zeller's congruance
    int day = 1, z_month, z_year, zeller;

    if(month < 3) z_month = month+10;
    else z_month = month-2;
    if(z_month > 10) z_year = year-1;
    else z_year = year;
    zeller = ((int)((13 * z_month - 1) / 5) + day + z_year % 100 +
             (int)((z_year % 100) / 4) - 2 * (int)(z_year / 100) +
             (int)(z_year / 400) + 77) % 7;

    return zeller;
}

int get_first_day_offset()
{
	int offset = first_day_offset(working_month, working_year);
	return offset;
}