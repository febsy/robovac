/*
 * globals.h
 *
 * Created: 13.06.2018 19:18:15
 *  Author: feb
 */ 


#ifndef GLOBALS_H_
#define GLOBALS_H_
// main
extern volatile uint8_t mSoftReset;
// sytemTime
extern volatile uint64_t mSysTimeMs;
// config
extern volatile uint8_t mStatusFlag;
// bms
extern volatile uint8_t mBatteryLoad;
// tracker
extern int16_t mDistancePerUnit;
extern int16_t mAnglePerUnit;
extern volatile int16_t mCurrentPosX;
extern volatile int16_t mCurrentPosY;
extern volatile int16_t mCurrentAngle;
// drivesystem
extern uint8_t mDriveSystemReady;
extern volatile uint8_t mDSDStatus;
//



#endif /* GLOBALS_H_ */