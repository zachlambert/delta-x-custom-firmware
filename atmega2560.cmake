SET(CMAKE_SYSTEM_NAME Generic)

SET(CMAKE_C_COMPILER avr-gcc)

SET(CSTANDARD "-std=gnu99")
set(CDEBUG "-gstabs")
set(CWARN "-Wall -Wstrict-prototypes")
set(CTUNING "-funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums")
SET(COPT "-Os")
SET(CMCU "-mmcu=atmega2560")
SET(CDEFS "-DF_CPU=16000000")

set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")

SET(CFLAGS "${CMCU} ${CDEFS} ${COPT} ${CWARN} ${CSTANDARD} ${CTUNING}")

SET(CMAKE_C_FLAGS  ${CFLAGS})
