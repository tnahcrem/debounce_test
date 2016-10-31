/*
 * debounce.h
 *
 *  Created on: Oct 30, 2016
 *      Author: hmerchan
 */

#ifndef DEBOUNCE_H_
#define DEBOUNCE_H_

typedef enum
{
	EVT_ON,
	EVT_TIMEOUT,
	EVT_OFF
}DEB_EVT_e;

typedef enum
{
	ST_OFF,
	ST_ON_DEB,
	ST_OFF_DEB,
	ST_ON
}DEB_ST_e;


#define DEB_TIMER	1

void deb_init(void);
void deb_handleEvent(DEB_EVT_e evt);
DEB_ST_e deb_getState(void);


#endif /* DEBOUNCE_H_ */
