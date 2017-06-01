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
CND_PLATFORM=Cygwin-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug_Windows
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
	${OBJECTDIR}/DMAretransmitter.o \
	${OBJECTDIR}/ExtMemModule.o \
	${OBJECTDIR}/FunctionsDiscovery.o \
	${OBJECTDIR}/Handler.o \
	${OBJECTDIR}/InOutBuffer.o \
	${OBJECTDIR}/PWMModule.o \
	${OBJECTDIR}/Packet.o \
	${OBJECTDIR}/StreamDataRecorder.o \
	${OBJECTDIR}/SymbolBuffer.o \
	${OBJECTDIR}/UpdateModule.o \
	${OBJECTDIR}/VideoModule.o \
	${OBJECTDIR}/generatorModule.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f6 \
	${TESTDIR}/TestFiles/f1 \
	${TESTDIR}/TestFiles/f2 \
	${TESTDIR}/TestFiles/f3 \
	${TESTDIR}/TestFiles/f7 \
	${TESTDIR}/TestFiles/f5 \
	${TESTDIR}/TestFiles/f4

# Test Object Files
TESTOBJECTFILES= \
	${TESTDIR}/tests/discovery_func_test.o \
	${TESTDIR}/tests/dma_test.o \
	${TESTDIR}/tests/ext_mem_test.o \
	${TESTDIR}/tests/file_cvep_test.o \
	${TESTDIR}/tests/json_parser.o \
	${TESTDIR}/tests/operation_test.o \
	${TESTDIR}/tests/pocket_test.o

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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libxitlib.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libxitlib.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libxitlib.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libxitlib.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libxitlib.a

${OBJECTDIR}/CRC16ANSI.o: CRC16ANSI.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -Werror -DCPU -DDEBUG -DPLATFORM_WINDOWS -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CRC16ANSI.o CRC16ANSI.c

${OBJECTDIR}/CommandModule.o: CommandModule.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -Werror -DCPU -DDEBUG -DPLATFORM_WINDOWS -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CommandModule.o CommandModule.c

${OBJECTDIR}/ConfigMem.o: ConfigMem.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -Werror -DCPU -DDEBUG -DPLATFORM_WINDOWS -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ConfigMem.o ConfigMem.c

${OBJECTDIR}/DMAretransmitter.o: DMAretransmitter.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -Werror -DCPU -DDEBUG -DPLATFORM_WINDOWS -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DMAretransmitter.o DMAretransmitter.c

${OBJECTDIR}/ExtMemModule.o: ExtMemModule.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -Werror -DCPU -DDEBUG -DPLATFORM_WINDOWS -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ExtMemModule.o ExtMemModule.c

${OBJECTDIR}/FunctionsDiscovery.o: FunctionsDiscovery.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -Werror -DCPU -DDEBUG -DPLATFORM_WINDOWS -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/FunctionsDiscovery.o FunctionsDiscovery.c

${OBJECTDIR}/Handler.o: Handler.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -Werror -DCPU -DDEBUG -DPLATFORM_WINDOWS -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Handler.o Handler.c

${OBJECTDIR}/InOutBuffer.o: InOutBuffer.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -Werror -DCPU -DDEBUG -DPLATFORM_WINDOWS -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/InOutBuffer.o InOutBuffer.c

${OBJECTDIR}/PWMModule.o: PWMModule.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -Werror -DCPU -DDEBUG -DPLATFORM_WINDOWS -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/PWMModule.o PWMModule.c

${OBJECTDIR}/Packet.o: Packet.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -Werror -DCPU -DDEBUG -DPLATFORM_WINDOWS -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Packet.o Packet.c

${OBJECTDIR}/StreamDataRecorder.o: StreamDataRecorder.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -Werror -DCPU -DDEBUG -DPLATFORM_WINDOWS -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/StreamDataRecorder.o StreamDataRecorder.c

${OBJECTDIR}/SymbolBuffer.o: SymbolBuffer.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -Werror -DCPU -DDEBUG -DPLATFORM_WINDOWS -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SymbolBuffer.o SymbolBuffer.c

${OBJECTDIR}/UpdateModule.o: UpdateModule.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -Werror -DCPU -DDEBUG -DPLATFORM_WINDOWS -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/UpdateModule.o UpdateModule.c

${OBJECTDIR}/VideoModule.o: VideoModule.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -Werror -DCPU -DDEBUG -DPLATFORM_WINDOWS -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/VideoModule.o VideoModule.c

${OBJECTDIR}/generatorModule.o: generatorModule.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -Werror -DCPU -DDEBUG -DPLATFORM_WINDOWS -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/generatorModule.o generatorModule.c

# Subprojects
.build-subprojects:
	cd ../CoAP && ${MAKE}  -f Makefile CONF=Debug

# Build Test Targets
.build-tests-conf: .build-tests-subprojects .build-conf ${TESTFILES}
.build-tests-subprojects:

${TESTDIR}/TestFiles/f6: ${TESTDIR}/tests/discovery_func_test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c} -o ${TESTDIR}/TestFiles/f6 $^ ${LDLIBSOPTIONS}   -lWs2_32 

${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/dma_test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c} -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS}   -lWs2_32 

${TESTDIR}/TestFiles/f2: ${TESTDIR}/tests/ext_mem_test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c} -o ${TESTDIR}/TestFiles/f2 $^ ${LDLIBSOPTIONS}   -lWs2_32 

${TESTDIR}/TestFiles/f3: ${TESTDIR}/tests/file_cvep_test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c} -o ${TESTDIR}/TestFiles/f3 $^ ${LDLIBSOPTIONS}   -L../cVEP/dist/Debug/MinGW-Windows -lWs2_32 -lcvep 

${TESTDIR}/TestFiles/f7: ${TESTDIR}/tests/operation_test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c} -o ${TESTDIR}/TestFiles/f7 $^ ${LDLIBSOPTIONS}   -lWs2_32 

${TESTDIR}/TestFiles/f5: ${TESTDIR}/tests/json_parser.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c} -o ${TESTDIR}/TestFiles/f5 $^ ${LDLIBSOPTIONS}   -lWs2_32 

${TESTDIR}/TestFiles/f4: ${TESTDIR}/tests/pocket_test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c} -o ${TESTDIR}/TestFiles/f4 $^ ${LDLIBSOPTIONS}   -lWs2_32 


${TESTDIR}/tests/discovery_func_test.o: tests/discovery_func_test.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -g -Werror -DCPU -DDEBUG -DPLATFORM_WINDOWS -DCPU -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/discovery_func_test.o tests/discovery_func_test.c


${TESTDIR}/tests/dma_test.o: tests/dma_test.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -g -Werror -DCPU -DDEBUG -DPLATFORM_WINDOWS -DCPU -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/dma_test.o tests/dma_test.c


${TESTDIR}/tests/ext_mem_test.o: tests/ext_mem_test.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -g -Werror -DCPU -DDEBUG -DPLATFORM_WINDOWS -DCPU -DDEBUG -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/ext_mem_test.o tests/ext_mem_test.c


${TESTDIR}/tests/file_cvep_test.o: tests/file_cvep_test.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -g -Werror -DCPU -DDEBUG -DPLATFORM_WINDOWS -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/file_cvep_test.o tests/file_cvep_test.c


${TESTDIR}/tests/operation_test.o: tests/operation_test.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -g -Werror -DCPU -DDEBUG -DPLATFORM_WINDOWS -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/operation_test.o tests/operation_test.c


${TESTDIR}/tests/json_parser.o: tests/json_parser.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -g -Werror -DCPU -DDEBUG -DPLATFORM_WINDOWS -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/json_parser.o tests/json_parser.c


${TESTDIR}/tests/pocket_test.o: tests/pocket_test.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -g -Werror -DCPU -DDEBUG -DPLATFORM_WINDOWS -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/pocket_test.o tests/pocket_test.c


${OBJECTDIR}/CRC16ANSI_nomain.o: ${OBJECTDIR}/CRC16ANSI.o CRC16ANSI.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/CRC16ANSI.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Werror -DCPU -DDEBUG -DPLATFORM_WINDOWS -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CRC16ANSI_nomain.o CRC16ANSI.c;\
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
	    $(COMPILE.c) -g -Werror -DCPU -DDEBUG -DPLATFORM_WINDOWS -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CommandModule_nomain.o CommandModule.c;\
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
	    $(COMPILE.c) -g -Werror -DCPU -DDEBUG -DPLATFORM_WINDOWS -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ConfigMem_nomain.o ConfigMem.c;\
	else  \
	    ${CP} ${OBJECTDIR}/ConfigMem.o ${OBJECTDIR}/ConfigMem_nomain.o;\
	fi

${OBJECTDIR}/DMAretransmitter_nomain.o: ${OBJECTDIR}/DMAretransmitter.o DMAretransmitter.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/DMAretransmitter.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Werror -DCPU -DDEBUG -DPLATFORM_WINDOWS -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DMAretransmitter_nomain.o DMAretransmitter.c;\
	else  \
	    ${CP} ${OBJECTDIR}/DMAretransmitter.o ${OBJECTDIR}/DMAretransmitter_nomain.o;\
	fi

${OBJECTDIR}/ExtMemModule_nomain.o: ${OBJECTDIR}/ExtMemModule.o ExtMemModule.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ExtMemModule.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Werror -DCPU -DDEBUG -DPLATFORM_WINDOWS -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ExtMemModule_nomain.o ExtMemModule.c;\
	else  \
	    ${CP} ${OBJECTDIR}/ExtMemModule.o ${OBJECTDIR}/ExtMemModule_nomain.o;\
	fi

${OBJECTDIR}/FunctionsDiscovery_nomain.o: ${OBJECTDIR}/FunctionsDiscovery.o FunctionsDiscovery.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/FunctionsDiscovery.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Werror -DCPU -DDEBUG -DPLATFORM_WINDOWS -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/FunctionsDiscovery_nomain.o FunctionsDiscovery.c;\
	else  \
	    ${CP} ${OBJECTDIR}/FunctionsDiscovery.o ${OBJECTDIR}/FunctionsDiscovery_nomain.o;\
	fi

${OBJECTDIR}/Handler_nomain.o: ${OBJECTDIR}/Handler.o Handler.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Handler.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Werror -DCPU -DDEBUG -DPLATFORM_WINDOWS -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Handler_nomain.o Handler.c;\
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
	    $(COMPILE.c) -g -Werror -DCPU -DDEBUG -DPLATFORM_WINDOWS -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/InOutBuffer_nomain.o InOutBuffer.c;\
	else  \
	    ${CP} ${OBJECTDIR}/InOutBuffer.o ${OBJECTDIR}/InOutBuffer_nomain.o;\
	fi

${OBJECTDIR}/PWMModule_nomain.o: ${OBJECTDIR}/PWMModule.o PWMModule.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/PWMModule.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Werror -DCPU -DDEBUG -DPLATFORM_WINDOWS -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/PWMModule_nomain.o PWMModule.c;\
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
	    $(COMPILE.c) -g -Werror -DCPU -DDEBUG -DPLATFORM_WINDOWS -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Packet_nomain.o Packet.c;\
	else  \
	    ${CP} ${OBJECTDIR}/Packet.o ${OBJECTDIR}/Packet_nomain.o;\
	fi

${OBJECTDIR}/StreamDataRecorder_nomain.o: ${OBJECTDIR}/StreamDataRecorder.o StreamDataRecorder.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/StreamDataRecorder.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Werror -DCPU -DDEBUG -DPLATFORM_WINDOWS -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/StreamDataRecorder_nomain.o StreamDataRecorder.c;\
	else  \
	    ${CP} ${OBJECTDIR}/StreamDataRecorder.o ${OBJECTDIR}/StreamDataRecorder_nomain.o;\
	fi

${OBJECTDIR}/SymbolBuffer_nomain.o: ${OBJECTDIR}/SymbolBuffer.o SymbolBuffer.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/SymbolBuffer.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Werror -DCPU -DDEBUG -DPLATFORM_WINDOWS -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SymbolBuffer_nomain.o SymbolBuffer.c;\
	else  \
	    ${CP} ${OBJECTDIR}/SymbolBuffer.o ${OBJECTDIR}/SymbolBuffer_nomain.o;\
	fi

${OBJECTDIR}/UpdateModule_nomain.o: ${OBJECTDIR}/UpdateModule.o UpdateModule.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/UpdateModule.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Werror -DCPU -DDEBUG -DPLATFORM_WINDOWS -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/UpdateModule_nomain.o UpdateModule.c;\
	else  \
	    ${CP} ${OBJECTDIR}/UpdateModule.o ${OBJECTDIR}/UpdateModule_nomain.o;\
	fi

${OBJECTDIR}/VideoModule_nomain.o: ${OBJECTDIR}/VideoModule.o VideoModule.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/VideoModule.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Werror -DCPU -DDEBUG -DPLATFORM_WINDOWS -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/VideoModule_nomain.o VideoModule.c;\
	else  \
	    ${CP} ${OBJECTDIR}/VideoModule.o ${OBJECTDIR}/VideoModule_nomain.o;\
	fi

${OBJECTDIR}/generatorModule_nomain.o: ${OBJECTDIR}/generatorModule.o generatorModule.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/generatorModule.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Werror -DCPU -DDEBUG -DPLATFORM_WINDOWS -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/generatorModule_nomain.o generatorModule.c;\
	else  \
	    ${CP} ${OBJECTDIR}/generatorModule.o ${OBJECTDIR}/generatorModule_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f6 || true; \
	    ${TESTDIR}/TestFiles/f1 || true; \
	    ${TESTDIR}/TestFiles/f2 || true; \
	    ${TESTDIR}/TestFiles/f3 || true; \
	    ${TESTDIR}/TestFiles/f7 || true; \
	    ${TESTDIR}/TestFiles/f5 || true; \
	    ${TESTDIR}/TestFiles/f4 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:
	cd ../CoAP && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
