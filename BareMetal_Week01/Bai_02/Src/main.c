#include <stdint.h>

#define RCC_APB2ENR  (*((volatile uint32_t *)0x40021018))
#define GPIOA_CRL    (*((volatile uint32_t *)0x40010800))
#define GPIOA_ODR    (*((volatile uint32_t *)0x4001080C))

void delay(volatile uint32_t count) {
    while (count--) {
        __asm("nop");
    }
}

void main(void) {
    // Cấp xung nhịp cho Port A
    RCC_APB2ENR |= (1 << 2);

    // Cấu hình 8 chân PA0 - PA7 ở chế độ Output Push-Pull
    GPIOA_CRL = 0x33333333;

    while (1) {
        // Chạy từ trái sang phải
        for (int i = 0; i <= 7; i++) {
            GPIOA_ODR = (1 << i); 
            delay(300000);        
        }
        
        // Chạy từ phải sang trái
        for (int i = 6; i >= 1; i--) {
            GPIOA_ODR = (1 << i); 
            delay(300000);
        }
    } 
} 