/*
#include "GPIOBlink.h"
*/

#ifndef	_GPIOBLINK_H
#define _GPIOBLINK_H

#include <Arduino.h>
#include "TimeOut.h"

typedef enum{
IO_STATE_ON = 0,
IO_STATE_OFF,
IO_STATE_IDLE
}IO_State;

class GPIOBlink : public TimeOut {
public:
	GPIOBlink(short _IO = 2, bool Lever = LOW);
	
	uint8_t State(void);
	void Blink(uint8_t Count, uint32_t DelayOn, uint32_t DelayOff);
	void Toggle(uint32_t Delay)
	{
		Blink(1,Delay,0);
	}
	void On(void);
	void Off(void);
	bool isChange(void);
	void handler(void);

protected:
	const short _IO_PIN;
	const bool 	_ON_LEVER;
	IO_State 	IoBState;
	uint32_t 	IoBDelayOff;
	uint32_t 	IoBDelayOn;
	int 		IoBCount;
	bool 		prevLever;   // for detect lever change
};
#endif
