#include "test_Temp.h"

#include "HardwareProfile.h"
#include "Enum.h"
#include "BrewTroller.h"

void tempInit() {
	for (byte i = 0; i < NUM_TS; i++) temp[i] = BAD_TEMP;
}


unsigned long convStart;

#if TS_ONEWIRE_RES == 12
#define CONV_DELAY 750
#elif TS_ONEWIRE_RES == 11
#define CONV_DELAY 375
#elif TS_ONEWIRE_RES == 10
#define CONV_DELAY 188
#else //Default to 9-bit
#define CONV_DELAY 94
#endif

void updateTemps() {
	if (convStart == 0) {
		convStart = millis();
	}
	else if (tsReady() || millis() - convStart >= CONV_DELAY) {
		for (byte i = 0; i < NUM_TS; i++) {
			if (validAddr(tSensor[i]))
				temp[i] = read_temp(tSensor[i]);
			else
				temp[i] = BAD_TEMP;
		}

		convStart = 0;

	}
}

boolean tsReady() {
	return true;
}

boolean validAddr(byte* addr) {
	for (byte i = 0; i < 8; i++) if (addr[i]) return 1;
	return 0;
}

//This function search for an address that is not currently assigned!
void getDSAddr(byte addrRet[8]) {
	framework.probeForUnregisteredTemperatureSensorAddress(addrRet);
}

//Returns Int representing hundreths of degree
int read_temp(byte* addr) {
	return framework.getTemperature(addr);
}
