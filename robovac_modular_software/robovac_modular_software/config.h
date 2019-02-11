/*
 * config.h
 *
 * Created: 11.06.2018 23:02:32
 *  Author: feb
 */ 


#ifndef CONFIG_H_
#define CONFIG_H_
uint8_t config_init();
uint8_t config_setLED(uint8_t,uint8_t,uint8_t);
uint8_t config_getStatus();
uint8_t config_getBatteryStatus();
uint16_t config_getTime();
uint8_t config_NTP(uint8_t,int16_t,int16_t);

uint8_t config_flagDEAMON();



#endif /* CONFIG_H_ */