
# Cross Tools and libs

TOOLCHAIN = x86

ifeq ($(TOOLCHAIN), x86)
	CROSS_PATH      ?=
	CROSS_PREFIX    ?=
	CPU_LIBC_PATH	?=/usr/lib/x86_64-linux-gnu/
	CPU_LIBGCC_PATH ?=/usr/lib/gcc/x86_64-linux-gnu/4.8/
else
	CROSS_PATH      ?= /opt/arm-anykav500-crosstool/usr
	CROSS_PREFIX    ?= arm-anykav500-linux-uclibcgnueabi-
	CPU_LIBC_PATH	?=$(CROSS_PATH)/arm-anykav500-linux-uclibcgnueabi/sysroot/usr/lib
	CPU_LIBGCC_PATH ?=$(CROSS_PATH)/lib/gcc/arm-anykav500-linux-uclibcgnueabi/4.8.5
endif

# Tools
CC           = $(CROSS_PREFIX)gcc
CXX          = $(CROSS_PREFIX)g++
AS           = $(CROSS_PREFIX)as
AR           = $(CROSS_PREFIX)ar
LD           = $(CROSS_PREFIX)ld
RM           = rm -rf
MKDIR        = mkdir
OBJDUMP      = $(CROSS_PREFIX)objdump
OBJCOPY	     = $(CROSS_PREFIX)objcopy
STRIP        = $(CROSS_PREFIX)strip

ifeq ($(TOOLCHAIN), x86)
	CFLAGS += -Werror -D_GNU_SOURCE -std=c99 -fno-builtin -nostdlib -O2 $(DEFINE) $(INCLUDE) $(GLB_INCLUDE)
	ASFLAGS += -mlittle-endian -x assembler-with-cpp -O2 
	CXXFLAGS += -Werror -std=gnu++11 -D_GNU_SOURCE -fno-builtin -nostdlib -O2 $(DEFINE) $(INCLUDE) $(GLB_INCLUDE)
else
	CFLAGS += -Werror -D_GNU_SOURCE -std=c99 -mlittle-endian  -fno-builtin -nostdlib -O2 -mlong-calls $(DEFINE) $(INCLUDE) $(GLB_INCLUDE)
	ASFLAGS += -mlittle-endian -x assembler-with-cpp -O2 
	CXXFLAGS += -Werror -std=gnu++11 -D_GNU_SOURCE -fno-builtin -nostdlib -O2 $(DEFINE) $(INCLUDE) $(GLB_INCLUDE)
endif

export CLIB := $(CPU_LIBC_PATH)/libm.a $(CPU_LIBC_PATH)/libc.a  $(CPU_LIBGCC_PATH)/libgcc.a

##specific CFLAGS
CFLAGS += -DWEBRTC_POSIX -fPIC

# Rules


# --------------------------- s -> o
%.o:%.s
	@echo ---------------------[build $<]----------------------------------
	$(CC) -c $(ASFLAGS) $(CFLAGS) -o $@ $<

# ----------------------------- c -> o
%.o:%.c
	@echo ---------------------[build $<]----------------------------------
	$(CC) -c $(CFLAGS) $(INCLUDE) -o $@ $<

# ----------------------------- cc -> o
%.o:%.cc
	@echo ---------------------[build $<]----------------------------------
	$(CXX) -c $(CXXFLAGS) $(INCLUDE) -o $@ $<

# ----------------------------- cpp -> o
%.o:%.cpp
	@echo ---------------------[build $<]----------------------------------
	$(CXX) -c $(CXXFLAGS) $(INCLUDE) -o $@ $<