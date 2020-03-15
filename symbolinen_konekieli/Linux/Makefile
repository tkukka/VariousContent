.SUFFIXES:
.SUFFIXES: .asm .c .o
SHELL := /bin/sh
OUT_DIR := ./bin
BITS := 32
AS := nasm
ASFLAGS := -w +all -f elf32 -g -F dwarf
CC := gcc-8
WARNINGS := -Wall -Wextra -pedantic -Wformat-security
DEBUG_OPTIONS := -g -ggdb3 -fno-omit-frame-pointer -O0
CFLAGS := -m32 -std=c11 $(DEBUG_OPTIONS) $(WARNINGS)
LD := ld
LDHARDENING := -z defs -z relro -z now -z notext -z noexecstack
LDFLAGS := -m elf_i386 -dynamic-linker /lib/ld-linux.so.2
TARGETS := $(OUT_DIR)/eka_32 $(OUT_DIR)/toka_32 $(OUT_DIR)/kolmas_32 $(OUT_DIR)/neljas_32 \
          $(OUT_DIR)/viides_32 $(OUT_DIR)/kuudes_32

ASM_SRCS := eka_32.asm toka_32.asm kolmas_32.asm kolmas_funktio_32.asm neljas_32.asm \
            viides_32.asm kuudes_x87_32.asm kuudes_sse_32.asm kuudes_c_fun_32.asm

ASM_OBJS := $(addprefix $(OUT_DIR)/,$(ASM_SRCS:.asm=.o))
C_SRCS := kuudes_main_32.c
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

ifdef USE_SSE
$(OUT_DIR)/kuudes_32: $(OUT_DIR)/kuudes_sse_32.o $(OUT_DIR)/kuudes_c_fun_32.o $(OUT_DIR)/kuudes_main_32.o
	@echo --- $(LD) linking $(BITS)-bit ---
	$(LD) $(LDHARDENING) $^ -o $@ -Wl,--Map,$@.map $(LDFLAGS)
else
$(OUT_DIR)/kuudes_32: $(OUT_DIR)/kuudes_x87_32.o $(OUT_DIR)/kuudes_c_fun_32.o $(OUT_DIR)/kuudes_main_32.o
	@echo --- $(LD) linking $(BITS)-bit ---
	$(LD) $(LDHARDENING) $^ -o $@ -Wl,--Map,$@.map $(LDFLAGS)
endif

clean:
	$(RM) $(ASM_OBJS) $(C_OBJS) $(TARGETS) $(OUT_DIR)/*.map $(OUT_DIR)/*.lst
	-rmdir $(OUT_DIR)

