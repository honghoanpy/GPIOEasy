#include "GPIOInput.h"

GPIOInput::GPIOInput(short _IO, uint8_t Lever)
: TimeOut(50)
, _pin(_IO)
, _activeLever(Lever)
, _state(!Lever)
, _has_changed(0)
{
  pinMode(_pin, INPUT_PULLUP);
}
// read input state
bool GPIOInput::read(void) 
{
	if(digitalRead(_pin) != _state)
  {
		if(Expired()) {
			Update(50);
			_state = !_state;
			_has_changed = true;
		}
  }
  return _state;
}

bool GPIOInput::hasChanged(void)
{
  if (_has_changed == true)
	{
		_has_changed = false;
		return true;
	}
	return false;
}

// has the input gone from off -> on
bool GPIOInput::actived(void)
{
	if (read() == _activeLever && hasChanged() == true)
		return true;
	else
		return false;
}

// has the input gone from off -> on
bool GPIOInput::isActive(void)
{
	if (read() == _activeLever)
		return true;
	else
		return false;
}

// has the input gone from on -> off
bool GPIOInput::inactived(void)
{
	if (read() != _activeLever && hasChanged() == true)
		return true;
	else
		return false;
}

// get time from last change input state
uint32_t GPIOInput::timeChange(void)
{
	return Passed();
}
