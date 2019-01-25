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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/RamosClock_firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/RamosClock_firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/RamosClock_firmware.o ${OBJECTDIR}/Ramos_Sys/Ramos_sys.o ${OBJECTDIR}/Ramos_Sys/LED_display.o ${OBJECTDIR}/Ramos_Sys/RTC.o ${OBJECTDIR}/Ramos_Sys/CC1101_slave.o ${OBJECTDIR}/Ramos_Sys/EEPROM.o ${OBJECTDIR}/Ramos_Sys/Sound.o ${OBJECTDIR}/HandleUserInput.o ${OBJECTDIR}/options.o ${OBJECTDIR}/Display.o ${OBJECTDIR}/_ext/1204784320/RAWRPI.o ${OBJECTDIR}/HandleStateChanges.o
POSSIBLE_DEPFILES=${OBJECTDIR}/RamosClock_firmware.o.d ${OBJECTDIR}/Ramos_Sys/Ramos_sys.o.d ${OBJECTDIR}/Ramos_Sys/LED_display.o.d ${OBJECTDIR}/Ramos_Sys/RTC.o.d ${OBJECTDIR}/Ramos_Sys/CC1101_slave.o.d ${OBJECTDIR}/Ramos_Sys/EEPROM.o.d ${OBJECTDIR}/Ramos_Sys/Sound.o.d ${OBJECTDIR}/HandleUserInput.o.d ${OBJECTDIR}/options.o.d ${OBJECTDIR}/Display.o.d ${OBJECTDIR}/_ext/1204784320/RAWRPI.o.d ${OBJECTDIR}/HandleStateChanges.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/RamosClock_firmware.o ${OBJECTDIR}/Ramos_Sys/Ramos_sys.o ${OBJECTDIR}/Ramos_Sys/LED_display.o ${OBJECTDIR}/Ramos_Sys/RTC.o ${OBJECTDIR}/Ramos_Sys/CC1101_slave.o ${OBJECTDIR}/Ramos_Sys/EEPROM.o ${OBJECTDIR}/Ramos_Sys/Sound.o ${OBJECTDIR}/HandleUserInput.o ${OBJECTDIR}/options.o ${OBJECTDIR}/Display.o ${OBJECTDIR}/_ext/1204784320/RAWRPI.o ${OBJECTDIR}/HandleStateChanges.o


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

# The following macros may be used in the pre and post step lines
Device=PIC18F45K20
ProjectDir="C:\DataRoom\Ramos\Code\RamosClock_firmware.X"
ConfName=default
ImagePath="dist\default\${IMAGE_TYPE}\RamosClock_firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ImageDir="dist\default\${IMAGE_TYPE}"
ImageName="RamosClock_firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"

.build-conf:  .pre ${BUILD_SUBPROJECTS}
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/RamosClock_firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
${OBJECTDIR}/RamosClock_firmware.o: RamosClock_firmware.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/RamosClock_firmware.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X" -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X/Ramos_Sys" -I"C:/DataRoom/Ramos/Code/Defuse_Panel.X"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/RamosClock_firmware.o   RamosClock_firmware.c 
	@${DEP_GEN} -d ${OBJECTDIR}/RamosClock_firmware.o 
	
${OBJECTDIR}/Ramos_Sys/Ramos_sys.o: Ramos_Sys/Ramos_sys.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Ramos_Sys 
	@${RM} ${OBJECTDIR}/Ramos_Sys/Ramos_sys.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X" -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X/Ramos_Sys" -I"C:/DataRoom/Ramos/Code/Defuse_Panel.X"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Ramos_Sys/Ramos_sys.o   Ramos_Sys/Ramos_sys.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Ramos_Sys/Ramos_sys.o 
	
${OBJECTDIR}/Ramos_Sys/LED_display.o: Ramos_Sys/LED_display.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Ramos_Sys 
	@${RM} ${OBJECTDIR}/Ramos_Sys/LED_display.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X" -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X/Ramos_Sys" -I"C:/DataRoom/Ramos/Code/Defuse_Panel.X"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Ramos_Sys/LED_display.o   Ramos_Sys/LED_display.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Ramos_Sys/LED_display.o 
	
${OBJECTDIR}/Ramos_Sys/RTC.o: Ramos_Sys/RTC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Ramos_Sys 
	@${RM} ${OBJECTDIR}/Ramos_Sys/RTC.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X" -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X/Ramos_Sys" -I"C:/DataRoom/Ramos/Code/Defuse_Panel.X"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Ramos_Sys/RTC.o   Ramos_Sys/RTC.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Ramos_Sys/RTC.o 
	
${OBJECTDIR}/Ramos_Sys/CC1101_slave.o: Ramos_Sys/CC1101_slave.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Ramos_Sys 
	@${RM} ${OBJECTDIR}/Ramos_Sys/CC1101_slave.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X" -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X/Ramos_Sys" -I"C:/DataRoom/Ramos/Code/Defuse_Panel.X"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Ramos_Sys/CC1101_slave.o   Ramos_Sys/CC1101_slave.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Ramos_Sys/CC1101_slave.o 
	
${OBJECTDIR}/Ramos_Sys/EEPROM.o: Ramos_Sys/EEPROM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Ramos_Sys 
	@${RM} ${OBJECTDIR}/Ramos_Sys/EEPROM.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X" -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X/Ramos_Sys" -I"C:/DataRoom/Ramos/Code/Defuse_Panel.X"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Ramos_Sys/EEPROM.o   Ramos_Sys/EEPROM.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Ramos_Sys/EEPROM.o 
	
${OBJECTDIR}/Ramos_Sys/Sound.o: Ramos_Sys/Sound.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Ramos_Sys 
	@${RM} ${OBJECTDIR}/Ramos_Sys/Sound.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X" -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X/Ramos_Sys" -I"C:/DataRoom/Ramos/Code/Defuse_Panel.X"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Ramos_Sys/Sound.o   Ramos_Sys/Sound.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Ramos_Sys/Sound.o 
	
${OBJECTDIR}/HandleUserInput.o: HandleUserInput.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/HandleUserInput.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X" -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X/Ramos_Sys" -I"C:/DataRoom/Ramos/Code/Defuse_Panel.X"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/HandleUserInput.o   HandleUserInput.c 
	@${DEP_GEN} -d ${OBJECTDIR}/HandleUserInput.o 
	
${OBJECTDIR}/options.o: options.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/options.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X" -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X/Ramos_Sys" -I"C:/DataRoom/Ramos/Code/Defuse_Panel.X"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/options.o   options.c 
	@${DEP_GEN} -d ${OBJECTDIR}/options.o 
	
${OBJECTDIR}/Display.o: Display.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Display.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X" -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X/Ramos_Sys" -I"C:/DataRoom/Ramos/Code/Defuse_Panel.X"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Display.o   Display.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Display.o 
	
${OBJECTDIR}/_ext/1204784320/RAWRPI.o: ../Defuse_Panel.X/RAWRPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1204784320 
	@${RM} ${OBJECTDIR}/_ext/1204784320/RAWRPI.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X" -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X/Ramos_Sys" -I"C:/DataRoom/Ramos/Code/Defuse_Panel.X"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1204784320/RAWRPI.o   ../Defuse_Panel.X/RAWRPI.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1204784320/RAWRPI.o 
	
${OBJECTDIR}/HandleStateChanges.o: HandleStateChanges.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/HandleStateChanges.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X" -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X/Ramos_Sys" -I"C:/DataRoom/Ramos/Code/Defuse_Panel.X"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/HandleStateChanges.o   HandleStateChanges.c 
	@${DEP_GEN} -d ${OBJECTDIR}/HandleStateChanges.o 
	
else
${OBJECTDIR}/RamosClock_firmware.o: RamosClock_firmware.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/RamosClock_firmware.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X" -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X/Ramos_Sys" -I"C:/DataRoom/Ramos/Code/Defuse_Panel.X"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/RamosClock_firmware.o   RamosClock_firmware.c 
	@${DEP_GEN} -d ${OBJECTDIR}/RamosClock_firmware.o 
	
${OBJECTDIR}/Ramos_Sys/Ramos_sys.o: Ramos_Sys/Ramos_sys.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Ramos_Sys 
	@${RM} ${OBJECTDIR}/Ramos_Sys/Ramos_sys.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X" -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X/Ramos_Sys" -I"C:/DataRoom/Ramos/Code/Defuse_Panel.X"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Ramos_Sys/Ramos_sys.o   Ramos_Sys/Ramos_sys.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Ramos_Sys/Ramos_sys.o 
	
${OBJECTDIR}/Ramos_Sys/LED_display.o: Ramos_Sys/LED_display.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Ramos_Sys 
	@${RM} ${OBJECTDIR}/Ramos_Sys/LED_display.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X" -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X/Ramos_Sys" -I"C:/DataRoom/Ramos/Code/Defuse_Panel.X"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Ramos_Sys/LED_display.o   Ramos_Sys/LED_display.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Ramos_Sys/LED_display.o 
	
${OBJECTDIR}/Ramos_Sys/RTC.o: Ramos_Sys/RTC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Ramos_Sys 
	@${RM} ${OBJECTDIR}/Ramos_Sys/RTC.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X" -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X/Ramos_Sys" -I"C:/DataRoom/Ramos/Code/Defuse_Panel.X"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Ramos_Sys/RTC.o   Ramos_Sys/RTC.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Ramos_Sys/RTC.o 
	
${OBJECTDIR}/Ramos_Sys/CC1101_slave.o: Ramos_Sys/CC1101_slave.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Ramos_Sys 
	@${RM} ${OBJECTDIR}/Ramos_Sys/CC1101_slave.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X" -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X/Ramos_Sys" -I"C:/DataRoom/Ramos/Code/Defuse_Panel.X"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Ramos_Sys/CC1101_slave.o   Ramos_Sys/CC1101_slave.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Ramos_Sys/CC1101_slave.o 
	
${OBJECTDIR}/Ramos_Sys/EEPROM.o: Ramos_Sys/EEPROM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Ramos_Sys 
	@${RM} ${OBJECTDIR}/Ramos_Sys/EEPROM.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X" -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X/Ramos_Sys" -I"C:/DataRoom/Ramos/Code/Defuse_Panel.X"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Ramos_Sys/EEPROM.o   Ramos_Sys/EEPROM.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Ramos_Sys/EEPROM.o 
	
${OBJECTDIR}/Ramos_Sys/Sound.o: Ramos_Sys/Sound.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Ramos_Sys 
	@${RM} ${OBJECTDIR}/Ramos_Sys/Sound.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X" -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X/Ramos_Sys" -I"C:/DataRoom/Ramos/Code/Defuse_Panel.X"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Ramos_Sys/Sound.o   Ramos_Sys/Sound.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Ramos_Sys/Sound.o 
	
${OBJECTDIR}/HandleUserInput.o: HandleUserInput.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/HandleUserInput.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X" -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X/Ramos_Sys" -I"C:/DataRoom/Ramos/Code/Defuse_Panel.X"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/HandleUserInput.o   HandleUserInput.c 
	@${DEP_GEN} -d ${OBJECTDIR}/HandleUserInput.o 
	
${OBJECTDIR}/options.o: options.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/options.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X" -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X/Ramos_Sys" -I"C:/DataRoom/Ramos/Code/Defuse_Panel.X"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/options.o   options.c 
	@${DEP_GEN} -d ${OBJECTDIR}/options.o 
	
${OBJECTDIR}/Display.o: Display.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Display.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X" -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X/Ramos_Sys" -I"C:/DataRoom/Ramos/Code/Defuse_Panel.X"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Display.o   Display.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Display.o 
	
${OBJECTDIR}/_ext/1204784320/RAWRPI.o: ../Defuse_Panel.X/RAWRPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1204784320 
	@${RM} ${OBJECTDIR}/_ext/1204784320/RAWRPI.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X" -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X/Ramos_Sys" -I"C:/DataRoom/Ramos/Code/Defuse_Panel.X"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1204784320/RAWRPI.o   ../Defuse_Panel.X/RAWRPI.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1204784320/RAWRPI.o 
	
${OBJECTDIR}/HandleStateChanges.o: HandleStateChanges.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/HandleStateChanges.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X" -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X/Ramos_Sys" -I"C:/DataRoom/Ramos/Code/Defuse_Panel.X"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/HandleStateChanges.o   HandleStateChanges.c 
	@${DEP_GEN} -d ${OBJECTDIR}/HandleStateChanges.o 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/RamosClock_firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE)   -p$(MP_PROCESSOR_OPTION_LD)  -w -x -u_DEBUG   -z__MPLAB_BUILD=1  -u_CRUNTIME -z__MPLAB_DEBUG=1 -z__MPLAB_DEBUGGER_PK3=1 $(MP_LINKER_DEBUG_OPTION) -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/RamosClock_firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
else
dist/${CND_CONF}/${IMAGE_TYPE}/RamosClock_firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE)   -p$(MP_PROCESSOR_OPTION_LD)  -w    -z__MPLAB_BUILD=1  -u_CRUNTIME -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/RamosClock_firmware.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
endif

.pre:
	@echo "--------------------------------------"
	@echo "User defined pre-build step: [del /s *.d]"
	@del /s *.d
	@echo "--------------------------------------"

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
