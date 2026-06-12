#include "GPIOBlink.h"

GPIOBlink::GPIOBlink(uint8_t _IO, bool Lever)
  : _IOPIN(_IO), On_Status(Lever), TimeOut(60000), _state(false), _has_changed(false)
{
  pinMode(_IOPIN, OUTPUT);
  Off_Status = !On_Status;
  digitalWrite(_IOPIN, Off_Status); // Turn off GPIO

  IoBCount=0;
  Disable(); // Disable Timeout
}

uint8_t GPIOBlink::State(void)
{
	return _state ? 1 : 0;
}

void GPIOBlink::Blink(uint8_t Count, uint32_t DelayOn, uint32_t DelayOff)
{
  IoBCount = Count;
  IoBDelayOff = DelayOff;
  IoBDelayOn = DelayOn;
  Update(IoBDelayOn); // Update timeout
  digitalWrite(_IOPIN, On_Status);  // Turn on GPIO
  _state = true;
  _has_changed = true;
}

// void GPIOBlink::Toggle(void)
// {
// 	if (_state) Off();
// 	else On();
// }

void GPIOBlink::On(void)
{
  if(State() == 0) {
    IoBCount = 0;
    Disable();
    digitalWrite(_IOPIN, On_Status);
    _state = true;
    _has_changed = true;
  }
}

void GPIOBlink::Off(void)
{
  if(State() == 1) {
    IoBCount = 0;
    Disable();
    digitalWrite(_IOPIN, Off_Status);
    _state = false;
    _has_changed = true;
  }
}

bool GPIOBlink::hasChange(void)
{
  if (_has_changed)
  {
    _has_changed = false;
    return true;
  }
  return false;
}

void GPIOBlink::handler(void)
{
  if (!Expired()) return;
  
  if (_state) { // Was ON → turn OFF
    if (IoBDelayOff != 0)
      Update(IoBDelayOff);
    else
      Disable();
    digitalWrite(_IOPIN, Off_Status);
    _state = false;
    _has_changed = true;
  } else { // Was OFF → maybe turn ON again
    if (IoBCount == 0 || IoBCount > 1) {
      // Count=0: infinite, Count>1: still more blinks left
      if (IoBCount > 1) IoBCount--;
      Update(IoBDelayOn);
      digitalWrite(_IOPIN, On_Status);
      _state = true;
      _has_changed = true;
    } else {
      // Last blink completed
      IoBCount = 0;
      Disable();
    }
  }
  
  // Update IoBState for backward compatibility
  IoBState = _state ? IO_STATE_ON : IO_STATE_OFF;
}
