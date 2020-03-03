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
TARGET := $(OUT_DIR)/eka_32
MAPFILE := $(TARGET).map
ASM_SRCS := eka_32.asm
ASM_OBJS := $(addprefix $(OUT_DIR)/,$(ASM_SRCS:.asm=.o)) 


.PHONY: all clean

all: $(TARGET)

$(OUT_DIR)/%.o: %.asm
	@echo --- $(AS) assembler $(BITS)-bit ----
	$(AS) $(ASFLAGS) $< -o $@

$(OUT_DIR):
	test -d $(OUT_DIR) || mkdir $(OUT_DIR)

$(ASM_OBJS): $(ASM_SRCS) | $(OUT_DIR)

$(TARGET): $(ASM_OBJS)
	@echo --- $(LD) linker $(BITS)-bit ---
	$(LD) $(LDHARDENING) $^ -o $@ --Map $(MAPFILE) $(LDFLAGS)

clean:
	$(RM) $(ASM_OBJS) $(TARGET) $(MAPFILE)
	-rmdir $(OUT_DIR)

