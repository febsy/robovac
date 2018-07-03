/*
 * word_interpreter.c
 *
 * Created: 03.03.2018 00:21:21
 *  Author: feb
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>

#include "word_interpreter.h"

#include "usart0.h"

#include "drivesystem.h"
#include "tracker.h"
#include "vacuum.h"
#include "config.h"
#include "globals.h"


uint8_t word_interpreter_core(int16_t *cmd_var1,int16_t *cmd_var2)
{
	char command[32];
	usart0_gets(command,sizeof(command)/sizeof(command[0]));
	switch (command[0])
	{
		case 'G': // G Commands
			if ((command[1] == '0') && (command[2] == '0') && (command[3] == ' ')) // G0 - linear Movement
			{
				char delims[] = "XY ";
				char *ptr;
				ptr = strtok(command,delims); // throw away G0
				if(ptr != NULL)
				{
					ptr = strtok(NULL,delims); // get X
					*cmd_var1 = (atoi(ptr));
					if (ptr != NULL)
					{
						ptr = strtok(NULL,delims); // get Y
						*cmd_var2 = (atoi(ptr));
						return 000;
					}
				}
				return -1;
			}
			else if ((command[1] == '0') && (command[2] == '1') && (command[3] == ' ')) // G1 - turning
			{
				char* delims;
				char *ptr;
				if ((command[4] == 'L'))
				{
					delims = "L ";
					*cmd_var1 = 'L';
					
				}
				else if ((command[4] == 'R'))
				{
					delims = "R ";
					*cmd_var1 = 'R';
				}
				else
				{
					return -1;
				}
				ptr = strtok(command,delims); // throw away G1
				if(ptr != NULL)
				{
					ptr = strtok(NULL,delims); // get Angle
					*cmd_var2 = atoi(ptr);
					return 001;
				}
				return -1;
			}	
		break;
		case 'M': // M Commands
			if ((command[1] == '0') && (command[2] == '0')) // M0 - VacMotor Status
			{
				if ((command[3] == ' ') && (command[4] == 'S'))
				{
					char *sval = &command[5];
					*cmd_var1 = atoi(sval);
				}
				else
				{
					*cmd_var1 = -1;
				}
				*cmd_var2 = -1;
				return 100;
			}
			if ((command[1] == '0') && (command[2] == '1')) // M1 - Position & Angle
			{
				*cmd_var1 = -1;
				*cmd_var2 = -1;
				return 101;
			}
			if ((command[1] == '0') && (command[2] == '2')) // M2 - Status
			{
				*cmd_var1 = -1;
				*cmd_var2 = -1;
				return 102;
			}
			if ((command[1] == '0') && (command[2] == '3')) // M3 - US Distance
			{
				*cmd_var1 = -1;
				*cmd_var2 = -1;
				return 103;
			}
			if ((command[1] == '0') && (command[2] == '4')) // M4 - Show SysTime
			{
				*cmd_var1 = -1;
				*cmd_var2 = -1;
				return 104;
			}
			if ((command[1] == '0') && (command[2] == '5') && (command[3] == ' ')) // M5 - Set Coordinates
			{
				char delims[] = "XY ";
				char *ptr;
				ptr = strtok(command,delims); // throw away M5
				if(ptr != NULL)
				{
					ptr = strtok(NULL,delims); // get X
					*cmd_var1 = atoi(ptr);
					if (ptr != NULL)
					{
						ptr = strtok(NULL,delims); // get Y
						*cmd_var2 = atoi(ptr);
						return 105;
					}
				}
				return -1;
			}
			if ((command[1] == '0') && (command[2] == '6') && (command[3] == ' ')) // M6 - Set Angle
			{
				char delims[5] = "A \r\n";
				char *ptr;
				ptr = strtok(command,delims); // throw away M6
				if(ptr != NULL)
				{
					ptr = strtok(NULL,delims); // get Angle
					*cmd_var1 = atoi(ptr);
					*cmd_var2 = 0;
					return 106;
				}
				return -1;
			}
			if ((command[1] == '0') && (command[2] == '7') && (command[3] == ' ')) // M7 - Finetune linear movement
			{
				char delims[] = "S ";
				char *ptr;
				ptr = strtok(command,delims); // throw away M7
				if(ptr != NULL)
				{
					ptr = strtok(NULL,delims); // get finetune-var
					*cmd_var1 = atoi(ptr);
					*cmd_var2 = 0;
					return 107;
				}
				return -1;	
			}
			if ((command[1] == '0') && (command[2] == '8') && (command[3] == ' ')) // M8 - Finetune angle
			{
				char delims[] = "S ";
				char *ptr;
				ptr = strtok(command,delims); // throw away M8
				if(ptr != NULL)
				{
					ptr = strtok(NULL,delims); // get finetune-var
					*cmd_var1 = atoi(ptr);
					*cmd_var2 = 0;
					return 108;
				}
				return -1;
			}
			if ((command[1] == '9') && (command[2] == '9')) // M99 - Softreset
			{
				*cmd_var1 = 0;
				*cmd_var2 = 0;
				return 199;
			}
			if ((command[1] == '3') && (command[2] == '0')) // M30 - Stop Motors
			{
				*cmd_var1 = 0;
				*cmd_var2 = 0;
				return 130;
			}
			if ((command[1] == '1') && (command[2] == '1')) // M11 - Position & Hitindicator
			{
				*cmd_var1 = 0;
				*cmd_var2 = 0;
				return 111;
			}
			if ((command[1] == '2') && (command[2] == '0')) // M20 - Accu-Status
			{
				*cmd_var1 = 0;
				*cmd_var2 = 0;
				return 120;
			}
			if ((command[1] == '4') && (command[2] == '1')) // M41 - NTP
			{
				if ((command[3] != ' '))
				{
					*cmd_var1 = 0;
					*cmd_var2 = 0;
					return 141;
				}
				else
				{
					char delims[] = "IO ";
					char *ptr;
					ptr = strtok(command,delims); // throw away M41
					if(ptr != NULL)
					{
						ptr = strtok(NULL,delims); // get I
						*cmd_var1 = atoi(ptr);
						if (ptr != NULL)
						{
							ptr = strtok(NULL,delims); // get O
							*cmd_var2 = atoi(ptr);
							return 141;
						}
					}
				}
				return -1;
			}
		break;
	}	
	return -1;
}

void word_interpreter_response(uint8_t cmd, int16_t res_var1, int16_t res_var2, int16_t res_var3)
{
	uint8_t noerr = 0;
	if (cmd == 255)
	{
		char message[31];
		snprintf(message,sizeof(message),"ERROR could not recognize CMD\n");
		usart0_puts(message);
		return;
	}
	if (res_var1 == -1)
	{
		char message[11];
		if (cmd > 99)
		{
			cmd = cmd/100;
			snprintf(message,sizeof(message),"ERROR M%d\n",cmd);
		}
		else
		{
			snprintf(message,sizeof(message),"ERROR G%d\n",cmd);
		}
		usart0_puts(message);
		return;
	}
	switch (cmd)
	{
	case 000: // G0
		noerr = 1;
		char message_0[12];
		snprintf(message_0,sizeof(message_0),"OK BUSY G0\n");
		usart0_puts(message_0);
		return;
		break;
	case 001: // G1
		noerr = 1;
		char message_1[12];
		snprintf(message_1,sizeof(message_1),"OK BUSY G1\n");
		usart0_puts(message_1);
		return;
		break;
	case 101: // M1
		noerr = 1;
		char message_101[25];
		snprintf(message_101,sizeof(message_101),"OK X%d Y%d A%d\n",res_var1,res_var2,res_var3);
		usart0_puts(message_101);
		return;
		break;
	case 111: // M11
		noerr = 1;
		char message_111[25];
		snprintf(message_111,sizeof(message_111),"OK X%d Y%d O%d\n",res_var1,res_var2,res_var3);
		usart0_puts(message_111);
		return;
		break;
	case 103: // M3
		noerr = 1;
		char message_103[18];
		snprintf(message_103,sizeof(message_103),"OK L%d R%d\n",res_var1,res_var2);
		usart0_puts(message_103);
		return;
		break;
	case 141: // M41
		noerr = 1;
		if (res_var3 == -1)
		{
			char message_141[8];
			snprintf(message_141,sizeof(message_141),"OK M41\n");
			usart0_puts(message_141);
		}
		else
		{
			char message_141_2[10];
			snprintf(message_141_2,sizeof(message_141_2),"OK %d\n",res_var1);
			usart0_puts(message_141_2);
		}
		return;
		break;
	default: // M0 M2 M20 M4 M5 M6 M7 M8 M30
		noerr = 1;
		if (res_var3 == -1)
		{
			char message_def[4];
			snprintf(message_def,sizeof(message_def),"OK\n");
			usart0_puts(message_def);
		}
		else
		{
			char message_def2[10];
			snprintf(message_def2,sizeof(message_def2),"OK %d\n",res_var1);
			usart0_puts(message_def2);
		}
		if (noerr == 0)
		{
			mSoftReset = 1;
		}
		return;
		break;
	}
}

void word_interpreter_actor(uint8_t cmd_0, int16_t cmd_1,int16_t cmd_2,int16_t *res_1,int16_t *res_2,int16_t *res_3)
{
	*res_1 = -1;
	*res_2 = -1;
	*res_3 = -1;
	switch (cmd_0)
	{
	case 000: // G0
		if (drivesystem_isReady() == 1)
		{
			drivesystem_SetDestination(cmd_1,cmd_2);
			*res_1 = 0;
		}
		return;
		break;
	case 001: // G1
		if (drivesystem_isReady() == 1)
		{
			if(cmd_1 == 'L')
			{
				drivesystem_SetAngle(-1,cmd_2);
				*res_1 = 0;
			}
			else if (cmd_1 == 'R')
			{
				drivesystem_SetAngle(1,cmd_2);
				*res_1 = 0;
			}
		}
		return;
		break;
	case 100: // M0
		if (cmd_1 == -1)
		{
			*res_1 = vacuum_getState();
			*res_3 = 0;
		}
		else
		{
			*res_1 = vacuum_setState(cmd_1);
		}
		return;
		break;
	case 101: // M1
		tracker_getPosition('A',res_1,res_2,res_3);
		return;
		break;
	case 111: // M11
		tracker_getPosition('O',res_1,res_2,res_3);
		return;
		break;
	case 102: // M2
		*res_1 = config_getStatus();
		*res_3 = 0;
		return;
		break;
	case 120: // M20
		*res_1 = config_getBatteryStatus();
		*res_3 = 0;
		return;
		break;
	case 103: // M3
		tracker_getUSDistance(res_1,res_2);
		return;
		break;
	case 104: // M4
		*res_1 = config_getTime();
		*res_3 = 0;
		return;
		break;
	case 141: // M41
		if (cmd_1 == 0 && cmd_2 == 0)
		{
			config_NTP(0,0,0);
			*res_1 = 0;
			return;
		}
		else
		{
			*res_1 = config_NTP(1,cmd_1,cmd_2);
			*res_3 = 0;
			return;
		}
		return;
		break;
	case 105: // M5
		*res_1 = tracker_setHome(cmd_1,cmd_2);
		return;
		break;
	case 106: // M6
		*res_1 = tracker_setOrientation(cmd_1);
		return;
		break;
	case 107: // M7
		*res_1 = tracker_setDistancePerUnit(cmd_1);
		return;
		break;
	case 108: // M8
		*res_1 = tracker_setAnglePerUnit(cmd_1);
		return;
		break;
	case 130: // M30
		drivesystem_Stop();
		vacuum_setState(0);
		*res_1 = 1;
		return;
		break;
	case 199: // M99
		mSoftReset = 1;
		*res_1 = 1;
		return;
		break;
	default:
		return;
		break;
	}
}

void word_interpreter_message_handler(void)
{
	if (!(UCSR0A & (1<<RXC0)))
	{
		return;
	}
	int16_t cmd_1 = -1,cmd_2 = -1,res_1 = -1,res_2 = -1,res_3 = -1;
	uint8_t cmd_0 = word_interpreter_core(&cmd_1,&cmd_2);

	word_interpreter_actor(cmd_0,cmd_1,cmd_2,&res_1,&res_2,&res_3);
	word_interpreter_response(cmd_0,res_1,res_2,res_3);
}