#ifndef ENCODER_H
#define ENCODER_H

#include "ArduinoTestFramework.h"

class test_Encoder
{
private:
	bool inited = false;
	byte encMin = 0, encMax = 0, count = 0;
	bool activeLow = false;
public:
	inline void begin(byte) { inited = true; };
	inline void begin(byte, byte, byte, byte) { inited = true; }
	void setActiveLow(byte aLow) {
		framework.assert(inited); activeLow = alow;
	}
	inline void setMin(byte newMin) { framework.assert(inited); encMin = newMin; }
	inline void setMax(byte newMax) { framework.assert(inited); encMax = newMax; }
	inline byte getCount() { framework.assert(inited);  return count = framework.getInt(encMin, encMax); }
	inline void setCount(byte newC) {
		framework.assert(inited); 
		count = newC;
	}
	inline bool ok() { framework.assert(inited); return framework.getBool(); }
	inline bool cancel() { framework.assert(inited); return framework.getCancel(); }
	int change() { 
		framework.assert(inited); 
		int newCount = framework.getInt(encMin, encMax);
		int delta = newCount - count;
		count = newCount;
		return delta;
	}
};
#endif


