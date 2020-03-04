.SUFFIXES:
.SUFFIXES: .asm .o
SHELL := /bin/sh
OUT_DIR := ./bin
BITS := 32
AS := nasm
ASFLAGS := -w +all -f elf32 -g -F dwarf
LD := ld
LDHARDENING := -z defs -z relro -z now -z notext -z noexecstack 
LDFLAGS := -m elf_i386 -dynamic-linker /lib/ld-linux.so.2
TARGETS := $(OUT_DIR)/eka_32 $(OUT_DIR)/toka_32
#MAPFILE := $(TARGET).map
ASM_SRCS := eka_32.asm toka_32.asm
ASM_OBJS := $(addprefix $(OUT_DIR)/,$(ASM_SRCS:.asm=.o)) 


.PHONY: all clean

all: $(TARGETS)

$(OUT_DIR)/%.o: %.asm
	@echo --- $(AS) assembler $(BITS)-bit ----
	$(AS) $(ASFLAGS) -l $(OUT_DIR)/$<.lst   $< -o $@

$(OUT_DIR):
	test -d $(OUT_DIR) || mkdir $(OUT_DIR)

$(ASM_OBJS): | $(OUT_DIR)

$(OUT_DIR)/eka_32.o: eka_32.asm

$(OUT_DIR)/toka_32.o: toka_32.asm

$(OUT_DIR)/eka_32: $(OUT_DIR)/eka_32.o
	@echo --- $(LD) linker $(BITS)-bit ---
	$(LD) $(LDHARDENING) $^ -o $@ --Map $@.map $(LDFLAGS)

$(OUT_DIR)/toka_32: $(OUT_DIR)/toka_32.o
	@echo --- $(LD) linker $(BITS)-bit ---
	$(LD) $(LDHARDENING) $^ -o $@ --Map $@.map $(LDFLAGS)

clean:
	$(RM) $(ASM_OBJS) $(TARGETS) $(OUT_DIR)/*.map $(OUT_DIR)/*.lst
	-rmdir $(OUT_DIR)

