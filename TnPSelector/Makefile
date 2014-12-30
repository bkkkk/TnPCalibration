CC      = g++
CFLAGS  = -Wall -I../JacobUtils/ -I../D3PDReaderAdapter/ -I. -I/usr/local/Cellar/root/5.34.24/include/root/ -std=c++11 -pedantic-errors

LINKER  = g++ -o
LDFLAGS = -Wall -I./ -I../D3PDReaderAdapter/ -I/usr/local/Cellar/root/5.34.24/include/root/ -L/usr/local/lib/ -L/usr/local/Cellar/root/5.34.24/lib/root -lcpptest -lCore -lPhysics

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

all: $(TSTBINS) test

$(TSTBINS): $(TSTBIN)/% : $(TSTCXX)/%.cxx $(OBJECTS)
	@$(LINKER) $@ $^ $(LDFLAGS)
	@echo "Linking completed!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cxx
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

test-first:
	@echo 'Running tests on Tree'
	./test-bin/ut_KinematicUtils

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

test: test-first
