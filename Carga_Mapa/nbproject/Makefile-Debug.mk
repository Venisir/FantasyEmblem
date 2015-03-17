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
	${OBJECTDIR}/main.o \
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
LDLIBSOPTIONS=/C/Users/Ricardo/Dropbox/SFML-2.1/lib/libsfml-graphics-d.a /C/Users/Ricardo/Dropbox/SFML-2.1/lib/libsfml-graphics.a /C/Users/Ricardo/Dropbox/SFML-2.1/lib/libsfml-window-d.a /C/Users/Ricardo/Dropbox/SFML-2.1/lib/libsfml-window.a /C/Users/Ricardo/Dropbox/SFML-2.1/lib/libsfml-system-d.a /C/Users/Ricardo/Dropbox/SFML-2.1/lib/libsfml-system.a /C/Users/Ricardo/Dropbox/SFML-2.1/lib/libsfml-audio-d.a /C/Users/Ricardo/Dropbox/SFML-2.1/lib/libsfml-audio.a /C/Users/Ricardo/Dropbox/SFML-2.1/lib/libsfml-network-d.a /C/Users/Ricardo/Dropbox/SFML-2.1/lib/libsfml-network.a /C/Users/Ricardo/Dropbox/SFML-2.1/lib/libsfml-main-d.a /C/Users/Ricardo/Dropbox/SFML-2.1/lib/libsfml-main.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/plantilla.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/plantilla.exe: /C/Users/Ricardo/Dropbox/SFML-2.1/lib/libsfml-graphics-d.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/plantilla.exe: /C/Users/Ricardo/Dropbox/SFML-2.1/lib/libsfml-graphics.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/plantilla.exe: /C/Users/Ricardo/Dropbox/SFML-2.1/lib/libsfml-window-d.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/plantilla.exe: /C/Users/Ricardo/Dropbox/SFML-2.1/lib/libsfml-window.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/plantilla.exe: /C/Users/Ricardo/Dropbox/SFML-2.1/lib/libsfml-system-d.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/plantilla.exe: /C/Users/Ricardo/Dropbox/SFML-2.1/lib/libsfml-system.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/plantilla.exe: /C/Users/Ricardo/Dropbox/SFML-2.1/lib/libsfml-audio-d.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/plantilla.exe: /C/Users/Ricardo/Dropbox/SFML-2.1/lib/libsfml-audio.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/plantilla.exe: /C/Users/Ricardo/Dropbox/SFML-2.1/lib/libsfml-network-d.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/plantilla.exe: /C/Users/Ricardo/Dropbox/SFML-2.1/lib/libsfml-network.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/plantilla.exe: /C/Users/Ricardo/Dropbox/SFML-2.1/lib/libsfml-main-d.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/plantilla.exe: /C/Users/Ricardo/Dropbox/SFML-2.1/lib/libsfml-main.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/plantilla.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/plantilla ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/Users/Ricardo/Dropbox/SFML-2.1/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/tinyxml2.o: tinyxml2.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/Users/Ricardo/Dropbox/SFML-2.1/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tinyxml2.o tinyxml2.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/plantilla.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
