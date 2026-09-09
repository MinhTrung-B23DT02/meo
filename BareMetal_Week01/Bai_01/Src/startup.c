#include <stdint.h>

// Khai báo các biến ngoại lai được định nghĩa từ file Linker
extern uint32_t _estack;
extern uint32_t _sidata, _sdata, _edata;
extern uint32_t _sbss, _ebss;

void main(void);

// Hàm Reset (được gọi đầu tiên khi cấp nguồn hoặc ấn nút Reset)
void Reset_Handler(void) {
    uint32_t *src = &_sidata; // Địa chỉ nguồn trong Flash
    uint32_t *dest = &_sdata; // Địa chỉ đích trong RAM
    
    // Copy dữ liệu có khởi tạo (data section) từ Flash sang RAM
    while (dest < &_edata) {
        *dest++ = *src++;
    }
    
    // Khởi tạo vùng dữ liệu chưa khởi tạo (bss section) bằng 0
    dest = &_sbss;
    while (dest < &_ebss) {
        *dest++ = 0;
    }
    
    // Gọi hàm main của chương trình
    main(); 
    
    // Vòng lặp vô tận đề phòng hàm main kết thúc
    while (1);
}

// Bảng Vector ngắt (Đặt ở đầu bộ nhớ Flash)
__attribute__((section(".isr_vector")))
uint32_t *isr_vector[] = {
    &_estack,                 // Đỉnh của Stack (Lấy tự động từ Linker)
    (uint32_t *)Reset_Handler // Địa chỉ hàm Reset_Handler
};