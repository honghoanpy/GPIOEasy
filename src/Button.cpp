/*
	Button - a small library for Arduino to handle button debouncing
	
	MIT licensed.
*/
#include "Button.h"

Button::Button(uint8_t pin, uint8_t activeLevel)
:  _pin(pin)
,  _activeLevel(activeLevel)   // ← Lưu active level
,  _delay(50)
,  _state(!activeLevel)        // ← Khởi tạo _state = mức không tích cực
,  _ignore_until(0)
,  _time_changed(0)
,  _has_changed(false)
{
}

void Button::begin()
{
	pinMode(_pin, INPUT_PULLUP);
}

// 
// public methods
// 

bool Button::read()
{
	// ignore pin changes until after this delay time
	if (_ignore_until > millis())
	{
		// ignore any changes during this period
	}
	// pin has changed 
	else if (digitalRead(_pin) != _state)
	{
		_ignore_until = millis() + _delay;
		_state = !_state;
		_has_changed = true;
		_time_changed = millis();
	}
	return _state;
}

// has the button been toggled from on -> off, or vice versa
bool Button::toggled()
{
	read();
	return has_changed();
}

// mostly internal, tells you if a button has changed after calling the read() function
bool Button::has_changed()
{
	if (_has_changed == true)
	{
		_has_changed = false;
		return true;
	}
	return false;
}
// tells you time button changed
uint32_t Button::time_changed()
{
	return (millis() - _time_changed);
}
// has the button gone from off -> on
bool Button::pressed()
{
  if (read() == _activeLevel && has_changed() == true)
    return true;
  else
    return false;
}

// has the button gone from off -> on
bool Button::pressedHold(uint32_t time)
{
  if (read() == _activeLevel && (time_changed() > time))
    return true;
  else
    return false;
}

// has the button gone from on -> off
bool Button::released()
{
  if (read() != _activeLevel && has_changed() == true)
    return true;
  else
    return false;
}
