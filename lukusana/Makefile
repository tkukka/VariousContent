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
LIB_NAME := liblukusana.so
LIB_TARGET := $(LIB_DIR)/$(LIB_NAME)
DEPENDFILE := ./.depend.$(BUILD)
SANITIZER := 
SANITIZER_TYPE := leak
.SUFFIXES:
.SUFFIXES: .c .h .cpp .o .a
CC = clang-8 # gcc-8
CXX = clang-8 # g++-8
CPP = $(CC) -E
SIZE = size -B
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
else
  DEBUG_INFO := -g3 -ggdb -O0
  LDFLAGS += -fuse-ld=gold
endif


# ========================      Debug    ===================================
ifeq ($(strip $(BUILD)),Debug)
  DEFS += -DDEBUG -UNDEBUG -D_GLIBCXX_ASSERTIONS
  CFLAGS += -fdebug-prefix-map=$$(pwd)=..
  CXXFLAGS += -fdebug-prefix-map=$$(pwd)=..
  LDFLAGS += $(DEBUG_INFO) $(WARNINGS)
endif

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

$(LIB_DIR_DEBUG)/%.o: CFLAGS += $(DEFS) $(DEBUG_INFO) $(WARNINGS) -std=c11 -fPIC -fno-omit-frame-pointer -fstack-protector-strong
$(LIB_DIR_DEBUG)/%.o: CXXFLAGS += $(DEFS) $(DEBUG_INFO) $(WARNINGS) -std=c++17 -fPIC -fno-omit-frame-pointer -fstack-protector-strong 
ifdef USE_CLANG
  $(LIB_DIR_DEBUG)/%.o: CXXFLAGS += -stdlib=libc++
endif
$(LIB_DIR_DEBUG)/$(LIB_NAME): LDFLAGS += -shared -fPIC -Wl,-soname,$(LIB_NAME) -Wl,-z,defs,-z,relro,-z,now,-z,noexecstack,-z,notext

# ========================      Release    ===================================
ifeq ($(strip $(BUILD)),Release)
  DEFS += -DNDEBUG -UDEBUG
endif

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



$(LIB_DIR_RELEASE)/%.o: CFLAGS += $(DEFS) -O2 $(WARNINGS) -std=c11 -march=native -fPIC -fstack-protector-strong
$(LIB_DIR_RELEASE)/%.o: CXXFLAGS += $(DEFS) -O2 $(WARNINGS) -std=c++17 -march=native -fPIC -fstack-protector-strong
$(LIB_DIR_RELEASE)/$(LIB_NAME): LDFLAGS += -O2 $(WARNINGS) -shared -fPIC -Wl,-soname,$(LIB_NAME) -Wl,-z,defs,-z,relro,-z,now,-z,notext,-z,noexecstack -Wl,-s

ifdef USE_CLANG
  $(LIB_DIR_RELEASE)/%.o: CFLAGS += -flto=thin #-fsanitize=cfi -fvisibility=hidden
  $(LIB_DIR_RELEASE)/%.o: CXXFLAGS += -stdlib=libc++ -flto=thin #-fsanitize=cfi -fvisibility=hidden
  $(LIB_DIR_RELEASE)/$(LIB_NAME): LDFLAGS += -flto=thin #-fsanitize=cfi -fvisibility=hidden
else
  $(LIB_DIR_RELEASE)/%.o: CFLAGS += -flto -fuse-linker-plugin -fstack-clash-protection
  $(LIB_DIR_RELEASE)/%.o: CXXFLAGS += -flto -fuse-linker-plugin -fstack-clash-protection
  $(LIB_DIR_RELEASE)/$(LIB_NAME): LDFLAGS += -flto -fuse-linker-plugin -fstack-clash-protection
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

.PHONY: all clean distclean depend memsize
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

all: $(TARGET) $(LIB_TARGET)

$(OBJS): | $(BUILD_DIR)

$(BUILD_DIR):
	-test -d $(BUILD_DIR) || mkdir $(BUILD_DIR)

$(TARGET): $(OBJS)
	@echo --- Linking [$(BUILD)] ---
	$(LINKER) $(LDFLAGS) $(OBJS) -o $@ $(LDLIBS)

$(LIB_OBJS): | $(LIB_DIR)

$(LIB_DIR):
	-test -d $(LIB_DIR) || mkdir $(LIB_DIR)

$(LIB_TARGET): $(LIB_OBJS)
	@echo --- Library linking [$(BUILD)] ---
	$(LINKER) $(LDFLAGS) $(LIB_OBJS) -o $@ $(LDLIBS)

memsize: $(TARGET)
	@echo --- Memory usage ---
	$(SIZE) $(OBJS) $(TARGET) || true

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
	$(RM) $(OBJS) $(TARGET) $(MAPFILE)
	$(RM) $(LIB_OBJS) $(LIB_TARGET)

distclean: clean
	@echo --- Distclean [$(BUILD)] ---
	$(RM) $(DEPENDFILE)
	rmdir $(BUILD_DIR) || true
	rmdir $(LIB_DIR) || true

ifneq ($(MAKECMDGOALS),clean)
   -include $(DEPENDFILE)
endif

