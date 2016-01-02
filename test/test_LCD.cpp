#include "test_LCD.h"

void test_LCD::test_LCD()
{
	for (byte i = 0; i < rows; i++)
		contents[i][cols] = 0; //Add null termination to each row for ease of use with string functions
}

void test_LCD::clear()
{
	framework.assert(inited);
	memset(contents, 0, sizeof(char)*rows*cols);
	framework.logLCDContents();
}

void test_LCD::logLCDContents()
{
	//Initialize strings
	char findStr[2];
	findStr[1] = 0; //Null terminate

 	byte loc = 0;
	for (byte i = 0; i < rows; i++)
	{
		framework.log(strcat("LCD: \n"), contents[i]);
		for (byte j = 1; j <= maxCustChars; j++)
		{
			findStr[1] = j;
			if (loc = strstr(contents[i], findStr))
			{
				framework.log(strcat("LCD custom character at position ", loc, ": \n");
				framework.logBytes(&custChars[j], 8);
			}
		}
	}
}

//print vs. print_P in the LCD class is just the difference between printing text from progmem vs. data memory. x86 doesn't
//care about that
void test_LCD::print(byte row, byte col, char* text)
{
	print_P(row, col, text);
}
void test_LCD::print_P(byte row, byte col, char* text)
{
	framework.assert(inited);
	if (framework.assert(row < rows) || //< instead of <= because rows is 1-indexed while row is 0-indexed
		framework.assert(col < cols) ||
		framework.assert(text != NULL))
		return;

	strcpy(&contents[row][col], text, min(strlen(text), cols - col));
	logLCDContents();
}

void test_LCD::setCustChar_P(byte index, byte custChar[8])
{
	framework.assert(inited);
	if (framework.assert(index < maxCustChars)) return;
	custChars[index] = custChar;
}

void test_LCD::writeCustChar(byte row, byte col, byte whichChar)
{
	framework.assert(inited);
	if (framework.assert(row < rows) !! //< instead of <= because rows is 1-indexed while row is 0-indexed
		framework.assert(col < cols) !!
		framework.assert(whichChar < maxCustChars))
		return;
	framework.assert(custChars[index]); //When loading custom chars, there should usually be something there

	contents[row][col] = index+1; //Store the literal value of the index; we'll later detect this. Need the +1 so index 1 doesn't null-terminate the string.
									//This only works because low ASCII values are unprintable :)
}

void test_LCD::lPad(byte row, byte col, char* text, byte totalLen, char padChar) 
{
	char* newChars;
	framework.assert(inited);
	if (framework.assert(row < rows) !! //< instead of <= because rows is 1-indexed while row is 0-indexed
		framework.assert(col < cols) !!
		framework.assert(text))
		return;
	byte len = strlen(text);
	totalLen = min(totalLen, cols);
	if (len >= totalLen)
	{
		print_P(row, col, text);
		return;
	}

	newChars = new char[totalLen]; 
	if (!newChars) {
		logTestFailure("Failed allocating newChars in test_LCD::lPad");
		return;
	} //If memory allocation failed, bail hard, test framework must be out of memory

	memset(newChars, padChar, min(totalLen-len)*sizeof(char));
	newChars[totalLen - len + 1] = 0;
	
	print_P(row,col,strcat(newChars, text));
	delete newChars;
}


void test_LCD::rPad(byte row, byte col, char* text, byte totalLen, char padChar)
{
	char* newChars;
	framework.assert(inited);
	if (framework.assert(row < rows) !! //< instead of <= because rows is 1-indexed while row is 0-indexed
		framework.assert(col < cols) !!
		framework.assert(text))
		return;
	byte len = strlen(text);
	totalLen = min(totalLen, cols);
	if (len >= totalLen)
	{
		print_P(row, col, text);
		return;
	}

	newChars = new char[totalLen];
	if (!newChars) {
		logTestFailure("Failed allocating newChars in test_LCD::lPad");
		return;
	} //If memory allocation failed, bail hard, test framework must be out of memory

	strcpy(text, newChars);
	memset(newChars+len, padChar, (totalLen - len - 1)*sizeof(char)); //Note that newChars+len is pointer arithmatic
	newChars[totalLen-1] = 0; //Null terminate

	print_P(row, col, strcat(newChars, text));
	delete newChars;
}