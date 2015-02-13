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
						 -I../JacobUtils/ \
						 -I/usr/local/gmock/gtest/include/ \
						 -I/usr/local/Cellar/root/5.34.25/include/root/ \

LDLIBS     = -L/usr/local/gmock/build/ -lmock \
				     -L/usr/local/lib/ \
				     -L/usr/local/Cellar/root/5.34.25/lib/root -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lpthread \
				     -lc++

LINKER  = clang -o
LDFLAGS = $(EXTRA_CCFLAGS) \
				  $(DEBUG_LEVEL) \
				  $(COMPILER_STD) \
				  $(LDINCLUDES) \
				  $(LDLIBS)

ARCHIVER = ar
ARFLAGS  = -cr

INCDIR  = TnPFitter
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
LIBRARY  := $(LIBDIR)/libTnPFitter.a

all: $(OBJECTS) $(LIBRARY) $(TSTBINS)

$(TSTBINS): $(TSTBIN)/% : $(TSTCXX)/%.cxx $(OBJECTS)
	@$(LINKER) $@ $^ $(LDFLAGS)
	@echo "Linking completed!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cxx
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

$(LIBRARY): $(OBJECTS)
	$(ARCHIVER) $(ARFLAGS) $(LIBRARY) $(OBJECTS)

print-dep:
	@echo 'Unit tests: '$(TSTFILES)
	@echo 'Unit tests bins: '$(TSTBINS)
	@echo 'Source files: '$(SOURCES)
	@echo 'Inlcudes files: '$(INCLUDES)
	@echo 'Object targets: '$(OBJECTS)

test: test-fitconfig test-singlegaus

test-fitconfig:
	$(TSTBIN)/ut_FitConfig

test-singlegaus:
	$(TSTBIN)/ut_SingleGausFit

.PHONY: clean

clean:
	-rm -f ./$(OBJDIR)/*.o
	-rm -f ./$(TSTBIN)/*
	-rm -f ./$(LIBDIR)/*
