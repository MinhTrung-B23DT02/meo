#include <stdint.h>

extern uint32_t _estack;
extern uint32_t _sidata, _sdata, _edata;
extern uint32_t _sbss, _ebss;

void main(void);

void Reset_Handler(void) {
    uint32_t *src = &_sidata;
    uint32_t *dest = &_sdata;
    
    while (dest < &_edata) {
        *dest++ = *src++;
    }
    
    dest = &_sbss;
    while (dest < &_ebss) {
        *dest++ = 0;
    }
    
    main(); 
    while (1);
}

__attribute__((section(".isr_vector")))
uint32_t *isr_vector[] = {
    &_estack,
    (uint32_t *)Reset_Handler
};