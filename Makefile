.PHONY: build
build:
	mkdir -p build
	cmake -E chdir build cmake ..
	cmake --build build

.PHONY: flash
flash:
	avr-objcopy -j .text -j .data -O ihex build/main.elf build/name.hex
	avr-size --format=avr --mcu=m2560 build/main.elf
	avrdude -c arduino -P /dev/ttyUSB0 -p m2560 -U flash:w:build/main.hex:i
