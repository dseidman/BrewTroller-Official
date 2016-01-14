#include "FlowController.h"

FlowController* f1;
Vessel* v1, v2;
pin* p1, p2;

void initVessel(Vessel* v,  int role)
{
	if (v) delete v;
	v = new Vessel(VS_HLT, { 0,0,0,0 }, 0, 0, 0, 100, 0, 100, false);
}

void initFC(FC* f, Vessel* from, Vessel* to)
{
	if (f) delete f;
	f = new FlowController(from, to, p1, false, false, false);
}

void FlowController_UnitTest()
{
	initVessel(v1, VS_HLT);
	initVessel(v2, VS_MASH);
	initFC(f1, v1, v2);
	
	p1 = new pin(0, OUTPUT);
	p2 = new pin(1, OUTPUT);
	
	FC_Config();
	FC_Switches();
	FC_Fill();
	FC_TargetRate();
	FC_Match();
}

void FC_Config()
{
	
	f1->setTargetFlowRate(5);
	assert(!f1->isPID());
	assert(!f1->usePWM());
	assert(f1->getTargetFlowRate() == 5);

	f1->usePID(true);
	assert(f1->isPID());
	assert(!f1->usePWM()); 
	assert(f1->getTargetFlowRate() == 5);
	
	f1->setPID(6, 7, 8, 9, 10);
	assert(f1->getCycle() == 6);
	assert(f1->getHysteresis() == 7);
	assert(f1->getP() == 8);
	assert(f1->getI() == 9);
	assert(f1->getD() == 10);

	f1->setCycle(16);
	f1->setHysteresis(17);
	assert(f1->getCycle() == 16);
	assert(f1->getHysteresis() == 17);
}

void FC_Switches()
{
	f1->setSwitch(SOFSTSWITCH_MANUAL);
	assert(f1->getSwitch() == SOFSTSWITCH_MANUAL);
		
	f1->setSwitch(AUTO);
	assert(f1->getSwitch() == SOFSTSWITCH_AUTO);
	//Auto modes tested elsewhere

	f1->setSwitch(SOFSTSWITCH_OFF);
	assert(f1->getSwitch() == SOFSTSWITCH_OFF);

	f1->startOn();
	assert(f1->getSwitch() == SOFSTSWITCH_ON);

	f1->startAuto();
	assert(f1->getSwitch() == SOFSTSWITCH_AUTO);

	f1->stop();
	assert(f1->getSwitch() == SOFSTSWITCH_OFF);
}

void FillTestVessel(Vessel* v, int role, Stage stage, bool increasing) //direction: should the volume be increasing or decreasing?
{
	//Test FILL stage 
	v->setTargetVolume(100); //Create a need to fill v1
	v->setStage(stage);
	framework.setVolume(role, 0);

	//Test non-pid mode first
	f1->usePID(false);
	f1->update();
	assert(f1->getOutput() == increasing); //0 < 100, should turn on in increasing mode and off otherwise
	v->setTargetVolume(0);
	assert(!f1->getOutput()); //0 == 0, should turn off in both modes
	v->setTargetVolume(100);
	framework.setVolume(role, 99);
	f1->update();
	assert(f1->getOutput() == increasing);// 99 < 100, should turn back on
	framework.setVolume(role, 100);
	f1->update();
	assert(!f1->getOutput()); //100 == 100, should turn off
	v->setTargetVolume(150);
	f1->update();
	assert(f1->getOutput() == increasing); //100 < 150, should turn on

	//Same tests in PID mode
	f1->usePID(true);
	f1->update();
	assert(f1->getOutput() == increasing); //0 < 100, should turn on
	v->setTargetVolume(0);
	assert(!f1->getOutput()); //0 == 0, should turn off
	v->setTargetVolume(100);
	framework.setVolume(VS_HLT, 99);
	f1->update();
	assert(f1->getOutput() == increasing);// 99 < 100, should turn back on
	framework.setVolume(VS_HLT, 100);
	f1->update();
	assert(!f1->getOutput()); //100 == 100, should turn off
	framework.setVolume(VS_HLT, 101);
	f1->update();
	assert(!f1->getOutput() == increasing); //101 > 100, should turn off
	v->setTargetVolume(150);
	f1->update();
	assert(f1->getOutput() == increasing); //100 < 150, should turn on
}

void FC_Fill()
{
	Stage stage;

	//Test FILL stage
	initVessel(v1, VS_HLT);
	initVessel(v2, VS_MASH);
	initFC(f1, v1, NULL);
	FillTestVessel(v1, VS_HLT, FILL, true);
	initFC(f1, v2, NULL);
	FillTestVessel(v2, VS_MASH, FILL, true);
	
	for (int role = VS_HLT; role < VS_KETTLE; role++) //Actually only two iterations, VS_HLT and VS_MASH, to test the two SPARGE flow controllers
	{
		//Test SPARGE stage
		initVessel(v1, role);
		initVessel(v2, role+1)
		initFC(f1, v1, v2);
		FillTestVessel(v1, role, SPARGE, false);
		FillTestVessel(v2, role + 1, SPARGE, true);
	}
}

void FC_TargetRate()
{
	initVessel(v1, VS_HLT);
	initVessel(v2, VS_MASH);
	
	initFC(f1, v1, v2);
	framework.setVolume(VS_HLT, 100); //Start with 100 in the HLT and 0 in the kettle to simulate a sparge
	framework.setVolume(VS_MASH, 0); //The mash will be kept at zero to simulate a typical scenario where the mash volume sensor isn't present.
			//TODO: add tests for when the mash sensor is present and used and when it's present and should be ignored

	v1->setStage(SPARGE);
	v2->setStage(SPARGE);
	v3->setStage(SPARGE);

	f1->setTargetFlowRate(10);
	f1->update();
	int tempOutput;
	assert(tempOutput = f1->getOutput());
	framework.setVolume(VS_HLT, 50); //TODO: incorporate varying time to verify the actual flow rate changes
	f1->update();
	assert(f1->getOutput < tempOutput); //Verifies that output is falling since we're flowing faster than target rate
	framework.setVolume(VS_HLT, 0);
	f1->update();
	assert(!f1->getOutput()); //Verify that filling stops when it hits zero
}


void FC_Match()
{
	Vessel* v3;
	FlowController* f2;
	initVessel(v1, VS_HLT);
	initVessel(v2, VS_MASH);
	initVessel(v3, VS_KETTLE);
	initFC(f1, v1, v2);
	initFC(f2, v2, v3);
	v1->setStage(SPARGE);
	v2->setStage(SPARGE);
	v3->setStage(SPARGE);

	for (int pid = 0; pid < 2; pid++)
	{
		f1->usePID(pid);
		f2->usePID(pid);

		//Initial volumes: 100, 0, 0
		framework.setVolume(VS_HLT, 100); //Start with 100 in the HLT and 0 in the kettle to simulate a sparge
		framework.setVolume(VS_MASH, 0); //The mash will be kept at zero to simulate a typical scenario where the mash volume sensor isn't present.
										 //TODO: add tests for when the mash sensor is present and used and when it's present and should be ignored
		framework.setVolume(VS_KETTLE, 0);

		v1->setTargetVolume(0);
		v2->setTargetVolume(0);
		v3->setTargetVolume(100); //Create a need to fill v3

		f1->matchFlow(f2); //f2 is master, f1 is slave
		f1->update();
		f2->update();

		assert(f2->getOutput()); //f2 should now be flowing. f1's state is unspecified until an f2 reading is taken
		framework.setVolume(VS_KETTLE, 10);
		f2->update(); //f1 is always an update cycle behind f2, so update f2 first. In real operation this is done in a loop so order doesn't matter
		assert(f2->getFlowRate());

		//f1 should now see the flow from f2 and update its own flow rate target and output
		f1->update();
		assert(f1->getTargetFlowRate());
		assert(f1->getTargetFlowRate() == f2->getFlowRate());
		assert(f1->getOutput());

		//Now pump some water out of HLT and make sure f1 stops
		framework.setVolume(VS_HLT, 50);
		f1->update();
		assert(!f1->getOutput());

		//Now pump more into the kettle and make sure f1 restarts
		framework.setVolume(VS_KETTLE, 50);
		f2->update();
		f1->update();
		assert(f1->getOutput());
		assert(f1->getTargetFlowRate() == f2->getFlowRate());

		//Finally, finish pumping
		framework.setVolume(VS_HLT, 0);
		framework.setVolume(VS_KETTLE, 100);
		f1->update();
		f2->update();
		assert(!f1->getOutput());
		assert(!f2->getOutput());
	}
}