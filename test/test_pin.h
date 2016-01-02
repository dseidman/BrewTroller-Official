#if !defined TEST_PIN_H && defined TEST
#define TEST_PIN_H

#include "ArduinoTestFramework.h"

class test_pin
{

private:
	int value;
	bool type; //true = OUTPUT, false = INPUT
	byte pinID;
public:

	void setup(byte initpinID, bool inittype);
	void set(bool newVal = 0) { framework.assert(type == OUTPUT);  value = newVal; }
	bool get() { return value; }
	void toggle() { value = !value; }
	void clear() { value = false; }
	void attachPCInt(byte, void*) { ; } //Ignore interrupts tied to this pin.
	int analogRead(test_pin) { framework.assert(type == INPUT); return value; }

	//Routines used by the testing framework to provide pin-level manipulation
	void test_set(bool newVal) { assert(type == INPUT); value = newVal; }
};



#endif