/*
 * ultrasonic.h
 *
 * Created: 29.04.2017 21:42:11
 *  Author: febs
 */ 


#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

extern volatile unsigned long runtime_us;

extern volatile unsigned long us1_time, us2_time;
extern volatile int us1_distance,us2_distance;

extern void ultrasonic_init(void);
extern int ultrasonic_transform(unsigned long);
extern uint8_t ultrasonic_getDistance(int16_t*,int16_t*);
extern void ultrasonic_measureDEAMON(void);



#endif /* ULTRASONIC_H_ */