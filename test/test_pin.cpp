#include "test_pin.h"

void test_pin::setup(byte initpinID, bool inittype)
{
	pinID = initpinID;
	type = inittype;
	value = 0;
}
