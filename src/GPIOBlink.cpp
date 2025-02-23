#include "GPIOBlink.h"

GPIOBlink::GPIOBlink(short _IO, bool Lever)
  : _IO_PIN(_IO), _ON_LEVER(Lever), TimeOut(60000)
{
  pinMode(_IO_PIN, OUTPUT);
  digitalWrite(_IO_PIN, !_ON_LEVER); // Turn off GPIO

  prevLever = State();
  IoBCount=0;
  Disable(); // Disable Timeout
}

uint8_t GPIOBlink::State(void)
{
	return (digitalRead(_IO_PIN) == _ON_LEVER)?1:0;
}

void GPIOBlink::Blink(uint8_t Count, uint32_t DelayOn, uint32_t DelayOff)
{
  IoBCount = Count;
  IoBDelayOff = DelayOff;
  IoBDelayOn = DelayOn;
  // IoBState = IO_STATE_ON;
  Update(IoBDelayOn); // Update timeout
  digitalWrite(_IO_PIN, _ON_LEVER);  // Turn on GPIO
}

void GPIOBlink::On(void)
{
  if(State() == 0) {
    IoBCount = 0;
    digitalWrite(_IO_PIN, _ON_LEVER);
  }
}

void GPIOBlink::Off(void)
{
  if(State() == 1) {
    IoBCount = 0;
    digitalWrite(_IO_PIN, !_ON_LEVER);
  }
}

bool GPIOBlink::isChange(void)
{
  if(prevLever != State()) {
    prevLever = State();
    return true;
  }
  return false;
}

void GPIOBlink::handler(void)
{
  switch(State()) 
  {
    case 0:
      IoBState = IO_STATE_OFF;
      break;
    case 1:
      IoBState = IO_STATE_ON;
      break;
  }

  switch (IoBState)
  {
    case IO_STATE_ON:
      /* code */
      if(Expired()) {
        if(IoBDelayOff != 0) Update(IoBDelayOff);
        else Disable();
        digitalWrite(_IO_PIN, !_ON_LEVER);
      }
      break;
    case IO_STATE_OFF:
      /* code */
      if(Expired()) {
        IoBCount--;
        if(IoBCount > 0) {        
          Update(IoBDelayOn);
          digitalWrite(_IO_PIN, _ON_LEVER);
        }
        else {
          Disable(); // Disable Timeout
        }
      }
      break;
  }
}
