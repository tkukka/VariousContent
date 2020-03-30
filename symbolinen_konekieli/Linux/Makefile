.SUFFIXES:
.SUFFIXES: .asm .c .o
SHELL := /bin/sh
OUT_DIR := ./bin
BITS := 32
AS := nasm

ifeq ($(strip $(BITS)),32)
  ASFLAGS := -w +all -f elf32 -g -F dwarf
else
  ASFLAGS := -w +all -f elf64 -g -F dwarf
endif

CC := gcc-8
WARNINGS := -Wall -Wextra -pedantic -Wformat-security
DEBUG_OPTIONS := -g -ggdb3 -fno-omit-frame-pointer -O0

ifeq ($(strip $(BITS)),32)
  CFLAGS := -m32 -std=c11 $(DEBUG_OPTIONS) $(WARNINGS)
else
  CFLAGS := -std=c11 $(DEBUG_OPTIONS) $(WARNINGS)
endif

LD := ld
LDHARDENING := -z defs -z relro -z now -z notext -z noexecstack

ifeq ($(strip $(BITS)),32)
  LDFLAGS := -m elf_i386 -dynamic-linker /lib/ld-linux.so.2
  TARGETS := $(OUT_DIR)/eka_32 $(OUT_DIR)/toka_32 $(OUT_DIR)/kolmas_32 $(OUT_DIR)/neljas_32 \
          $(OUT_DIR)/viides_32 $(OUT_DIR)/kuudes_32 $(OUT_DIR)/seiska_32

  ASM_SRCS := eka_32.asm toka_32.asm kolmas_32.asm kolmas_funktio_32.asm neljas_32.asm \
            viides_32.asm kuudes_x87_32.asm kuudes_sse_32.asm kuudes_c_fun_32.asm seiska_32.asm

  C_SRCS := kuudes_main_32.c seiska_main_32.c
else
  LDFLAGS :=

  TARGETS := $(OUT_DIR)/eka_64 $(OUT_DIR)/toka_64

  ASM_SRCS := eka_64.asm toka_funktio_64.asm toka_64.asm
  C_SRCS :=
endif

ASM_OBJS := $(addprefix $(OUT_DIR)/,$(ASM_SRCS:.asm=.o))
C_OBJS := $(addprefix $(OUT_DIR)/,$(C_SRCS:.c=.o))

.PHONY: all clean

all: $(TARGETS)

$(OUT_DIR)/%.o: %.asm
	@echo --- $(AS) assembler $(BITS)-bit ----
	$(AS) $(ASFLAGS) -l $(OUT_DIR)/$<.lst $< -o $@

$(OUT_DIR)/%.o: %.c
	@echo --- $(CC) compiler $(BITS)-bit mode ----
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT_DIR):
	test -d $(OUT_DIR) || mkdir $(OUT_DIR)

$(ASM_OBJS) $(C_OBJS): | $(OUT_DIR)

ifeq ($(strip $(BITS)),32)
$(OUT_DIR)/eka_32.o: eka_32.asm

$(OUT_DIR)/toka_32.o: toka_32.asm

$(OUT_DIR)/kolmas_32.o: kolmas_32.asm
$(OUT_DIR)/kolmas_funktio_32.o: kolmas_funktio_32.asm

$(OUT_DIR)/neljas_32.o: neljas_32.asm

$(OUT_DIR)/viides_32.o: viides_32.asm

$(OUT_DIR)/kuudes_main_32.o: kuudes_main_32.c
$(OUT_DIR)/kuudes_x87_32.o: kuudes_x87_32.asm
$(OUT_DIR)/kuudes_sse_32.o: kuudes_sse_32.asm
$(OUT_DIR)/kuudes_c_fun_32.o: kuudes_c_fun_32.asm

$(OUT_DIR)/seiska_32.o: seiska_32.asm
$(OUT_DIR)/seiska_main_32.o: seiska_main_32.c

$(OUT_DIR)/eka_32: $(OUT_DIR)/eka_32.o
	@echo --- $(LD) linker $(BITS)-bit ---
	$(LD) $(LDHARDENING) $< -o $@ --Map $@.map $(LDFLAGS)

$(OUT_DIR)/toka_32: $(OUT_DIR)/toka_32.o
	@echo --- $(LD) linker $(BITS)-bit ---
	$(LD) $(LDHARDENING) $< -o $@ --Map $@.map $(LDFLAGS)

$(OUT_DIR)/kolmas_32: $(OUT_DIR)/kolmas_32.o $(OUT_DIR)/kolmas_funktio_32.o
	@echo --- $(LD) linker $(BITS)-bit ---
	$(LD) $(LDHARDENING) $^ -o $@ --Map $@.map $(LDFLAGS)

$(OUT_DIR)/neljas_32: $(OUT_DIR)/neljas_32.o
	@echo --- $(LD) linker $(BITS)-bit ---
	$(LD) $(LDHARDENING) $^ -o $@ --Map $@.map $(LDFLAGS)

$(OUT_DIR)/viides_32: $(OUT_DIR)/viides_32.o
	@echo --- $(LD) linker $(BITS)-bit ---
	$(LD) $(LDHARDENING) $^ -o $@ --Map $@.map $(LDFLAGS) -lc

$(OUT_DIR)/kuudes_32: LD := gcc-8
$(OUT_DIR)/kuudes_32: LDHARDENING := -Wl,-z,defs,-z,relro,-z,now,-z,notext,-z,noexecstack
$(OUT_DIR)/kuudes_32: LDFLAGS := -m32

$(OUT_DIR)/seiska_32: LD := gcc-8
$(OUT_DIR)/seiska_32: LDHARDENING := -Wl,-z,defs,-z,relro,-z,now,-z,notext,-z,noexecstack
$(OUT_DIR)/seiska_32: LDFLAGS := -m32

ifdef USE_SSE
$(OUT_DIR)/kuudes_32: $(OUT_DIR)/kuudes_sse_32.o $(OUT_DIR)/kuudes_c_fun_32.o $(OUT_DIR)/kuudes_main_32.o
	@echo --- $(LD) linking $(BITS)-bit ---
	$(LD) $(LDHARDENING) $^ -o $@ -Wl,--Map,$@.map $(LDFLAGS)
else
$(OUT_DIR)/kuudes_32: $(OUT_DIR)/kuudes_x87_32.o $(OUT_DIR)/kuudes_c_fun_32.o $(OUT_DIR)/kuudes_main_32.o
	@echo --- $(LD) linking $(BITS)-bit ---
	$(LD) $(LDHARDENING) $^ -o $@ -Wl,--Map,$@.map $(LDFLAGS)
endif

$(OUT_DIR)/seiska_32: $(OUT_DIR)/seiska_32.o $(OUT_DIR)/seiska_main_32.o
	@echo --- $(LD) linking $(BITS)-bit ---
	$(LD) $(LDHARDENING) $^ -o $@ -Wl,--Map,$@.map $(LDFLAGS)

else
# 64-bit
$(OUT_DIR)/eka_64.o: eka_64.asm

$(OUT_DIR)/toka_64.o: toka_64.asm
$(OUT_DIR)/toka_funktio_64.o: toka_funktio_64.asm

$(OUT_DIR)/eka_64: $(OUT_DIR)/eka_64.o
	@echo --- $(LD) linker $(BITS)-bit ---
	$(LD) $(LDHARDENING) $< -o $@ --Map $@.map $(LDFLAGS)

$(OUT_DIR)/toka_64: $(OUT_DIR)/toka_funktio_64.o $(OUT_DIR)/toka_64.o
	@echo --- $(LD) linker $(BITS)-bit ---
	$(LD) $(LDHARDENING) $^ -o $@ --Map $@.map $(LDFLAGS)

endif

clean:
	$(RM) $(ASM_OBJS) $(C_OBJS) $(TARGETS) $(OUT_DIR)/*.map $(OUT_DIR)/*.lst
	-rmdir $(OUT_DIR)

