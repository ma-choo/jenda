
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
* Read and write calendar and event files.
	* Parse DDMMYYYY strings.
	* Parse calendar-name and event-name strings.
	* Store event vectors in calendar structs.
		* Need a C vector implementation for this.
	* Implement .ical format compatibility.
* Dynamically resize events window based on the "length" of the month.
	* Use the sum of the zeller offset and the number of days in the month to determine if the events window will need 5 or 6 rows to display the the entire month.
		* ```if(first_day_offset + days_in_month >= 35) ...```
