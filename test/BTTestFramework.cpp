
#include "BTTestFramework.h"

BTTestFramework framework;

	int BTTestFnamework::probeForUnregisteredTemperatureSensorAddress(byte addrRet[8])
	{
		bool cont = false;
		for (byte i = 0; i < numTempSensors; i++)
		{
			for (byte j = 0; j < 8; j++)
			{
				if (temperatureAddresses[i][j])
				{
					cont = true;
					break;
				}
			}
			if (cont)
			{
				cont = false;  
				continue;
			}
			
			//If we make it here we found an empty slot at i. Create a random address
			for (byte j = 0; j < 8; j++)
			{
				temperatureAddresses[i][j] = rand() % 255;
			}
			return i;
		}
		//If we made it here, no addresses were available. This is probably a bug in the test program.

	}

	byte BTTestFramework::getIndexOfAddr(byte addr[8])
	{
		for (byte i = 0; i < numTempSensors; i++)
		{
			for (byte j = 0; j < 8; j++)
			{
				if (temperatureAddresses[i][j] != addr[j])
				{
					cont = true;
					break;
				}
			}
			if (cont)
			{
				cont = false;
				continue;
			}
			

			//If we make it here we found a match
			return i;
		}
		//If we made it here, no address matched
		return -1;
	}
	

	int BTTestFramework::getTemperature(byte addr[8])
	{
		int index = getIndexOfAddr(addr);
		assert(index != -1);
		return temperatures(index);
	}

	//Load EEPROM from file, returning whether one was found
	bool BTTestFramework::loadEEPROM()
	{
		//Load EEPROM data from file

		//Set temp sensors to values from EEPROM
	}

	void BTTestFramework::saveEEPROM()
	{
		//Save EEPROM data to file
	}