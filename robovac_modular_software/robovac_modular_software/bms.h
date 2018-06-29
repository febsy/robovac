/*
 * bms.h
 *
 * Created: 24.04.2018 22:33:59
 *  Author: feb
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_

extern uint8_t mBatteryLoad;

uint8_t bms_init(void);
uint8_t bms_getBatteryLoad(void);

#endif /* INCFILE1_H_ */