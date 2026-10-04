#ifndef GPIO_H
#define GPIO_H
#include <stdint.h> // Include stdint header


typedef struct {
    volatile uint32_t MODER;   // 0x00
    volatile uint32_t na[4];  // 0x04
    volatile uint32_t ODR;     // 0x14
} _GPIO_TypeDef;



#endif
