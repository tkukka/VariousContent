SHELL = /bin/sh
BUILD = Debug
TARGET = ./$(BUILD)/lukusana
MAPFILE = $(TARGET).map
SANITIZER := 
ASAN_TYPE := leak
.SUFFIXES:
.SUFFIXES: .c .h .cpp .o .a
CC = clang-8 # gcc-8
CXX = clang-8 # g++-8
CPP = $(CXX) -E
SIZE = size -B
CPPFLAGS =
WARNINGS = -pedantic -Wall -Wextra -Wformat-security -Werror=format-security

ifeq ($(findstring clang,$(CC)),clang)
  USE_CLANG := 1
endif
ifeq  ($(findstring clang,$(CXX)),clang)
  USE_CLANG := 1
endif

ifdef USE_CLANG
   DEBUG_INFO := -g3 -glldb -Og
   WARNINGS += -Wtautological-compare -Wtautological-constant-in-range-compare -Wgnu
   LDFLAGS += -fuse-ld=lld-8
else
   DEBUG_INFO := -g3 -ggdb -Og
   LDFLAGS += -fuse-ld=gold
endif

ifeq ($(strip $(BUILD)),Debug)
   CFLAGS += -fdebug-prefix-map=$$(pwd)=.. 
   CXXFLAGS += -fdebug-prefix-map=$$(pwd)=.. 
   
   DEFS = -DDEBUG -UNDEBUG -D_GLIBCXX_ASSERTIONS
   LDFLAGS += $(DEBUG_INFO)

   ifeq ($(strip $(SANITIZER)),asan)
      DEFS += -U_FORTIFY_SOURCE
      CFLAGS += $(DEFS) $(DEBUG_INFO) $(WARNINGS) -std=c11 -fsanitize=$(ASAN_TYPE) \
              -fno-omit-frame-pointer -fstack-protector-strong  
      CXXFLAGS += $(DEFS) $(DEBUG_INFO) $(WARNINGS) -std=c++17 -fsanitize=$(ASAN_TYPE) \
              -fno-omit-frame-pointer -fstack-protector-strong
      LDFLAGS += -fsanitize=$(ASAN_TYPE) -Wl,-z,relro,-z,now,-z,noexecstack -Wl,--Map,$(MAPFILE)
   endif

   ifeq ($(strip $(SANITIZER)),valgrind)
      DEFS += -U_FORTIFY_SOURCE
      CFLAGS += $(DEFS) $(DEBUG_INFO) $(WARNINGS) -std=c11 \
              -fno-omit-frame-pointer -fstack-protector-strong 
      CXXFLAGS += $(DEFS) $(DEBUG_INFO) $(WARNINGS) -std=c++17 \
              -fno-omit-frame-pointer -fstack-protector-strong
      LDFLAGS += -Wl,-z,defs,-z,relro,-z,now,-z,noexecstack -Wl,--Map,$(MAPFILE)
   endif


   ifeq ($(strip $(SANITIZER)),) # empty
      CFLAGS += $(DEFS) $(DEBUG_INFO) $(WARNINGS) -std=c11 \
              -fno-omit-frame-pointer -fstack-protector-strong
      CXXFLAGS += $(DEFS) $(DEBUG_INFO) $(WARNINGS) -std=c++17 \
              -fno-omit-frame-pointer -fstack-protector-strong 
      LDFLAGS += -Wl,-z,defs,-z,relro,-z,now,-z,noexecstack -Wl,--Map,$(MAPFILE)

   endif
# Release    
else
   DEFS = -DNDEBUG -UDEBUG
   CFLAGS += $(DEFS) -O2 $(WARNINGS) -std=c11 -march=native -fPIE -fstack-protector-strong 
   CXXFLAGS += $(DEFS) -O2 $(WARNINGS) -std=c++17 -march=native -fPIE -fstack-protector-strong
   ifdef USE_CLANG
      CFLAGS += -flto=thin
      CXXFLAGS += -flto=thin
      LDFLAGS += -O2 -flto=thin -pie -Wl,-z,defs,-z,relro,-z,now,-z,notext,-z,noexecstack -Wl,--Map,$(MAPFILE) -Wl,-s
   else
      CFLAGS += -flto
      CXXFLAGS += -flto
      LDFLAGS += -O2 -flto -fuse-linker-plugin -pie -fPIE -Wl,-z,defs,-z,relro,-z,now,-z,notext,-z,noexecstack -Wl,--Map,$(MAPFILE) -Wl,-s
   endif
   
endif

SRCS_C = lukusana.c ls_stack.c
SRCS_CXX =
SRCS = $(SRCS_CXX) $(SRCS_C)
OBJS_CXX = $(SRCS_CXX:.cpp=.o)
OBJS_C = $(SRCS_C:.c=.o)
OBJS := $(addprefix ./$(BUILD)/,$(OBJS_CXX)) $(addprefix ./$(BUILD)/,$(OBJS_C))

DEPENDFILE := ./.depend.$(BUILD)

ifeq ($(strip $(OBJS_CXX)),)
   LINKER := $(CC)
else
   LINKER := $(CXX)
endif

.PHONY: clean distclean depend all memsize

./$(BUILD)/%.o: %.c
	@echo --- C compiling ---
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

./$(BUILD)/%.o: %.cpp
	@echo --- C++ compiling ---
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

all: $(TARGET)

$(OBJS): | ./$(BUILD)

./$(BUILD):
	-test -d $(BUILD) || mkdir $(BUILD)

$(TARGET): $(OBJS)
	@echo --- Linking ---
	$(LINKER) $(LDFLAGS) $(OBJS) -o $@ $(LDLIBS) 

memsize: $(TARGET)
	@echo --- Memory usage ---
	$(SIZE) $(OBJS) $(TARGET)

depend: $(DEPENDFILE)

$(DEPENDFILE): $(SRCS)
	@echo --- Depencies ---
	$(RM) $(DEPENDFILE)
	$(CPP) -MM $^ >> $(DEPENDFILE).tmp
	gawk -v S="./$(BUILD)/" -F: '{printf "%s%s:%s\n",S,$$1,$$2}' $(DEPENDFILE).tmp >> $(DEPENDFILE)
	$(RM) $(DEPENDFILE).tmp

clean:
	@echo --- Clean ---
	$(RM) $(OBJS) $(TARGET) $(MAPFILE)

distclean: clean
	@echo --- Distclean ---
	$(RM) $(DEPENDFILE)
	-test -d $(BUILD) && rmdir $(BUILD)

ifneq ($(MAKECMDGOALS),clean)
   -include $(DEPENDFILE)
endif

