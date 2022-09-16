#include <stdio.h>

#include "../interrupt/interrupt.h"
#include "timerInterrupt.h"
#include "timer.h"
#include "pruThread.h"



// Timer constructor
pruTimer::pruTimer(TIM_TypeDef* timer, IRQn_Type irq, uint32_t frequency, pruThread* ownerPtr):
	timer(timer),
	irq(irq),
	frequency(frequency),
	timerOwnerPtr(ownerPtr)
{
	interruptPtr = new TimerInterrupt(this->irq, this);	// Instantiate a new Timer Interrupt object and pass "this" pointer

	this->startTimer();
}


void pruTimer::timerTick(void)
{
	//Do something here
	this->timerOwnerPtr->run();
}



void pruTimer::startTimer(void)
{
    uint32_t TIM_CLK;

    if (this->timer == TIM9)
    {
        printf("	power on Timer 9\n\r");
        __HAL_RCC_TIM9_CLK_ENABLE();
        TIM_CLK = APB1CLK;
    }
    else if (this->timer == TIM10)
    {
        printf("	power on Timer 10\n\r");
        __HAL_RCC_TIM10_CLK_ENABLE();
        TIM_CLK = APB1CLK;
    }



    //timer update frequency = TIM_CLK/(TIM_PSC+1)/(TIM_ARR + 1)

    this->timer->CR2 &= 0;                                            // UG used as trigg output
    this->timer->PSC = TIM_PSC-1;                                     // prescaler
    this->timer->ARR = ((TIM_CLK / TIM_PSC / this->frequency) - 1);   // period
    this->timer->EGR = TIM_EGR_UG;                                    // reinit the counter
    this->timer->DIER = TIM_DIER_UIE;                                 // enable update interrupts
    this->timer->CR1 |= TIM_CR1_CEN;                                  // enable timer

    NVIC_EnableIRQ(this->irq);

    printf("	timer started\n");
}

void pruTimer::stopTimer()
{
    NVIC_DisableIRQ(this->irq);

    printf("	timer stop\n\r");
    this->timer->CR1 &= (~(TIM_CR1_CEN));     // disable timer
}
