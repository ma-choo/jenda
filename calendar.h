#ifndef CALENDAR_H
#define CALENDAR_H

typedef struct
{
	char *name;
	int hidden;
} CALENDAR;

CALENDAR *newcalendar(char *name);

#endif