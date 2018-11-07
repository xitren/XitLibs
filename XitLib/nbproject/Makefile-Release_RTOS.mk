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
CCC=g++
CXX=g++
FC=gfortran
AS=arm-none-eabi-ld

# Macros
CND_PLATFORM=GNU-ARM-Windows
CND_DLIB_EXT=dll
CND_CONF=Release_RTOS
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/CRC16ANSI.o \
	${OBJECTDIR}/CommandModule.o \
	${OBJECTDIR}/ConfigMem.o \
	${OBJECTDIR}/DistCalc.o \
	${OBJECTDIR}/Handler.o \
	${OBJECTDIR}/InOutBuffer.o \
	${OBJECTDIR}/LogModule.o \
	${OBJECTDIR}/PWMModule.o \
	${OBJECTDIR}/Packet.o \
	${OBJECTDIR}/Schedule.o \
	${OBJECTDIR}/StreamDataRecorder.o \
	${OBJECTDIR}/coap/coap.o \
	${OBJECTDIR}/json/cJSON.o \
	${OBJECTDIR}/json/cJSON_Utils.o \
	${OBJECTDIR}/malloc/umm_malloc.o \
	${OBJECTDIR}/models/src/array.o \
	${OBJECTDIR}/models/src/circularbuffer.o \
	${OBJECTDIR}/models/src/common.o \
	${OBJECTDIR}/models/src/deque.o \
	${OBJECTDIR}/models/src/hashset.o \
	${OBJECTDIR}/models/src/hashtable.o \
	${OBJECTDIR}/models/src/list.o \
	${OBJECTDIR}/models/src/queue.o \
	${OBJECTDIR}/models/src/slist.o \
	${OBJECTDIR}/models/src/stack.o \
	${OBJECTDIR}/models/src/treeset.o \
	${OBJECTDIR}/models/src/treetable.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f2 \
	${TESTDIR}/TestFiles/f1 \
	${TESTDIR}/TestFiles/f5 \
	${TESTDIR}/TestFiles/f3 \
	${TESTDIR}/TestFiles/f4

# Test Object Files
TESTOBJECTFILES= \
	${TESTDIR}/tests/array_test.o \
	${TESTDIR}/tests/coap_test.o \
	${TESTDIR}/tests/datasystem_test.o \
	${TESTDIR}/tests/hashtable_test.o \
	${TESTDIR}/tests/json_test.o \
	${TESTDIR}/tests/malloc_test.o \
	${TESTDIR}/tests/models_test.o

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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libxitlib_cortexm4_rtos.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libxitlib_cortexm4_rtos.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libxitlib_cortexm4_rtos.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libxitlib_cortexm4_rtos.a ${OBJECTFILES} 

${OBJECTDIR}/CRC16ANSI.o: CRC16ANSI.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CRC16ANSI.o CRC16ANSI.c

${OBJECTDIR}/CommandModule.o: CommandModule.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CommandModule.o CommandModule.c

${OBJECTDIR}/ConfigMem.o: ConfigMem.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ConfigMem.o ConfigMem.c

${OBJECTDIR}/DistCalc.o: DistCalc.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DistCalc.o DistCalc.c

${OBJECTDIR}/Handler.o: Handler.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Handler.o Handler.c

${OBJECTDIR}/InOutBuffer.o: InOutBuffer.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/InOutBuffer.o InOutBuffer.c

${OBJECTDIR}/LogModule.o: LogModule.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/LogModule.o LogModule.c

${OBJECTDIR}/PWMModule.o: PWMModule.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/PWMModule.o PWMModule.c

${OBJECTDIR}/Packet.o: Packet.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Packet.o Packet.c

${OBJECTDIR}/Schedule.o: Schedule.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Schedule.o Schedule.c

${OBJECTDIR}/StreamDataRecorder.o: StreamDataRecorder.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/StreamDataRecorder.o StreamDataRecorder.c

${OBJECTDIR}/coap/coap.o: coap/coap.c
	${MKDIR} -p ${OBJECTDIR}/coap
	${RM} "$@.d"
	$(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/coap/coap.o coap/coap.c

${OBJECTDIR}/json/cJSON.o: json/cJSON.c
	${MKDIR} -p ${OBJECTDIR}/json
	${RM} "$@.d"
	$(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/json/cJSON.o json/cJSON.c

${OBJECTDIR}/json/cJSON_Utils.o: json/cJSON_Utils.c
	${MKDIR} -p ${OBJECTDIR}/json
	${RM} "$@.d"
	$(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/json/cJSON_Utils.o json/cJSON_Utils.c

${OBJECTDIR}/malloc/umm_malloc.o: malloc/umm_malloc.c
	${MKDIR} -p ${OBJECTDIR}/malloc
	${RM} "$@.d"
	$(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/malloc/umm_malloc.o malloc/umm_malloc.c

${OBJECTDIR}/models/src/array.o: models/src/array.c
	${MKDIR} -p ${OBJECTDIR}/models/src
	${RM} "$@.d"
	$(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/models/src/array.o models/src/array.c

${OBJECTDIR}/models/src/circularbuffer.o: models/src/circularbuffer.c
	${MKDIR} -p ${OBJECTDIR}/models/src
	${RM} "$@.d"
	$(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/models/src/circularbuffer.o models/src/circularbuffer.c

${OBJECTDIR}/models/src/common.o: models/src/common.c
	${MKDIR} -p ${OBJECTDIR}/models/src
	${RM} "$@.d"
	$(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/models/src/common.o models/src/common.c

${OBJECTDIR}/models/src/deque.o: models/src/deque.c
	${MKDIR} -p ${OBJECTDIR}/models/src
	${RM} "$@.d"
	$(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/models/src/deque.o models/src/deque.c

${OBJECTDIR}/models/src/hashset.o: models/src/hashset.c
	${MKDIR} -p ${OBJECTDIR}/models/src
	${RM} "$@.d"
	$(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/models/src/hashset.o models/src/hashset.c

${OBJECTDIR}/models/src/hashtable.o: models/src/hashtable.c
	${MKDIR} -p ${OBJECTDIR}/models/src
	${RM} "$@.d"
	$(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/models/src/hashtable.o models/src/hashtable.c

${OBJECTDIR}/models/src/list.o: models/src/list.c
	${MKDIR} -p ${OBJECTDIR}/models/src
	${RM} "$@.d"
	$(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/models/src/list.o models/src/list.c

${OBJECTDIR}/models/src/queue.o: models/src/queue.c
	${MKDIR} -p ${OBJECTDIR}/models/src
	${RM} "$@.d"
	$(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/models/src/queue.o models/src/queue.c

${OBJECTDIR}/models/src/slist.o: models/src/slist.c
	${MKDIR} -p ${OBJECTDIR}/models/src
	${RM} "$@.d"
	$(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/models/src/slist.o models/src/slist.c

${OBJECTDIR}/models/src/stack.o: models/src/stack.c
	${MKDIR} -p ${OBJECTDIR}/models/src
	${RM} "$@.d"
	$(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/models/src/stack.o models/src/stack.c

${OBJECTDIR}/models/src/treeset.o: models/src/treeset.c
	${MKDIR} -p ${OBJECTDIR}/models/src
	${RM} "$@.d"
	$(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/models/src/treeset.o models/src/treeset.c

${OBJECTDIR}/models/src/treetable.o: models/src/treetable.c
	${MKDIR} -p ${OBJECTDIR}/models/src
	${RM} "$@.d"
	$(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/models/src/treetable.o models/src/treetable.c

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-tests-subprojects .build-conf ${TESTFILES}
.build-tests-subprojects:

${TESTDIR}/TestFiles/f2: ${TESTDIR}/tests/coap_test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c} -o ${TESTDIR}/TestFiles/f2 $^ ${LDLIBSOPTIONS}   

${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/json_test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c} -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS}   

${TESTDIR}/TestFiles/f5: ${TESTDIR}/tests/datasystem_test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c} -o ${TESTDIR}/TestFiles/f5 $^ ${LDLIBSOPTIONS}   

${TESTDIR}/TestFiles/f3: ${TESTDIR}/tests/malloc_test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c} -o ${TESTDIR}/TestFiles/f3 $^ ${LDLIBSOPTIONS}   

${TESTDIR}/TestFiles/f4: ${TESTDIR}/tests/array_test.o ${TESTDIR}/tests/hashtable_test.o ${TESTDIR}/tests/models_test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c} -o ${TESTDIR}/TestFiles/f4 $^ ${LDLIBSOPTIONS}   


${TESTDIR}/tests/coap_test.o: tests/coap_test.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/coap_test.o tests/coap_test.c


${TESTDIR}/tests/json_test.o: tests/json_test.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/json_test.o tests/json_test.c


${TESTDIR}/tests/datasystem_test.o: tests/datasystem_test.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/datasystem_test.o tests/datasystem_test.c


${TESTDIR}/tests/malloc_test.o: tests/malloc_test.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/malloc_test.o tests/malloc_test.c


${TESTDIR}/tests/array_test.o: tests/array_test.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/array_test.o tests/array_test.c


${TESTDIR}/tests/hashtable_test.o: tests/hashtable_test.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/hashtable_test.o tests/hashtable_test.c


${TESTDIR}/tests/models_test.o: tests/models_test.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/models_test.o tests/models_test.c


${OBJECTDIR}/CRC16ANSI_nomain.o: ${OBJECTDIR}/CRC16ANSI.o CRC16ANSI.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/CRC16ANSI.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CRC16ANSI_nomain.o CRC16ANSI.c;\
	else  \
	    ${CP} ${OBJECTDIR}/CRC16ANSI.o ${OBJECTDIR}/CRC16ANSI_nomain.o;\
	fi

${OBJECTDIR}/CommandModule_nomain.o: ${OBJECTDIR}/CommandModule.o CommandModule.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/CommandModule.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CommandModule_nomain.o CommandModule.c;\
	else  \
	    ${CP} ${OBJECTDIR}/CommandModule.o ${OBJECTDIR}/CommandModule_nomain.o;\
	fi

${OBJECTDIR}/ConfigMem_nomain.o: ${OBJECTDIR}/ConfigMem.o ConfigMem.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ConfigMem.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ConfigMem_nomain.o ConfigMem.c;\
	else  \
	    ${CP} ${OBJECTDIR}/ConfigMem.o ${OBJECTDIR}/ConfigMem_nomain.o;\
	fi

${OBJECTDIR}/DistCalc_nomain.o: ${OBJECTDIR}/DistCalc.o DistCalc.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/DistCalc.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DistCalc_nomain.o DistCalc.c;\
	else  \
	    ${CP} ${OBJECTDIR}/DistCalc.o ${OBJECTDIR}/DistCalc_nomain.o;\
	fi

${OBJECTDIR}/Handler_nomain.o: ${OBJECTDIR}/Handler.o Handler.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Handler.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Handler_nomain.o Handler.c;\
	else  \
	    ${CP} ${OBJECTDIR}/Handler.o ${OBJECTDIR}/Handler_nomain.o;\
	fi

${OBJECTDIR}/InOutBuffer_nomain.o: ${OBJECTDIR}/InOutBuffer.o InOutBuffer.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/InOutBuffer.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/InOutBuffer_nomain.o InOutBuffer.c;\
	else  \
	    ${CP} ${OBJECTDIR}/InOutBuffer.o ${OBJECTDIR}/InOutBuffer_nomain.o;\
	fi

${OBJECTDIR}/LogModule_nomain.o: ${OBJECTDIR}/LogModule.o LogModule.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/LogModule.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/LogModule_nomain.o LogModule.c;\
	else  \
	    ${CP} ${OBJECTDIR}/LogModule.o ${OBJECTDIR}/LogModule_nomain.o;\
	fi

${OBJECTDIR}/PWMModule_nomain.o: ${OBJECTDIR}/PWMModule.o PWMModule.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/PWMModule.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/PWMModule_nomain.o PWMModule.c;\
	else  \
	    ${CP} ${OBJECTDIR}/PWMModule.o ${OBJECTDIR}/PWMModule_nomain.o;\
	fi

${OBJECTDIR}/Packet_nomain.o: ${OBJECTDIR}/Packet.o Packet.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Packet.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Packet_nomain.o Packet.c;\
	else  \
	    ${CP} ${OBJECTDIR}/Packet.o ${OBJECTDIR}/Packet_nomain.o;\
	fi

${OBJECTDIR}/Schedule_nomain.o: ${OBJECTDIR}/Schedule.o Schedule.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Schedule.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Schedule_nomain.o Schedule.c;\
	else  \
	    ${CP} ${OBJECTDIR}/Schedule.o ${OBJECTDIR}/Schedule_nomain.o;\
	fi

${OBJECTDIR}/StreamDataRecorder_nomain.o: ${OBJECTDIR}/StreamDataRecorder.o StreamDataRecorder.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/StreamDataRecorder.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/StreamDataRecorder_nomain.o StreamDataRecorder.c;\
	else  \
	    ${CP} ${OBJECTDIR}/StreamDataRecorder.o ${OBJECTDIR}/StreamDataRecorder_nomain.o;\
	fi

${OBJECTDIR}/coap/coap_nomain.o: ${OBJECTDIR}/coap/coap.o coap/coap.c 
	${MKDIR} -p ${OBJECTDIR}/coap
	@NMOUTPUT=`${NM} ${OBJECTDIR}/coap/coap.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/coap/coap_nomain.o coap/coap.c;\
	else  \
	    ${CP} ${OBJECTDIR}/coap/coap.o ${OBJECTDIR}/coap/coap_nomain.o;\
	fi

${OBJECTDIR}/json/cJSON_nomain.o: ${OBJECTDIR}/json/cJSON.o json/cJSON.c 
	${MKDIR} -p ${OBJECTDIR}/json
	@NMOUTPUT=`${NM} ${OBJECTDIR}/json/cJSON.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/json/cJSON_nomain.o json/cJSON.c;\
	else  \
	    ${CP} ${OBJECTDIR}/json/cJSON.o ${OBJECTDIR}/json/cJSON_nomain.o;\
	fi

${OBJECTDIR}/json/cJSON_Utils_nomain.o: ${OBJECTDIR}/json/cJSON_Utils.o json/cJSON_Utils.c 
	${MKDIR} -p ${OBJECTDIR}/json
	@NMOUTPUT=`${NM} ${OBJECTDIR}/json/cJSON_Utils.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/json/cJSON_Utils_nomain.o json/cJSON_Utils.c;\
	else  \
	    ${CP} ${OBJECTDIR}/json/cJSON_Utils.o ${OBJECTDIR}/json/cJSON_Utils_nomain.o;\
	fi

${OBJECTDIR}/malloc/umm_malloc_nomain.o: ${OBJECTDIR}/malloc/umm_malloc.o malloc/umm_malloc.c 
	${MKDIR} -p ${OBJECTDIR}/malloc
	@NMOUTPUT=`${NM} ${OBJECTDIR}/malloc/umm_malloc.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/malloc/umm_malloc_nomain.o malloc/umm_malloc.c;\
	else  \
	    ${CP} ${OBJECTDIR}/malloc/umm_malloc.o ${OBJECTDIR}/malloc/umm_malloc_nomain.o;\
	fi

${OBJECTDIR}/models/src/array_nomain.o: ${OBJECTDIR}/models/src/array.o models/src/array.c 
	${MKDIR} -p ${OBJECTDIR}/models/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/models/src/array.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/models/src/array_nomain.o models/src/array.c;\
	else  \
	    ${CP} ${OBJECTDIR}/models/src/array.o ${OBJECTDIR}/models/src/array_nomain.o;\
	fi

${OBJECTDIR}/models/src/circularbuffer_nomain.o: ${OBJECTDIR}/models/src/circularbuffer.o models/src/circularbuffer.c 
	${MKDIR} -p ${OBJECTDIR}/models/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/models/src/circularbuffer.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/models/src/circularbuffer_nomain.o models/src/circularbuffer.c;\
	else  \
	    ${CP} ${OBJECTDIR}/models/src/circularbuffer.o ${OBJECTDIR}/models/src/circularbuffer_nomain.o;\
	fi

${OBJECTDIR}/models/src/common_nomain.o: ${OBJECTDIR}/models/src/common.o models/src/common.c 
	${MKDIR} -p ${OBJECTDIR}/models/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/models/src/common.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/models/src/common_nomain.o models/src/common.c;\
	else  \
	    ${CP} ${OBJECTDIR}/models/src/common.o ${OBJECTDIR}/models/src/common_nomain.o;\
	fi

${OBJECTDIR}/models/src/deque_nomain.o: ${OBJECTDIR}/models/src/deque.o models/src/deque.c 
	${MKDIR} -p ${OBJECTDIR}/models/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/models/src/deque.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/models/src/deque_nomain.o models/src/deque.c;\
	else  \
	    ${CP} ${OBJECTDIR}/models/src/deque.o ${OBJECTDIR}/models/src/deque_nomain.o;\
	fi

${OBJECTDIR}/models/src/hashset_nomain.o: ${OBJECTDIR}/models/src/hashset.o models/src/hashset.c 
	${MKDIR} -p ${OBJECTDIR}/models/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/models/src/hashset.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/models/src/hashset_nomain.o models/src/hashset.c;\
	else  \
	    ${CP} ${OBJECTDIR}/models/src/hashset.o ${OBJECTDIR}/models/src/hashset_nomain.o;\
	fi

${OBJECTDIR}/models/src/hashtable_nomain.o: ${OBJECTDIR}/models/src/hashtable.o models/src/hashtable.c 
	${MKDIR} -p ${OBJECTDIR}/models/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/models/src/hashtable.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/models/src/hashtable_nomain.o models/src/hashtable.c;\
	else  \
	    ${CP} ${OBJECTDIR}/models/src/hashtable.o ${OBJECTDIR}/models/src/hashtable_nomain.o;\
	fi

${OBJECTDIR}/models/src/list_nomain.o: ${OBJECTDIR}/models/src/list.o models/src/list.c 
	${MKDIR} -p ${OBJECTDIR}/models/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/models/src/list.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/models/src/list_nomain.o models/src/list.c;\
	else  \
	    ${CP} ${OBJECTDIR}/models/src/list.o ${OBJECTDIR}/models/src/list_nomain.o;\
	fi

${OBJECTDIR}/models/src/queue_nomain.o: ${OBJECTDIR}/models/src/queue.o models/src/queue.c 
	${MKDIR} -p ${OBJECTDIR}/models/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/models/src/queue.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/models/src/queue_nomain.o models/src/queue.c;\
	else  \
	    ${CP} ${OBJECTDIR}/models/src/queue.o ${OBJECTDIR}/models/src/queue_nomain.o;\
	fi

${OBJECTDIR}/models/src/slist_nomain.o: ${OBJECTDIR}/models/src/slist.o models/src/slist.c 
	${MKDIR} -p ${OBJECTDIR}/models/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/models/src/slist.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/models/src/slist_nomain.o models/src/slist.c;\
	else  \
	    ${CP} ${OBJECTDIR}/models/src/slist.o ${OBJECTDIR}/models/src/slist_nomain.o;\
	fi

${OBJECTDIR}/models/src/stack_nomain.o: ${OBJECTDIR}/models/src/stack.o models/src/stack.c 
	${MKDIR} -p ${OBJECTDIR}/models/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/models/src/stack.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/models/src/stack_nomain.o models/src/stack.c;\
	else  \
	    ${CP} ${OBJECTDIR}/models/src/stack.o ${OBJECTDIR}/models/src/stack_nomain.o;\
	fi

${OBJECTDIR}/models/src/treeset_nomain.o: ${OBJECTDIR}/models/src/treeset.o models/src/treeset.c 
	${MKDIR} -p ${OBJECTDIR}/models/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/models/src/treeset.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/models/src/treeset_nomain.o models/src/treeset.c;\
	else  \
	    ${CP} ${OBJECTDIR}/models/src/treeset.o ${OBJECTDIR}/models/src/treeset_nomain.o;\
	fi

${OBJECTDIR}/models/src/treetable_nomain.o: ${OBJECTDIR}/models/src/treetable.o models/src/treetable.c 
	${MKDIR} -p ${OBJECTDIR}/models/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/models/src/treetable.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O3 -DDEBUG -DMC -DRTOS -I../EEG_Evoker -I. -Imodels/include -Icoap -Ijson -Imalloc -Imodels -IExternal -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/models/src/treetable_nomain.o models/src/treetable.c;\
	else  \
	    ${CP} ${OBJECTDIR}/models/src/treetable.o ${OBJECTDIR}/models/src/treetable_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f2 || true; \
	    ${TESTDIR}/TestFiles/f1 || true; \
	    ${TESTDIR}/TestFiles/f5 || true; \
	    ${TESTDIR}/TestFiles/f3 || true; \
	    ${TESTDIR}/TestFiles/f4 || true; \
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
