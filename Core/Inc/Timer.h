/*
 * Tim1.h
 *
 *  Created on: Jul 29, 2021
 *      Author: Pang
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "stdint.h"
#include "IO.h"

#define timSetOutCompareReg(tim, chn, val)	\
	((_IO_ uint32_t *)&(tim)->ccr1)[chn - 1] = (val)

#define timGetInCapReg(tim, chn, val)	\
	(((_IO_ uint32_t *)&(tim)->ccr1)[chn - 1])

//All TIMER base addresses
#define TIM1_BASE_ADDRESS 		0x40010000
#define TIM2_BASE_ADDRESS 		0x40000000
#define TIM3_BASE_ADDRESS 		0x40000400
#define TIM4_BASE_ADDRESS 		0x40000800
#define TIM5_BASE_ADDRESS 		0x40000C00
#define TIM9_BASE_ADDRESS 		0x40014000
#define TIM10_BASE_ADDRESS 		0x40014400
#define TIM11_BASE_ADDRESS 		0x40014800

//All TIMER pointers
#define timer1			 		((TimReg*)TIM1_BASE_ADDRESS)
#define timer2			 		((TimReg*)TIM2_BASE_ADDRESS)
#define timer3			 		((TimReg*)TIM3_BASE_ADDRESS)
#define timer4			 		((TimReg*)TIM4_BASE_ADDRESS)
#define timer5			 		((TimReg*)TIM5_BASE_ADDRESS)
#define timer9			 		((TimReg*)TIM9_BASE_ADDRESS)
#define timer10			 		((TimReg*)TIM10_BASE_ADDRESS)
#define timer11			 		((TimReg*)TIM11_BASE_ADDRESS)

//TIMER registers
typedef struct TimReg_t TimReg;
struct TimReg_t {
	_IO_ uint32_t CR1;
	_IO_ uint32_t CR2;
	_IO_ uint32_t SMCR;
	_IO_ uint32_t DIER;
	_IO_ uint32_t SR;
	_IO_ uint32_t EGR;
	_IO_ uint32_t CCMR1;
	_IO_ uint32_t CCMR2;
	_IO_ uint32_t CCER;
	_IO_ uint32_t CNT;
	_IO_ uint32_t PSC;
	_IO_ uint32_t ARR;
	_IO_ uint32_t RCR;
	_IO_ uint32_t CCR[4];
	_IO_ uint32_t BDTR;
	_IO_ uint32_t DCR;
	_IO_ uint32_t DMAR;
	_IO_ uint32_t OR;
};

typedef enum {
	//---------------------------------------CR1---------------------------------------
	TIM_EN = 1 << 0,
	TIM_UPDATE_EN = 0 << 1, TIM_UPDATE_DISABLE = 1 << 1,
	TIM_URS_CNT_ONLY = 1 << 2,
	TIM_OPM_EN = 1 << 3,
	TIM_DIR_UP = 0 << 4, TIM_DIR_DOWN = 1 << 4,
	TIM_CMS_EDGE = 0 << 5, TIM_CMS_MODE1 = 1 << 5, TIM_CMS_MODE2 = 2 << 5, TIM_CMS_MODE3 = 3 << 5,
	TIM_AUTO_RELOAD_PRELOAD_EN = 1 << 7,
	TIM_CLK_DIV_1 = 0 << 8, TIM_CLK_DIV_2 = 1 << 8, TIM_CLK_DIV_4 = 2 << 8,
	//---------------------------------------CR2---------------------------------------
	TIM_CCPC_EN = 1 << (0 + 16),
	TIM_CCUS_SEL1 = 0 << (2 + 16), TIM_CCUS_SEL2 = 1 << (2 + 16),
	TIM_CCDS_CCx = 0 << (3 + 16), TIM_CCDS_UPDATE = 1 << (3 + 16),
	TIM_MMS_RST = 0 << (4 + 16), TIM_MMS_EN = 1 << (4 + 16), TIM_MMS_UPDATE = 2 << (4 + 16),
	TIM_MMS_CMP_PULSE = 3 << (4 + 16), TIM_MMS_CMP_OC1REF = 4 << (4 + 16), TIM_MMS_CMP_OC2REF = 5 << (4 + 16),
	TIM_MMS_CMP_OC3REF = 6 << (4 + 16), TIM_MMS_CMP_OC4REF = 7 << (4 + 16),
	TIM_TI1S_TIM_CH1_ONLY = 0 << (7 + 16), TIM_TI1S_TIM_CH1_2_3 = 1 << (7 + 16),
	TIM_OIS1_OC1_0 = 0 << (8 + 16), TIM_OIS1_OC1_1 = 1 << (8 + 16),
	TIM_OIS1N_OC1N_0 = 0 << (9 + 16), TIM_OIS1N_OC1N_1 = 1 << (9 + 16),
	TIM_OIS2_OC2_0 = 0 << (10 + 16), TIM_OIS2_OC2_1 = 1 << (10 + 16),
	TIM_OIS2N_OC2N_0 = 0 << (11 + 16), TIM_OIS2N_OC2N_1 = 1 << (11 + 16),
	TIM_OIS3_OC3_0 = 0 << (12 + 16), TIM_OIS3_OC3_1 = 1 << (12 + 16),
	TIM_OIS3N_OC3N_0 = 0 << (13 + 16), TIM_OIS3N_OC3N_1 = 1 << (13 + 16),
	TIM_OIS4_OC4_0 = 0 << (14 + 16), TIM_OIS4_OC4_1 = 1 << (14 + 16),
	//---------------------------------------SMCR---------------------------------------
	TIM_SLAVE_DISABLE = 0LL << (0 + 32), TIM_SLAVE_ENC_MODE1 = 1LL << (0 + 32), TIM_SLAVE_ENC_MODE2 = 2LL << (0 + 32),
	TIM_SLAVE_ENC_MODE3 = 3LL << (0 + 32), TIM_SLAVE_RST = 4LL << (0 + 32), TIM_SLAVE_GATED = 5LL << (0 + 32),
	TIM_SLAVE_TRIGGER = 6LL << (0 + 32), TIM_SLAVE_EXT_CLK = 7LL << (0 + 32),
	TIM_TS_ITR0 = 0LL << (4 + 32), TIM_TS_ITR1 = 1LL << (4 + 32), TIM_TS_ITR2 = 2LL << (4 + 32),
	TIM_TS_ITR3 = 3LL << (4 + 32), TIM_TS_TI1F_ED = 4LL << (4 + 32), TIM_TS_TI1FP1 = 5LL << (4 + 32),
	TIM_TS_TI1FP2 = 6LL << (4 + 32), TIM_TS_ETRF = 7LL << (4 + 32),
	TIM_MSM = 1LL << (7 + 32),
	TIM_ETF_NO_FILTER = 0LL << (8 + 32), TIM_ETF_FCK_INT_N2 = 1LL << (8 + 32), TIM_ETF_FCK_INT_N4 = 2LL << (8 + 32),
	TIM_ETF_FCK_INT_N8 = 3LL << (8 + 32), TIM_ETF_FDTS2_N6 = 4LL << (8 + 32), TIM_ETF_FDTS2_N8 = 5LL << (8 + 32),
	TIM_ETF_FDTS4_N6 = 6LL << (8 + 32), TIM_ETF_FDTS4_N8 = 7LL << (8 + 32), TIM_ETF_FDTS8_N6 = 8LL << (8 + 32),
	TIM_ETF_FDTS8_N8 = 9LL << (8 + 32), TIM_ETF_FDTS16_N5 = 10LL << (8 + 32), TIM_ETF_FDTS16_N6 = 11LL << (8 + 32),
	TIM_ETF_FDTS16_N8 = 12LL << (8 + 32), TIM_ETF_FDTS32_N5 = 13LL << (8 + 32), TIM_ETF_FDTS32_N6 = 14LL << (8 + 32),
	TIM_ETF_FDTS32_N8 = 15LL << (8 + 32),
	TIM_ETPS_OFF = 0LL << (12 + 32), TIM_ETPS_2 = 1LL << (12 + 32),
	TIM_ETPS_4 = 2LL << (12 + 32), TIM_ETPS_8 = 3LL << (12 + 32),
	TIM_EXT_CLK_MODE2_EN = 1LL << (14 + 32),
	TIM_ETP_NON_INVERT = 0LL << (15 + 32), TIM_ETP_INVERT = 1LL << (15 + 32),
	//---------------------------------------DIER---------------------------------------
	TIM_UI_EN = 1LL << (0 + 48),
	TIM_CC1I_EN = 1LL << (1 + 48),
	TIM_CC2I_EN = 1LL << (2 + 48),
	TIM_CC3I_EN = 1LL << (3 + 48),
	TIM_CC4I_EN = 1LL << (4 + 48),
	TIM_COMI_EN = 1LL << (5 + 48),
	TIM_TI_EN = 1LL << (6 + 48),
	TIM_BI_EN = 1LL << (7 + 48),
	TIM_UD_EN = 1LL << (8 + 48),
	TIM_CC1D_EN = 1LL << (9 + 48),
	TIM_CC2D_EN = 1LL << (10 + 48),
	TIM_CC3D_EN = 1LL << (11 + 48),
	TIM_CC4D_EN = 1LL << (12 + 48),
	TIM_COMD_EN = 1LL << (13 + 48),
	TIM_TD_EN = 1LL << (14 + 48),
} TimerConfig;

typedef enum {
	//---------------------------------------CCMR1---------------------------------------
	TIM_CC1S_OUTPUT = 0, TIM_CC1S_INPUT_IC1_TI1 = 1,
	TIM_CC1S_INPUT_IC1_TI2 = 2, TIM_CC1S_INPUT_IC1_TRC = 3,
	TIM_CC2S_OUTPUT = 0 << 8, TIM_CC2S_INPUT_IC2_TI2 = 1 << 8,
	TIM_CC2S_INPUT_IC2_TI1 = 2 << 8, TIM_CC2S_INPUT_IC2_TRC = 3 << 8,

	//Output compare mode only
	TIM_OC1_FAST_EN = 1 << 2,
	TIM_OC1_PRELOAD_EN = 1 << 3,
	TIM_OC1M_FROZEN = 0 << 4, TIM_OC1M_CH1_ACT_ON_MATCH = 1 << 4, TIM_OC1M_CH1_INACT_ON_MATCH = 2 << 4,
	TIM_OC1M_TOGGLE = 3 << 4, TIM_OC1M_FORCE_INACT = 4 << 4, TIM_OC1M_FORCE_ACT = 5 << 4,
	TIM_OC1M_PWM_MODE1 = 6 << 4, TIM_OC1M_PWM_MODE2 = 7 << 4,
	TIM_OC1_CLR_EN = 1 << 7,

	TIM_OC2_FAST_EN = 1 << 10,
	TIM_OC2_PRELOAD_EN = 1 << 11,
	TIM_OC2M_FROZEN = 0 << 12, TIM_OC2M_CH2_ACT_ON_MATCH = 1 << 12, TIM_OC2M_CH2_INACT_ON_MATCH = 2 << 12,
	TIM_OC2M_TOGGLE = 3 << 12, TIM_OC2M_FORCE_INACT = 4 << 12, TIM_OC2M_FORCE_ACT = 5 << 12,
	TIM_OC2M_PWM_MODE1 = 6 << 12, TIM_OC2M_PWM_MODE2 = 7 << 12,
	TIM_OC2_CLR_EN = 1 << 15,

	//Input capture mode only
	TIM_IC1PSC_OFF = 0 << 2, TIM_IC1PSC_2 = 1 << 2,
	TIM_IC1PSC_4 = 2 << 2, TIM_IC1PSC_8 = 3 << 2,
	TIM_IC1F_NO_FILTER = 0 << 4, TIM_IC1F_FCK_INT_N2 = 1 << 4, TIM_IC1F_FCK_INT_N4 = 2 << 4,
	TIM_IC1F_FCK_INT_N8 = 3 << 4, TIM_IC1F_FDTS2_N6 = 4 << 4, TIM_IC1F_FDTS2_N8 = 5 << 4,
	TIM_IC1F_FDTS4_N6 = 6 << 4, TIM_IC1F_FDTS4_N8 = 7 << 4, TIM_IC1F_FDTS8_N6 = 8 << 4,
	TIM_IC1F_FDTS8_N8 = 9 << 4, TIM_IC1F_FDTS16_N5 = 10 << 4, TIM_IC1F_FDTS16_N6 = 11 << 4,
	TIM_IC1F_FDTS16_N8 = 12 << 4, TIM_IC1F_FDTS32_N5 = 13 << 4, TIM_IC1F_FDTS32_N6 = 14 << 4,
	TIM_IC1F_FDTS32_N8 = 15 << 4,

	TIM_IC2PSC_OFF = 0 << 10, TIM_IC2PSC_2 = 1 << 10,
	TIM_IC2PSC_4 = 2 << 10, TIM_IC2PSC_8 = 3 << 10,
	TIM_ICF2_NO_FILTER = 0 << 12, TIM_ICF2_FCK_INT_N2 = 1 << 12, TIM_ICF2_FCK_INT_N4 = 2 << 12,
	TIM_ICF2_FCK_INT_N8 = 3 << 12, TIM_ICF2_FDTS2_N6 = 4 << 12, TIM_ICF2_FDTS2_N8 = 5 << 12,
	TIM_ICF2_FDTS4_N6 = 6 << 12, TIM_ICF2_FDTS4_N8 = 7 << 12, TIM_ICF2_FDTS8_N6 = 8 << 12,
	TIM_ICF2_FDTS8_N8 = 9 << 12, TIM_ICF2_FDTS16_N5 = 10 << 12, TIM_ICF2_FDTS16_N6 = 11 << 12,
	TIM_ICF2_FDTS16_N8 = 12 << 12, TIM_ICF2_FDTS32_N5 = 13 << 12, TIM_ICF2_FDTS32_N6 = 14 << 12,
	TIM_ICF2_FDTS32_N8 = 15 << 12,

	//---------------------------------------CCMR2---------------------------------------
	TIM_CC3S_OUTPUT = 0LL << (0 + 16), TIM_CC3S_INPUT_IC1_TI1 = 1LL << (0 + 16),
	TIM_CC3S_INPUT_IC1_TI2 = 2LL << (0 + 16), TIM_CC3S_INPUT_IC1_TRC = 3LL << (0 + 16),
	TIM_CC4S_OUTPUT = 0LL << (8 + 16), TIM_CC4S_INPUT_IC2_TI2 = 1LL << (8 + 16),
	TIM_CC4S_INPUT_IC2_TI1 = 2LL << (8 + 16), TIM_CC4S_INPUT_IC2_TRC = 3LL << (8 + 16),

	//Output compare mode only
	TIM_OC3_FAST_EN = 1LL << (2 + 16),
	TIM_OC3_PRELOAD_EN = 1LL << (3 + 16),
	TIM_OC3M_FROZEN = 0LL << (4 + 16), TIM_OC3M_CH3_ACT_ON_MATCH = 1LL << (4 + 16), TIM_OC3M_CH3_INACT_ON_MATCH = 2LL << (4 + 16),
	TIM_OC3M_TOGGLE = 3LL << (4 + 16), TIM_OC3M_FORCE_INACT = 4LL << (4 + 16), TIM_OC3M_FORCE_ACT = 5LL << (4 + 16),
	TIM_OC3M_PWM_MODE1 = 6LL << (4 + 16), TIM_OC3M_PWM_MODE2 = 7LL << (4 + 16),
	TIM_OC3_CLR_EN = 1LL << (7 + 16),

	TIM_OC4_FAST_EN = 1LL << (10 + 16),
	TIM_OC4_PRELOAD_EN = 1LL << (11 + 16),
	TIM_OC4M_FROZEN = 0LL << (12 + 16), TIM_OC4M_CH4_ACT_ON_MATCH = 1LL << (12 + 16), TIM_OC4M_CH4_INACT_ON_MATCH = 2LL << (12 + 16),
	TIM_OC4M_TOGGLE = 3LL << (12 + 16), TIM_OC4M_FORCE_INACT = 4LL << (12 + 16), TIM_OC4M_FORCE_ACT = 5LL << (12 + 16),
	TIM_OC4M_PWM_MODE1 = 6LL << (12 + 16), TIM_OC4M_PWM_MODE2 = 7LL << (12 + 16),
	TIM_OC4_CLR_EN = 1LL << (15 + 16),

	//Input capture mode only
	TIM_IC3PSC_OFF = 0LL << (2 + 16), TIM_IC3PSC_2 = 1LL << (2 + 16),
	TIM_IC3PSC_4 = 2LL << (2 + 16), TIM_IC3PSC_8 = 3LL << (2 + 16),
	TIM_IC3F_NO_FILTER = 0LL << (4 + 16), TIM_IC3F_FCK_INT_N2 = 1LL << (4 + 16), TIM_IC3F_FCK_INT_N4 = 2LL << (4 + 16),
	TIM_IC3F_FCK_INT_N8 = 3LL << (4 + 16), TIM_IC3F_FDTS2_N6 = 4LL << (4 + 16), TIM_IC3F_FDTS2_N8 = 5LL << (4 + 16),
	TIM_IC3F_FDTS4_N6 = 6LL << (4 + 16), TIM_IC3F_FDTS4_N8 = 7LL << (4 + 16), TIM_IC3F_FDTS8_N6 = 8LL << (4 + 16),
	TIM_IC3F_FDTS8_N8 = 9LL << (4 + 16), TIM_IC3F_FDTS16_N5 = 10LL << (4 + 16), TIM_IC3F_FDTS16_N6 = 11LL << (4 + 16),
	TIM_IC3F_FDTS16_N8 = 12LL << (4 + 16), TIM_IC3F_FDTS32_N5 = 13LL << (4 + 16), TIM_IC3F_FDTS32_N6 = 14LL << (4 + 16),
	TIM_IC3F_FDTS32_N8 = 15LL << (4 + 16),

	TIM_IC4PSC_OFF = 0LL << (10 + 16), TIM_IC4PSC_2 = 1LL << (10 + 16),
	TIM_IC4PSC_4 = 2LL << (10 + 16), TIM_IC4PSC_8 = 3LL << (10 + 16),
	TIM_ICF4_NO_FILTER = 0LL << (12 + 16), TIM_ICF4_FCK_INT_N2 = 1LL << (12 + 16), TIM_ICF4_FCK_INT_N4 = 2LL << (12 + 16),
	TIM_ICF4_FCK_INT_N8 = 3LL << (12 + 16), TIM_ICF4_FDTS2_N6 = 4LL << (12 + 16), TIM_ICF4_FDTS2_N8 = 5LL << (12 + 16),
	TIM_ICF4_FDTS4_N6 = 6LL << (12 + 16), TIM_ICF4_FDTS4_N8 = 7LL << (12 + 16), TIM_ICF4_FDTS8_N6 = 8LL << (12 + 16),
	TIM_ICF4_FDTS8_N8 = 9LL << (12 + 16), TIM_ICF4_FDTS16_N5 = 10LL << (12 + 16), TIM_ICF4_FDTS16_N6 = 11LL << (12 + 16),
	TIM_ICF4_FDTS16_N8 = 12LL << (12 + 16), TIM_ICF4_FDTS32_N5 = 13LL << (12 + 16), TIM_ICF4_FDTS32_N6 = 14LL << (12 + 16),
	TIM_ICF4_FDTS32_N8 = 15LL << (12 + 16),

	//---------------------------------------CCER---------------------------------------
	TIM_CC1NE_OP_OFF = 0LL << (2 + 32), TIM_CC1NE_OP_EN = 1LL << (2 + 32),
	TIM_CC1NP_OC1N_HIGH = 0LL << (3 + 32), TIM_CC1NP_OC1N_LOW = 1LL << (3 + 32),
	TIM_CC2NE_OP_OFF = 0LL << (6 + 32), TIM_CC2NE_OP_EN = 1LL << (6 + 32),
	TIM_CC2NP_OC1N_HIGH = 0LL << (7 + 32), TIM_CC2NP_OC1N_LOW = 1LL << (7 + 32),
	TIM_CC3NE_OP_OFF = 0LL << (10 + 32), TIM_CC3NE_OP_EN = 1LL << (10 + 32),
	TIM_CC3NP_OC1N_HIGH = 0LL << (11 + 32), TIM_CC3NP_OC1N_LOW = 1LL << (11 + 32),

	//Only for CCx channel configured as OUTPUT
	TIM_CC1_OP_OFF = 0LL << (0 + 32), TIM_CC1_OP_EN = 1LL << (0 + 32),
	TIM_CC1P_OC_HIGH = 0LL << (1 + 32), TIM_CC1P_OC_LOW = 1LL << (1 + 32),
	TIM_CC2_OP_OFF = 0LL << (4 + 32), TIM_CC2_OP_EN = 1LL << (4 + 32),
	TIM_CC2P_OC_HIGH = 0LL << (5 + 32), TIM_CC2P_OC_LOW = 1LL << (5 + 32),
	TIM_CC3_OP_OFF = 0LL << (8 + 32), TIM_CC3_OP_EN = 1LL << (8 + 32),
	TIM_CC3P_OC_HIGH = 0LL << (9 + 32), TIM_CC3P_OC_LOW = 1LL << (9 + 32),
	TIM_CC4_OP_OFF = 0LL << (12 + 32), TIM_CC4_OP_EN = 1LL << (12 + 32),
	TIM_CC4P_OC_HIGH = 0LL << (13 + 32), TIM_CC4P_OC_LOW = 1LL << (13 + 32),

	//Only for CCx channel configured as INPUT
	TIM_CC1_IP_CAPTURE_DISABLE = 0LL << (0 + 32), TIM_CC1_IP_CAPTURE_EN = 1LL << (0 + 32),
	TIM_CC1P_RISING_EDGE = 0LL << (1 + 32), TIM_CC1P_FALLING_EDGE = 1LL << (1 + 32), TIM_CC1P_BOTH_EDGE = 3LL << (1 + 32),
	TIM_CC2_IP_CAPTURE_DISABLE = 0LL << (4 + 32), TIM_CC2_IP_CAPTURE_EN = 1LL << (4 + 32),
	TIM_CC2P_RISING_EDGE = 0LL << (5 + 32), TIM_CC2P_FALLING_EDGE = 1LL << (5 + 32), TIM_CC2P_BOTH_EDGE = 3LL << (5 + 32),
	TIM_CC3_IP_CAPTURE_DISABLE = 0LL << (8 + 32), TIM_CC3_IP_CAPTURE_EN = 1LL << (8 + 32),
	TIM_CC3P_RISING_EDGE = 0LL << (9 + 32), TIM_CC3P_FALLING_EDGE = 1LL << (9 + 32), TIM_CC3P_BOTH_EDGE = 3LL << (9 + 32),
	TIM_CC4_IP_CAPTURE_DISABLE = 0LL << (12 + 32), TIM_CC4_IP_CAPTURE_EN = 1LL << (12 + 32),
	TIM_CC4P_RISING_EDGE = 0LL << (13 + 32), TIM_CC4P_FALLING_EDGE = 1LL << (13 + 32), TIM_CC4P_BOTH_EDGE = 3LL << (13 + 32),
} TimerCapComConfig;

typedef enum {
	TIM_UG = 1 << 0,
	TIM_CC1G = 1 << 1,
	TIM_CC2G = 1 << 2,
	TIM_CC3G = 1 << 3,
	TIM_CC4G = 1 << 4,
	TIM_COMG = 1 << 5,
	TIM_TG = 1 << 6,
	TIM_BG = 1 << 7,
} TimerEventGenConfig;

typedef enum {
	TIM_UIF = (1 << 0), TIM_CC1IF = (1 << 1), TIM_CC2IF = (1 << 2), TIM_CC3IF = (1 << 3),
	TIM_CC4IF = (1 << 4), TIM_COMIF = (1 << 5), TIM_TIF = (1 << 6), TIM_BIF = (1 << 7),
	TIM_CC1OF = (1 << 9), TIM_CC2OF = (1 << 10), TIM_CC3OF = (1 << 11), TIM_CC4OF = (1 << 12),
} TimerStatusFlags;

void timerConfigure(TimReg *timer, TimerConfig cfg);
void timerConfigureCaptureCompare(TimReg *timer, int chnNum, TimerCapComConfig cfg);
void timerConfigureEventGeneration(TimReg *timer, TimerEventGenConfig cfg);
void timerSetCapComReg(TimReg *timer, int chnNum, uint16_t value);
void timerSetPrescaler(TimReg *timer, uint16_t val);
void timerSetARR(TimReg *timer, uint32_t val);

#endif /* INC_TIMER_H_ */
