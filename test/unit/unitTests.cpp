#include "BTTestFramework.h"
#include "BrewTroller.h"

void vesselUnitTests();
void setupFramework();
void main(int argc, void[] argv)
{
	setupFramework();
	vesselUnitTests();
	sub_main(); //Invoke the actual main loop of the program
	framework.saveEEPROM();
}
void setupFramework()
{
	byte addr[8];
	if (!framework.loadEEPROM())
	{
		initEEPROM();
		//Set up temp sensors
		for (int i = 0; i < framework.numTempSensors; i++)
		{
			framework.probeForUnregisteredTemperatureSensorAddress(&addr);
			setTSAddr(i, addr);
			framework.setTemperature(i, 68); //Set all sensors to room temperature to start
		}
	}
	//Volumes automatically initialized to 0 by compiler
}