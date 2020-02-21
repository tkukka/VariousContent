SHELL := /bin/sh
BUILD := Debug
BUILD_DIR := ./$(BUILD)
DEBUG_STR := Debug
RELEASE_STR := Release
BUILD_DIR_DEBUG := ./$(DEBUG_STR)
BUILD_DIR_RELEASE := ./$(RELEASE_STR)
TARGET_NAME := lukusana
TARGET := $(BUILD_DIR)/$(TARGET_NAME)
MAPFILE := $(TARGET).map
LIB_DIR := ./lib-$(BUILD)
LIB_DIR_DEBUG := ./lib-$(DEBUG_STR)
LIB_DIR_RELEASE := ./lib-$(RELEASE_STR)
LIB_SO_NAME := liblukusana.so
LIB_SO_TARGET := $(LIB_DIR)/$(LIB_SO_NAME)
LIB_A_NAME := liblukusana.a
LIB_A_TARGET := $(BUILD_DIR)/$(LIB_A_NAME)
DEPENDFILE := ./.depend.$(BUILD)
SANITIZER := 
SANITIZER_TYPE := leak
.SUFFIXES:
.SUFFIXES: .c .h .cpp .o .a
CC = clang-8 # gcc-8
CXX = clang-8 # g++-8
CPP = $(CC) -E
SIZE = size -B
ARFLAGS = rcs
CPPFLAGS =
WARNINGS = -pedantic -Wall -Wextra -Wformat-security -Werror=format-security
#USE_CXX_SOURCES := 1

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
  AR := llvm-ar-8
  COV_FLAGS = -fprofile-instr-generate -fcoverage-mapping
  COV_LDFLAGS = -fprofile-instr-generate -fcoverage-mapping
else
  DEBUG_INFO := -g3 -ggdb -O0
  LDFLAGS += -fuse-ld=gold
  AR = ar
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
  DEFS += -DDEBUG -UNDEBUG -D_GLIBCXX_ASSERTIONS
  CFLAGS += -fdebug-prefix-map=$$(pwd)=..
  CXXFLAGS += -fdebug-prefix-map=$$(pwd)=..
  LDFLAGS += $(DEBUG_INFO) $(WARNINGS)

  coverage: DEFS += -U_FORTIFY_SOURCE
  coverage: CFLAGS += $(COV_FLAGS)
  coverage: CXXFLAGS += $(COV_FLAGS)
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

  $(BUILD_DIR_DEBUG)/$(TARGET_NAME): LDFLAGS += -fstack-protector-strong -Wl,-z,relro,-z,now,-z,noexecstack -Wl,--Map,$(MAPFILE)
  ifeq ($(strip $(SANITIZER)),asan)
    $(BUILD_DIR_DEBUG)/$(TARGET_NAME): LDFLAGS += -fsanitize=$(SANITIZER_TYPE)
  else
    $(BUILD_DIR_DEBUG)/$(TARGET_NAME): LDFLAGS += -Wl,-z,defs
  endif

  $(LIB_DIR_DEBUG)/%.o: CFLAGS += $(DEFS) $(DEBUG_INFO) $(WARNINGS) -std=c11 -fPIC -fno-omit-frame-pointer -fstack-protector-strong
  $(LIB_DIR_DEBUG)/%.o: CXXFLAGS += $(DEFS) $(DEBUG_INFO) $(WARNINGS) -std=c++17 -fPIC -fno-omit-frame-pointer -fstack-protector-strong
  ifdef USE_CLANG
    $(LIB_DIR_DEBUG)/%.o: CXXFLAGS += -stdlib=libc++
  endif
  $(LIB_DIR_DEBUG)/$(LIB_SO_NAME): LDFLAGS += -fstack-protector-strong -shared -fPIC -Wl,-soname,$(LIB_SO_NAME) -Wl,-z,defs,-z,relro,-z,now,-z,noexecstack,-z,notext
endif
# ========================      Release    ===================================
ifeq ($(strip $(BUILD)),$(RELEASE_STR))
  DEFS += -DNDEBUG -UDEBUG
  ifndef USE_CLANG
    AR := gcc-ar-8
  endif


  $(BUILD_DIR_RELEASE)/%.o: CFLAGS += $(DEFS) -O2 $(WARNINGS) -std=c11 -march=native -fPIE -fstack-protector-strong
  $(BUILD_DIR_RELEASE)/%.o: CXXFLAGS += $(DEFS) -O2 $(WARNINGS) -std=c++17 -march=native -fPIE -fstack-protector-strong

  $(BUILD_DIR_RELEASE)/$(TARGET_NAME): LDFLAGS += -fstack-protector-strong -O2 $(WARNINGS) -pie -Wl,-pie -Wl,-z,defs,-z,relro,-z,now,-z,notext,-z,noexecstack -Wl,--Map,$(MAPFILE) -Wl,-s

  ifdef USE_CLANG
    $(BUILD_DIR_RELEASE)/%.o: CFLAGS += -flto=thin -fsanitize=cfi -fvisibility=hidden #-fsanitize=safe-stack
    $(BUILD_DIR_RELEASE)/%.o: CXXFLAGS += -stdlib=libc++ -flto=thin -fsanitize=cfi -fvisibility=hidden #-fsanitize=safe-stack
    $(BUILD_DIR_RELEASE)/$(TARGET_NAME): LDFLAGS += -flto=thin -fsanitize=cfi -fvisibility=hidden #-fsanitize=safe-stack
  else
    $(BUILD_DIR_RELEASE)/%.o: CFLAGS += -flto -fuse-linker-plugin -fstack-clash-protection
    $(BUILD_DIR_RELEASE)/%.o: CXXFLAGS += -flto -fuse-linker-plugin -fstack-clash-protection
    $(BUILD_DIR_RELEASE)/$(TARGET_NAME): LDFLAGS += -flto -fuse-linker-plugin -fPIE -fstack-clash-protection
  endif

  $(LIB_DIR_RELEASE)/%.o: CFLAGS += $(DEFS) -O2 $(WARNINGS) -std=c11 -march=native -fPIC -fstack-protector-strong
  $(LIB_DIR_RELEASE)/%.o: CXXFLAGS += $(DEFS) -O2 $(WARNINGS) -std=c++17 -march=native -fPIC -fstack-protector-strong
  $(LIB_DIR_RELEASE)/$(LIB_SO_NAME): LDFLAGS += -fstack-protector-strong -O2 $(WARNINGS) -shared -fPIC -Wl,-soname,$(LIB_SO_NAME) -Wl,-z,defs,-z,relro,-z,now,-z,notext,-z,noexecstack -Wl,-s

  ifdef USE_CLANG
    $(LIB_DIR_RELEASE)/%.o: CFLAGS += -flto=thin #-fsanitize=cfi -fvisibility=hidden
    $(LIB_DIR_RELEASE)/%.o: CXXFLAGS += -stdlib=libc++ -flto=thin #-fsanitize=cfi -fvisibility=hidden
    $(LIB_DIR_RELEASE)/$(LIB_SO_NAME): LDFLAGS += -flto=thin #-fsanitize=cfi -fvisibility=hidden
  else
    $(LIB_DIR_RELEASE)/%.o: CFLAGS += -flto -fuse-linker-plugin -fstack-clash-protection
    $(LIB_DIR_RELEASE)/%.o: CXXFLAGS += -flto -fuse-linker-plugin -fstack-clash-protection
    $(LIB_DIR_RELEASE)/$(LIB_SO_NAME): LDFLAGS += -flto -fuse-linker-plugin -fstack-clash-protection
  endif
endif

# Source .c and .cpp files 
ifdef USE_CXX_SOURCES
  CXX_SRC_DIR := ./cplusplus
  LIB_SRCS_CXX = ls_input.cpp ls_stack.cpp ls_presentation.cpp
  SRCS_CXX = lukusana_main.cpp $(LIB_SRCS_CXX)
  LIB_SRCS_C =
  SRCS_C = $(LIB_SRCS_C)
else
  LIB_SRCS_C = ls_input.c ls_stack.c ls_presentation.c
  SRCS_C = lukusana_main.c $(LIB_SRCS_C)
  LIB_SRCS_CXX =
  SRCS_CXX = $(LIB_SRCS_CXX)
endif

LIB_SRCS = $(LIB_SRCS_CXX) $(LIB_SRCS_C)
SRCS = $(SRCS_CXX) $(SRCS_C)

OBJS_CXX = $(SRCS_CXX:.cpp=.o)
OBJS_C = $(SRCS_C:.c=.o)
OBJS := $(addprefix $(BUILD_DIR)/,$(OBJS_CXX)) $(addprefix $(BUILD_DIR)/,$(OBJS_C))

LIB_OBJS_CXX = $(LIB_SRCS_CXX:.cpp=.o)
LIB_OBJS_C = $(LIB_SRCS_C:.c=.o)
LIB_A_OBJS := $(addprefix $(BUILD_DIR)/,$(LIB_OBJS_CXX)) $(addprefix $(BUILD_DIR)/,$(LIB_OBJS_C))
LIB_OBJS := $(addprefix $(LIB_DIR)/,$(LIB_OBJS_CXX)) $(addprefix $(LIB_DIR)/,$(LIB_OBJS_C))

ifdef USE_CXX_SOURCES
  SRCS := $(addprefix $(CXX_SRC_DIR)/,$(SRCS_CXX))
  LIB_SRCS := $(addprefix $(CXX_SRC_DIR)/,$(LIB_SRCS_CXX))
endif


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

# ========================   Pattern rules   ================================
ifdef USE_CXX_SOURCES

$(BUILD_DIR)/%.o: $(CXX_SRC_DIR)/%.cpp
	@echo --- C++ compiling [$(BUILD)] ---
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(LIB_DIR)/%.o: $(CXX_SRC_DIR)/%.cpp
	@echo --- Library C++ compiling [$(BUILD)] ---
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

else

$(BUILD_DIR)/%.o: %.c
	@echo --- C compiling [$(BUILD)] ---
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.cpp
	@echo --- C++ compiling [$(BUILD)] ---
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(LIB_DIR)/%.o: %.c
	@echo --- Library C compiling [$(BUILD)] ---
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(LIB_DIR)/%.o: %.cpp
	@echo --- Library C++ compiling [$(BUILD)] ---
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

endif

all: $(TARGET) $(LIB_SO_TARGET)

$(OBJS): | $(BUILD_DIR)

$(BUILD_DIR):
	-test -d $(BUILD_DIR) || mkdir $(BUILD_DIR)

$(TARGET): $(OBJS)
	@echo --- Linking [$(BUILD)] ---
	$(LINKER) $(LDFLAGS) $(OBJS) -o $@ $(LDLIBS)
	@echo --- Creating archive [$(BUILD)] ---
	$(AR) $(ARFLAGS) $(LIB_A_TARGET) $(LIB_A_OBJS)

$(LIB_OBJS): | $(LIB_DIR)

$(LIB_DIR):
	-test -d $(LIB_DIR) || mkdir $(LIB_DIR)

$(LIB_SO_TARGET): $(LIB_OBJS)
	@echo --- Library linking [$(BUILD)] ---
	$(LINKER) $(LDFLAGS) $(LIB_OBJS) -o $@ $(LDLIBS)

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
	$(CPP) -MM $(LIB_SRCS) >> $@.tmp
	gawk -v S="$(LIB_DIR)/" -F: '{if (NF<2) {print $$0; next} else { printf "%s%s:%s\n",S,$$1,$$2} }' $@.tmp >> $@
	$(RM) $@.tmp

clean:
	@echo --- Clean [$(BUILD)]  ---
	$(RM) $(OBJS) $(TARGET) $(LIB_A_TARGET) $(MAPFILE)
	$(RM) $(LIB_OBJS) $(LIB_SO_TARGET)
	$(RM) $(BUILD_DIR)/*.gcda $(BUILD_DIR)/*.gcno

distclean: clean
	@echo --- Distclean [$(BUILD)] ---
	$(RM) $(DEPENDFILE)
	rmdir $(BUILD_DIR) || true
	rmdir $(LIB_DIR) || true

override undefine USE_CLEAN
ifeq ($(MAKECMDGOALS),clean)
   USE_CLEAN := 1
endif
ifeq ($(MAKECMDGOALS),distclean)
   USE_CLEAN := 1
endif

ifndef USE_CLEAN
   -include $(DEPENDFILE)
endif

