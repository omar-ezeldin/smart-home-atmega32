/*==========================================
  TIMER.h
  Timer Driver
============================================
  Type           : Driver Header
  Author         : Omar Ezzeldin
==========================================*/

#ifndef TIMER_H_
#define TIMER_H_

/*==========================================
GENERAL TIMER REGISTER DEFINITIONS
==========================================*/

#define TIMSK (*((volatile u8 *)0x59)) // Timer/Counter Interrupt Mask Register
#define TIFR  (*((volatile u8 *)0x58)) // Timer/Counter Interrupt Flag Register

/*==========================================
TIMER MODE DEFINITIONS
==========================================*/

#define TIMER_MD_NORMAL       0
#define TIMER_MD_CTC          1
#define TIMER_MD_PHASECORRECT 2
#define TIMER_MD_FASTPWM      3

/*==========================================
TIMER PRESCALER DEFINITIONS
==========================================*/

#define TIMER_PS_1               0
#define TIMER_PS_8               1
#define TIMER_PS_64              2
#define TIMER_PS_256             3
#define TIMER_PS_1024            4
#define TIMER_PS_EXTCLK_FALLEDGE 5
#define TIMER_PS_EXTCLK_RAISEDGE 6

/*==========================================
TIMER CONFIGURATION DEFINITIONS
==========================================*/

#define TIMER_FCPU 16 // The MCU's clock frequency in MHz

#endif /* TIMER_H_ */