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
CND_PLATFORM=None-Linux
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
	${OBJECTDIR}/_ext/8209c8dc/ExtFunctions.o \
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
LDLIBSOPTIONS=../EEG_Evoker/dist/Release/MinGW-Linux/libeeg_evoker.a ../XitLib/dist/Release_Linux/GNU-Linux/libxitlib.a ../CoAP/dist/Release/None-Linux/libcoap.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/iot_server_linux

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/iot_server_linux: ../EEG_Evoker/dist/Release/MinGW-Linux/libeeg_evoker.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/iot_server_linux: ../XitLib/dist/Release_Linux/GNU-Linux/libxitlib.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/iot_server_linux: ../CoAP/dist/Release/None-Linux/libcoap.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/iot_server_linux: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/iot_server_linux ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/8209c8dc/ExtFunctions.o: ../../../Downloads/ExtFunctions.c
	${MKDIR} -p ${OBJECTDIR}/_ext/8209c8dc
	${RM} "$@.d"
	$(COMPILE.c) -O2 -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/8209c8dc/ExtFunctions.o ../../../Downloads/ExtFunctions.c

${OBJECTDIR}/main.o: main.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.c

# Subprojects
.build-subprojects:
	cd ../EEG_Evoker && ${MAKE}  -f Makefile CONF=Release
	cd ../XitLib && ${MAKE}  -f Makefile CONF=Release_Linux
	cd ../CoAP && ${MAKE}  -f Makefile CONF=Release
	cd ../EEG_Evoker && ${MAKE}  -f Makefile CONF=Release
	cd ../XitLib && ${MAKE}  -f Makefile CONF=Release_Linux
	cd ../CoAP && ${MAKE}  -f Makefile CONF=Release

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:
	cd ../EEG_Evoker && ${MAKE}  -f Makefile CONF=Release clean
	cd ../XitLib && ${MAKE}  -f Makefile CONF=Release_Linux clean
	cd ../CoAP && ${MAKE}  -f Makefile CONF=Release clean
	cd ../EEG_Evoker && ${MAKE}  -f Makefile CONF=Release clean
	cd ../XitLib && ${MAKE}  -f Makefile CONF=Release_Linux clean
	cd ../CoAP && ${MAKE}  -f Makefile CONF=Release clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
