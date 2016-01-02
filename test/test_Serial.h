#if defined TEST_SERIAL_H && defined TEST
#define TEST_SERIAL_H

#include "ArduinoTestFramework.h"

class test_Serial
{
private:
	bool inited = false;
	bool writeintro = false;
public:
	inline void begin(byte) { inited = true; }
	inline void print(char* msg) { assert(inited); writeintro = false; framework.log(strcat("Serial write: \n",msg)); }
	inline void println(char* msg) {   print(strcat(msg, "/n")); }
	inline bool available() { assert(inited); return framework.getBool(); }
	inline void write(byte b) {
		assert(inited);
		if (writeintro)
		{
			framework.log(strcat("Serial write: \n", b));
			writeintro = true;
		}
			else
				framework.log(b); 
	}
	inline byte read() { assert(inited); return framework.getByte(); }
};

#endif