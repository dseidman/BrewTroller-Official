#if !defined TEST_EEPROM_H && defined TEST
#define TEST_EEPROM_H

class test_EEPROM
{
private:
	static byte storage[];
	constexpr int size = 2048;
public:
	inline public static void write(int index, byte value)
	{
		if (!assert(index < size)) return;
		storage[index] = value;
	}
	inline public static byte read(int index)
	{
		if (!assert(index < size)) return;
		return storage[index];
	}

	//Used by testing framework only
	inline public static void setFullEEPROM(byte newMemory[2048])
	{
		storage = newMemory;
	}
	inline public static byte[] getFullEEPROM() { return storage; }
};
#endif

