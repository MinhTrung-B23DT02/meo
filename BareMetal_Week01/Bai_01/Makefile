# Tên project (sẽ là tên file .bin và .elf)
PROJ_NAME = firmware

# Cấu hình các thư mục
SRC_DIR = Src
BUILD_DIR = Build
BIN_DIR = Bin
LINKER_DIR = Linker

# Các công cụ biên dịch của ARM
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size

# Cờ biên dịch: Chọn lõi Cortex-M3, tập lệnh Thumb, không dùng thư viện chuẩn, trỏ tới file Linker
CFLAGS = -mcpu=cortex-m3 -mthumb -nostdlib -T $(LINKER_DIR)/STM32F103C8.ld -Wl,-Map=$(BUILD_DIR)/$(PROJ_NAME).map

# Tìm tất cả các file .c trong thư mục Src và tạo đường dẫn cho các file .o
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))

# Mục tiêu mặc định khi gõ lệnh 'make'
all: $(BIN_DIR)/$(PROJ_NAME).bin

# Tạo file .bin từ file .elf
$(BIN_DIR)/$(PROJ_NAME).bin: $(BIN_DIR)/$(PROJ_NAME).elf
	@mkdir -p $(BIN_DIR)
	$(OBJCOPY) -O binary $< $@
	@echo "--- Build successful! Memory usage: ---"
	@$(SIZE) $<

# Liên kết các file .o thành file .elf
$(BIN_DIR)/$(PROJ_NAME).elf: $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Biên dịch từng file .c thành .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Lệnh 'make clean' để xóa các file đã biên dịch cũ
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Lệnh 'make flash' để nạp thẳng vào mạch
flash:
	st-flash write $(BIN_DIR)/$(PROJ_NAME).bin 0x08000000