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
CND_PLATFORM=GNU-Linux-x86
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
	${OBJECTDIR}/config/MPIGameConfig.o \
	${OBJECTDIR}/config/Utils.o \
	${OBJECTDIR}/control/GameLoop.o \
	${OBJECTDIR}/control/MPIControl.o \
	${OBJECTDIR}/control/MPIGameMain.o \
	${OBJECTDIR}/model/Action.o \
	${OBJECTDIR}/model/Character.o \
	${OBJECTDIR}/model/Facing.o \
	${OBJECTDIR}/model/Movement.o \
	${OBJECTDIR}/model/NPC.o \
	${OBJECTDIR}/model/Player.o \
	${OBJECTDIR}/model/Position.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mpi-game

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mpi-game: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mpi-game ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/config/MPIGameConfig.o: config/MPIGameConfig.cpp 
	${MKDIR} -p ${OBJECTDIR}/config
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/config/MPIGameConfig.o config/MPIGameConfig.cpp

${OBJECTDIR}/config/Utils.o: config/Utils.cpp 
	${MKDIR} -p ${OBJECTDIR}/config
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/config/Utils.o config/Utils.cpp

${OBJECTDIR}/control/GameLoop.o: control/GameLoop.cpp 
	${MKDIR} -p ${OBJECTDIR}/control
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/control/GameLoop.o control/GameLoop.cpp

${OBJECTDIR}/control/MPIControl.o: control/MPIControl.cpp 
	${MKDIR} -p ${OBJECTDIR}/control
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/control/MPIControl.o control/MPIControl.cpp

${OBJECTDIR}/control/MPIGameMain.o: control/MPIGameMain.cpp 
	${MKDIR} -p ${OBJECTDIR}/control
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/control/MPIGameMain.o control/MPIGameMain.cpp

${OBJECTDIR}/model/Action.o: model/Action.cpp 
	${MKDIR} -p ${OBJECTDIR}/model
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/model/Action.o model/Action.cpp

${OBJECTDIR}/model/Character.o: model/Character.cpp 
	${MKDIR} -p ${OBJECTDIR}/model
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/model/Character.o model/Character.cpp

${OBJECTDIR}/model/Facing.o: model/Facing.cpp 
	${MKDIR} -p ${OBJECTDIR}/model
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/model/Facing.o model/Facing.cpp

${OBJECTDIR}/model/Movement.o: model/Movement.cpp 
	${MKDIR} -p ${OBJECTDIR}/model
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/model/Movement.o model/Movement.cpp

${OBJECTDIR}/model/NPC.o: model/NPC.cpp 
	${MKDIR} -p ${OBJECTDIR}/model
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/model/NPC.o model/NPC.cpp

${OBJECTDIR}/model/Player.o: model/Player.cpp 
	${MKDIR} -p ${OBJECTDIR}/model
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/model/Player.o model/Player.cpp

${OBJECTDIR}/model/Position.o: model/Position.cpp 
	${MKDIR} -p ${OBJECTDIR}/model
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/model/Position.o model/Position.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mpi-game

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
