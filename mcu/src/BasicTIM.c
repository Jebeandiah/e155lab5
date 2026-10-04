#include "BasicTIM.h"

void wait_millis(_TIM_TypeDef* TIMx, uint32_t millis){
  TIMx->CR1 &= ~(1U<<0);  //cenable off
  //uint16_t maxcount = ms*4000; //maybe safer to cast down
  uint16_t prescaler = 1;
  //if(micros%1000 ==0U) //if divisible into clean millis
  //  {
  //  prescaler = 4000; //scale to 1 khz
  //  } 

  
  TIMx->ARR = (uint16_t)(millis-1);

  TIMx->PSC = (uint16_t) 4000-1; //set presc
  TIMx ->EGR |=(1U<<0);  //update flag set
  TIMx->SR &= ~(1U<<0); //clear uif flag

  //while((TIMx->SR &= (1U<<0))==0){}
  TIMx->CR1 |= (1U<<0);  //cenable on
  while((TIMx->SR & (1U<<0))==0){}
}