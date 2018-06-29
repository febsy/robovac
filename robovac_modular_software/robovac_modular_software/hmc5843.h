/*
 * hmc5843.h
 *
 * Created: 05.05.2017 23:44:26
 *  Author: febs
 */ 


#ifndef HMC5843_H_
#define HMC5843_H_


extern volatile int dir_angle;

extern void hmc5883_init(void);
extern void hmc5883_mean_angle(void);


#endif /* HMC5843_H_ */