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
	${OBJECTDIR}/json/cJSON.o \
	${OBJECTDIR}/json/cJSON_Utils.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/malloc/umm_malloc.o \
	${OBJECTDIR}/models/src/array.o \
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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/structures.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/structures.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/structures ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/json/cJSON.o: json/cJSON.c
	${MKDIR} -p ${OBJECTDIR}/json
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/json/cJSON.o json/cJSON.c

${OBJECTDIR}/json/cJSON_Utils.o: json/cJSON_Utils.c
	${MKDIR} -p ${OBJECTDIR}/json
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/json/cJSON_Utils.o json/cJSON_Utils.c

${OBJECTDIR}/main.o: main.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.c

${OBJECTDIR}/malloc/umm_malloc.o: malloc/umm_malloc.c
	${MKDIR} -p ${OBJECTDIR}/malloc
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/malloc/umm_malloc.o malloc/umm_malloc.c

${OBJECTDIR}/models/src/array.o: models/src/array.c
	${MKDIR} -p ${OBJECTDIR}/models/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/models/src/array.o models/src/array.c

${OBJECTDIR}/models/src/common.o: models/src/common.c
	${MKDIR} -p ${OBJECTDIR}/models/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/models/src/common.o models/src/common.c

${OBJECTDIR}/models/src/deque.o: models/src/deque.c
	${MKDIR} -p ${OBJECTDIR}/models/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/models/src/deque.o models/src/deque.c

${OBJECTDIR}/models/src/hashset.o: models/src/hashset.c
	${MKDIR} -p ${OBJECTDIR}/models/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/models/src/hashset.o models/src/hashset.c

${OBJECTDIR}/models/src/hashtable.o: models/src/hashtable.c
	${MKDIR} -p ${OBJECTDIR}/models/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/models/src/hashtable.o models/src/hashtable.c

${OBJECTDIR}/models/src/list.o: models/src/list.c
	${MKDIR} -p ${OBJECTDIR}/models/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/models/src/list.o models/src/list.c

${OBJECTDIR}/models/src/queue.o: models/src/queue.c
	${MKDIR} -p ${OBJECTDIR}/models/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/models/src/queue.o models/src/queue.c

${OBJECTDIR}/models/src/slist.o: models/src/slist.c
	${MKDIR} -p ${OBJECTDIR}/models/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/models/src/slist.o models/src/slist.c

${OBJECTDIR}/models/src/stack.o: models/src/stack.c
	${MKDIR} -p ${OBJECTDIR}/models/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/models/src/stack.o models/src/stack.c

${OBJECTDIR}/models/src/treeset.o: models/src/treeset.c
	${MKDIR} -p ${OBJECTDIR}/models/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/models/src/treeset.o models/src/treeset.c

${OBJECTDIR}/models/src/treetable.o: models/src/treetable.c
	${MKDIR} -p ${OBJECTDIR}/models/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/models/src/treetable.o models/src/treetable.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
