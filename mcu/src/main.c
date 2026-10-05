//Author: Benjamin Lertwachara
//Date: 9/30/28
//Function: Initialize and comfigure GPIO and basic timers
//to make pwm signal to play notes.
#include "stm32l432xx.h"
#include "GPIO.h"
#include "BasicTIM.h"
#include <stdint.h>
#include <stdio.h>

#define GPIOA_BASE_ADR (0x48000000UL)
#define TIM6_BASE_ADR (0x40001000UL)

#define RCC_BASE_ADR (0x40021000UL)
#define RCC_APB1ENR  (*(uint32_t *) (RCC_BASE_ADR + 0x58))
#define RCC_AHB2ENR (*(uint32_t *) (RCC_BASE_ADR + 0x4C))

#define PA8_OFFSET (8)
#define PA10_OFFSET (10)

#define _GPIOA ((_GPIO_TypeDef *) GPIOA_BASE_ADR)
#define _TIM6 ((_TIM_TypeDef *) TIM6_BASE_ADR)

volatile int counts =0;
volatile uint8_t last_source =0;
volatile uint8_t last_edge =0;

void init(void) {
  RCC->APB2ENR |= (1 << 0); // SYSCFGEN
    //strt gpioa clk
  RCC_AHB2ENR |= (1U<<0);

  //start tim6 clks
  RCC_APB1ENR |= (1<<4);
  
  SYSCFG->EXTICR[2] &= ~(0b111 << 0);  //pa8 in extir3
  SYSCFG->EXTICR[2] &= ~(0b111 << 8);
  EXTI->IMR1 |= (1 << PA8_OFFSET);   // 1. Configure mask bit
  EXTI->RTSR1 |= (1 << PA8_OFFSET); // 2. Enable rising edge trigger
  EXTI->FTSR1 |= (1 << PA8_OFFSET);  // 3. Enable falling edge trigger

  EXTI->IMR1 |= (1 << PA10_OFFSET);  
  EXTI->RTSR1 |= (1 << PA10_OFFSET);
  EXTI->FTSR1 |= (1 << PA10_OFFSET);  
  NVIC->ISER[0] |= (1 << 23);                       // 4. Turn on EXTI interrupt in NVIC_ISER (EXTI9_5 is IRQ 23)
   NVIC->ISER[1] |= (1 << 8);        


  _TIM6->CR1 &= ~(1U<<0);  //cenable off

  _GPIOA->MODER &= ~(0b11 << 2*PA8_OFFSET); //set as inputs
  _GPIOA->MODER &= ~(0b11 << 2*PA10_OFFSET);
  //GPIOA->PUPDR |= (0b01 << 2*PA8_OFFSET); 
  //GPIOA->PUPDR |= (0b01 << 2*PA10_OFFSET); 
  __enable_irq();
}


int main(void) {
printf("starting init");
  init();
  while(1)
  {
    wait_millis(_TIM6, 100);
    int rpm = (counts*10*60)/1632;
    printf("counts: %d\n", counts);
    printf("rpm: %d\n", rpm);
    counts=0;

  }
}

void pulse_received(uint8_t source_offset){
  uint8_t edge = (_GPIOA->IDR >> source_offset) & 1; //read pin to determine edge
  uint32_t direction =1;
  if(source_offset!=last_source){
    if(last_source==PA8_OFFSET){
      if(last_edge==1 && edge==1) {
        direction = -1;
        }
      if(last_edge==0 && edge==1) {
        direction = -1;
        }
    }
    if(last_source==PA10_OFFSET){
      if(last_edge==1 && edge==0) {
        direction = -1;
        }
      if(last_edge==0 && edge==1) {
        direction = -1;
        }
    }
  } 
  else if (edge ==1) {
    direction = -1;
  }
  last_edge = edge;
  last_source =source_offset;
  counts += direction;
  //printf("adding to the count: %d\n", direction);
}
void EXTI9_5_IRQHandler(void){
  EXTI->PR1 = (1 << PA8_OFFSET);
  pulse_received(PA8_OFFSET);
  //printf("got pulse 0");
}

void EXTI15_10_IRQHandler(void){
  EXTI->PR1 = (1 << PA10_OFFSET);
  pulse_received(PA10_OFFSET);
  //printf("got pulse 1");
}

