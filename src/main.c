/*
 * main.c
 */

#include "DSP2833x_Device.h"     // Device Header Include File
#include "DSP2833x_Examples.h"
#include "GPIO_Driver.h"
#include "usDelay.h"

#include <CanBus.h>
#include <timer.h>

#define READY 1
#define SOFTSTART 2
#define RUN	3
#define SOFTOFF 4
#define FAULT 5
#define DEBUG 6

void main(void) {

	//0. init Sys
	InitSysCtrl();
	InitPieCtrl();

	//1. =========================interrupt=============================================
	// Disable CPU interrupts and clear all CPU interrupt flags:
	DINT;
	IER = 0x0000;
	IFR = 0x0000;

	//ram Funcs

	//	MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);

	InitFlash();
	// Initialize the PIE vector table with pointers to the shell Interrupt
	// Service Routines (ISR).
	// This will populate the entire table, even if the interrupt
	// is not used in this example.  This is useful for debug purposes.
	// The shell ISR routines are found in DSP2833x_DefaultIsr.c.
	// This function is found in DSP2833x_PieVect.c.c0
	InitPieVectTable();

	EINT;
	// Enable Global interrupt INTM
	ERTM;
	// Enable Global realtime interrupt DBGM

	//===============user module=======================
	//initialize GPIO
	configureLED();
	configureTimer0();
	configureEcanB();
	Uint32 i = 0;
	for (i = 0;; i++) {
		//      send_data (int16 MBXnbr, Uint32 low, Uint32 high, Uint32 id);
		send_data(MBX_BIC, i, i + 1);
		DELAY_US(1000000);
	}
}

