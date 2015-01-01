CC      = g++
CFLAGS  = -Wall -I. -I../JacobUtils/ -I../D3PDReaderAdapter/ -I/usr/local/Cellar/root/5.34.24/include/root/ -I/usr/local/gmock/include/ -std=c++11 -pedantic-errors

LINKER  = g++ -o
LDFLAGS = -Wall -I. -I../D3PDReaderAdapter/ -I/usr/local/gmock/gtest/include/ -I/usr/local/Cellar/root/5.34.24/include/root/ -L/usr/local/gmock/build/ -lmock -L/usr/local/lib/ -L/usr/local/Cellar/root/5.34.24/lib/root -lcpptest -lCore -lPhysics

INCDIR  = TnPSelector
OBJDIR  = lib
SRCDIR  = Root

TSTCXX  = test
TSTBIN  = test-bin

SOURCES  := $(wildcard $(SRCDIR)/*.cxx)
TSTFILES := $(wildcard $(TSTCXX)/*.cxx)
TSTBINS  := $(TSTFILES:$(TSTCXX)/%.cxx=$(TSTBIN)/%)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cxx=$(OBJDIR)/%.o)
INCLUDES := $(SOURCES:$(SRCDIR)/%.cxx=$(INCDIR)/%.hpp)

all: $(OBJECTS) $(TSTBINS) test

$(TSTBINS): $(TSTBIN)/% : $(TSTCXX)/%.cxx $(OBJECTS)
	@$(LINKER) $@ $^ $(LDFLAGS)
	@echo "Linking completed!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cxx
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

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
