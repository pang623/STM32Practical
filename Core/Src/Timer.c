/*
 * Tim1.c
 *
 *  Created on: Jul 29, 2021
 *      Author: Pang
 */

#include "Timer.h"

void timerConfigure(TimReg *timer, TimerConfig cfg) {
	timer->CR1 |= cfg & 0x3FF;
	timer->CR2 |= (cfg >> 16) & 0x7FFD;
	timer->SMCR |= (cfg >> 32) & 0xFFF7;
	timer->DIER |= (cfg >> 48) & 0x7FFF;
}

void timerConfigureCaptureCompare(TimReg *timer, int chnNum, TimerCapComConfig cfg) {
	if(chnNum <= 2) {
		timer->CCMR1 = 0;
		timer->CCMR1 |= cfg & 0xFFFF;
	}else {
		timer->CCMR2 = 0;
		timer->CCMR2 |= (cfg >> 16) & 0xFFFF;
	}
	timer->CCER |= (cfg >> 32) & 0x3FFF;
}

void timerConfigureEventGeneration(TimReg *timer, TimerEventGenConfig cfg) {
	timer->EGR = cfg & 0xFF;
}

void timerSetCapComReg(TimReg *timer, int chnNum, uint16_t value) {
	timer->CCR[chnNum - 1] = value;
}

void timerSetPrescaler(TimReg *timer, uint16_t val) {
	timer->PSC = val;
}

void timerSetARR(TimReg *timer, uint32_t val) {
	timer->ARR = (uint32_t)val;
}
