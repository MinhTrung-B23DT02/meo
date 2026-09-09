PROJ_NAME = firmware
SRC_DIR = Src
BUILD_DIR = Build
BIN_DIR = Bin
LINKER_DIR = Linker

CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size

CFLAGS = -mcpu=cortex-m3 -mthumb -nostdlib -T $(LINKER_DIR)/STM32F103C8.ld -Wl,-Map=$(BUILD_DIR)/$(PROJ_NAME).map

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))

all: $(BIN_DIR)/$(PROJ_NAME).bin

$(BIN_DIR)/$(PROJ_NAME).bin: $(BIN_DIR)/$(PROJ_NAME).elf
	@mkdir -p $(BIN_DIR)
	$(OBJCOPY) -O binary $< $@
	@echo "--- Build successful! Memory usage: ---"
	@$(SIZE) $<

$(BIN_DIR)/$(PROJ_NAME).elf: $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

flash:
	st-flash write $(BIN_DIR)/$(PROJ_NAME).bin 0x08000000