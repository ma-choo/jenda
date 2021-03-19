#ifndef EVENT_H
#define EVENT_H

typedef struct
{
	char *name;
	int day;
	int month;
	int year;
	int completed;
} EVENT;

EVENT *newevent(char *name, int day, int month, int year);

#endif