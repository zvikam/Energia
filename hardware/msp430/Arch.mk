######################################
# Common amongst all boards for this architecture
CFLAGS := -Os -DF_CPU=$(F_CPU) -g -Os -w -Wall -ffunction-sections -fdata-sections -DARDUINO=101 -DENERGIA=12 $(EXTRA_CFLAGS)
CPPFLAGS := $(CFLAGS) -fno-threadsafe-statics -funsigned-bitfields -fpack-struct -fshort-enums -fno-exceptions -fno-rtti
ASFLAGS := -DF_CPU=$(F_CPU) -x assembler-with-cpp
LDFLAGS := $(MCU_FLAG) -Os -Wl,--gc-sections,-u,main $(EXTRA_LDFLAGS)
TOOLS_PATH := $(APPLICATION_PATH)/hardware/tools/msp430/bin
CC := msp430-elf-gcc
CXX := msp430-elf-g++
AR := msp430-elf-ar
SIZE := msp430-elf-size
#MSPDEBUG := LD_LIBRARY_PATH=$(APPLICATION_PATH)/hardware/tools/msp430/mspdebug $(LD_LIBRARY_PATH) $(APPLICATION_PATH)/hardware/tools/msp430/mspdebug/mspdebug
MSPDEBUG := mspdebug
OBJCOPY := msp430-elf-objcopy
OBJCOPY_FLAGS := -O ihex -R .eeprom
OBJDUMP := msp430-elf-objdump
######################################
