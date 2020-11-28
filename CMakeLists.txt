cmake_minimum_required(VERSION 3.0)
project(
    "Delta X Firmware"
    VERSION 0.1.0
    DESCRIPTION "Minimal firmware for delta-x robot."
    LANGUAGES C
)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

include(atmega2560.cmake)

add_executable(main.elf
    src/main.c
    src/pin.c
    src/robot.c
    src/uart.c
)
target_include_directories(main.elf
    PRIVATE include /usr/lib/avr/include
)
