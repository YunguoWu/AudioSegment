# Project name

PROJ = libwebrtcvad.so

LIB_DEP :=
LIB_DEP +=

ifeq ($(OS_SUPPORT), 1)
    TARGET = lib$(PROJ).a
else
    TARGET = $(PROJ)
    LIB_DEP += pthread
endif

LIBS = $(addprefix -l, $(LIB_DEP))

TOPDIR 	?= $(shell pwd)/..

# Flags

INCLUDE    =	-I. \
		-I../../include_inner \
		-I../../include \
		-I../../src/include \
		-I../include \

#Locations

SRCDIR += .
SRCDIR += ./webrtc/common_audio/vad/
SRCDIR += ./webrtc/common_audio/signal_processing

CSRCS += $(foreach d, $(SRCDIR), $(wildcard $d/*.c))

COBJS += $(patsubst %.c, %.o, $(CSRCS))

LIB_DIR = $(TOPDIR)/lib

LD_FLAGS = -Xlinker "-(" $(LIBS) -Xlinker "-)" -L$(LIB_DIR)

#build rule
.PHONY: all target install clean

all: $(COBJS)
ifeq ($(OS_SUPPORT), 1)
	$(AR) -rsv $(TARGET) $(COBJS)
	@cp -r $(TARGET) $(TOPDIR)/lib
else
	$(CC) $(COBJS) $(LD_FLAGS) -shared -o $(TARGET)
endif

install:
	@cp -f $(TARGET) $(OUTFS_BIN_DIR)

clean : 
	$(RM) $(COBJS) $(TARGET)


# Rules
include $(TOPDIR)/rules.mk
