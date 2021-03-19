#include <stdlib.h>
#include "calendar.h"

CALENDAR *newcalendar(char *name)
{
	CALENDAR *cal = malloc(sizeof(CALENDAR));
	cal->name = name;
	cal->hidden = 0;
	return cal;
}