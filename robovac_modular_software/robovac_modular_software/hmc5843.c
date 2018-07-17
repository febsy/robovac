/*
    5-18-10
    Copyright Spark Fun Electronics© 2010
    Nathan Seidle
	
	Example I2C to control the HMC5843 3-axis magnetometer
	
	Based on Aaron Weiss' code.
	
	Designed to run on an Arduino using the standard serial bootloader.
	This is not written in Arduino, this is a C example.
	
	Things to know: 
	Unlike other I2C devices, in the HMC5843 you can keep reading registers and 
	the adress pointer will continue to increment.
	
	The only register you have to write to, to get the HMC5843 to start outputting data
	is 0x02, the 'Mode' register. You have to clear bit 1 (MD1) to go into continous coversion mode.
	
	Don't forget to enable or add pullups to SDA/SCL. This firmware uses the internal
	pullups. Should work fine without them.
	
	SCL is Analog pin 5 (aka PC5)
	SDA is Analog pin 4 (aka PC4)
*/

#include <stdio.h>
#include <avr/io.h>
#include "i2c.h" //Needed for I2C sensors
#include <math.h>
#include <util/delay.h>

#include "globals.h"


#define HMC5843_W	0x3C
#define HMC5843_R	0x3D

//Function definitions
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void ioinit(void);

int read_hmc5843(char reg_adr);
void hmc5883_init(void);
int hmc5883_readvalues(void);
void init_hmc5843(void);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

//Global variables
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

void hmc5883_init (void)
{
    ioinit(); //Boot up defaults

	i2cInit(); //Get the I2C bus ready

	init_hmc5843(); //Write to 0x02 Mode register - clear MD1 bit
}

int hmc5883_readvalues(void){
	int x,y;
	x = read_hmc5843(0x03);
	read_hmc5843(0x05);
	y = read_hmc5843(0x07); 
	int angle = (int)((1.0000*((atan2(-y,x)*180)/M_PI))+180);
	return angle;
}

void hmc5883_mean_angle(void){
	volatile int internal_angle = 0, i;
	for(i = 0;i < 8;i++){
		internal_angle += hmc5883_readvalues();
	}
	mCurrentAngle = internal_angle/8;
}

void ioinit(void)
{
	PORTC = 0b00110000; //pullups on the I2C bus
}

int read_hmc5843(char reg_adr)
{		
	char lsb, msb;

	i2cSendStart();
	i2cWaitForComplete();
	
	i2cSendByte(HMC5843_W);	// write to this I2C address, R/*W cleared
	i2cWaitForComplete();
	
	i2cSendByte(reg_adr);	//Read from a given address
	i2cWaitForComplete();
	
	i2cSendStart();
	
	i2cSendByte(HMC5843_R); // read from this I2C address, R/*W Set
	i2cWaitForComplete();
	
	i2cReceiveByte(1);
	i2cWaitForComplete();
	msb = i2cGetReceivedByte(); //Read the LSB data
	i2cWaitForComplete();

	i2cReceiveByte(0);
	i2cWaitForComplete();
	lsb = i2cGetReceivedByte(); //Read the MSB data
	i2cWaitForComplete();
	
	i2cSendStop();
	
	return( (msb<<8) | lsb);
}

//Setup HMC5843 for constant measurement mode
void init_hmc5843(void)
{
	i2cSendStart();
	i2cWaitForComplete();

	i2cSendByte(HMC5843_W); //write to the HMC5843
	i2cWaitForComplete();

	i2cSendByte(0x02); //Write to Mode register
	i2cWaitForComplete();

	i2cSendByte(0x00); //Clear bit 1, the MD1 bit
	i2cWaitForComplete();

	i2cSendStop();
}