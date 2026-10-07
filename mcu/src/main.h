#define PPR (120)

#define GPIOA_BASE_ADR (0x48000000UL)
#define TIM6_BASE_ADR (0x40001000UL)

#define RCC_BASE_ADR (0x40021000UL)
#define RCC_APB1ENR  (*(uint32_t *) (RCC_BASE_ADR + 0x58))
#define RCC_AHB2ENR (*(uint32_t *) (RCC_BASE_ADR + 0x4C))

#define PA8_OFFSET (8)
#define PA10_OFFSET (10)

#define _GPIOA ((_GPIO_TypeDef *) GPIOA_BASE_ADR)
#define _TIM6 ((_TIM_TypeDef *) TIM6_BASE_ADR)