#include <Arduino.h>
#include <stddef.h>
#include <stdint.h>
#include "GPIOInput.h"

#define IOINPUT_PORT Serial
#define IOINPUT_DBG(fmt, ...) //IOINPUT_PORT.printf("\r\n>IOINPUT< " fmt, ##__VA_ARGS__)

IOInput::IOInput(short _IO, uint8_t _MODE, uint8_t level)
    : TimeOut(10), _IOPIN(_IO), _Mode(_MODE), _ActiveLevel(level) {
  pinMode(_IOPIN, _Mode);
  _ActiveState=0;
  _ActiveEvent=0;
}

void IOInput::handler(void)
{
  if(Expired()) {
    Update(10);
    if (digitalRead(_IOPIN) == _ActiveLevel)  // Tact event
    {
      /* code */
      _TimeActive+=10;
      if(_TimeActive>=50) {
        if(_ActiveState==0) {
          _ActiveEvent=1;
          _ActiveState=1;
        }
      }
    }
    else
    {
      /* code */
      _TimeActive=0;
      if(_ActiveState==1) {
        _DeactiveEvent=1;
        _ActiveState=0;
      }
    }
  }
}

bool IOInput::GetState(void)
{
  return digitalRead(_IOPIN);
}

/* ----- Get timeout hold ------ */
uint8_t IOInput::isActive(void)
{
  return _ActiveState;
}

uint32_t IOInput::GetTimeActive(void)
{
  return _TimeActive;
}

uint8_t IOInput::GetActiveEvent(void)
{
	if(_ActiveEvent == 1) {
    _ActiveEvent = 0;
		return 1;
	}
	return 0;
}

uint8_t IOInput::GetDeactiveEvent(void)
{
	if(_DeactiveEvent == 1) {
    _DeactiveEvent = 0;
		return 1;
	}
	return 0;
}