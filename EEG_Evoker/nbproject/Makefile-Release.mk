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
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/ImageVisualise.o \
	${OBJECTDIR}/p300v5.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1

# Test Object Files
TESTOBJECTFILES= \
	${TESTDIR}/tests/P300test.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libeeg_evoker.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libeeg_evoker.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libeeg_evoker.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libeeg_evoker.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libeeg_evoker.a

${OBJECTDIR}/ImageVisualise.o: ImageVisualise.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -DCPU -DP300 -I../ControllerNew/Periph -I../ControllerNew/libraries/CMSIS/Include -I../ControllerNew/libraries/STM32F4xx_HAL_Driver/Inc -I../ControllerNew -I../ControllerNew/libraries/CMSIS/Device/ST/STM32F4xx/Include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ImageVisualise.o ImageVisualise.c

${OBJECTDIR}/p300v5.o: p300v5.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -DCPU -DP300 -I../ControllerNew/Periph -I../ControllerNew/libraries/CMSIS/Include -I../ControllerNew/libraries/STM32F4xx_HAL_Driver/Inc -I../ControllerNew -I../ControllerNew/libraries/CMSIS/Device/ST/STM32F4xx/Include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/p300v5.o p300v5.c

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-tests-subprojects .build-conf ${TESTFILES}
.build-tests-subprojects:

${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/P300test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c} -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS}   


${TESTDIR}/tests/P300test.o: tests/P300test.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -O2 -DCPU -DP300 -I../ControllerNew/Periph -I../ControllerNew/libraries/CMSIS/Include -I../ControllerNew/libraries/STM32F4xx_HAL_Driver/Inc -I../ControllerNew -I../ControllerNew/libraries/CMSIS/Device/ST/STM32F4xx/Include -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/P300test.o tests/P300test.c


${OBJECTDIR}/ImageVisualise_nomain.o: ${OBJECTDIR}/ImageVisualise.o ImageVisualise.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ImageVisualise.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -DCPU -DP300 -I../ControllerNew/Periph -I../ControllerNew/libraries/CMSIS/Include -I../ControllerNew/libraries/STM32F4xx_HAL_Driver/Inc -I../ControllerNew -I../ControllerNew/libraries/CMSIS/Device/ST/STM32F4xx/Include -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ImageVisualise_nomain.o ImageVisualise.c;\
	else  \
	    ${CP} ${OBJECTDIR}/ImageVisualise.o ${OBJECTDIR}/ImageVisualise_nomain.o;\
	fi

${OBJECTDIR}/p300v5_nomain.o: ${OBJECTDIR}/p300v5.o p300v5.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/p300v5.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -DCPU -DP300 -I../ControllerNew/Periph -I../ControllerNew/libraries/CMSIS/Include -I../ControllerNew/libraries/STM32F4xx_HAL_Driver/Inc -I../ControllerNew -I../ControllerNew/libraries/CMSIS/Device/ST/STM32F4xx/Include -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/p300v5_nomain.o p300v5.c;\
	else  \
	    ${CP} ${OBJECTDIR}/p300v5.o ${OBJECTDIR}/p300v5_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
