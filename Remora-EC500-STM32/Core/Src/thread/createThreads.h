#include "extern.h"


void createThreads(void)
{
    baseThread = new pruThread(TIM9, TIM1_BRK_TIM9_IRQn, base_freq);
    //NVIC_SetVector(TIM1_BRK_TIM9_IRQn, (uint32_t)TIM9_IRQHandler);
    NVIC_SetPriority(TIM1_BRK_TIM9_IRQn, 2);

    servoThread = new pruThread(TIM10, TIM1_UP_TIM10_IRQn, servo_freq);
    //NVIC_SetVector(TIM1_UP_TIM10_IRQn, (uint32_t)TIM10_IRQHandler);
    NVIC_SetPriority(TIM1_UP_TIM10_IRQn, 3);
}
