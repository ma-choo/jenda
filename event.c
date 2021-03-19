#include <stdlib.h>
#include "event.h"

EVENT *newevent(char *name, int day, int month, int year)
{
	EVENT *ev = malloc(sizeof(EVENT));
	ev->name = name;
	ev->day = day;
	ev->month = month;
	ev->year = year;
	ev->completed = 0;
	return ev;
}