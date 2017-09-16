# Makefile
# for Maxeler Platform Ver 2013.2.2+
# orogonally based on file from Brittle
# heavily modded by Tim to use common Makefile

PRJ:=PearsonCoefficient
PKG_NAME:=pearsoncoefficient
BOARD_MODEL:= MAX3424A
EXE_NAME:=DefaultApplication
MAIN_CLASS_NAME:=${PRJ}Manager
MAIN_SW_FILE:=${PRJ}CpuCode

# general/shared dirs
INC_DIR:=include
# source dirs for hardware and software
SW_SRC_DIR:=src/C_Code/
HW_SRC_DIR:=src/Maxeler/



# hardware sources
HW_SRC_NAMES:=  mem_block.maxj ${PRJ}Kernel.maxj ${PRJ}Manager.maxj 
HW_SRCS:= $(addprefix ${HW_SRC_DIR}/,${HW_SRC_NAMES})

# software sources
SW_SRC_NAMES:=  ${MAIN_SW_FILE}.cpp 
SW_SRCS:= $(addprefix "${SW_SRC_DIR}"/,${SW_SRC_NAMES})


# objects built by Maxeler tools
HW_OBJS:= slic_${PRJ}.o

# include file defining HW platform
include platform_max3.mk

# include macro defining build commands
include build_max_v2.mk



