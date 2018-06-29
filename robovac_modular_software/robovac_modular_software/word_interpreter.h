/*
 * word_interpreter.h
 *
 * Created: 03.03.2018 00:21:59
 *  Author: feb
 */ 


#ifndef WORD_INTERPRETER_H_
#define WORD_INTERPRETER_H_


void word_interpreter_message_handler(void);

uint8_t word_interpreter_core(int16_t*,int16_t*);
void word_interpreter_response(uint8_t, int16_t, int16_t, int16_t);


#endif /* WORD_INTERPRETER_H_ */