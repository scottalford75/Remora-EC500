#include "interrupt.h"

extern "C" {

	void TIM1_BRK_TIM9_IRQHandler()
	{
	  if(TIM9->SR & TIM_SR_UIF) // if UIF flag is set
	  {
		TIM9->SR &= ~TIM_SR_UIF; // clear UIF flag

		Interrupt::TIM9_Wrapper();
	  }
	}

	void TIM1_UP_TIM10_IRQHandler()
	{
	  if(TIM10->SR & TIM_SR_UIF) // if UIF flag is set
	  {
		TIM10->SR &= ~TIM_SR_UIF; // clear UIF flag

		Interrupt::TIM10_Wrapper();
	  }
	}

	void DMA2_Stream2_IRQHandler(void)
	{
		Interrupt::DMA2_Stream2_Wrapper();
	}
}

