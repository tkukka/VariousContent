SHELL = /bin/sh
.SUFFIXES:
.SUFFIXES: .java .class
# Java settings
OUTPUT_DIR := ./bin
JAR_FILE := StudyCards.jar
JAVA_SOURCES := FileHandler.java StudyCards.java StudyCardsController.java WordPair.java WordPairList.java
JAVA_CLASSES := $(addprefix $(OUTPUT_DIR)/,$(JAVA_SOURCES:.java=.class))
JAVAC := javac
JAVAC_FLAGS := -encoding UTF-8 -Werror -Xlint:all -Xdiags:verbose 
MANIFEST := ./Manifest.txt

# ========================   Pattern rules   ================================
#$(OUTPUT_DIR)/%.class: %.java
#	@echo --- Java compiling: $< ---
#	$(JAVAC) $(JAVAC_FLAGS) $< -d $(OUTPUT_DIR)
#	@echo

.PHONY: all clean

all: $(OUTPUT_DIR)/$(JAR_FILE)

$(OUTPUT_DIR):
	-test -d $(OUTPUT_DIR) || mkdir $(OUTPUT_DIR)

$(JAVA_CLASSES): $(JAVA_SOURCES) | $(OUTPUT_DIR)
	@echo --- Java compiling ---
	$(JAVAC) $(JAVAC_FLAGS) $^ -d $(OUTPUT_DIR)
	@echo

$(OUTPUT_DIR)/$(JAR_FILE): $(JAVA_CLASSES) $(MANIFEST)
	@echo --- Making Java Archive: $@ ---
	cd $(OUTPUT_DIR) && jar --verbose --create --manifest ../$(MANIFEST) --file $(JAR_FILE) *.class

clean:
	-$(RM) $(JAVA_CLASSES) $(OUTPUT_DIR)/$(JAR_FILE)
	-rmdir $(OUTPUT_DIR) || true

