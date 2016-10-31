/*
 * debounce.c
 *
 *  Created on: Oct 30, 2016
 *      Author: hmerchan
 */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "debounce.h"

// GLOBALS
DEB_ST_e curDebSt;
DEB_EVT_e lastPostEvt;

// macro to do system level operation
// can be changed depending on the system
#define START_TIMER()		(alarm(DEB_TIMER))
#define STOP_TIMER() 		(alarm(0))

// LOCAL FUNCTIONS
void _deb_timeout(int signal);
void _deb_postEvent(DEB_EVT_e evt);

/*****************************************************************************
*    Function: void _deb_timeout(int signal)
*
*    Abstract: The timeout callback of the timer
*
*    Input/Output: The signal which is enabled for the timer
*
*    Return:
*
*****************************************************************************/
void _deb_timeout(int signal)
{
	deb_handleEvent(EVT_TIMEOUT);
}

/*****************************************************************************
*    Function: void _deb_postEvent(DEB_EVT_e evt)
*
*    Abstract: The function to post the event after it is debounced
*    			In this setup we use a simple printf to post event
*    			Depending on the system; the output mode can be changed
*    			This function is only called form the state machine
*
*    Input/Output: The event to be posted;
*
*    Return:
*
*****************************************************************************/
void _deb_postEvent(DEB_EVT_e evt)
{
	if(lastPostEvt == evt)
	{
		return;
	}
	printf("\n DEB FSM: Got event ");
	switch(evt)
	{
	case EVT_OFF:
		printf("OFF");
		lastPostEvt = evt;
		break;
	case EVT_ON:
		printf("ON");
		lastPostEvt = evt;
		break;
	default:
		printf("INVALID");
		break;
	}
}

/*****************************************************************************
*    Function: void deb_init(void)
*
*    Abstract: Initialization function to be called once after boot
*
*    Input/Output:
*
*    Return:
*
*****************************************************************************/
void deb_init(void)
{
	curDebSt = ST_OFF;
	lastPostEvt = EVT_OFF;
	signal(SIGALRM, _deb_timeout); // on a RTOS based system change this to a more controlled form of timer
}



/*****************************************************************************
*    Function: void deb_handleEvent(DEB_EVT_e evt)
*
*    Abstract: The main function that handles teh debounce state machine
*
*    Input/Output:Takes input event
*
*    Return:
*
*****************************************************************************/
void deb_handleEvent(DEB_EVT_e evt)
{
	switch(curDebSt)
	{
	case ST_OFF:
		if(evt == EVT_ON)
		{
			START_TIMER();
			curDebSt = ST_ON_DEB;
		}
		break;
	case ST_ON_DEB:
		if(evt == EVT_TIMEOUT)
		{
			_deb_postEvent(EVT_ON);
			curDebSt = ST_ON;
		}
		if(evt == EVT_OFF)
		{
			START_TIMER();
			curDebSt = ST_OFF_DEB;
		}
		break;
	case ST_OFF_DEB:
		if(evt == EVT_TIMEOUT)
		{
			_deb_postEvent(EVT_OFF);
			curDebSt = ST_OFF;
		}
		if(evt == EVT_ON)
		{
			START_TIMER();
			curDebSt = ST_ON_DEB;
		}
		break;
	case ST_ON:
		if(evt == EVT_OFF)
		{
			START_TIMER();
			curDebSt = ST_OFF_DEB;
		}
		break;
	default:
		break;
	}

}

/*****************************************************************************
*    Function: DEB_ST_e deb_getState(void)
*
*    Abstract: Utilitly function to check current state
*
*    Input/Output:Returns current state
*
*    Return:
*
*****************************************************************************/
DEB_ST_e deb_getState(void)
{
	return curDebSt;
}
