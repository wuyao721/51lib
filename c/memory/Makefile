PRJ_VER := 1.0.0
PRJ_NAME := mem_test_cavium

OCTEON_TARGET=linux_64
ifndef OCTEON_ROOT
OCTEON_ROOT = /usr/local/Cavium_Networks/OCTEON-SDK/
endif

all: application-target

#  standard common Makefile fragment

include $(OCTEON_ROOT)/common.mk
CFLAGS_GLOBAL += -DPRJ_VER="\"${PRJ_VER}\"" -DPRJ_NAME="\"${PRJ_NAME}\""

#  include relevant component Makefile fragments

dir := $(OCTEON_ROOT)/executive
include $(dir)/cvmx.mk

TARGET = $(PRJ_NAME)-$(PRJ_VER)

OBJS   = $(OBJ_DIR)/mem_test_cavium.o
CFLAGS_LOCAL = -g -O2 -W -Wall -Wno-unused
#LDFLAGS_GLOBAL += -L/usr/ntc/src/libpublic -lpublic -pthread -lm

include $(OCTEON_ROOT)/application.mk

clean:
	rm -f $(TARGET) *.log queue-*
	rm -fr $(OBJ_DIR) $(OBJ_DIR)-*
	rm -f $(CVMX_CONFIG)

install:
#	/bin/cp -f $(TARGET) ../release/ntc/bin
	/bin/cp -f $(TARGET) ../release/ntc/bin/$(PRJ_NAME)

tftp:
	/bin/cp -f $(TARGET) /tftpboot/$(PRJ_NAME)
