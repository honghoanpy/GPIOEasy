/*
#include "IOInput.h"

*/
#ifndef _INPUT_H
#define _INPUT_H
/* Include */
#include <Arduino.h>
#include "TimeOut.h"

class GPIOInput : public TimeOut {
  public:
		GPIOInput(short _IO = 0, uint8_t activeLever = HIGH);
		bool read(void);
		bool actived(void);
		bool isActive(void);
		bool inactived(void);
		bool hasChanged(void);
		uint32_t timeChange(void);

  private:
		uint8_t 	_pin;
		bool 			_state;
		bool 			_activeLever;
		bool 			_has_changed;
};

#endif
