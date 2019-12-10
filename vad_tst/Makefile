# Project name

PROJ = vad_tst

LIB_DEP := webrtcvad
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
		-I./include \
		-I../WebrtcVad \

#Locations

SRCDIR += .
SRCDIR += ./src

CSRCS += $(foreach d, $(SRCDIR), $(wildcard $d/*.cc))

COBJS += $(patsubst %.cc, %.o, $(CSRCS))

LIB_DIR = $(TOPDIR)/WebrtcVad

LD_FLAGS = -Xlinker "-(" $(LIBS) -Xlinker "-)" -L$(LIB_DIR)

#build rule
.PHONY: all target install clean

##$(warning ==$(COBJS))

all: $(COBJS)
ifeq ($(OS_SUPPORT), 1)
	$(AR) -rsv $(TARGET) $(COBJS)
	@cp -r $(TARGET) $(TOPDIR)/WebrtcVad
else
	$(CXX) $(COBJS) $(LD_FLAGS) -o $(TARGET)
endif

install:
	@cp -f $(TARGET) $(OUTFS_BIN_DIR)

clean : 
	$(RM) $(COBJS) $(TARGET)


# Rules
include $(TOPDIR)/rules.mk
