MKDIR_P = mkdir -p

CXXFLAGS += -Wall -pedantic-errors -std=c++11
CXXFLAGS += -I.
CXXFLAGS += -I../JacobUtils
CXXFLAGS += -I../D3PDReaderAdapter
CXXFLAGS += -I/usr/local/Cellar/root6/6.02.05/include/root
CXXFLAGS += -I/usr/local/gmock/include

LDFLAGS += -L/usr/local/gmock/build/
LDFLAGS += -L/usr/local/lib/
LDFLAGS += -L/usr/local/Cellar/root6/6.02.05/lib/root

LDLIBS += -lc++
LDLIBS += -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lpthread -lmock

INCLUDE_DIR := TnPFitter
OBJECT_DIR := obj
SOURCE_DIR  = Root
LIBRARY_DIR := lib

TEST_DIR  = test
TEST_BIN  = test-bin

SOURCES := $(wildcard $(SOURCE_DIR)/*.cxx)
INCLUDES := $(SOURCES:$(SOURCE_DIR)/%.cxx=$(INCLUDE_DIR)/%.hpp)
TEST_SOURCES := $(wildcard $(TEST_DIR)/*.cxx)
TEST_BINS := $(TEST_SOURCES:$(TEST_DIR)/%.cxx=$(TEST_BIN)/%)
OBJECTS := $(SOURCES:$(SOURCE_DIR)/%.cxx=$(OBJECT_DIR)/%.o)
LIBRARY := $(LIBRARY_DIR)/libTnPFitter.a

all: directories $(LIBRARY) $(TEST_BINS)

directories:
	$(MKDIR_P) "obj"
	$(MKDIR_P) lib
	$(MKDIR_P) test-bin

$(TEST_BINS): $(TEST_SOURCES) $(OBJECTS)
	@$(LINK.cc) $@ $^
	@echo "Linking completed!"

$(OBJECTS): $(SOURCES)
	$(COMPILE.cc) $< -o $@
	@echo "Compiled "$<" successfully!"

$(LIBRARY): $(OBJECTS)
	$(AR) $(ARFLAGS) $(LIBRARY) $(OBJECTS)

print-dep:
	@echo 'Unit tests: '$(TEST_SOURCES)
	@echo 'Unit tests bins: '$(TEST_BINS)
	@echo 'Source files: '$(SOURCES)
	@echo 'Inlcudes files: '$(INCLUDES)
	@echo 'Object targets: '$(OBJECTS)

test: test-fitconfig test-singlegaus

test-fitconfig:
	$(TEST_BIN)/ut_FitConfig

test-singlegaus:
	$(TEST_BIN)/ut_SingleGausFit

.PHONY: clean distclean test

distclean: clean

clean:
	$(RM) ./$(OBJECT_DIR)/*.o
	$(RM) ./$(TEST_BIN)/*
	$(RM) ./$(LIBRARY_DIR)/*
