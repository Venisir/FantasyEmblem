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
	${OBJECTDIR}/clases/Armas.o \
	${OBJECTDIR}/clases/Cursor.o \
	${OBJECTDIR}/clases/Escenario.o \
	${OBJECTDIR}/clases/Estado.o \
	${OBJECTDIR}/clases/EventoMapa.o \
	${OBJECTDIR}/clases/Juego.o \
	${OBJECTDIR}/clases/Mapa.o \
	${OBJECTDIR}/clases/MenuPrincipal.o \
	${OBJECTDIR}/clases/Objetos.o \
	${OBJECTDIR}/clases/Partida.o \
	${OBJECTDIR}/clases/Unidad.o \
	${OBJECTDIR}/clases/main.o \
	${OBJECTDIR}/tinyxml2.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/fantasyemblem.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/fantasyemblem.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/fantasyemblem ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/clases/Armas.o: clases/Armas.cpp 
	${MKDIR} -p ${OBJECTDIR}/clases
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/clases/Armas.o clases/Armas.cpp

${OBJECTDIR}/clases/Cursor.o: clases/Cursor.cpp 
	${MKDIR} -p ${OBJECTDIR}/clases
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/clases/Cursor.o clases/Cursor.cpp

${OBJECTDIR}/clases/Escenario.o: clases/Escenario.cpp 
	${MKDIR} -p ${OBJECTDIR}/clases
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/clases/Escenario.o clases/Escenario.cpp

${OBJECTDIR}/clases/Estado.o: clases/Estado.cpp 
	${MKDIR} -p ${OBJECTDIR}/clases
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/clases/Estado.o clases/Estado.cpp

${OBJECTDIR}/clases/EventoMapa.o: clases/EventoMapa.cpp 
	${MKDIR} -p ${OBJECTDIR}/clases
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/clases/EventoMapa.o clases/EventoMapa.cpp

${OBJECTDIR}/clases/Juego.o: clases/Juego.cpp 
	${MKDIR} -p ${OBJECTDIR}/clases
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/clases/Juego.o clases/Juego.cpp

${OBJECTDIR}/clases/Mapa.o: clases/Mapa.cpp 
	${MKDIR} -p ${OBJECTDIR}/clases
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/clases/Mapa.o clases/Mapa.cpp

${OBJECTDIR}/clases/MenuPrincipal.o: clases/MenuPrincipal.cpp 
	${MKDIR} -p ${OBJECTDIR}/clases
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/clases/MenuPrincipal.o clases/MenuPrincipal.cpp

${OBJECTDIR}/clases/Objetos.o: clases/Objetos.cpp 
	${MKDIR} -p ${OBJECTDIR}/clases
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/clases/Objetos.o clases/Objetos.cpp

${OBJECTDIR}/clases/Partida.o: clases/Partida.cpp 
	${MKDIR} -p ${OBJECTDIR}/clases
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/clases/Partida.o clases/Partida.cpp

${OBJECTDIR}/clases/Unidad.o: clases/Unidad.cpp 
	${MKDIR} -p ${OBJECTDIR}/clases
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/clases/Unidad.o clases/Unidad.cpp

${OBJECTDIR}/clases/main.o: clases/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/clases
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/clases/main.o clases/main.cpp

${OBJECTDIR}/tinyxml2.o: tinyxml2.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tinyxml2.o tinyxml2.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/fantasyemblem.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
