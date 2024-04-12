# Makefile for GameEngine
NAME=GameEngine

STATIC_LIBS:=
SHARED_LIBS:=SDL2 image

# Project directories
SRCDIR:=src
INCDIR:=inc
OBJDIR:=bin

# Custom library directories
SHLIBSDIR:=$(CUSTOM_LIBS_DIR)

SHLIBDIR:=$(SHLIBSDIR)/shared
SHARCDIR:=$(SHLIBSDIR)/static
SHINCDIR:=$(SHLIBSDIR)/headers

# Platform settings
UNAME:=$(shell uname)

ifeq ($(UNAME),Linux)
EXT.EXEC:=elf
EXT.DLIB:=so
EXT.SLIB:=a

PF.FLAGS:=
PF.RUN=./$(EXEC)
else ifeq ($(UNAME),Windows)
SHARED_LIBS:=mingw32 $(SHARED_LIBS)

EXT.EXEC:=exe
EXT.DLL:=dll
EXT.SLIB:=a

PF.FLAGS:=-mwindows
PF.RUN=winpty ./$(EXEC)
endif

# Build files
SRCS=$(foreach dir,$(shell find $(SRCDIR) -type d),$(wildcard $(dir)/*.cpp))
OBJS=$(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))
SHOBJS=$(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.so,$(SRCS))
DEPS=$(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.d,$(SRCS)) $(LIBDEPS)

# Output files
SHLIB:=$(OBJDIR)/lib$(NAME).$(EXT.DLIB)
STLIB:=$(OBJDIR)/lib$(NAME).$(EXT.SLIB)
EXEC:=$(NAME).$(EXT.EXEC)

DIRS=$(SRCDIR)/ $(OBJDIR)/ $(INCDIR)/

DEBUG=-ggdb -g3
LIBS=

# Add custom libraries
# Static libraries
OBJS+=$(foreach lname,$(STATIC_LIBS),$(shell find $(SHARCDIR) -iname "lib$(lname).a"))
# Shared libraries
LIBS+=$(foreach lname,$(SHARED_LIBS),-l$(lname))

FLAGS=-Wall -I$(INCDIR) -I$(SHINCDIR) -L$(SHARCDIR) -L$(SHLIBDIR) $(PF.FLAGS) -pthread
#FLAGS+=-Dmain=SDL_main

#FLAGS+=$(shell sdl2-config --cflags)
#LIBS+=$(shell sdl2-config --libs)

FLAGS+=$(LIBS)



all: exec

libs: shlib stlib

# Makefile rules
debug: FLAGS+=$(DEBUG)
debug: all

exec: $(EXEC)

shlib: $(SHLIB)

stlib: $(STLIB)

dirs: $(DIRS)

-include $(DEPS)

$(EXEC): $(OBJS)
	g++ $^ $(FLAGS) -o $(EXEC)


$(OBJDIR)/lib%.$(EXT.SLIB): $(filter-out $(OBJDIR)/main.o, $(OBJS))
	ar rcs $@ $^

$(OBJDIR)/lib%.$(EXT.DLIB): $(filter-out $(OBJDIR)/main.so, $(SHOBJS))
	g++ $^ -shared $(FLAGS) -o $@


$(OBJDIR)/%.so : $(SRCDIR)/%.cpp
	g++ -MMD -MP -fpic $(FLAGS) -c $< -o $@

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	g++ -MMD -MP $(FLAGS) -c $< -o $@


%/:
	mkdir -p $@

update: shlib stlib
	cp $(SHLIB) $(SHLIBDIR)/
	cp $(STLIB) $(SHARCDIR)/
	cp -r $(INCDIR)

clean:
	rm -f $(OBJS) $(SHOBJS) $(DEPS) $(SHLIB) $(STLIB) $(EXEC)


#Run program using winpty
run: $(EXEC)
	@$(PF.RUN)

.PHONY: all libs debug exec shlib stlib dirs update clean run
