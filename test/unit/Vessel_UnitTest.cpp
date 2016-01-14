#include "BTTestFramework.h"

Vessel* tVessel;
void Vessel_UnitTest()
{
	for (int i = 0; i < NUM_VESSELS; i++)
	{
		tVessel = new Vessel(i, FALSE, NULL, 0, 0, 100, 0, 300, false);

		Vessel_Switches();
		Vessel_HeatOutputs(i);
		Vessel_Volume(i); //Need to know which vessel so we can set the 
	}
}

void Vessel_Switches()
{
	//Test it in both PID and non-PID modes
	for (int i = 0; i < 2; i++)
	{
		tVessel->setPID((bool)i);

		tVessel->setHeatOverride(SOFTSWITCH_ON);
		assert(tVessel->getHeatOverride() == SOFTSWITCH_ON);
		assert(tVessel->isOn());
		assert(tVessel->getOutput());
		assert(tVessel->getPercentOutput());

		tVessel->setHeatOverride(SOFTSWITCH_OFF);
		assert(tVessel->getHeatOverride() == SOFTSWITCH_OFF);
		assert(!tVessel->isOn());
		assert(!tVessel->getOutput());
		assert(!tVessel->getPercentOutput());

		tVessel->manualOutput(52);
		assert(tVessel->getOutput() == 52);

		tVessel->setHeatOverride(SOFTSWITCH_AUTO);
		assert(tVessel->getHeatOverride() == SOFTSWITCH_AUTO);
		//The code to test that auto modes work is elsewhere
	}
}

void Vessel_HeatOutputsPID(int vesselIndex) 
{ 
	Vessel_HeatOutputsTest(true, vesselIndex); 
	tVessel->setTunings(0, 1, 2);
	tVessel->setCycle(5);
	tVessel->setHysteresis(6);

	assert(tVessel->getP() == 0);
	assert(tVessel->getI() == 1);
	assert(tVessel->getD() == 2);
	assert(tVessel->getCycle() == 5);
	assert(tVessel->getHysteresis() == 6);


}
void Vessel_HeatOutputsOnOff(int vesselIndex) { Vessel_HeatOutputsTest(false, vesselIndex); }

void Vessel_HeatOutputsTest(bool usePID, int vesselIndex) 
{
	tVessel->setHeatOverride(SOFTSWITCH_AUTO);
	tVessel->setPID(usePID);
	assert(usePID == tVessel->getPID());

	//Test that PID turns off when it's supposed to
	framework.setTemperature(vesselIndex, 100); //Temperature is 100
	assert(vessel.getTemperature() == 100); //Verify that the temperature is read properly
	tVessel->setSetpoint(50); //50 < 100
	assert(!tVessel->isOn());
	assert(!tVessel->getOutput());
	assert(!tVessel->getPercentOutput());
	assert(tVessel->isPreheated());

	tVessel->setSetpoint(100); // 100 == 100
	assert(!tVessel->isOn());
	assert(!tVessel->getOutput());
	assert(!tVessel->getPercentOutput());
	assert(tVessel->isPreheated());

	//Now test turning it on
	int output;
	tVessel->setSetpoint(150); // 150 > 100
	assert(tVessel->isOn());
	assert(output = tVessel->getOutput());
	assert(tVessel->getPercentOutput());
	assert(!tVessel->isPreheated());

	//Now turn off via temperature change
	framework.setTemperature(vesselIndex, 200);
	tVessel->updateOutput();
	assert(!tVessel->isOn());
	assert(!tVessel->getOutput());
	assert(!tVessel->getPercentOutput());
	assert(tVessel->isPreheated()); //Vessel should now be maked as preheated

	//Now turn on via temperature change
	framework.setTemperature(vesselIndex, 50);
	tVessel->updateOutput();
	assert(tVessel->isOn());
	assert(tVessel->getOutput());
	assert(tVessel->getPercentOutput());
	assert(tVessel->isPreheated()); //Vessel should stay preheated in this case

	tVessel->updateOutput();
	assert((tVessel->getOutput != output) || output == 100);
	//TODO: more robust testing of ramp-up in pid mode
}

void Vessel_HeatOutputsPWM()
{
	//TODO: test PWM
}

void Vessel_HeatOutputs(int vesselIndex)
{
	tVessel->setMaxPower(75);
	assert(tVessel->getMaxPower() == 75);

	Vessel_HeatOutputsOnOff(vesselIndex);
	Vessel_HeatOutputsPID(vesselIndex);
	Vessel_HeatOutputsPWM();
}

void Vessel_Volume()
{
	Vessel_Config();
	Vessel_Calibrate();
	Vessel_Fill();

	//TODO: test flow rates
}

void Vessel_Config()
{
	tVessel->setDeadspace(12);
	tVessel->setCapacity(120);
	tVessel->setTargetVolume(23);
	assert(tVessel->getDeadspace() == 12);
	assert(tVessel->getCapacity() == 120);
	assert(tVessel->getTargetVolume() == 120);
	assert(tVessel->getTargetPressure() == 120);
}

void Vessel_Calibrate(int vesselIndex)
{
	/*Calibration values:
		Vol		Pressure
		10		5
		20		10
		30		15
	*/
	//Test setting calibration values and reading them back
	tVessel->setCalibrationVolume(0, 10);
	tVessel->setCalibrationVolume(1, 20);
	tVessel->setCalibrationVolume(2, 30);

	tVessel->setCalibrationValue(0, 5);
	tVessel->setCalibrationValue(1, 10);
	tVessel->setCalibrationValue(2, 15);

	assert(tVessel->getCalibrationVolume(0) == 10);
	assert(tVessel->getCalibrationVolume(1) == 20);
	assert(tVessel->getCalibrationVolume(2) == 30);

	assert(tVessel->getCalibrationValue(0) == 5);
	assert(tVessel->getCalibrationValue(1) == 10);
	assert(tVessel->getCalibrationValue(2) == 15);

	//Test reading volumes
	forceVolume(vesselIndex, 10); //Equals a point
	assert(tVessel->getVolume() == 20);
	forceVolume(vesselIndex, 12.5); //Between points
	assert(tVessel->getVolume() == 25);
	forceVolume(vesselIndex, 2.5); //Below lowest point
	assert(tVessel->getVolume() == 5);
	forceVolume(vesselIndex, 20); //Above highest point
	assert(tVessel->getVolume() == 40);

	//Test volume averaging
	forceVolume(vesselIndex, 0);
	framework.setVolume(vesselIndex, 10); //Pressure of 10 == volume of 20, as calibrated above
	tVessel->takeVolumeReading();
	assert(tVessel->getVolume() == (20 / VOLUME_READ_COUNT));

	assert(tVessel->getPressure() == = tVessel->getVolume() * 1000);
}

//This makes sure the vessel's volume readings contain only this point by reading it as many times
//as the vessel's averaging array can hold
void forceVolume(int vesselIndex, int vol)
{
	framework.setVolume(vesselIndex, vol); //Equals a point
	for (int i = 0; i < VOLUME_READ_COUNT; i++)
		tVessel->takeVolumeReading();
}

void Vessel_Fill(int vesselIndex)
{
	int curProfile;

	//Fill stage
	curProfile = actProfiles;
	tVessel->setStage(FILL);
	tVessel->fill();
	switch (vesselIndex)
	{
	case VS_HLT:
		assert(actProfiles | VLV_FILLHLT);
		break;
	case VS_MASH:
		assert(actProfiles | VLV_FILLMASH);
		break;

	case VS_KETTLE:
	case VS_STEAM:
		//No filling or for steam
		assert(curProfile == actProfiles);
		break;
	}

	tVessel->stopFilling();
	assert(curProfile == actProfiles);

	//Mash stage, should be no filling happening
	curProfile = actProfiles;
	tVessel->setStage(MASH);
	tVessel->fill();
	assert(curProfile == actProfiles);
	tVessel->stopFilling();
	assert(curProfile == actProfiles);

	//Sparge stage
	curProfile = actProfiles;
	tVessel->setStage(SPARGE);
	tVessel->fill();
	switch (vesselIndex)
	{
	case VS_HLT:
		assert(actProfiles == curProfile);
		break;
	case VS_MASH:
		assert(actProfiles | VLV_SPARGEIN);
		break;
	case VS_KETTLE:
		assert(actProfiles | VLV_SPARGEOUT);
		break;

	case VS_STEAM:
		//No filling for kettle or steam
		assert(curProfile == actProfiles);
		break;
	}
	tVessel->stopFilling();
	assert(curProfile == actProfiles);
}