#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=arm-none-eabi-gcc
CCC=arm-none-eabi-g++
CXX=arm-none-eabi-g++
FC=gfortran
AS=arm-none-eabi-as

# Macros
CND_PLATFORM=GNU_ARM-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/ExtFunctions.o \
	${OBJECTDIR}/Periph/ads1299.o \
	${OBJECTDIR}/Periph/dma.o \
	${OBJECTDIR}/Periph/gpio.o \
	${OBJECTDIR}/Periph/i2c.o \
	${OBJECTDIR}/Periph/spi.o \
	${OBJECTDIR}/Periph/tim.o \
	${OBJECTDIR}/Periph/usart.o \
	${OBJECTDIR}/libraries/Imp/Src/AD5933.o \
	${OBJECTDIR}/libraries/Imp/Src/ADG728.o \
	${OBJECTDIR}/libraries/Imp/Src/PCF8574A.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc_ex.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_can.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cec.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_crc.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cryp.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cryp_ex.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dac.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dac_ex.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dcmi.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dcmi_ex.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma2d.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dsi.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_eth.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_fmpi2c.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_fmpi2c_ex.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_hash.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_hash_ex.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_hcd.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c_ex.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2s.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2s_ex.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_irda.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_iwdg.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_lptim.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_ltdc.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_ltdc_ex.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_nand.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_nor.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pccard.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pcd.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pcd_ex.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_qspi.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rng.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rtc.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rtc_ex.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sai.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sai_ex.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sd.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sdram.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_smartcard.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_spdifrx.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_spi.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sram.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_usart.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_wwdg.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_fmc.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_fsmc.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_sdmmc.o \
	${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_usb.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/newlib_stab.o \
	${OBJECTDIR}/startup_stm32f4xx.o \
	${OBJECTDIR}/stm32f4xx_hal_msp.o \
	${OBJECTDIR}/stm32f4xx_it.o \
	${OBJECTDIR}/system_stm32f4xx.o


# C Compiler Flags
CFLAGS=-mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=../XitLib/dist/Debug_MC/GNU-Linux/libxitlib.a ../EEG_Evoker/dist/Debug_MC/GNU_ARM-Windows/libeeg_evoker.a ../CoAP/dist/Debug_MC/GNU_ARM-Windows/libcoap.a -lgcc -lm -lc

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/controllernew.elf.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/controllernew.elf.exe: ../XitLib/dist/Debug_MC/GNU-Linux/libxitlib.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/controllernew.elf.exe: ../EEG_Evoker/dist/Debug_MC/GNU_ARM-Windows/libeeg_evoker.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/controllernew.elf.exe: ../CoAP/dist/Debug_MC/GNU_ARM-Windows/libcoap.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/controllernew.elf.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/controllernew.elf ${OBJECTFILES} ${LDLIBSOPTIONS} -Tstm32f4_flash.ld

${OBJECTDIR}/ExtFunctions.o: ExtFunctions.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ExtFunctions.o ExtFunctions.c

${OBJECTDIR}/Periph/ads1299.o: Periph/ads1299.c 
	${MKDIR} -p ${OBJECTDIR}/Periph
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Periph/ads1299.o Periph/ads1299.c

${OBJECTDIR}/Periph/dma.o: Periph/dma.c 
	${MKDIR} -p ${OBJECTDIR}/Periph
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Periph/dma.o Periph/dma.c

${OBJECTDIR}/Periph/gpio.o: Periph/gpio.c 
	${MKDIR} -p ${OBJECTDIR}/Periph
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Periph/gpio.o Periph/gpio.c

${OBJECTDIR}/Periph/i2c.o: Periph/i2c.c 
	${MKDIR} -p ${OBJECTDIR}/Periph
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Periph/i2c.o Periph/i2c.c

${OBJECTDIR}/Periph/spi.o: Periph/spi.c 
	${MKDIR} -p ${OBJECTDIR}/Periph
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Periph/spi.o Periph/spi.c

${OBJECTDIR}/Periph/tim.o: Periph/tim.c 
	${MKDIR} -p ${OBJECTDIR}/Periph
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Periph/tim.o Periph/tim.c

${OBJECTDIR}/Periph/usart.o: Periph/usart.c 
	${MKDIR} -p ${OBJECTDIR}/Periph
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Periph/usart.o Periph/usart.c

${OBJECTDIR}/libraries/Imp/Src/AD5933.o: libraries/Imp/Src/AD5933.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/Imp/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/Imp/Src/AD5933.o libraries/Imp/Src/AD5933.c

${OBJECTDIR}/libraries/Imp/Src/ADG728.o: libraries/Imp/Src/ADG728.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/Imp/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/Imp/Src/ADG728.o libraries/Imp/Src/ADG728.c

${OBJECTDIR}/libraries/Imp/Src/PCF8574A.o: libraries/Imp/Src/PCF8574A.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/Imp/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/Imp/Src/PCF8574A.o libraries/Imp/Src/PCF8574A.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc_ex.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc_ex.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc_ex.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc_ex.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_can.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_can.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_can.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_can.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cec.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cec.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cec.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cec.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_crc.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_crc.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_crc.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_crc.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cryp.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cryp.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cryp.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cryp.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cryp_ex.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cryp_ex.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cryp_ex.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cryp_ex.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dac.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dac.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dac.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dac.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dac_ex.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dac_ex.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dac_ex.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dac_ex.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dcmi.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dcmi.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dcmi.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dcmi.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dcmi_ex.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dcmi_ex.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dcmi_ex.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dcmi_ex.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma2d.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma2d.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma2d.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma2d.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dsi.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dsi.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dsi.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dsi.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_eth.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_eth.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_eth.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_eth.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_fmpi2c.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_fmpi2c.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_fmpi2c.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_fmpi2c.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_fmpi2c_ex.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_fmpi2c_ex.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_fmpi2c_ex.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_fmpi2c_ex.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_hash.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_hash.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_hash.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_hash.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_hash_ex.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_hash_ex.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_hash_ex.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_hash_ex.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_hcd.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_hcd.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_hcd.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_hcd.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c_ex.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c_ex.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c_ex.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c_ex.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2s.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2s.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2s.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2s.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2s_ex.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2s_ex.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2s_ex.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2s_ex.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_irda.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_irda.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_irda.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_irda.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_iwdg.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_iwdg.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_iwdg.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_iwdg.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_lptim.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_lptim.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_lptim.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_lptim.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_ltdc.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_ltdc.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_ltdc.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_ltdc.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_ltdc_ex.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_ltdc_ex.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_ltdc_ex.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_ltdc_ex.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_nand.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_nand.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_nand.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_nand.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_nor.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_nor.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_nor.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_nor.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pccard.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pccard.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pccard.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pccard.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pcd.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pcd.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pcd.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pcd.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pcd_ex.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pcd_ex.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pcd_ex.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pcd_ex.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_qspi.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_qspi.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_qspi.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_qspi.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rng.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rng.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rng.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rng.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rtc.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rtc.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rtc.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rtc.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rtc_ex.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rtc_ex.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rtc_ex.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rtc_ex.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sai.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sai.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sai.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sai.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sai_ex.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sai_ex.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sai_ex.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sai_ex.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sd.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sd.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sd.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sd.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sdram.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sdram.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sdram.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sdram.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_smartcard.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_smartcard.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_smartcard.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_smartcard.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_spdifrx.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_spdifrx.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_spdifrx.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_spdifrx.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_spi.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_spi.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_spi.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_spi.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sram.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sram.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sram.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sram.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_usart.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_usart.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_usart.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_usart.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_wwdg.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_wwdg.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_wwdg.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_wwdg.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_fmc.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_fmc.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_fmc.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_fmc.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_fsmc.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_fsmc.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_fsmc.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_fsmc.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_sdmmc.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_sdmmc.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_sdmmc.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_sdmmc.c

${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_usb.o: libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_usb.c 
	${MKDIR} -p ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_usb.o libraries/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_usb.c

${OBJECTDIR}/main.o: main.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.c

${OBJECTDIR}/newlib_stab.o: newlib_stab.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/newlib_stab.o newlib_stab.c

${OBJECTDIR}/startup_stm32f4xx.o: startup_stm32f4xx.s 
	${MKDIR} -p ${OBJECTDIR}
	$(AS) $(ASFLAGS) -g -o ${OBJECTDIR}/startup_stm32f4xx.o startup_stm32f4xx.s

${OBJECTDIR}/stm32f4xx_hal_msp.o: stm32f4xx_hal_msp.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/stm32f4xx_hal_msp.o stm32f4xx_hal_msp.c

${OBJECTDIR}/stm32f4xx_it.o: stm32f4xx_it.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/stm32f4xx_it.o stm32f4xx_it.c

${OBJECTDIR}/system_stm32f4xx.o: system_stm32f4xx.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -DSTM32F429xx -DUSE_HAL_DRIVER -I../XitLib -IPeriph -Ilibraries/Imp/Inc -I. -Ilibraries/CMSIS/Include -Ilibraries/CMSIS/Device/ST/STM32F4xx/Include -Ilibraries/STM32F4xx_HAL_Driver/Inc -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/system_stm32f4xx.o system_stm32f4xx.c

# Subprojects
.build-subprojects:
	cd ../XitLib && ${MAKE}  -f Makefile CONF=Debug_MC
	cd ../EEG_Evoker && ${MAKE}  -f Makefile CONF=Debug_MC
	cd ../CoAP && ${MAKE}  -f Makefile CONF=Debug_MC
	cd ../EEG_Evoker && ${MAKE}  -f Makefile CONF=Debug_MC
	cd ../XitLib && ${MAKE}  -f Makefile CONF=Debug_MC
	cd ../CoAP && ${MAKE}  -f Makefile CONF=Debug_MC

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/controllernew.elf.exe

# Subprojects
.clean-subprojects:
	cd ../XitLib && ${MAKE}  -f Makefile CONF=Debug_MC clean
	cd ../EEG_Evoker && ${MAKE}  -f Makefile CONF=Debug_MC clean
	cd ../CoAP && ${MAKE}  -f Makefile CONF=Debug_MC clean
	cd ../EEG_Evoker && ${MAKE}  -f Makefile CONF=Debug_MC clean
	cd ../XitLib && ${MAKE}  -f Makefile CONF=Debug_MC clean
	cd ../CoAP && ${MAKE}  -f Makefile CONF=Debug_MC clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
