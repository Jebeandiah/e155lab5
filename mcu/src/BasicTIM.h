#ifndef BasicTIM_H
#define BasicTIM_H
#include <stdint.h> // Include stdint header
typedef struct {
    volatile uint32_t CR1;          // 0x00 - register 1
    volatile uint32_t na[3];          // 0x04
    volatile uint32_t SR;           // 0x10
    volatile uint32_t EGR;   
    volatile uint32_t na1[4]; // Reserved: 0x18, 0x1C, 0x20         // 0x28
    volatile uint32_t PSC; 
    volatile uint32_t ARR;          // 0x2C   only first 16 bits
} _TIM_TypeDef;

void wait_millis(_TIM_TypeDef* TIMx, uint32_t millis);

#endif
