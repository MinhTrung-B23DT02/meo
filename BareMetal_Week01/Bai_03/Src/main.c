#include "stm32f1xx.h"

void config(void){
    RCC -> APB2ENR |= 0xFC;

    // config input
    GPIOA -> CRL &= ~0xFFFFFFFF;
    GPIOA -> CRL |= 0x88888888;
    GPIOA -> ODR |= 0x00FF;

    // config LED PB3 - PB10
    GPIOB -> CRL &= ~0xFFFFF000;
    GPIOB -> CRL |= 0x33333000;     // PB3 - PB7 output 50MHz

    GPIOB -> CRH &= ~0x00000FFF;
    GPIOB -> CRH |= 0x00000333;     // PB8 - PB10 output 50MHz
}

int main(){
    config();

    while(1){
        uint16_t in_val = (GPIOA -> IDR) & 0x00FF;

        // Đảo trạng thái bit
        uint16_t ined_val = (~in_val);

        // dịch trái 3 bit để xuất từ PB3 - PB10
        uint16_t out_val = ined_val << 3;

        // ghi ra LED PB3 - PB10
        GPIOB -> ODR = (GPIOB -> ODR & ~(0x00FF << 3)) | out_val;
    }
}