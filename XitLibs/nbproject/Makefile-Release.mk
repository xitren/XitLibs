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
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/CRC16ANSI.o \
	${OBJECTDIR}/src/CSMACD.o \
	${OBJECTDIR}/src/CommandModule.o \
	${OBJECTDIR}/src/ConfigMem.o \
	${OBJECTDIR}/src/DistCalc.o \
	${OBJECTDIR}/src/InOutBuffer.o \
	${OBJECTDIR}/src/LogModule.o \
	${OBJECTDIR}/src/PWMModule.o \
	${OBJECTDIR}/src/Schedule.o \
	${OBJECTDIR}/src/StreamDataRecorder.o \
	${OBJECTDIR}/src/coap/coap.o \
	${OBJECTDIR}/src/json/cJSON.o \
	${OBJECTDIR}/src/json/cJSON_Utils.o \
	${OBJECTDIR}/src/malloc/umm_malloc.o \
	${OBJECTDIR}/src/models/src/array.o \
	${OBJECTDIR}/src/models/src/circularbuffer.o \
	${OBJECTDIR}/src/models/src/common.o \
	${OBJECTDIR}/src/models/src/deque.o \
	${OBJECTDIR}/src/models/src/hashset.o \
	${OBJECTDIR}/src/models/src/hashtable.o \
	${OBJECTDIR}/src/models/src/list.o \
	${OBJECTDIR}/src/models/src/queue.o \
	${OBJECTDIR}/src/models/src/slist.o \
	${OBJECTDIR}/src/models/src/stack.o \
	${OBJECTDIR}/src/models/src/treeset.o \
	${OBJECTDIR}/src/models/src/treetable.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f3 \
	${TESTDIR}/TestFiles/f4 \
	${TESTDIR}/TestFiles/f5 \
	${TESTDIR}/TestFiles/f1 \
	${TESTDIR}/TestFiles/f2

# Test Object Files
TESTOBJECTFILES= \
	${TESTDIR}/tests/circlebuffertest.o \
	${TESTDIR}/tests/coaptest.o \
	${TESTDIR}/tests/csmacdtest.o \
	${TESTDIR}/tests/memorytest.o \
	${TESTDIR}/tests/streamtest.o

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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libxitlibs.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libxitlibs.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libxitlibs.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libxitlibs.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libxitlibs.a

${OBJECTDIR}/src/CRC16ANSI.o: src/CRC16ANSI.c
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CRC16ANSI.o src/CRC16ANSI.c

${OBJECTDIR}/src/CSMACD.o: src/CSMACD.c
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CSMACD.o src/CSMACD.c

${OBJECTDIR}/src/CommandModule.o: src/CommandModule.c
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CommandModule.o src/CommandModule.c

${OBJECTDIR}/src/ConfigMem.o: src/ConfigMem.c
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/ConfigMem.o src/ConfigMem.c

${OBJECTDIR}/src/DistCalc.o: src/DistCalc.c
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/DistCalc.o src/DistCalc.c

${OBJECTDIR}/src/InOutBuffer.o: src/InOutBuffer.c
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/InOutBuffer.o src/InOutBuffer.c

${OBJECTDIR}/src/LogModule.o: src/LogModule.c
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/LogModule.o src/LogModule.c

${OBJECTDIR}/src/PWMModule.o: src/PWMModule.c
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/PWMModule.o src/PWMModule.c

${OBJECTDIR}/src/Schedule.o: src/Schedule.c
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Schedule.o src/Schedule.c

${OBJECTDIR}/src/StreamDataRecorder.o: src/StreamDataRecorder.c
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/StreamDataRecorder.o src/StreamDataRecorder.c

${OBJECTDIR}/src/coap/coap.o: src/coap/coap.c
	${MKDIR} -p ${OBJECTDIR}/src/coap
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/coap/coap.o src/coap/coap.c

${OBJECTDIR}/src/json/cJSON.o: src/json/cJSON.c
	${MKDIR} -p ${OBJECTDIR}/src/json
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/json/cJSON.o src/json/cJSON.c

${OBJECTDIR}/src/json/cJSON_Utils.o: src/json/cJSON_Utils.c
	${MKDIR} -p ${OBJECTDIR}/src/json
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/json/cJSON_Utils.o src/json/cJSON_Utils.c

${OBJECTDIR}/src/malloc/umm_malloc.o: src/malloc/umm_malloc.c
	${MKDIR} -p ${OBJECTDIR}/src/malloc
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/malloc/umm_malloc.o src/malloc/umm_malloc.c

${OBJECTDIR}/src/models/src/array.o: src/models/src/array.c
	${MKDIR} -p ${OBJECTDIR}/src/models/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/models/src/array.o src/models/src/array.c

${OBJECTDIR}/src/models/src/circularbuffer.o: src/models/src/circularbuffer.c
	${MKDIR} -p ${OBJECTDIR}/src/models/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/models/src/circularbuffer.o src/models/src/circularbuffer.c

${OBJECTDIR}/src/models/src/common.o: src/models/src/common.c
	${MKDIR} -p ${OBJECTDIR}/src/models/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/models/src/common.o src/models/src/common.c

${OBJECTDIR}/src/models/src/deque.o: src/models/src/deque.c
	${MKDIR} -p ${OBJECTDIR}/src/models/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/models/src/deque.o src/models/src/deque.c

${OBJECTDIR}/src/models/src/hashset.o: src/models/src/hashset.c
	${MKDIR} -p ${OBJECTDIR}/src/models/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/models/src/hashset.o src/models/src/hashset.c

${OBJECTDIR}/src/models/src/hashtable.o: src/models/src/hashtable.c
	${MKDIR} -p ${OBJECTDIR}/src/models/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/models/src/hashtable.o src/models/src/hashtable.c

${OBJECTDIR}/src/models/src/list.o: src/models/src/list.c
	${MKDIR} -p ${OBJECTDIR}/src/models/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/models/src/list.o src/models/src/list.c

${OBJECTDIR}/src/models/src/queue.o: src/models/src/queue.c
	${MKDIR} -p ${OBJECTDIR}/src/models/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/models/src/queue.o src/models/src/queue.c

${OBJECTDIR}/src/models/src/slist.o: src/models/src/slist.c
	${MKDIR} -p ${OBJECTDIR}/src/models/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/models/src/slist.o src/models/src/slist.c

${OBJECTDIR}/src/models/src/stack.o: src/models/src/stack.c
	${MKDIR} -p ${OBJECTDIR}/src/models/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/models/src/stack.o src/models/src/stack.c

${OBJECTDIR}/src/models/src/treeset.o: src/models/src/treeset.c
	${MKDIR} -p ${OBJECTDIR}/src/models/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/models/src/treeset.o src/models/src/treeset.c

${OBJECTDIR}/src/models/src/treetable.o: src/models/src/treetable.c
	${MKDIR} -p ${OBJECTDIR}/src/models/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/models/src/treetable.o src/models/src/treetable.c

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-tests-subprojects .build-conf ${TESTFILES}
.build-tests-subprojects:

${TESTDIR}/TestFiles/f3: ${TESTDIR}/tests/streamtest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c} -o ${TESTDIR}/TestFiles/f3 $^ ${LDLIBSOPTIONS}   

${TESTDIR}/TestFiles/f4: ${TESTDIR}/tests/circlebuffertest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c} -o ${TESTDIR}/TestFiles/f4 $^ ${LDLIBSOPTIONS}   

${TESTDIR}/TestFiles/f5: ${TESTDIR}/tests/coaptest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c} -o ${TESTDIR}/TestFiles/f5 $^ ${LDLIBSOPTIONS}   

${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/csmacdtest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c} -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS}   

${TESTDIR}/TestFiles/f2: ${TESTDIR}/tests/memorytest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c} -o ${TESTDIR}/TestFiles/f2 $^ ${LDLIBSOPTIONS}   


${TESTDIR}/tests/streamtest.o: tests/streamtest.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/streamtest.o tests/streamtest.c


${TESTDIR}/tests/circlebuffertest.o: tests/circlebuffertest.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/circlebuffertest.o tests/circlebuffertest.c


${TESTDIR}/tests/coaptest.o: tests/coaptest.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/coaptest.o tests/coaptest.c


${TESTDIR}/tests/csmacdtest.o: tests/csmacdtest.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/csmacdtest.o tests/csmacdtest.c


${TESTDIR}/tests/memorytest.o: tests/memorytest.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/memorytest.o tests/memorytest.c


${OBJECTDIR}/src/CRC16ANSI_nomain.o: ${OBJECTDIR}/src/CRC16ANSI.o src/CRC16ANSI.c 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/CRC16ANSI.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CRC16ANSI_nomain.o src/CRC16ANSI.c;\
	else  \
	    ${CP} ${OBJECTDIR}/src/CRC16ANSI.o ${OBJECTDIR}/src/CRC16ANSI_nomain.o;\
	fi

${OBJECTDIR}/src/CSMACD_nomain.o: ${OBJECTDIR}/src/CSMACD.o src/CSMACD.c 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/CSMACD.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CSMACD_nomain.o src/CSMACD.c;\
	else  \
	    ${CP} ${OBJECTDIR}/src/CSMACD.o ${OBJECTDIR}/src/CSMACD_nomain.o;\
	fi

${OBJECTDIR}/src/CommandModule_nomain.o: ${OBJECTDIR}/src/CommandModule.o src/CommandModule.c 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/CommandModule.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CommandModule_nomain.o src/CommandModule.c;\
	else  \
	    ${CP} ${OBJECTDIR}/src/CommandModule.o ${OBJECTDIR}/src/CommandModule_nomain.o;\
	fi

${OBJECTDIR}/src/ConfigMem_nomain.o: ${OBJECTDIR}/src/ConfigMem.o src/ConfigMem.c 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/ConfigMem.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/ConfigMem_nomain.o src/ConfigMem.c;\
	else  \
	    ${CP} ${OBJECTDIR}/src/ConfigMem.o ${OBJECTDIR}/src/ConfigMem_nomain.o;\
	fi

${OBJECTDIR}/src/DistCalc_nomain.o: ${OBJECTDIR}/src/DistCalc.o src/DistCalc.c 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/DistCalc.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/DistCalc_nomain.o src/DistCalc.c;\
	else  \
	    ${CP} ${OBJECTDIR}/src/DistCalc.o ${OBJECTDIR}/src/DistCalc_nomain.o;\
	fi

${OBJECTDIR}/src/InOutBuffer_nomain.o: ${OBJECTDIR}/src/InOutBuffer.o src/InOutBuffer.c 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/InOutBuffer.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/InOutBuffer_nomain.o src/InOutBuffer.c;\
	else  \
	    ${CP} ${OBJECTDIR}/src/InOutBuffer.o ${OBJECTDIR}/src/InOutBuffer_nomain.o;\
	fi

${OBJECTDIR}/src/LogModule_nomain.o: ${OBJECTDIR}/src/LogModule.o src/LogModule.c 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/LogModule.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/LogModule_nomain.o src/LogModule.c;\
	else  \
	    ${CP} ${OBJECTDIR}/src/LogModule.o ${OBJECTDIR}/src/LogModule_nomain.o;\
	fi

${OBJECTDIR}/src/PWMModule_nomain.o: ${OBJECTDIR}/src/PWMModule.o src/PWMModule.c 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/PWMModule.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/PWMModule_nomain.o src/PWMModule.c;\
	else  \
	    ${CP} ${OBJECTDIR}/src/PWMModule.o ${OBJECTDIR}/src/PWMModule_nomain.o;\
	fi

${OBJECTDIR}/src/Schedule_nomain.o: ${OBJECTDIR}/src/Schedule.o src/Schedule.c 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/Schedule.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Schedule_nomain.o src/Schedule.c;\
	else  \
	    ${CP} ${OBJECTDIR}/src/Schedule.o ${OBJECTDIR}/src/Schedule_nomain.o;\
	fi

${OBJECTDIR}/src/StreamDataRecorder_nomain.o: ${OBJECTDIR}/src/StreamDataRecorder.o src/StreamDataRecorder.c 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/StreamDataRecorder.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/StreamDataRecorder_nomain.o src/StreamDataRecorder.c;\
	else  \
	    ${CP} ${OBJECTDIR}/src/StreamDataRecorder.o ${OBJECTDIR}/src/StreamDataRecorder_nomain.o;\
	fi

${OBJECTDIR}/src/coap/coap_nomain.o: ${OBJECTDIR}/src/coap/coap.o src/coap/coap.c 
	${MKDIR} -p ${OBJECTDIR}/src/coap
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/coap/coap.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/coap/coap_nomain.o src/coap/coap.c;\
	else  \
	    ${CP} ${OBJECTDIR}/src/coap/coap.o ${OBJECTDIR}/src/coap/coap_nomain.o;\
	fi

${OBJECTDIR}/src/json/cJSON_nomain.o: ${OBJECTDIR}/src/json/cJSON.o src/json/cJSON.c 
	${MKDIR} -p ${OBJECTDIR}/src/json
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/json/cJSON.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/json/cJSON_nomain.o src/json/cJSON.c;\
	else  \
	    ${CP} ${OBJECTDIR}/src/json/cJSON.o ${OBJECTDIR}/src/json/cJSON_nomain.o;\
	fi

${OBJECTDIR}/src/json/cJSON_Utils_nomain.o: ${OBJECTDIR}/src/json/cJSON_Utils.o src/json/cJSON_Utils.c 
	${MKDIR} -p ${OBJECTDIR}/src/json
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/json/cJSON_Utils.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/json/cJSON_Utils_nomain.o src/json/cJSON_Utils.c;\
	else  \
	    ${CP} ${OBJECTDIR}/src/json/cJSON_Utils.o ${OBJECTDIR}/src/json/cJSON_Utils_nomain.o;\
	fi

${OBJECTDIR}/src/malloc/umm_malloc_nomain.o: ${OBJECTDIR}/src/malloc/umm_malloc.o src/malloc/umm_malloc.c 
	${MKDIR} -p ${OBJECTDIR}/src/malloc
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/malloc/umm_malloc.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/malloc/umm_malloc_nomain.o src/malloc/umm_malloc.c;\
	else  \
	    ${CP} ${OBJECTDIR}/src/malloc/umm_malloc.o ${OBJECTDIR}/src/malloc/umm_malloc_nomain.o;\
	fi

${OBJECTDIR}/src/models/src/array_nomain.o: ${OBJECTDIR}/src/models/src/array.o src/models/src/array.c 
	${MKDIR} -p ${OBJECTDIR}/src/models/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/models/src/array.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/models/src/array_nomain.o src/models/src/array.c;\
	else  \
	    ${CP} ${OBJECTDIR}/src/models/src/array.o ${OBJECTDIR}/src/models/src/array_nomain.o;\
	fi

${OBJECTDIR}/src/models/src/circularbuffer_nomain.o: ${OBJECTDIR}/src/models/src/circularbuffer.o src/models/src/circularbuffer.c 
	${MKDIR} -p ${OBJECTDIR}/src/models/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/models/src/circularbuffer.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/models/src/circularbuffer_nomain.o src/models/src/circularbuffer.c;\
	else  \
	    ${CP} ${OBJECTDIR}/src/models/src/circularbuffer.o ${OBJECTDIR}/src/models/src/circularbuffer_nomain.o;\
	fi

${OBJECTDIR}/src/models/src/common_nomain.o: ${OBJECTDIR}/src/models/src/common.o src/models/src/common.c 
	${MKDIR} -p ${OBJECTDIR}/src/models/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/models/src/common.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/models/src/common_nomain.o src/models/src/common.c;\
	else  \
	    ${CP} ${OBJECTDIR}/src/models/src/common.o ${OBJECTDIR}/src/models/src/common_nomain.o;\
	fi

${OBJECTDIR}/src/models/src/deque_nomain.o: ${OBJECTDIR}/src/models/src/deque.o src/models/src/deque.c 
	${MKDIR} -p ${OBJECTDIR}/src/models/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/models/src/deque.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/models/src/deque_nomain.o src/models/src/deque.c;\
	else  \
	    ${CP} ${OBJECTDIR}/src/models/src/deque.o ${OBJECTDIR}/src/models/src/deque_nomain.o;\
	fi

${OBJECTDIR}/src/models/src/hashset_nomain.o: ${OBJECTDIR}/src/models/src/hashset.o src/models/src/hashset.c 
	${MKDIR} -p ${OBJECTDIR}/src/models/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/models/src/hashset.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/models/src/hashset_nomain.o src/models/src/hashset.c;\
	else  \
	    ${CP} ${OBJECTDIR}/src/models/src/hashset.o ${OBJECTDIR}/src/models/src/hashset_nomain.o;\
	fi

${OBJECTDIR}/src/models/src/hashtable_nomain.o: ${OBJECTDIR}/src/models/src/hashtable.o src/models/src/hashtable.c 
	${MKDIR} -p ${OBJECTDIR}/src/models/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/models/src/hashtable.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/models/src/hashtable_nomain.o src/models/src/hashtable.c;\
	else  \
	    ${CP} ${OBJECTDIR}/src/models/src/hashtable.o ${OBJECTDIR}/src/models/src/hashtable_nomain.o;\
	fi

${OBJECTDIR}/src/models/src/list_nomain.o: ${OBJECTDIR}/src/models/src/list.o src/models/src/list.c 
	${MKDIR} -p ${OBJECTDIR}/src/models/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/models/src/list.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/models/src/list_nomain.o src/models/src/list.c;\
	else  \
	    ${CP} ${OBJECTDIR}/src/models/src/list.o ${OBJECTDIR}/src/models/src/list_nomain.o;\
	fi

${OBJECTDIR}/src/models/src/queue_nomain.o: ${OBJECTDIR}/src/models/src/queue.o src/models/src/queue.c 
	${MKDIR} -p ${OBJECTDIR}/src/models/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/models/src/queue.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/models/src/queue_nomain.o src/models/src/queue.c;\
	else  \
	    ${CP} ${OBJECTDIR}/src/models/src/queue.o ${OBJECTDIR}/src/models/src/queue_nomain.o;\
	fi

${OBJECTDIR}/src/models/src/slist_nomain.o: ${OBJECTDIR}/src/models/src/slist.o src/models/src/slist.c 
	${MKDIR} -p ${OBJECTDIR}/src/models/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/models/src/slist.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/models/src/slist_nomain.o src/models/src/slist.c;\
	else  \
	    ${CP} ${OBJECTDIR}/src/models/src/slist.o ${OBJECTDIR}/src/models/src/slist_nomain.o;\
	fi

${OBJECTDIR}/src/models/src/stack_nomain.o: ${OBJECTDIR}/src/models/src/stack.o src/models/src/stack.c 
	${MKDIR} -p ${OBJECTDIR}/src/models/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/models/src/stack.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/models/src/stack_nomain.o src/models/src/stack.c;\
	else  \
	    ${CP} ${OBJECTDIR}/src/models/src/stack.o ${OBJECTDIR}/src/models/src/stack_nomain.o;\
	fi

${OBJECTDIR}/src/models/src/treeset_nomain.o: ${OBJECTDIR}/src/models/src/treeset.o src/models/src/treeset.c 
	${MKDIR} -p ${OBJECTDIR}/src/models/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/models/src/treeset.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/models/src/treeset_nomain.o src/models/src/treeset.c;\
	else  \
	    ${CP} ${OBJECTDIR}/src/models/src/treeset.o ${OBJECTDIR}/src/models/src/treeset_nomain.o;\
	fi

${OBJECTDIR}/src/models/src/treetable_nomain.o: ${OBJECTDIR}/src/models/src/treetable.o src/models/src/treetable.c 
	${MKDIR} -p ${OBJECTDIR}/src/models/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/models/src/treetable.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/models/src/treetable_nomain.o src/models/src/treetable.c;\
	else  \
	    ${CP} ${OBJECTDIR}/src/models/src/treetable.o ${OBJECTDIR}/src/models/src/treetable_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f3 || true; \
	    ${TESTDIR}/TestFiles/f4 || true; \
	    ${TESTDIR}/TestFiles/f5 || true; \
	    ${TESTDIR}/TestFiles/f1 || true; \
	    ${TESTDIR}/TestFiles/f2 || true; \
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
