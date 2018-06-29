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
extern void ultrasonic_startmeasurement(void);
extern void ultrasonic_getdistance(void);



#endif /* ULTRASONIC_H_ */