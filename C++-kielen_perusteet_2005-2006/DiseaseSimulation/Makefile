SHELL = /bin/sh
.SUFFIXES:
.SUFFIXES: .h .c .cpp .o .d

# C/C++ settings
BUILD =
TARGET:= DiseaseSimulation
SRCS_CXX = main.cpp Randomizer.cpp Simulator.cpp Vaccine.cpp Creature.cpp Virus.cpp Human.cpp Population.cpp SimulatorHumanFactory.cpp
OBJS_CXX = $(SRCS_CXX:.cpp=.o)
DEPS := $(SRCS_CXX:.cpp=.d)
CC = gcc
CXX = g++
CPP = $(CXX) -E
CPPFLAGS =
WARNINGS = -Wpedantic -Wall -Wextra -Wformat-security -Werror=format-security
CXX_STD := c++17
DEBUG_INFO := -g3 -ggdb -O0
LDFLAGS += -fuse-ld=gold


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

  CXXFLAGS += -fdebug-prefix-map=$$(pwd)=..
  LDFLAGS += $(DEBUG_INFO)

  %.o: CXXFLAGS += $(DEFS) $(DEBUG_INFO) $(WARNINGS) -std=$(CXX_STD) -fno-omit-frame-pointer -fstack-protector-strong 

  $(TARGET): LDFLAGS += -Wl,-z,relro,-z,now,-z,noexecstack,-z,defs -fstack-protector-strong
endif # Debug
# ========================      Release    =================================
ifeq ($(strip $(BUILD)),Release)
  DEFS += -DNDEBUG -UDEBUG

  %.o: CXXFLAGS += $(DEFS) -O2 $(WARNINGS) -std=$(CXX_STD) -march=native -fPIE -fstack-protector-strong
  %.o: CXXFLAGS += -flto -fuse-linker-plugin -fstack-clash-protection
  $(TARGET): LDFLAGS += -O2 -pie -Wl,-pie -Wl,-z,defs,-z,relro,-z,now,-z,notext,-z,noexecstack,-s -fstack-protector-strong
  $(TARGET): LDFLAGS += -flto -fuse-linker-plugin -fPIE -fstack-clash-protection
endif # Release

# ========================   Pattern rules   ================================
%.o: %.cpp
	@echo --- C++ compiling [$(BUILD)] ---
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

%.d: %.cpp
	@echo --- Making C++ Dependency [$(BUILD)] ---
	$(RM) $@
	$(CPP) -MM $^ >> $@

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS_CXX)
	@echo --- Linking [$(BUILD)] ---
	$(CXX) $(LDFLAGS) $^ -o $@ $(LDLIBS)

clean:
	@echo --- Clean [$(BUILD)]  ---
	-$(RM) *.o $(DEPS)
	-$(RM) $(TARGET)

override undefine USE_CLEAN
ifeq ($(MAKECMDGOALS),clean)
   USE_CLEAN := 1
endif
ifeq ($(MAKECMDGOALS),distclean)
   USE_CLEAN := 1
endif
ifndef USE_CLEAN
   -include $(DEPS)
endif

