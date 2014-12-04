

#include <msp430g2553.h>
#include "robotMotion.h"

void initTimerOutputSignals()
{
	P1DIR|=BIT1; //TA0.0
	P1DIR|=BIT2; //TA0.1
	P2DIR|=BIT0; //TA1.0
	P2DIR|=BIT1; //TA1.1

	P1SEL|=BIT1; //configures pins as pull-up/ pull-down networks
	P1SEL|=BIT2;
	P2SEL|=BIT0;
	P2SEL|=BIT1;
}

void configureA0andA1Timers()
{
	TA0CTL &= ~MC1|MC0;     // stop timer A0

	TA0CTL |= TACLR;        // clear timer A0

	TA0CTL |= TASSEL1;      // configure for SMCLK

	TA1CTL &= ~MC1|MC0;     // stop timer A0

	TA1CTL |= TACLR;        // clear timer A0

	TA1CTL |= TASSEL1;      // configure for SMCLK

	TA0CCR0 = 100;          // set signal period to 100 clock cycles (~100 microseconds)
	TA0CCR1 = 50;           // set duty cycle to 50/100 (50%)

	TA1CCR0 = 100;          // set signal period to 100 clock cycles (~100 microseconds)
	TA1CCR1 = 50;           // set duty cycle to 50/100 (50%)

	TA0CTL |= MC0;          // count up

	TA1CTL |= MC0;		    //count up
}

void clearModes()
{
	TA0CCTL1 &= ~OUTMOD_7;        // clear mode
	TA0CCTL0 &= ~OUTMOD_7;		 // clear mode

	TA1CCTL1 &= ~OUTMOD_7;  //clear mode
	TA1CCTL0 &= ~OUTMOD_7;  //clear mode
}

void turnSmallRight()
{
	clearModes();
	TA0CCR1 = 30;  //30%duty cycle, just to slow things down a bit
	TA1CCR1 = 30;
	TA0CCTL1 |= OUTMOD_5;        // set TACCTL1 to Reset mode
	TA0CCTL0 |= OUTMOD_7;		 // set TACCTL0 to Reset/Set

	TA1CCTL1 |= OUTMOD_7; //reset/set
	__delay_cycles(200000);
	clearModes();
}

void turnBigRight()
{
	clearModes();
	TA0CCR1 = 30;
	TA1CCR1 = 30;
	TA0CCTL1 |= OUTMOD_5;        // set TACCTL1 to Reset mode
	TA0CCTL0 |= OUTMOD_7;		 // set TACCTL0 to Reset/Set

	TA1CCTL1 |= OUTMOD_7; //reset/set
	__delay_cycles(300000);
	clearModes();
}

void turnSmallLeft()
{
	clearModes();
	TA0CCR1 = 30;
	TA1CCR1 = 30;
	TA1CCTL1 |= OUTMOD_5;        // set TACCTL1 to Reset / Set mode
	TA1CCTL0 |= OUTMOD_7;		 // set TACCTL0 to Reset

	TA0CCTL1 |= OUTMOD_7;
	__delay_cycles(200000);
	clearModes();
}

void turnBigLeft()
{
	clearModes();
	TA0CCR1 = 30;
	TA1CCR1 = 30;
	TA1CCTL1 |= OUTMOD_5;        // set TACCTL1 to Reset / Set mode
	TA1CCTL0 |= OUTMOD_7;		 // set TACCTL0 to Reset

	TA0CCTL1 |= OUTMOD_7;
	__delay_cycles(300000);
	clearModes();
}

void moveForward()
{
	clearModes();
	TA0CCR1 = 50;
	TA1CCR1 = 50;
	TA1CCTL1 |= OUTMOD_7; //reset/set
	TA0CCTL1 |= OUTMOD_7; //reset/set
	__delay_cycles(900000);
	clearModes();
}

void moveBackward()
{
	clearModes();
	TA0CCR1 = 5;  //this is because backward moves super fast
	TA1CCR1 = 5;
	TA1CCTL1 |= OUTMOD_5;        // set TACCTL1 to Reset mode
	TA1CCTL0 |= OUTMOD_7;		 // set TACCTL0 to Reset/Set
	TA0CCTL1 |= OUTMOD_5;        // set TACCTL1 to Reset mode
	TA0CCTL0 |= OUTMOD_7;		 // set TACCTL0 to Reset/Set
	__delay_cycles(500000);
	clearModes();
}
//functions


