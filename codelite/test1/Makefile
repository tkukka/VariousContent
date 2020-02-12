SHELL = /bin/sh
BUILD = Debug
TARGET = ./$(BUILD)/test1
.SUFFIXES:
.SUFFIXES: .c .h .cpp .o .a
CC = gcc
CXX = g++
CPP = $(CXX) -E
SIZE = size -B

ifeq ($(strip $(BUILD)),Debug)
   DEFS = -DDEBUG -UNDEBUG
   CFLAGS += $(DEFS) -g3 -ggdb -Og -pedantic -Wall -Wextra -std=c11
   CXXFLAGS += $(DEFS) -g3 -ggdb -Og -pedantic -Wall -Wextra -std=c++17
   LDFLAGS += -Wl,-z,defs -Wl,-z,now -Wl,-M=$(TARGET).map
else
   DEFS = -DNDEBUG -UDEBUG
   CFLAGS += $(DEFS) -O2 -pedantic -Wall -Wextra -std=c11 -march=native
   CXXFLAGS += $(DEFS) -O2 -pedantic -Wall -Wextra -std=c++17 -march=native
   LDFLAGS += -Wl,-z,defs -Wl,-z,now -Wl,-M=$(TARGET).map -Wl,-s
endif

SRCS_C =
SRCS_CXX = test1.cpp
SRCS = $(SRCS_CXX) $(SRCS_C)
OBJS_CXX = $(SRCS_CXX:.cpp=.o)
OBJS_C = $(SRCS_C:.c=.o)
OBJS := $(addprefix ./$(BUILD)/,$(OBJS_CXX)) $(addprefix ./$(BUILD)/,$(OBJS_C))
DEPEND = ./.depend.$(BUILD)

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
	$(CXX) $(LDFLAGS) $(OBJS) -o $@ $(LDLIBS) 

memsize: $(TARGET)
	@echo --- Memory usage ---
	$(SIZE) $(OBJS) $(TARGET)

depend: $(DEPEND)

$(DEPEND): $(SRCS)
	@echo --- Depencies ---
	$(RM) $(DEPEND)
	$(CPP) -MM $^ >> $(DEPEND).tmp
	gawk -v S="./$(BUILD)/" -F: '{printf "%s%s:%s\n",S,$$1,$$2}' $(DEPEND).tmp >> $(DEPEND)
	$(RM) $(DEPEND).tmp

clean:
	@echo --- Clean ---
	$(RM) $(OBJS) $(TARGET) $(TARGET).map

distclean: clean
	@echo --- Distclean ---
	$(RM) $(DEPEND)
	rmdir $(BUILD) || true

override undefine USE_CLEAN
ifeq ($(MAKECMDGOALS),clean)
   USE_CLEAN := 1
endif
ifeq ($(MAKECMDGOALS),distclean)
   USE_CLEAN := 1
endif
ifndef USE_CLEAN
   -include $(DEPEND)           # ./$(BUILD)/test1.o: test1.cpp test1.h
endif

