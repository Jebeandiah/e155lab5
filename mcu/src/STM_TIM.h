#include <stdint.h>

typedef  uint32_t TIM_TypeDef;

void initTIM(TIM_TypeDef *TIMx);

void delay_millis(TIM_TypeDef *TIMx, uint32_t ms);


