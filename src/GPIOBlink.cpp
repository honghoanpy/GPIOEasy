#include "GPIOBlink.h"

IOBlink::IOBlink(short _IO, bool Lever)
  : _IOPIN(_IO), On_Status(Lever), TimeOut(60000)
{
  pinMode(_IOPIN, OUTPUT);
  Off_Status = !On_Status;
  digitalWrite(_IOPIN, Off_Status); // Turn off GPIO

  IoBState=IO_STATE_OFF;
  IoBCount=0;
  Disable(); // Disable Timeout
}

void IOBlink::Blink(uint8_t Count, uint16_t DelayOn, uint16_t DelayOff)
{
  IoBCount = Count;
  IoBDelayOff = DelayOff;
  IoBDelayOn = DelayOn;
  IoBState = IO_STATE_ON;
  Update(IoBDelayOn); // Update timeout
  digitalWrite(_IOPIN, On_Status);  // Turn on GPIO
}

void IOBlink::On(void)
{
	IoBCount = 0;
	digitalWrite(_IOPIN, On_Status);
}

void IOBlink::Off(void)
{
	IoBCount = 0;
	digitalWrite(_IOPIN, Off_Status);
}

void IOBlink::handler(void)
{
    switch (IoBState)
    {
    case IO_STATE_ON:
      /* code */
      if(Expired()) {
        Update(IoBDelayOff);
        IoBState = IO_STATE_OFF;
        digitalWrite(_IOPIN, Off_Status);
      }
      break;
    case IO_STATE_OFF:
      /* code */
      if(Expired()) {
        Update(IoBDelayOn);
        IoBCount--;
        if(IoBCount > 0) {
          IoBState = IO_STATE_ON;
          digitalWrite(_IOPIN, On_Status);
        }
        else {
          IoBState = IO_STATE_IDLE;
          digitalWrite(_IOPIN, Off_Status);
        }
      }
      break;
    case IO_STATE_IDLE:
      /* code */
      Disable(); // Disable Timeout
      break;
    // default:
    //   break;
  }
}
