# Makefile for TerminalEngine
#

OUT_DIR=bin/
SRC_DIR=src/
INC_DIR=inc/

DEBUG=-ggdb -g3
LIBS=-pthread

FLAGS=-Wall -I$(INC_DIR)
#FLAGS+=-std=c++2a
#FLAGS+=$(DEBUG)
FLAGS+=$(LIBS)

OBJECTS=$(patsubst $(SRC_DIR)%.cpp, $(OUT_DIR)%.o, $(wildcard $(SRC_DIR)*.cpp))
DEPENDS=$(patsubst $(SRC_DIR)%.cpp, $(OUT_DIR)%.d, $(wildcard $(SRC_DIR)*.cpp))
OUTFILE=./TerminalEngine.exe

all: $(OBJECTS)
	g++ $(OBJECTS) $(FLAGS) -o $(OUTFILE)

debug: FLAGS += $(DEBUG)
debug: all

-include $(DEPENDS)

$(OUT_DIR)%.o : $(SRC_DIR)%.cpp
	g++ -MMD -MP $(FLAGS) -c $< -o $@


# Clean objects, dependencies, and executable
clean:
	rm $(OBJECTS) $(DEPENDS) $(OUTFILE)



#Section to run program using winpty
run:
	@winpty $(OUTFILE)
