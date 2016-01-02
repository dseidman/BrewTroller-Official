#ifndef #BTTESTFRAMEWORK_H
#define #BTTESTFRAMEWORK_H

#include "ArduinoTestFramework.h"


//Replace this section with your own high-level defines.
//These are things like remapping an I2C LCD display to cout so you don't have to simulate the entire I2C protocol,
//remapping serial to console, etc. 
#define LCD test_LCD
#include "test_LCD.h"

#define EEPROM test_EEPROM
#include "test_EEPROM.h"

#define "int main(void)" "int sub_main(void)"

class BTTestFramework : public ArduinoTestFramework
{
private:
	byte temperatureAddresses[numTempSensors][8];
	byte temperatures[numTempSensors];
	double volumes[numVessels];

	int getTemperature(byte address[8]);
	int getIndexOfAddr(byte[8]);
public:
	BTTestFramework();
	//Constants defining the physical "reality" of the system
	constexpr byte numTempSensors = 9;
	constexpr byte numVessels = 4;

	//High level functions called by BT test code where we don't want to have to simulate the hardware protocol
	int probeForUnregisteredTemperatureSensorAddress(byte addrRet[8]);
	int getTemperature(addr);

	//Functions for script control
	void setSensorAddress(byte sensorIndex, byte sensorAddress[8]);
	void setupRandomSensor(byte sensorIndex);
	void setTemperature(byte sensorIndex, int temperature);
	inline void setVolume(byte index, double vol) { volumes[index] = vol; }
	inline void getVolume(byte index) { return volumes[index]; }

	bool loadEEPROM(); //Returns whether a stored EEPROM file was found to load
	void saveEEPROM();
};

extern BTTestFramework framework;

inline byte pgm_read_byte(int index) { return 0; } //Simulate a disconnected BTNic connection. BTNic testing is not yet implemented.
inline word pgm_read_word(void* addr) { return (word)*addr; }

#endif
