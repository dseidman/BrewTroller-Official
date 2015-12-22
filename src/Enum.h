#ifndef BT_ENUM
#define BT_ENUM

//TSensor and Output (0-2) Array Element Constants
#define TS_HLT 0
#define TS_MASH 1
#define TS_KETTLE 2
#define TS_H2OIN 3
#define TS_H2OOUT 4
#define TS_BEEROUT 5
#define TS_AUX1 6
#define TS_AUX2 7
#define TS_AUX3 8
#define NUM_TS 9
#define BAD_TEMP -32768
constexpr uint8_t TS_ADDR_BYTES = 8;

#define VS_HLT 0
#define VS_MASH 1
#define VS_KETTLE 2
#define VS_STEAM 3
#define VS_PUMP 3
constexpr uint8_t VS_COUNT = 4;

//Volume Calibrations
constexpr uint8_t VOL_CALIB_COUNT = 10;

//Auto-Valve Modes
#define AV_FILL 0
#define AV_MASH 1
#define AV_SPARGEIN 2
#define AV_SPARGEOUT 3
#define AV_FLYSPARGE 4
#define AV_CHILL 5
#define AV_HLT 6
#define AV_KETTLE 7
#define NUM_AV 8

//Valve Array Element Constants and Variables
#define VLV_ALL 4294967295
#define VLV_FILLHLT 0
#define VLV_FILLMASH 1
#define VLV_ADDGRAIN 2
#define VLV_MASHHEAT 3
#define VLV_MASHIDLE 4
#define VLV_SPARGEIN 5
#define VLV_SPARGEOUT 6
#define VLV_HOPADD 7
#define VLV_KETTLELID 8
#define VLV_CHILLH2O 9
#define VLV_CHILLBEER 10
#define VLV_BOILRECIRC 11
#define VLV_DRAIN 12
#define VLV_HLTHEAT 13
#define VLV_HLTIDLE 14
#define VLV_KETTLEHEAT 15
#define VLV_KETTLEIDLE 16
#define VLV_USER1 17
#define VLV_USER2 18
#define VLV_USER3 19
#define NUM_VLVCFGS 20

//Timers
#define TIMER_MASH 0
#define TIMER_BOIL 1

//Brew Steps
enum BrewStepIndex {
  BREWSTEP_FILL,
  BREWSTEP_DELAY,
  BREWSTEP_PREHEAT,
  BREWSTEP_GRAININ,
  BREWSTEP_REFILL,
  BREWSTEP_DOUGHIN,
  BREWSTEP_ACID,
  BREWSTEP_PROTEIN,
  BREWSTEP_SACCH,
  BREWSTEP_SACCH2,
  BREWSTEP_MASHOUT,
  BREWSTEP_MASHHOLD,
  BREWSTEP_SPARGE,
  BREWSTEP_BOIL,
  BREWSTEP_CHILL,
  BREWSTEP_COUNT,
  BREWSTEP_NONE = 255
};

enum StepSignal {
  STEPSIGNAL_INIT,
  STEPSIGNAL_UPDATE,
  STEPSIGNAL_ADVANCE,
  STEPSIGNAL_ABORT
};

#define PROGRAMTHREAD_MAX 2
#define PROGRAMTHREAD_NONE 255

#define RECIPE_MAX 20
#define RECIPE_NONE 255
constexpr uint8_t PROG_NAME_LEN = 20;

enum MashStepIndex {
  MASHSTEP_DOUGHIN,
  MASHSTEP_ACID,
  MASHSTEP_PROTEIN,
  MASHSTEP_SACCH,
  MASHSTEP_SACCH2,
  MASHSTEP_MASHOUT,
  MASHSTEP_COUNT
};

//Zones
enum ZoneIndex {
  ZONE_MASH,
  ZONE_BOIL
};

//Events
#define EVENT_STEPINIT 0
#define EVENT_STEPEXIT 1
#define EVENT_SETPOINT 2
#define EVENT_ESTOP 3

//Log Constants
#define CMD_MSG_FIELDS 25
#define CMD_FIELD_CHARS 21

#define BT_I2C_ADDR 0x10
#define BTNIC_I2C_ADDR 0x11

#define ASCII 0
#define BTNIC 1
#define BINARY 2

typedef enum {
  TRIGGER_ESTOP,
  TRIGGER_SPARGEMAX,
  TRIGGER_HLTMIN,
  TRIGGER_MASHMIN,
  TRIGGER_KETTLEMIN,
  NUM_TRIGGERS
} TriggerType;

typedef enum {
  CONTROLSTATE_OFF,
  CONTROLSTATE_AUTO,
  CONTROLSTATE_ON,
  NUM_CONTROLSTATES
} ControlState;

#endif
