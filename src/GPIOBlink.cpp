#include "GPIOBlink.h"

GPIOBlink::GPIOBlink(short _IO, bool Lever)
  : _IOPIN(_IO), On_Status(Lever), TimeOut(60000)
{
  pinMode(_IOPIN, OUTPUT);
  Off_Status = !On_Status;
  digitalWrite(_IOPIN, Off_Status); // Turn off GPIO

  // IoBState=IO_STATE_OFF;
  IoBCount=0;
  Disable(); // Disable Timeout
}

uint8_t GPIOBlink::State(void)
{
	return (digitalRead(_IOPIN) == On_Status)?1:0;
}

void GPIOBlink::Blink(uint8_t Count, uint32_t DelayOn, uint32_t DelayOff)
{
  IoBCount = Count;
  IoBDelayOff = DelayOff;
  IoBDelayOn = DelayOn;
  // IoBState = IO_STATE_ON;
  Update(IoBDelayOn); // Update timeout
  digitalWrite(_IOPIN, On_Status);  // Turn on GPIO
}

void GPIOBlink::On(void)
{
	IoBCount = 0;
	digitalWrite(_IOPIN, On_Status);
}

void GPIOBlink::Off(void)
{
	IoBCount = 0;
	digitalWrite(_IOPIN, Off_Status);
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
        digitalWrite(_IOPIN, Off_Status);
      }
      break;
    case IO_STATE_OFF:
      /* code */
      if(Expired()) {
        IoBCount--;
        if(IoBCount > 0) {        
          Update(IoBDelayOn);
          digitalWrite(_IOPIN, On_Status);
        }
        else {
          Disable(); // Disable Timeout
        }
      }
      break;
    // case IO_STATE_IDLE:
    //   /* code */
    //   Disable(); // Disable Timeout
    //   break;
  }
}
