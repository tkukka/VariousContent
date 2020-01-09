SHELL = /bin/sh
BUILD = Debug
TARGET = ./$(BUILD)/test1
.SUFFIXES:
.SUFFIXES: .c .h .cpp .o .a
CC = gcc
CXX = g++
CPP = $(CXX) -E

ifeq ($(strip $(BUILD)),Debug)
   DEFS = -DDEDUG -UNDEBUG
   CFLAGS += $(DEFS) -g3 -ggdb -O0 -pedantic -Wall -Wextra -std=C99 -pie
   CXXFLAGS += $(DEFS) -g3 -ggdb -O0 -pedantic -Wall -Wextra -std=c++17 -pie
   LDFLAGS += -Wl,-pie -Wl,-z,defs -Wl,-z,now -Wl,-M=$(TARGET).map
else
   DEFS = -DNDEDUG -UDEBUG
   CFLAGS += $(DEFS) -O2 -pedantic -Wall -Wextra -std=C99 -pie -s
   CXXFLAGS += $(DEFS) -O2 -pedantic -Wall -Wextra -std=c++17 -pie
   LDFLAGS += -Wl,-pie -Wl,-z,defs -Wl,-z,now -Wl,-M=$(TARGET).map -Wl,-s
endif

SRCS_C =
SRCS_CXX = test1.cpp
SRCS = $(SRCS_CXX) $(SRCS_C)
OBJS_CXX = $(SRCS_CXX:.cpp=.o)
OBJS_C = $(SRCS_C:.c=.o)
SIZE = size -B
DEPEND = ./.depend.$(BUILD)

ifeq ($(strip $(SRCS_C)),)
   OBJS := $(addprefix ./$(BUILD)/,$(OBJS_CXX))
else
   OBJS := $(addprefix ./$(BUILD)/,$(OBJS_CXX)) $(addprefix ./$(BUILD)/,$(OBJS_C))
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
	-test -d $(BUILD) && rmdir $(BUILD)

ifneq ($(MAKECMDGOALS),clean)
   -include $(DEPEND)           # ./$(BUILD)/test1.o: test1.cpp test1.h
endif
