cmd_src/lib/built-in.o :=  arm-none-eabi-gcc --specs=nosys.specs --specs=nano.specs -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16   -r -o src/lib/built-in.o src/lib/CMSIS/STM32F4xx/Source/system_stm32f4xx.o src/lib/FatFS/ff.o src/lib/FatFS/ffunicode.o src/lib/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_adc.o src/lib/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dbgmcu.o src/lib/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma.o src/lib/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_exti.o src/lib/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_flash.o src/lib/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.o src/lib/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_i2c.o src/lib/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_iwdg.o src/lib/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_misc.o src/lib/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.o src/lib/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_spi.o src/lib/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_syscfg.o src/lib/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_tim.o src/lib/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_usart.o src/lib/STM32_USB_Device_Library/Core/src/usbd_core.o src/lib/STM32_USB_Device_Library/Core/src/usbd_ioreq.o src/lib/STM32_USB_Device_Library/Core/src/usbd_req.o src/lib/STM32_USB_OTG_Driver/src/usb_core.o src/lib/STM32_USB_OTG_Driver/src/usb_dcd_int.o src/lib/STM32_USB_OTG_Driver/src/usb_dcd.o src/lib/vl53l1/core/src/vl53l1_api_calibration.o src/lib/vl53l1/core/src/vl53l1_api_core.o src/lib/vl53l1/core/src/vl53l1_api_debug.o src/lib/vl53l1/core/src/vl53l1_api.o src/lib/vl53l1/core/src/vl53l1_api_preset_modes.o src/lib/vl53l1/core/src/vl53l1_api_strings.o src/lib/vl53l1/core/src/vl53l1_core.o src/lib/vl53l1/core/src/vl53l1_core_support.o src/lib/vl53l1/core/src/vl53l1_error_strings.o src/lib/vl53l1/core/src/vl53l1_register_funcs.o src/lib/vl53l1/core/src/vl53l1_silicon_core.o src/lib/vl53l1/core/src/vl53l1_wait.o