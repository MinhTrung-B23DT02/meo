#include <stdint.h>

// Định nghĩa địa chỉ vật lý các thanh ghi của STM32F103
#define RCC_APB2ENR  (*((volatile uint32_t *)0x40021018))
#define GPIOC_CRH    (*((volatile uint32_t *)0x40011004))
#define GPIOC_ODR    (*((volatile uint32_t *)0x4001100C))

// Hàm tạo trễ (delay)
void delay(volatile uint32_t count) {
    while (count--) {
        __asm("nop");
    }
}

void main(void) {
    // 1. Cấp xung nhịp cho Port C (Set bit 4)
    RCC_APB2ENR |= (1 << 4);

    // 2. Cấu hình chân C13 ở chế độ Output Push-Pull (Tốc độ 50MHz)
    GPIOC_CRH &= ~(0xF << 20); // Xóa cấu hình cũ của C13 (bit 20-23)
    GPIOC_CRH |= (0x3 << 20);  // Ghi 0011 vào để cấu hình Output

    while (1) {
        // Bật LED (Kéo C13 xuống mức 0)
        GPIOC_ODR &= ~(1 << 13); 
        delay(500000); // Thay đổi số này để đổi chu kỳ nháy
        
        // Tắt LED (Kéo C13 lên mức 1)
        GPIOC_ODR |= (1 << 13);  
        delay(500000); 
    }
}