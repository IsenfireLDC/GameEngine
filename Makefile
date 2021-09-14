# Makefile for TerminalEngine
#

OUT_DIR=bin/
SRC_DIR=src/
INC_DIR=inc/

DEBUG=-ggdb -g3

FLAGS=-Wall -I$(INC_DIR)
#FLAGS+=$(DEBUG)

OBJECTS=$(patsubst $(SRC_DIR)%.cpp, $(OUT_DIR)%.o, $(wildcard $(SRC_DIR)*.cpp))
DEPENDS=$(patsubst $(SRC_DIR)%.cpp, $(OUT_DIR)%.d, $(wildcard $(SRC_DIR)*.cpp))
OUTFILE=$(OUT_DIR)TerminalEngine.exe

all: $(OBJECTS)
	g++ $(OBJECTS) -o $(OUTFILE)

-include $(DEPENDS)

$(OUT_DIR)%.o : $(SRC_DIR)%.cpp
	g++ $(FLAGS) -MMD -MP -c $< -o $@


# Clean objects, dependencies, and executable
clean:
	rm $(OBJECTS) $(DEPENDS) $(OUTFILE)



#Section to run program using winpty
run:
	@winpty $(OUTFILE)
