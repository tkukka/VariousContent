SHELL := /bin/sh
BUILD := Debug
BUILD_DIR := ./$(BUILD)
DEBUG_STR := Debug
RELEASE_STR := Release
BUILD_DIR_DEBUG := ./$(DEBUG_STR)
BUILD_DIR_RELEASE := ./$(RELEASE_STR)
TARGET_NAME := test_lukusana
TARGET := $(BUILD_DIR)/$(TARGET_NAME)
MAPFILE := $(TARGET).map
DEPENDFILE := ./.depend.$(BUILD)
LIB_FILE := ../$(DEBUG_STR)/liblukusana.a
SANITIZER := 
SANITIZER_TYPE := leak
.SUFFIXES:
.SUFFIXES: .c .h .cpp .o .a
CC = gcc-8 #clang-8
CXX = g++-8 #clang-8
CPP = $(CC) -E
SIZE = size -B
CPPFLAGS =
WARNINGS = -pedantic -Wall -Wextra -Wformat-security -Werror=format-security

ifeq ($(findstring clang,$(CC)),clang)
  USE_CLANG := 1
endif
ifeq  ($(findstring clang,$(CXX)),clang)
  USE_CLANG := 1
endif

# Common
ifdef USE_CLANG
  WARNINGS += -Wtautological-compare -Wtautological-constant-in-range-compare -Wgnu
  DEBUG_INFO := -g3 -glldb -O0
  LDFLAGS += -fuse-ld=lld-8
  COV_FLAGS = -fprofile-instr-generate -fcoverage-mapping
  COV_LDFLAGS = -fprofile-instr-generate -fcoverage-mapping
else
  DEBUG_INFO := -g3 -ggdb -O0
  LDFLAGS += -fuse-ld=gold
  COV_FLAGS = --coverage -ftest-coverage
  COV_LDFLAGS = -lgcov --coverage
endif


ifeq ($(strip $(BUILD)),)
  $(error Build [$(DEBUG_STR) | $(RELEASE_STR)] not specified.)
endif
ifeq ($(strip $(BUILD)),$(DEBUG_STR))
  BUILD_SPECIFIED := 1
endif
ifeq ($(strip $(BUILD)),$(RELEASE_STR))
  BUILD_SPECIFIED := 1
endif
ifndef BUILD_SPECIFIED
  $(error Build "$(BUILD)" is not a proper build [$(DEBUG_STR) | $(RELEASE_STR)].)
endif


# ========================      Debug    ===================================
ifeq ($(strip $(BUILD)),$(DEBUG_STR))
  DEFS += -DDEBUG -UNDEBUG -D_GLIBCXX_ASSERTIONS -UCATCH2
  CFLAGS += -fdebug-prefix-map=$$(pwd)=..
  CXXFLAGS += -fdebug-prefix-map=$$(pwd)=..
  LDFLAGS += $(DEBUG_INFO) $(WARNINGS)

  coverage: DEFS += -U_FORTIFY_SOURCE
  #coverage: CFLAGS += $(COV_FLAGS)
  #coverage: CXXFLAGS += $(COV_FLAGS)
  coverage: LDFLAGS += $(COV_LDFLAGS)


  ifdef USE_CLANG
  #  $(BUILD_DIR_DEBUG)/%.o: CFLAGS += -fsanitize=safe-stack
  #  $(BUILD_DIR_DEBUG)/%.o: CXXFLAGS += -fsanitize=safe-stack
    $(BUILD_DIR_DEBUG)/%.o: CXXFLAGS += -stdlib=libc++
  endif

  ifeq ($(strip $(SANITIZER)),asan)
    $(BUILD_DIR_DEBUG)/%.o: DEFS += -U_FORTIFY_SOURCE
    $(BUILD_DIR_DEBUG)/%.o: CFLAGS += -fsanitize=$(SANITIZER_TYPE)
    $(BUILD_DIR_DEBUG)/%.o: CXXFLAGS += -fsanitize=$(SANITIZER_TYPE)
  endif
  ifeq ($(strip $(SANITIZER)),valgrind)
    $(BUILD_DIR_DEBUG)/%.o: DEFS += -U_FORTIFY_SOURCE
  endif

  $(BUILD_DIR_DEBUG)/%.o: CFLAGS += $(DEFS) $(DEBUG_INFO) $(WARNINGS) -std=c11 -fno-omit-frame-pointer -fstack-protector-strong
  $(BUILD_DIR_DEBUG)/%.o: CXXFLAGS += $(DEFS) $(DEBUG_INFO) $(WARNINGS) -std=c++17 -fno-omit-frame-pointer -fstack-protector-strong

  #ifdef USE_CLANG
  #  $(BUILD_DIR_DEBUG)/$(TARGET_NAME): LDFLAGS += -fsanitize=safe-stack
  #endif

  $(BUILD_DIR_DEBUG)/$(TARGET_NAME): LDFLAGS += -Wl,-z,relro,-z,now,-z,noexecstack -Wl,--Map,$(MAPFILE)
  ifeq ($(strip $(SANITIZER)),asan)
    $(BUILD_DIR_DEBUG)/$(TARGET_NAME): LDFLAGS += -fsanitize=$(SANITIZER_TYPE)
  else
    $(BUILD_DIR_DEBUG)/$(TARGET_NAME): LDFLAGS += -Wl,-z,defs
  endif

endif
# ========================      Release    ===================================
ifeq ($(strip $(BUILD)),$(RELEASE_STR))
  DEFS += -DNDEBUG -UDEBUG -UCATCH2


  $(BUILD_DIR_RELEASE)/%.o: CFLAGS += $(DEFS) -O2 $(WARNINGS) -std=c11 -march=native -fPIE -fstack-protector-strong
  $(BUILD_DIR_RELEASE)/%.o: CXXFLAGS += $(DEFS) -O2 $(WARNINGS) -std=c++17 -march=native -fPIE -fstack-protector-strong

  $(BUILD_DIR_RELEASE)/$(TARGET_NAME): LDFLAGS += -O2 $(WARNINGS) -pie -Wl,-pie -Wl,-z,defs,-z,relro,-z,now,-z,notext,-z,noexecstack -Wl,--Map,$(MAPFILE) -Wl,-s

  ifdef USE_CLANG
    $(BUILD_DIR_RELEASE)/%.o: CFLAGS += -flto=thin -fsanitize=cfi -fvisibility=hidden #-fsanitize=safe-stack
    $(BUILD_DIR_RELEASE)/%.o: CXXFLAGS += -stdlib=libc++ -flto=thin -fsanitize=cfi -fvisibility=hidden #-fsanitize=safe-stack
    $(BUILD_DIR_RELEASE)/$(TARGET_NAME): LDFLAGS += -flto=thin -fsanitize=cfi -fvisibility=hidden #-fsanitize=safe-stack
  else
    $(BUILD_DIR_RELEASE)/%.o: CFLAGS += -flto -fuse-linker-plugin -fstack-clash-protection
    $(BUILD_DIR_RELEASE)/%.o: CXXFLAGS += -flto -fuse-linker-plugin -fstack-clash-protection
    $(BUILD_DIR_RELEASE)/$(TARGET_NAME): LDFLAGS += -flto -fuse-linker-plugin -fPIE -fstack-clash-protection
  endif
endif


# Source .c and .cpp files
SRCS_CXX = test_main.cpp test_input.cpp test_stack.cpp test_presentation.cpp
SRCS_C =
SRCS = $(SRCS_CXX) $(SRCS_C)

OBJS_CXX = $(SRCS_CXX:.cpp=.o)
OBJS_C = $(SRCS_C:.c=.o)
OBJS := $(addprefix $(BUILD_DIR)/,$(OBJS_CXX)) $(addprefix $(BUILD_DIR)/,$(OBJS_C))


ifeq ($(strip $(OBJS_CXX)),)
   LINKER := $(CC)
else
   LINKER := $(CXX)
   CPP := $(CXX) -E

  ifdef USE_CLANG
     LDLIBS += -lc++
  endif

endif

.PHONY: all clean distclean depend memsize coverage

$(BUILD_DIR)/%.o: %.c
	@echo --- C compiling [$(BUILD)] ---
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.cpp
	@echo --- C++ compiling [$(BUILD)] ---
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

all: $(TARGET)

$(OBJS): | $(BUILD_DIR)

$(BUILD_DIR):
	-test -d $(BUILD_DIR) || mkdir $(BUILD_DIR)

$(TARGET): $(OBJS)
	@echo --- Linking [$(BUILD)] ---
	$(LINKER) $(LDFLAGS) $(OBJS) $(LIB_FILE) -o $@ $(LDLIBS)

memsize: $(TARGET)
	@echo --- Memory usage ---
	$(SIZE) $(OBJS) $(TARGET) || true

coverage: $(TARGET)

depend: $(DEPENDFILE)

$(DEPENDFILE): $(SRCS)
	@echo --- Depencies [$(BUILD)] ---
	$(RM) $@
	$(CPP) -MM $^ >> $@.tmp
	gawk -v S="$(BUILD_DIR)/" -F: '{if (NF<2) {print $$0; next} else { printf "%s%s:%s\n",S,$$1,$$2} }' $@.tmp >> $@
	$(RM) $@.tmp
	$(RM) $@.tmp

clean:
	@echo --- Clean [$(BUILD)]  ---
	$(RM) $(OBJS) $(TARGET) $(MAPFILE)

distclean: clean
	@echo --- Distclean [$(BUILD)] ---
	$(RM) $(DEPENDFILE)
	rmdir $(BUILD_DIR) || true

ifneq ($(MAKECMDGOALS),clean)
   -include $(DEPENDFILE)
endif

