
jenda
=====
A Google Calendar-esque console application.

Building
--------
This requires the PDCurses library to build on Windows. It should build with regular ncurses on Linux, too.

https://pdcurses.org/

Add PDCurses to your gcc library. Until I can figure out makefiles, just run this at the terminal:

	gcc jenda.c calendarmath.c calendar.c event.c ui.c -lpdcurses
	
Roadmap
-------
* Show multiple events in one day.
	* Maybe by adding/popping day_pos to/from stack?
* Show events from the previous month and next month in the events window.
	* Don't be so confined to zeller offsets and a global "working month."
* Read, write, and create calendar files.
	* Create calendar and event structs at runtime.
	* Create calendar vectors, and store a vector of events in each calendar.
	* Read/write calendar files.
		* Parse DDMMYYYY strings.
		* Parse calendar-name and event-name strings.
	* Implement .ical format compatibility.
