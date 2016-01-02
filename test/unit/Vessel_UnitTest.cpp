#include "BTTestFramework.h"

Vessel* tVessel;
void Vessel_UnitTest()
{
	Vessel_Switches();
	Vessel_HeatOutputs();
	Vessel_Volume();
}

void Vessel_Switches()
{
	tVessel = new Vessel(VS_HLT, FALSE, NULL, 0, 0, 100, 0, 300, false);
	
	tVessel->setHeatOverride(SOFTSWITCH_ON);
	assert(tVessel->getHeatOverride() == SOFTSWITCH_ON);
	assert(tVessel->getOutput());
	assert(tVessel->getPercentOutput());

}

void Vessel_HeatOutputs()
{
	Vessel_HeatOutputsOnOff();
	Vessel_HeatOutputsPID();
	Vessel_HeatOutputsPWM();
	Vessel_HeatOutputsMixed();
}

void Vessel_Volume()
{

}