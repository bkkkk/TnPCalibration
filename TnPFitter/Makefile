BUILD ?= debug

TARGET := TnPFitter

RM += -r

MKDIR_P = mkdir -p

CXXFLAGS += -Wall -Wextra -Wstring-plus-int -pedantic -Werror -Wunreachable-code -std=c++11
CXXFLAGS += -MMD -MP
CXXFLAGS += -I.
CXXFLAGS += -I../JacobUtils
CXXFLAGS += -I../D3PDReaderAdapter
CXXFLAGS += -I../RootAdapters
CXXFLAGS += -I/usr/local/Cellar/root6/6.02.05/include/root
CXXFLAGS += -I/usr/local/gmock/include
CXXFLAGS += -I/usr/local/gmock/gtest/include

LDFLAGS += -L/usr/local/gmock/build/
LDFLAGS += -L/usr/local/lib/
LDFLAGS += -L/usr/local/Cellar/root6/6.02.05/lib/root

LDLIBS += -lc++
LDLIBS += -lCore -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lpthread -lm -ldl
LDLIBS += -lmock

# Input directories
ROOT = $(shell dirname 'pwd')
SOURCE_DIR := $(ROOT)/src
INCLUDE_DIR := $(ROOT)/$(TARGET)
TEST_DIR := $(ROOT)/test

# Output directories
OBJECT_DIR := obj
LIBRARY_DIR := lib
TEST_BIN_DIR := test-bin
DEP_DIR = .deps

# Input files
SOURCES = $(wildcard $(SOURCE_DIR)/*.cxx)
INCLUDES = $(SOURCES:$(SOURCE_DIR)/%.cxx=$(INCLUDE_DIR)/%.hpp)
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.cxx)

# Output
OBJECTS = $(SOURCES:$(SOURCE_DIR)/%.cxx=$(OBJECT_DIR)/%.o)
LIBRARY = $(LIBRARY_DIR)/lib$(TARGET).a
DEP_FILES = $(DEP_DIR)/$(*F)
TEST_BINS = $(TEST_SOURCES:$(TEST_DIR)/%.cxx=$(TEST_BIN_DIR)/%)

all: directories $(LIBRARY) $(TEST_BINS)

directories:
	@$(MKDIR_P) $(OBJECT_DIR)
	@$(MKDIR_P) $(LIBRARY_DIR)
	@$(MKDIR_P) $(TEST_BIN_DIR)
	@$(MKDIR_P) $(DEP_DIR)

-include $(TEST_SOURCES:$(TEST_DIR)/%.cxx=$(DEP_DIR)/%.d)

$(TEST_BIN_DIR)/%: $(TEST_DIR)/%.cxx
	@echo "Link: $@"
	@$(LINK.cc) $(LDLIBS) -L$(LIBRARY_DIR) -l$(TARGET) $< -o $@
	@mv $(TEST_BIN_DIR)/*.d $(DEP_DIR)/

-include $(SOURCES:$(SOURCE_DIR)/%.cxx=$(DEP_DIR)/%.d)

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.cxx
	@echo "Compile: $@"
	@$(COMPILE.cc) $< -o $@
	@mv $(OBJECT_DIR)/*.d $(DEP_DIR)/

$(LIBRARY): $(OBJECTS)
	@echo "Archiving: $@"
	@$(AR) $(ARFLAGS) $(LIBRARY) $(OBJECTS)

.PHONY: print-dep
print-dep:
	@echo 'Unit tests: '$(TEST_SOURCES)
	@echo 'Unit tests bins: '$(TEST_BINS)
	@echo 'Source files: '$(SOURCES)
	@echo 'Inlcudes files: '$(INCLUDES)
	@echo 'Object targets: '$(OBJECTS)

.PHONY: test
test:
	sh ./run_tests.sh

.PHONY: distclean
distclean: clean

.PHONY: clean
clean:
	$(RM) ./$(OBJECT_DIR)
	$(RM) ./$(TEST_BIN_DIR)
	$(RM) ./$(LIBRARY_DIR)
