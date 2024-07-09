/*
#include "GPIOBlink.h"

*/

#ifndef	_GPIOBLINK_H
#define _GPIOBLINK_H

#include <Arduino.h>
#include <stdint.h>
#include <stddef.h>
#include "TimeOut.h"

typedef enum{
IO_STATE_ON = 0,
IO_STATE_OFF,
IO_STATE_IDLE
}IO_State;

class IOBlink : public TimeOut {
public:
	IOBlink(short _IO = 2, bool Lever = LOW);
	void Blink(uint16_t DelayOn)
	{
		Blink(1,DelayOn,60000);
	}
	void Blink(uint8_t Count, uint16_t DelayOn, uint16_t DelayOff);
	void On(void);
	void Off(void);
	void handller(void);

protected:
	const short _IOPIN;
	IO_State 	IoBState;
	uint16_t 	IoBDelayOff;
	uint16_t 	IoBDelayOn;
	int 		IoBCount;
	bool 		On_Status;
	bool 		Off_Status;
};
#endif
