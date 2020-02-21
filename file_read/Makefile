SHELL = /bin/sh
.SUFFIXES:
.SUFFIXES: .h .c .cpp .o .java .class
# Java settings
CLASS := FileRead
JAVA_SRC := $(CLASS).java
JAVA_TARGET := $(CLASS).class
JAVAC := javac
JAVAC_FLAGS := -encoding UTF-8 -Xlint -Xdiags:verbose -Werror
# C/C++ settings
BUILD =
TARGET_C := file_read_c
TARGET_CXX := file_read_cxx
SRCS_C = file_read_c.c
OBJS_C = $(SRCS_C:.c=.o)
SRCS_CXX = file_read_cxx.cpp
OBJS_CXX = $(SRCS_CXX:.cpp=.o)

CC = gcc-8 #clang-8
CXX = g++-8 #clang-8
CPP = $(CC) -E
CPPFLAGS =
WARNINGS = -pedantic -Wall -Wextra -Wformat-security -Werror=format-security
CXX_STD := c++17 #c++03


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
else
  DEBUG_INFO := -g3 -ggdb -O0
  LDFLAGS += -fuse-ld=gold
endif

ifneq ($(MAKECMDGOALS),clean)
  ifeq ($(strip $(BUILD)),)
    $(error Build [Debug | Release] not specified.)
  endif
  ifeq ($(strip $(BUILD)),Debug)
    BUILD_SPECIFIED := 1
  endif
  ifeq ($(strip $(BUILD)),Release)
    BUILD_SPECIFIED := 1
  endif
  ifndef BUILD_SPECIFIED
    $(error Build "$(BUILD)" is not a proper build [Debug | Release].)
  endif
endif

# ========================      Debug    ===================================
ifeq ($(strip $(BUILD)),Debug)
  DEFS += -DDEBUG -UNDEBUG -D_GLIBCXX_ASSERTIONS
  CFLAGS += -fdebug-prefix-map=$$(pwd)=..
  CXXFLAGS += -fdebug-prefix-map=$$(pwd)=..
  LDFLAGS += $(DEBUG_INFO) $(WARNINGS)

  ifdef USE_CLANG
    %.o: CXXFLAGS += -stdlib=libc++
  endif

  %.o: CFLAGS += $(DEFS) $(DEBUG_INFO) $(WARNINGS) -std=c11 -fno-omit-frame-pointer -fstack-protector-strong
  %.o: CXXFLAGS += $(DEFS) $(DEBUG_INFO) $(WARNINGS) -std=$(CXX_STD) -fno-omit-frame-pointer -fstack-protector-strong 

  $(TARGET_C):: LDFLAGS += -Wl,-z,relro,-z,now,-z,noexecstack,-z,defs -fstack-protector-strong
  $(TARGET_CXX): LDFLAGS += -Wl,-z,relro,-z,now,-z,noexecstack,-z,defs -fstack-protector-strong
  ifdef USE_CLANG
    $(TARGET_CXX): LDFLAGS += -lc++
  endif
endif # Debug
# ========================      Release    =================================
ifeq ($(strip $(BUILD)),Release)
  DEFS += -DNDEBUG -UDEBUG

  %.o: CFLAGS += $(DEFS) -O2 $(WARNINGS) -std=c11 -march=native -fPIE -fstack-protector-strong
  %.o: CXXFLAGS += $(DEFS) -O2 $(WARNINGS) -std=$(CXX_STD) -march=native -fPIE -fstack-protector-strong

  $(TARGET_C): LDFLAGS += -O2 $(WARNINGS) -pie -Wl,-pie -Wl,-z,defs,-z,relro,-z,now,-z,notext,-z,noexecstack,-s -fstack-protector-strong
  $(TARGET_CXX): LDFLAGS += -O2 $(WARNINGS) -pie -Wl,-pie -Wl,-z,defs,-z,relro,-z,now,-z,notext,-z,noexecstack,-s -fstack-protector-strong

  ifdef USE_CLANG
    %.o: CFLAGS += -flto=thin -fsanitize=cfi -fvisibility=hidden
    %.o: CXXFLAGS += -stdlib=libc++ -flto=thin -fsanitize=cfi -fvisibility=hidden
    $(TARGET_C): LDFLAGS += -flto=thin -fsanitize=cfi -fvisibility=hidden
    $(TARGET_CXX): LDFLAGS += -flto=thin -fsanitize=cfi -fvisibility=hidden -lc++
  else
    %.o: CFLAGS += -flto -fuse-linker-plugin -fstack-clash-protection
    %.o: CXXFLAGS += -flto -fuse-linker-plugin -fstack-clash-protection
    $(TARGET_C): LDFLAGS += -flto -fuse-linker-plugin -fPIE -fstack-clash-protection
    $(TARGET_CXX): LDFLAGS += -flto -fuse-linker-plugin -fPIE -fstack-clash-protection
  endif

endif # Release

# ========================   Pattern rules   ================================
%.class: %.java
	@echo --- Java compiling ---
	$(JAVAC) $(JAVAC_FLAGS) $<

%.o: %.c
	@echo --- C compiling [$(BUILD)] ---
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

%.o: %.cpp
	@echo --- C++ compiling [$(BUILD)] ---
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@


.PHONY: all clean

all: $(JAVA_TARGET) $(TARGET_C) $(TARGET_CXX)

$(JAVA_TARGET): $(JAVA_SRC)

$(TARGET_C): $(OBJS_C)
	@echo --- Linking [$(BUILD)] ---
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

$(TARGET_CXX): $(OBJS_CXX)
	@echo --- Linking [$(BUILD)] ---
	$(CXX) $(LDFLAGS) $^ -o $@ $(LDLIBS)

$(TARGET_C).o: file_read_c.c

$(TARGET_CXX).o: file_read_cxx.cpp

clean:
	-$(RM) *.o *.class
	-$(RM) $(JAVA_TARGET) $(TARGET_C) $(TARGET_CXX)


