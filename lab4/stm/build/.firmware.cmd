cmd_firmware := arm-none-eabi-gcc -Wl,-Map=cf2.map,--cref,--gc-sections,--undefined=uxTopUsedPriority -L/home/bitcraze/projects/crazyflie-firmware/tools/make/F405/linker -T /home/bitcraze/projects/crazyflie-firmware/tools/make/F405/linker/FLASH_CLOAD.ld --specs=nosys.specs --specs=nano.specs -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 src/built-in.o vendor/built-in.o app_api/built-in.o /home/bitcraze/Desktop/IAA_Labs/lab4/stm/built-in.o  -lm -o firmware.elf
