# out global info

WORKDIR:=$(shell pwd)

OUT_BIN_DIR?=$(WORKDIR)/out/bin
OUT_LIB_DIR?=$(WORKDIR)/out/lib
OUT_SBIN_DIR?=$(WORKDIR)/out/sbin

MAKE:=make

export WORKDIR OUT_BIN_DIR OUT_LIB_DIR OUT_SBIN_DIR MAKE

LIB_DIR:=$(WORKDIR)/lib
INC_DIR:=$(WORKDIR)/include
INC_INNER_DIR:=$(WORKDIR)/include_inner

export LIB_DIR INC_DIR INC_INNER_DIR

# out dir MUST be placed at first

dir-y := out
dir-y += WebrtcVad
dir-y += vad_tst

all:
	@for i in $(dir-y); \
	do \
		$(MAKE) -C $$i; \
		echo ""; \
		if [ $$? -ne 0 ]; then exit 1; fi \
	done

install:
	@for i in $(dir-y); \
	do \
		$(MAKE) -C $$i install; \
		echo ""; \
	done
	@cp -r lib/*.so $(OUT_LIB_DIR)

image:
	@for i in $(dir-y); \
	do \
		$(MAKE) -C $$i image; \
	done

clean:
	@for i in $(dir-y); \
	do \
		$(MAKE) -C $$i clean; \
		echo ""; \
	done

.PHONY: all install image clean
