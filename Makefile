LFU = 0xFF
HFU = 0xD8
EFU = 0xFD

PRG = usbtiny
MCU = m2560
AVRDUDE = avrdude -c $(PRG) -p $(MCU)
AVRDUDE_ARDUINO = avrdude -c arduino -b 115200 -p $(MCU)

NAME = main
PORT = /dev/ttyACM0

.PHONY: build
build:
	mkdir -p build
	cmake -E chdir build cmake ..
	cmake --build build

.PHONY: flash
flash:
	avr-objcopy -j .text -j .data -O ihex build/$(NAME).elf build/$(NAME).hex
	avr-size --format=avr --mcu=$(MCU) build/$(NAME).elf
	$(AVRDUDE_ARDUINO) -P $(PORT) -p $(MCU) -U flash:w:build/$(NAME).hex:i

.PHONY: bootloader
bootloader:
	$(AVRDUDE) -U flash:w:bootloader.hex:i

.PHONY: fuse
fuse:
	# 0xFF 0xD8 0xFD
	$(AVRDUDE) -U lfuse:w:$(LFU):m -U hfuse:w:$(HFU):m -U efuse:w:$(EFU):m

.PHONY: monitor
monitor:
	serial_monitor /dev/ttyACM0 9600
