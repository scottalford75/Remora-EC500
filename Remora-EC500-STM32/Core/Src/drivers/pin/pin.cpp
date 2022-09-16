#include "pin.h"
#include <cstdio>
#include <cerrno>
#include <string>


Pin::Pin(std::string portAndPin, int dir) :
    portAndPin(portAndPin),
    dir(dir)
{
    // Set direction
    if (this->dir == INPUT)
    {
        this->mode = GPIO_MODE_INPUT;
        this->pull = GPIO_NOPULL;
    }
    else
    {
        this->mode = GPIO_MODE_OUTPUT_PP;
        this->pull = GPIO_NOPULL;
    }

    this->configPin();
}

Pin::Pin(std::string portAndPin, int dir, int modifier) :
    portAndPin(portAndPin),
    dir(dir),
    modifier(modifier)
{
    // Set direction
    if (this->dir == INPUT)
    {
        this->mode = GPIO_MODE_INPUT;

        // Set pin  modifier
        switch(this->modifier)
        {
            case PULLUP:
                printf("  Setting pin as Pull Up\n");
                this->pull = GPIO_PULLUP;
                break;
            case PULLDOWN:
                printf("  Setting pin as Pull Down\n");
                this->pull = GPIO_PULLDOWN;
                break;
            case NONE:
            case PULLNONE:
                printf("  Setting pin as No Pull\n");
                this->pull = GPIO_NOPULL;
                break;
        }
    }
    else
    {
        this->mode = GPIO_MODE_OUTPUT_PP;
        this->pull = GPIO_NOPULL;
    }

    this->configPin();
}

void Pin::configPin()
{
    printf("Creating Pin @\n");

    //x can be (A..H) to select the GPIO peripheral for STM32F40XX and STM32F427X devices.
    GPIO_TypeDef* gpios[8] ={GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF,GPIOG,GPIOH};
    

    if (this->portAndPin[0] == 'P') // PXXX e.g.PA_2 PC_15
    {  
        this->portIndex     = this->portAndPin[1] - 'A';
        this->pinNumber     = this->portAndPin[3] - '0';       
        uint16_t pin2       = this->portAndPin[4] - '0';       

        if (pin2 <= 8) 
        {
            this->pinNumber = this->pinNumber * 10 + pin2;
        }

        this->pin = 1 << this->pinNumber; // this is equivalent to GPIO_PIN_x definition
    }
    else
    {
        printf("  Invalid port and pin definition\n");
        return;
    }    

    printf("  port = GPIO%c\n", char('A' + this->portIndex));
    printf("  pin = %d\n", this->pinNumber);

    // translate port index into something useful
    this->GPIOx = gpios[this->portIndex];

    // enable the peripheral clock
    switch (portIndex){
        case 0:
            __HAL_RCC_GPIOA_CLK_ENABLE();
            break;

        case 1:
            __HAL_RCC_GPIOB_CLK_ENABLE();
            break;

        case 2:
            __HAL_RCC_GPIOC_CLK_ENABLE();
            break;
        
        case 3:
            __HAL_RCC_GPIOD_CLK_ENABLE();
            break;

        case 4:
            __HAL_RCC_GPIOE_CLK_ENABLE();
            break;

        case 5:
            __HAL_RCC_GPIOF_CLK_ENABLE();
            break;

        case 6:
            __HAL_RCC_GPIOG_CLK_ENABLE();
            break;

        case 7:
            __HAL_RCC_GPIOH_CLK_ENABLE();
            break;
    }

    this->initPin();
}


void Pin::initPin()
{
    // Configure GPIO pin Output Level
    HAL_GPIO_WritePin(this->GPIOx, this->pin, GPIO_PIN_RESET);

    // Configure the GPIO pin
    this->GPIO_InitStruct.Pin = this->pin;
    this->GPIO_InitStruct.Mode = this->mode;
    this->GPIO_InitStruct.Pull = this->pull;
    this->GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(this->GPIOx, &this->GPIO_InitStruct);  
}

void Pin::setAsOutput()
{
    this->mode = GPIO_MODE_OUTPUT_PP;
    this->pull = GPIO_NOPULL;
    this->initPin();
}


void Pin::setAsInput()
{
    this->mode = GPIO_MODE_INPUT;
    this->pull = GPIO_NOPULL;
    this->initPin();
}


void Pin::pull_none()
{
    this->pull = GPIO_NOPULL;
    this->initPin();
}


void Pin::pull_up()
{
    this->pull = GPIO_PULLUP;
    this->initPin();
}


void Pin::pull_down()
{
    this->pull = GPIO_PULLDOWN;
    this->initPin();
}

