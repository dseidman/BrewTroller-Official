#ifndef TEST_LCD_H
#define TEST_LCD_H

#define UILCD_H //Prevent including the actual LCD code

#include "ArduinoTestFramework.h"

class test_LCD
{
private:
	static constexpr byte rows = 4;
	static constexpr byte cols = 17;
	static constexpr byte maxCustChars = 8;
	byte numCustChars = 0;
	bool inited = false;
	char contents[rows][cols+1]; //+1 allows for null termination, for ease of use of Cstr functions
	byte custChars[maxCustChars];

	logLCDContents();
public:
	test_LCD();
	void update() { assert(inited); };
	void init() { inited = true; };
	void clear();

	void setCustChar_P(byte index, char custChar);
	void writeCustChar(byte row, byte col, byte whichChar);

	void print_P(byte row, byte col, char* text);
	void lPad(byte, byte, char*, byte, char);
	void rPad(byte, byte, char*, byte, char);
};

#endif