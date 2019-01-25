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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Nixie_Ramos.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Nixie_Ramos.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/Nixie_main.o ${OBJECTDIR}/_ext/359309802/RTC.o ${OBJECTDIR}/_ext/359309802/CC1101_slave.o ${OBJECTDIR}/_ext/359309802/Ramos_sys.o ${OBJECTDIR}/_ext/359309802/Sound.o ${OBJECTDIR}/_ext/1204784320/RAWRPI.o ${OBJECTDIR}/Nixie_display.o ${OBJECTDIR}/_ext/2048639273/Display.o ${OBJECTDIR}/_ext/2048639273/HandleStateChanges.o ${OBJECTDIR}/_ext/2048639273/HandleUserInput.o ${OBJECTDIR}/_ext/2048639273/options.o ${OBJECTDIR}/_ext/359309802/EEPROM.o
POSSIBLE_DEPFILES=${OBJECTDIR}/Nixie_main.o.d ${OBJECTDIR}/_ext/359309802/RTC.o.d ${OBJECTDIR}/_ext/359309802/CC1101_slave.o.d ${OBJECTDIR}/_ext/359309802/Ramos_sys.o.d ${OBJECTDIR}/_ext/359309802/Sound.o.d ${OBJECTDIR}/_ext/1204784320/RAWRPI.o.d ${OBJECTDIR}/Nixie_display.o.d ${OBJECTDIR}/_ext/2048639273/Display.o.d ${OBJECTDIR}/_ext/2048639273/HandleStateChanges.o.d ${OBJECTDIR}/_ext/2048639273/HandleUserInput.o.d ${OBJECTDIR}/_ext/2048639273/options.o.d ${OBJECTDIR}/_ext/359309802/EEPROM.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/Nixie_main.o ${OBJECTDIR}/_ext/359309802/RTC.o ${OBJECTDIR}/_ext/359309802/CC1101_slave.o ${OBJECTDIR}/_ext/359309802/Ramos_sys.o ${OBJECTDIR}/_ext/359309802/Sound.o ${OBJECTDIR}/_ext/1204784320/RAWRPI.o ${OBJECTDIR}/Nixie_display.o ${OBJECTDIR}/_ext/2048639273/Display.o ${OBJECTDIR}/_ext/2048639273/HandleStateChanges.o ${OBJECTDIR}/_ext/2048639273/HandleUserInput.o ${OBJECTDIR}/_ext/2048639273/options.o ${OBJECTDIR}/_ext/359309802/EEPROM.o


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
ProjectDir="C:\DataRoom\Ramos\Code\Nixie Ramos.X"
ConfName=default
ImagePath="dist\default\${IMAGE_TYPE}\Nixie_Ramos.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ImageDir="dist\default\${IMAGE_TYPE}"
ImageName="Nixie_Ramos.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"

.build-conf:  .pre ${BUILD_SUBPROJECTS}
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Nixie_Ramos.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
${OBJECTDIR}/Nixie_main.o: Nixie_main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Nixie_main.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X" -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X/Ramos_Sys" -I"C:/DataRoom/Ramos/Code/Defuse_Panel.X"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Nixie_main.o   Nixie_main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Nixie_main.o 
	
${OBJECTDIR}/_ext/359309802/RTC.o: ../RamosClock_firmware.X/Ramos_Sys/RTC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/359309802 
	@${RM} ${OBJECTDIR}/_ext/359309802/RTC.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X" -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X/Ramos_Sys" -I"C:/DataRoom/Ramos/Code/Defuse_Panel.X"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/359309802/RTC.o   ../RamosClock_firmware.X/Ramos_Sys/RTC.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/359309802/RTC.o 
	
${OBJECTDIR}/_ext/359309802/CC1101_slave.o: ../RamosClock_firmware.X/Ramos_Sys/CC1101_slave.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/359309802 
	@${RM} ${OBJECTDIR}/_ext/359309802/CC1101_slave.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X" -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X/Ramos_Sys" -I"C:/DataRoom/Ramos/Code/Defuse_Panel.X"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/359309802/CC1101_slave.o   ../RamosClock_firmware.X/Ramos_Sys/CC1101_slave.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/359309802/CC1101_slave.o 
	
${OBJECTDIR}/_ext/359309802/Ramos_sys.o: ../RamosClock_firmware.X/Ramos_Sys/Ramos_sys.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/359309802 
	@${RM} ${OBJECTDIR}/_ext/359309802/Ramos_sys.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X" -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X/Ramos_Sys" -I"C:/DataRoom/Ramos/Code/Defuse_Panel.X"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/359309802/Ramos_sys.o   ../RamosClock_firmware.X/Ramos_Sys/Ramos_sys.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/359309802/Ramos_sys.o 
	
${OBJECTDIR}/_ext/359309802/Sound.o: ../RamosClock_firmware.X/Ramos_Sys/Sound.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/359309802 
	@${RM} ${OBJECTDIR}/_ext/359309802/Sound.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X" -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X/Ramos_Sys" -I"C:/DataRoom/Ramos/Code/Defuse_Panel.X"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/359309802/Sound.o   ../RamosClock_firmware.X/Ramos_Sys/Sound.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/359309802/Sound.o 
	
${OBJECTDIR}/_ext/1204784320/RAWRPI.o: ../Defuse_Panel.X/RAWRPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1204784320 
	@${RM} ${OBJECTDIR}/_ext/1204784320/RAWRPI.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X" -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X/Ramos_Sys" -I"C:/DataRoom/Ramos/Code/Defuse_Panel.X"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1204784320/RAWRPI.o   ../Defuse_Panel.X/RAWRPI.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1204784320/RAWRPI.o 
	
${OBJECTDIR}/Nixie_display.o: Nixie_display.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Nixie_display.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X" -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X/Ramos_Sys" -I"C:/DataRoom/Ramos/Code/Defuse_Panel.X"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Nixie_display.o   Nixie_display.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Nixie_display.o 
	
${OBJECTDIR}/_ext/2048639273/Display.o: ../RamosClock_firmware.X/Display.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2048639273 
	@${RM} ${OBJECTDIR}/_ext/2048639273/Display.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X" -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X/Ramos_Sys" -I"C:/DataRoom/Ramos/Code/Defuse_Panel.X"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/2048639273/Display.o   ../RamosClock_firmware.X/Display.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/2048639273/Display.o 
	
${OBJECTDIR}/_ext/2048639273/HandleStateChanges.o: ../RamosClock_firmware.X/HandleStateChanges.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2048639273 
	@${RM} ${OBJECTDIR}/_ext/2048639273/HandleStateChanges.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X" -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X/Ramos_Sys" -I"C:/DataRoom/Ramos/Code/Defuse_Panel.X"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/2048639273/HandleStateChanges.o   ../RamosClock_firmware.X/HandleStateChanges.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/2048639273/HandleStateChanges.o 
	
${OBJECTDIR}/_ext/2048639273/HandleUserInput.o: ../RamosClock_firmware.X/HandleUserInput.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2048639273 
	@${RM} ${OBJECTDIR}/_ext/2048639273/HandleUserInput.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X" -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X/Ramos_Sys" -I"C:/DataRoom/Ramos/Code/Defuse_Panel.X"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/2048639273/HandleUserInput.o   ../RamosClock_firmware.X/HandleUserInput.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/2048639273/HandleUserInput.o 
	
${OBJECTDIR}/_ext/2048639273/options.o: ../RamosClock_firmware.X/options.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2048639273 
	@${RM} ${OBJECTDIR}/_ext/2048639273/options.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X" -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X/Ramos_Sys" -I"C:/DataRoom/Ramos/Code/Defuse_Panel.X"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/2048639273/options.o   ../RamosClock_firmware.X/options.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/2048639273/options.o 
	
${OBJECTDIR}/_ext/359309802/EEPROM.o: ../RamosClock_firmware.X/Ramos_Sys/EEPROM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/359309802 
	@${RM} ${OBJECTDIR}/_ext/359309802/EEPROM.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X" -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X/Ramos_Sys" -I"C:/DataRoom/Ramos/Code/Defuse_Panel.X"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/359309802/EEPROM.o   ../RamosClock_firmware.X/Ramos_Sys/EEPROM.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/359309802/EEPROM.o 
	
else
${OBJECTDIR}/Nixie_main.o: Nixie_main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Nixie_main.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X" -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X/Ramos_Sys" -I"C:/DataRoom/Ramos/Code/Defuse_Panel.X"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Nixie_main.o   Nixie_main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Nixie_main.o 
	
${OBJECTDIR}/_ext/359309802/RTC.o: ../RamosClock_firmware.X/Ramos_Sys/RTC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/359309802 
	@${RM} ${OBJECTDIR}/_ext/359309802/RTC.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X" -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X/Ramos_Sys" -I"C:/DataRoom/Ramos/Code/Defuse_Panel.X"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/359309802/RTC.o   ../RamosClock_firmware.X/Ramos_Sys/RTC.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/359309802/RTC.o 
	
${OBJECTDIR}/_ext/359309802/CC1101_slave.o: ../RamosClock_firmware.X/Ramos_Sys/CC1101_slave.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/359309802 
	@${RM} ${OBJECTDIR}/_ext/359309802/CC1101_slave.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X" -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X/Ramos_Sys" -I"C:/DataRoom/Ramos/Code/Defuse_Panel.X"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/359309802/CC1101_slave.o   ../RamosClock_firmware.X/Ramos_Sys/CC1101_slave.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/359309802/CC1101_slave.o 
	
${OBJECTDIR}/_ext/359309802/Ramos_sys.o: ../RamosClock_firmware.X/Ramos_Sys/Ramos_sys.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/359309802 
	@${RM} ${OBJECTDIR}/_ext/359309802/Ramos_sys.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X" -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X/Ramos_Sys" -I"C:/DataRoom/Ramos/Code/Defuse_Panel.X"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/359309802/Ramos_sys.o   ../RamosClock_firmware.X/Ramos_Sys/Ramos_sys.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/359309802/Ramos_sys.o 
	
${OBJECTDIR}/_ext/359309802/Sound.o: ../RamosClock_firmware.X/Ramos_Sys/Sound.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/359309802 
	@${RM} ${OBJECTDIR}/_ext/359309802/Sound.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X" -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X/Ramos_Sys" -I"C:/DataRoom/Ramos/Code/Defuse_Panel.X"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/359309802/Sound.o   ../RamosClock_firmware.X/Ramos_Sys/Sound.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/359309802/Sound.o 
	
${OBJECTDIR}/_ext/1204784320/RAWRPI.o: ../Defuse_Panel.X/RAWRPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1204784320 
	@${RM} ${OBJECTDIR}/_ext/1204784320/RAWRPI.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X" -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X/Ramos_Sys" -I"C:/DataRoom/Ramos/Code/Defuse_Panel.X"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1204784320/RAWRPI.o   ../Defuse_Panel.X/RAWRPI.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1204784320/RAWRPI.o 
	
${OBJECTDIR}/Nixie_display.o: Nixie_display.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Nixie_display.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X" -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X/Ramos_Sys" -I"C:/DataRoom/Ramos/Code/Defuse_Panel.X"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Nixie_display.o   Nixie_display.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Nixie_display.o 
	
${OBJECTDIR}/_ext/2048639273/Display.o: ../RamosClock_firmware.X/Display.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2048639273 
	@${RM} ${OBJECTDIR}/_ext/2048639273/Display.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X" -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X/Ramos_Sys" -I"C:/DataRoom/Ramos/Code/Defuse_Panel.X"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/2048639273/Display.o   ../RamosClock_firmware.X/Display.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/2048639273/Display.o 
	
${OBJECTDIR}/_ext/2048639273/HandleStateChanges.o: ../RamosClock_firmware.X/HandleStateChanges.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2048639273 
	@${RM} ${OBJECTDIR}/_ext/2048639273/HandleStateChanges.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X" -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X/Ramos_Sys" -I"C:/DataRoom/Ramos/Code/Defuse_Panel.X"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/2048639273/HandleStateChanges.o   ../RamosClock_firmware.X/HandleStateChanges.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/2048639273/HandleStateChanges.o 
	
${OBJECTDIR}/_ext/2048639273/HandleUserInput.o: ../RamosClock_firmware.X/HandleUserInput.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2048639273 
	@${RM} ${OBJECTDIR}/_ext/2048639273/HandleUserInput.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X" -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X/Ramos_Sys" -I"C:/DataRoom/Ramos/Code/Defuse_Panel.X"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/2048639273/HandleUserInput.o   ../RamosClock_firmware.X/HandleUserInput.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/2048639273/HandleUserInput.o 
	
${OBJECTDIR}/_ext/2048639273/options.o: ../RamosClock_firmware.X/options.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2048639273 
	@${RM} ${OBJECTDIR}/_ext/2048639273/options.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X" -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X/Ramos_Sys" -I"C:/DataRoom/Ramos/Code/Defuse_Panel.X"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/2048639273/options.o   ../RamosClock_firmware.X/options.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/2048639273/options.o 
	
${OBJECTDIR}/_ext/359309802/EEPROM.o: ../RamosClock_firmware.X/Ramos_Sys/EEPROM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/359309802 
	@${RM} ${OBJECTDIR}/_ext/359309802/EEPROM.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X" -I"C:/DataRoom/Ramos/Code/RamosClock_firmware.X/Ramos_Sys" -I"C:/DataRoom/Ramos/Code/Defuse_Panel.X"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/359309802/EEPROM.o   ../RamosClock_firmware.X/Ramos_Sys/EEPROM.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/359309802/EEPROM.o 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Nixie_Ramos.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE)   -p$(MP_PROCESSOR_OPTION_LD)  -w -x -u_DEBUG   -z__MPLAB_BUILD=1  -u_CRUNTIME -z__MPLAB_DEBUG=1 -z__MPLAB_DEBUGGER_PK3=1 $(MP_LINKER_DEBUG_OPTION) -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/Nixie_Ramos.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
else
dist/${CND_CONF}/${IMAGE_TYPE}/Nixie_Ramos.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE)   -p$(MP_PROCESSOR_OPTION_LD)  -w    -z__MPLAB_BUILD=1  -u_CRUNTIME -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/Nixie_Ramos.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
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
