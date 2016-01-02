#cmakedefine TEST
#if defined TEST and !defined ARDUINOTESTFRAMEWORK_H

#include "testController.h"

#include "test_pin.h"

#include "test_Encoder.h"
#include "test_Serial.h"

//General Arduino redefinitions
#define pin test_pin
#define Encoder test_Encoder
#define Serial test_Serial


	//Global Arduino defines
#define OUTPUT false
#define INPUT true
#define HIGH true
#define LOW false

//Define away interrupt handlers. We will ignore them completely; testing interrupt interaction on x86 would be very difficult to implement correctly
#define cli() ; //
#define sbi(a,b) ;//
#define cbi(a,b) ;//

//Values used for interrupt handlers
#define CHANGE 0
#define RISING 1
#define FALLING 2

extern int ICR1;

class ArduinoTestFramework
{
public:
	void log(char*);
	void log(int);
	bool assert(bool);
	int getInt() { return getInt(0, MAX_INT); }
	int getInt(int min, int max) {
		return (rand % (max-min)) + min;
	};
	void log(char* c) { printf(c); }
	void logBytes(char* c, byte numBytes) { for (byte i = 0; i < numBytes; i++) printf(c[i]); }
	bool assert(bool value, char[] funcName, char[] file, int line);
};

extern ArduinoTestFramework framework;

//Build out assert handler with debug info
#define assert(x) assert(x, __PRETTY_FUNCTION__, __FILE__, __LINE__)
#endif

