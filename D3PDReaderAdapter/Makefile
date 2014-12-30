CC      = g++
CFLAGS  = -Wall -I. -std=c++11 -pedantic-errors

LINKER  = g++ -o
LDFLAGS = -Wall -L/usr/local/lib/ -lcpptest

INCDIR  = include
OBJDIR  = lib
SRCDIR  = src

TSTCXX  = test
TSTBIN  = test-bin

SOURCES  := $(wildcard $(SRCDIR)/*.cpp)
TSTFILES := $(wildcard $(TSTCXX)/*.cpp)
TSTBINS  := $(TSTFILES:$(TSTCXX)/%.cpp=$(TSTBIN)/%)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
INCLUDES := $(SOURCES:$(SRCDIR)/%.cpp=$(INCDIR)/%.hpp)

all: $(TSTBINS) test

$(TSTBINS): $(TSTBIN)/% : $(TSTCXX)/%.cpp $(OBJECTS)
	@$(LINKER)  $^ $(LDFLAGS)
	@echo 'Linking completed!'

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(CC) $(CFLAGS) -c $< -o 
	@echo 'Compiled "$<" successfully!'

test-first:
	@echo 'Running tests on Tree'
	bash -c "for ut in test-bin/*; do ./test-bin/; done;"

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
