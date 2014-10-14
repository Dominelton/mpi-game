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
CCC=mpicxx
CXX=mpicxx
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/control/GameLoop.o \
	${OBJECTDIR}/control/mpiGameMain.o \
	${OBJECTDIR}/model/NPC.o \
	${OBJECTDIR}/model/Personagem.o \
	${OBJECTDIR}/model/Player.o \
	${OBJECTDIR}/model/Posicao.o


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
LDLIBSOPTIONS=-L../../mpich_install/lib

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mpi-game

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mpi-game: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	mpicxx -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mpi-game ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/control/GameLoop.o: control/GameLoop.cpp 
	${MKDIR} -p ${OBJECTDIR}/control
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../mpich_install/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/control/GameLoop.o control/GameLoop.cpp

${OBJECTDIR}/control/mpiGameMain.o: control/mpiGameMain.cpp 
	${MKDIR} -p ${OBJECTDIR}/control
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../mpich_install/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/control/mpiGameMain.o control/mpiGameMain.cpp

${OBJECTDIR}/model/NPC.o: model/NPC.cpp 
	${MKDIR} -p ${OBJECTDIR}/model
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../mpich_install/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/model/NPC.o model/NPC.cpp

${OBJECTDIR}/model/Personagem.o: model/Personagem.cpp 
	${MKDIR} -p ${OBJECTDIR}/model
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../mpich_install/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/model/Personagem.o model/Personagem.cpp

${OBJECTDIR}/model/Player.o: model/Player.cpp 
	${MKDIR} -p ${OBJECTDIR}/model
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../mpich_install/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/model/Player.o model/Player.cpp

${OBJECTDIR}/model/Posicao.o: model/Posicao.cpp 
	${MKDIR} -p ${OBJECTDIR}/model
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../mpich_install/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/model/Posicao.o model/Posicao.cpp

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
