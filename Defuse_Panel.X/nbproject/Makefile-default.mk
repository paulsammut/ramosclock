#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=cof
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Defuse_Panel.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Defuse_Panel.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/defusePanel_sys.o ${OBJECTDIR}/defusePanel_main.o ${OBJECTDIR}/keypad.o ${OBJECTDIR}/EEPROM.o ${OBJECTDIR}/lightPlay.o ${OBJECTDIR}/CC1101_master.o ${OBJECTDIR}/RAWRPI.o
POSSIBLE_DEPFILES=${OBJECTDIR}/defusePanel_sys.o.d ${OBJECTDIR}/defusePanel_main.o.d ${OBJECTDIR}/keypad.o.d ${OBJECTDIR}/EEPROM.o.d ${OBJECTDIR}/lightPlay.o.d ${OBJECTDIR}/CC1101_master.o.d ${OBJECTDIR}/RAWRPI.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/defusePanel_sys.o ${OBJECTDIR}/defusePanel_main.o ${OBJECTDIR}/keypad.o ${OBJECTDIR}/EEPROM.o ${OBJECTDIR}/lightPlay.o ${OBJECTDIR}/CC1101_master.o ${OBJECTDIR}/RAWRPI.o


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Defuse_Panel.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F45K20
MP_PROCESSOR_OPTION_LD=18f45k20
MP_LINKER_DEBUG_OPTION= -u_DEBUGCODESTART=0x7dc0 -u_DEBUGCODELEN=0x240 -u_DEBUGDATASTART=0x5f4 -u_DEBUGDATALEN=0xb
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/defusePanel_sys.o: defusePanel_sys.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/defusePanel_sys.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/defusePanel_sys.o   defusePanel_sys.c 
	@${DEP_GEN} -d ${OBJECTDIR}/defusePanel_sys.o 
	
${OBJECTDIR}/defusePanel_main.o: defusePanel_main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/defusePanel_main.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/defusePanel_main.o   defusePanel_main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/defusePanel_main.o 
	
${OBJECTDIR}/keypad.o: keypad.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/keypad.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/keypad.o   keypad.c 
	@${DEP_GEN} -d ${OBJECTDIR}/keypad.o 
	
${OBJECTDIR}/EEPROM.o: EEPROM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/EEPROM.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/EEPROM.o   EEPROM.c 
	@${DEP_GEN} -d ${OBJECTDIR}/EEPROM.o 
	
${OBJECTDIR}/lightPlay.o: lightPlay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/lightPlay.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/lightPlay.o   lightPlay.c 
	@${DEP_GEN} -d ${OBJECTDIR}/lightPlay.o 
	
${OBJECTDIR}/CC1101_master.o: CC1101_master.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/CC1101_master.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/CC1101_master.o   CC1101_master.c 
	@${DEP_GEN} -d ${OBJECTDIR}/CC1101_master.o 
	
${OBJECTDIR}/RAWRPI.o: RAWRPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/RAWRPI.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/RAWRPI.o   RAWRPI.c 
	@${DEP_GEN} -d ${OBJECTDIR}/RAWRPI.o 
	
else
${OBJECTDIR}/defusePanel_sys.o: defusePanel_sys.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/defusePanel_sys.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/defusePanel_sys.o   defusePanel_sys.c 
	@${DEP_GEN} -d ${OBJECTDIR}/defusePanel_sys.o 
	
${OBJECTDIR}/defusePanel_main.o: defusePanel_main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/defusePanel_main.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/defusePanel_main.o   defusePanel_main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/defusePanel_main.o 
	
${OBJECTDIR}/keypad.o: keypad.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/keypad.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/keypad.o   keypad.c 
	@${DEP_GEN} -d ${OBJECTDIR}/keypad.o 
	
${OBJECTDIR}/EEPROM.o: EEPROM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/EEPROM.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/EEPROM.o   EEPROM.c 
	@${DEP_GEN} -d ${OBJECTDIR}/EEPROM.o 
	
${OBJECTDIR}/lightPlay.o: lightPlay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/lightPlay.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/lightPlay.o   lightPlay.c 
	@${DEP_GEN} -d ${OBJECTDIR}/lightPlay.o 
	
${OBJECTDIR}/CC1101_master.o: CC1101_master.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/CC1101_master.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/CC1101_master.o   CC1101_master.c 
	@${DEP_GEN} -d ${OBJECTDIR}/CC1101_master.o 
	
${OBJECTDIR}/RAWRPI.o: RAWRPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/RAWRPI.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION)   -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/RAWRPI.o   RAWRPI.c 
	@${DEP_GEN} -d ${OBJECTDIR}/RAWRPI.o 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Defuse_Panel.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE)   -p$(MP_PROCESSOR_OPTION_LD)  -w -x -u_DEBUG   -z__MPLAB_BUILD=1  -u_CRUNTIME -z__MPLAB_DEBUG=1 -z__MPLAB_DEBUGGER_PK3=1 $(MP_LINKER_DEBUG_OPTION) -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/Defuse_Panel.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
else
dist/${CND_CONF}/${IMAGE_TYPE}/Defuse_Panel.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE)   -p$(MP_PROCESSOR_OPTION_LD)  -w    -z__MPLAB_BUILD=1  -u_CRUNTIME -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/Defuse_Panel.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
