CC      		  = clang -O2
ERROR_LEVEL   = -pedantic-errors
DEBUG_LEVEL   = -lprofiler
COMPILER_STD  = -std=c++11
EXTRA_CCFLAGS = -Wall

CINCLUDES = -I. \
						-I../JacobUtils/ \
						-I../D3PDReaderAdapter/ \
						-I/usr/local/Cellar/root/5.34.25/include/root/ \
						-I/usr/local/gmock/include/

CFLAGS  = $(EXTRA_CCFLAGS) \
				  $(ERROR_LEVEL) \
				  $(COMPILER_STD) \
				  $(CINCLUDES) \

LDINCLUDES = -I. \
						 -I../D3PDReaderAdapter/ \
						 -I/usr/local/gmock/gtest/include/ \
						 -I/usr/local/Cellar/root/5.34.25/include/root/ \

LDLIBS     = -L/usr/local/gmock/build/ -lmock \
				     -L/usr/local/lib/ \
				     -L/usr/local/Cellar/root/5.34.25/lib/root -lCore -lPhysics \
				     -lc++

LINKER  = clang -o
LDFLAGS = $(EXTRA_CCFLAGS) \
				  $(DEBUG_LEVEL) \
				  $(COMPILER_STD) \
				  $(LDINCLUDES) \
				  $(LDLIBS)

ARCHIVER = ar
ARFLAGS  = -cr

INCDIR  = TnPSelector
OBJDIR  = obj
SRCDIR  = Root
LIBDIR  = lib

TSTCXX  = test
TSTBIN  = test-bin

SOURCES  := $(wildcard $(SRCDIR)/*.cxx)
TSTFILES := $(wildcard $(TSTCXX)/*.cxx)
TSTBINS  := $(TSTFILES:$(TSTCXX)/%.cxx=$(TSTBIN)/%)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cxx=$(OBJDIR)/%.o)
INCLUDES := $(SOURCES:$(SRCDIR)/%.cxx=$(INCDIR)/%.hpp)
LIBRARY  := $(LIBDIR)/libTnPSelector.a

all: $(OBJECTS) $(LIBRARY) $(TSTBINS)

$(TSTBINS): $(TSTBIN)/% : $(TSTCXX)/%.cxx $(OBJECTS)
	@$(LINKER) $@ $^ $(LDFLAGS)
	@echo "Linking completed!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cxx
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

$(LIBRARY): $(OBJECTS)
	$(ARCHIVER) $(ARFLAGS) $(LIBRARY) $(OBJECTS)

test-tag:
	@echo 'Testing Tag Selector'
	@echo ''
	./test-bin/ut_TagSelector

test-kinematic:
	@echo 'Testing KinematicUtils'
	@echo ''
	./test-bin/ut_KinematicUtils

test-mp:
	@echo 'Testing Muon Probe Selector'
	@echo ''
	./test-bin/ut_MuonProbeSelector

test-probe:
	@echo 'Testing Probe Selector'
	@echo ''
	./test-bin/ut_ProbeSelector	

test-smt:
	@echo 'Testing Probe Selector'
	@echo ''
	./test-bin/ut_SMTSelector	

print-dep:
	@echo 'Unit tests: '$(TSTFILES)
	@echo 'Unit tests bins: '$(TSTBINS)
	@echo 'Source files: '$(SOURCES)
	@echo 'Inlcudes files: '$(INCLUDES)
	@echo 'Object targets: '$(OBJECTS)

.PHONY: clean

clean:
	-rm -f ./$(OBJDIR)/*.o
	-rm -f ./$(TSTBIN)/*

test: test-kinematic test-tag test-probe test-mp

test-perf: perf-tag
