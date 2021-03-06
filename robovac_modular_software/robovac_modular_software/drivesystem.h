/*
 * drivesystem.h
 *
 * Created: 11.06.2018 23:00:38
 *  Author: feb
 */ 


#ifndef DRIVESYSTEM_H_
#define DRIVESYSTEM_H_

uint8_t drivesystem_init();

uint8_t drivesystem_isReady(void);
uint8_t drivesystem_SetDestination(int16_t,int16_t);
uint8_t drivesystem_SetDistance(int16_t);
uint8_t drivesystem_SetAngle(int8_t,uint16_t);
uint8_t drivesystem_Stop(void);

void drivesystem_linearmovement();
void drivesystem_rotationalmovement();

uint8_t drivesystem_driveDEAMON();



#endif /* DRIVESYSTEM_H_ */