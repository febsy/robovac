/*
 * tracker.h
 *
 * Created: 11.06.2018 23:00:58
 *  Author: feb
 */ 


#ifndef TRACKER_H_
#define TRACKER_H_

uint8_t tracker_init();
uint8_t tracker_isInitialized();
uint8_t tracker_getPosition(uint8_t,int16_t*,int16_t*,int16_t*);
uint8_t tracker_getUSDistance(int16_t*,int16_t*);
uint8_t tracker_getAngle(int16_t*);

uint8_t tracker_setHome(int16_t,int16_t);
uint8_t tracker_setOrientation(int16_t);
uint8_t tracker_setDistancePerUnit(int16_t);
uint8_t tracker_setAnglePerUnit(int16_t);



uint8_t tracker_refreshPositionDEAMON(void);
#endif /* TRACKER_H_ */