#include <stdint.h>

#define RCC_APB2ENR  (*((volatile uint32_t *)0x40021018))
#define GPIOC_CRH    (*((volatile uint32_t *)0x40011004))
#define GPIOC_IDR    (*((volatile uint32_t *)0x40011008))
#define GPIOC_ODR    (*((volatile uint32_t *)0x4001100C))

void delay(uint16_t t) {
    volatile uint16_t i,j;
    for( i = 0 ; i < t; i++){
        for( j = 0; j < 2000; j++);
    }
}

void main(void) {
    // 1. Cấp xung nhịp cho Port C (bit 4 trong APB2ENR)
    RCC_APB2ENR |= (1 << 4);

    // 2. Cấu hình PC13 (LED) là Output 50MHz và PC14 (Nút nhấn) là Input Pull-up/down
    GPIOC_CRH &= ~0x0FF00000; 
    GPIOC_CRH |=  0x08300000; // PC14 = 8 (Input pull-up/down), PC13 = 3 (Output 50MHz)

    // 3. Bật trở kéo lên (Pull-up) cho chân PC14
    GPIOC_ODR |= (1 << 14);

    while (1) {
        // Kiểm tra nút nhấn ở PC14 (Nhấn xuống mức 0)
        if ((GPIOC_IDR & (1 << 14)) == 0) {
            delay(100);                  // Chống dội phím
            GPIOC_ODR ^= (1 << 13);   // Đảo trạng thái đèn LED ở PC13
        }
        // Chờ nhả nút
        while ((GPIOC_IDR & (1 << 14)) == 0);
    }
}