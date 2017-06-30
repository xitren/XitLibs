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
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/83d34d09/ExtFunctions.o \
	${OBJECTDIR}/_ext/83d34d09/UpdateModule.o \
	${OBJECTDIR}/main.o


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
LDLIBSOPTIONS=../XitLib/dist/Release_Windows/MinGW-Windows/libxitlib.a -lWs2_32 ../EEG_Evoker/dist/Release/MinGW-Windows/libeeg_evoker.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/iot_server.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/iot_server.exe: ../XitLib/dist/Release_Windows/MinGW-Windows/libxitlib.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/iot_server.exe: ../EEG_Evoker/dist/Release/MinGW-Windows/libeeg_evoker.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/iot_server.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/iot_server ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/83d34d09/ExtFunctions.o: ../XitLib/External/ExtFunctions.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/83d34d09
	${RM} "$@.d"
	$(COMPILE.c) -g -DCPU -DP300 -DPLATFORM_WINDOWS -I../EEG_Evoker -I../XitLib -I../XitLib/External -I../XitLib/coap -I../XitLib/json -I../XitLib/malloc -I../XitLib/models/include -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/83d34d09/ExtFunctions.o ../XitLib/External/ExtFunctions.c

${OBJECTDIR}/_ext/83d34d09/UpdateModule.o: ../XitLib/External/UpdateModule.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/83d34d09
	${RM} "$@.d"
	$(COMPILE.c) -g -DCPU -DP300 -DPLATFORM_WINDOWS -I../EEG_Evoker -I../XitLib -I../XitLib/External -I../XitLib/coap -I../XitLib/json -I../XitLib/malloc -I../XitLib/models/include -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/83d34d09/UpdateModule.o ../XitLib/External/UpdateModule.c

${OBJECTDIR}/main.o: main.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -DCPU -DP300 -DPLATFORM_WINDOWS -I../EEG_Evoker -I../XitLib -I../XitLib/External -I../XitLib/coap -I../XitLib/json -I../XitLib/malloc -I../XitLib/models/include -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/iot_server.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
