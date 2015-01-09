# Compiler setup
CC     = g++
CFLAGS = -Wall -std=c++11 -pedantic-errors 
CFLAGS += -I. 
CFLAGS += -I../TnPSelector/ -I../JacobUtils/ -I../D3PDReaderAdapter/ 
CFLAGS += -I/usr/local/Cellar/root/5.34.24/include/root/ 
CFLAGS += -I/usr/local/gmock/include/

# Linker setup
LINKER  = g++ -o
LDFLAGS = -Wall

# Linker header includes
LDFLAGS += -I.
LDFLAGS += -I../D3PDReaderAdapter/
LDFLAGS += -I/usr/local/gmock/gtest/include/ -I/usr/local/gmock/include/
LDFLAGS += -I/usr/local/Cellar/root/5.34.24/include/root/ 

# Linker lib
LDFLAGS += -L/usr/local/lib/ 
LDFLAGS += -L../TnPSelector/lib/ -lTnPSelector 
LDFLAGS += -L/usr/local/Cellar/root/5.34.24/lib/root -lCore -lPhysics 
LDFLAGS += -L/usr/local/gmock/build/ -lmock 

INCLUDE_DIR = TruthNavigationTools
OBJECT_DIR  = lib
SOURCE_DIR  = Root

TEST_DIR     = test
TEST_BIN_DIR = test-bin

SOURCES   := $(wildcard $(SOURCE_DIR)/*.cxx)
TEST_CXX  := $(wildcard $(TEST_DIR)/*.cxx)
TEST_BINS := $(TEST_CXX:$(TEST_DIR)/%.cxx=$(TEST_BIN_DIR)/%)
OBJECTS   := $(SOURCES:$(SOURCE_DIR)/%.cxx=$(OBJECT_DIR)/%.o)
INCLUDES  := $(SOURCES:$(SOURCE_DIR)/%.cxx=$(INCLUDE_DIR)/%.hpp)

all: $(OBJECTS) $(TEST_BINS) test

$(TEST_BINS): $(TEST_BIN_DIR)/% : $(TEST_DIR)/%.cxx $(OBJECTS)
	@$(LINKER) $@ $^ $(LDFLAGS)
	@echo "Linking completed!"

$(OBJECTS): $(OBJECT_DIR)/%.o : $(SOURCE_DIR)/%.cxx
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

test-truthtools:
	@echo 'Testing TruthTools'
	@echo ''
	./test-bin/ut_TruthTools

print-dep:
	@echo 'Unit tests: '$(TEST_CXX)
	@echo 'Unit tests bins: '$(TEST_BINS)
	@echo 'Source files: '$(SOURCES)
	@echo 'Inlcudes files: '$(INCLUDES)
	@echo 'Object targets: '$(OBJECTS)

.PHONY: clean

clean:
	-rm -f ./$(OBJECT_DIR)/*.o
	-rm -f ./$(TEST_BIN_DIR)/*

test: test-truthtools
