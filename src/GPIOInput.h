/*
#include "IOInput.h"

*/

#ifndef _GPIOINPUT_H
#define _GPIOINPUT_H
/* Include */
#include <Arduino.h>
#include <stdint.h>
#include <stddef.h>
#include "TimeOut.h"

#ifndef RISING
#define RISING	2
#endif
#ifndef FALLING
#define FALLING	3
#endif

//typedef void (*callbackFunc) (void);	
//using callbackFunc = void (*)(const char*); //type aliasing
//C++ version of: typedef void (*callbackFunc)(const char*)

class IOInput : public TimeOut {
  public:
	IOInput(short _IO = 0, uint8_t _MODE = INPUT, uint8_t level = HIGH);
	uint8_t GetActiveEvent(void);
	uint8_t GetDeactiveEvent(void);
	uint8_t isActive(void);
	bool GetState(void);
	uint32_t GetTimeActive(void);
	void handler(void);

  private:
	uint8_t _ActiveState;
	uint8_t _ActiveLevel;
	uint8_t _ActiveEvent;
	uint8_t _DeactiveEvent;
	uint32_t _TimeActive;
	const short _IOPIN;
	uint8_t _Mode;
};


#endif
