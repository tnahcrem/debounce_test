/*
 ============================================================================
 Name        : debounce_test.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "debounce.h"

void waitFor (unsigned int secs)
{
    unsigned int retTime = time(0) + secs;   // Get finishing time.
    while (time(0) < retTime);               // Loop until it arrives.
}

int main(void) {
	deb_init();

	printf("\n \n TEST1:  check on debounce");
	deb_handleEvent(EVT_ON);
	deb_handleEvent(EVT_OFF);
	waitFor(DEB_TIMER + 1);

	printf("\n \n TEST2:  check on debounce timeout");
	deb_handleEvent(EVT_ON);
	waitFor(DEB_TIMER + 1);
	deb_handleEvent(EVT_OFF);
	waitFor(DEB_TIMER + 1);

	printf("\n \n TEST3:  check off debounce");
	deb_handleEvent(EVT_ON);
	waitFor(DEB_TIMER + 1);
	deb_handleEvent(EVT_OFF);
	deb_handleEvent(EVT_ON);
	waitFor(DEB_TIMER + 1);


	return EXIT_SUCCESS;
}
