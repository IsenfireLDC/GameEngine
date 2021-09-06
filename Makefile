# Makefile for TerminalEngine
#

OUT_DIR=bin/

DEBUG=-ggdb -g3

OBJECTS=$(patsubst %.cpp, $(OUT_DIR)%.o, $(wildcard *.cpp))
OUTFILE=$(OUT_DIR)TerminalEngine.exe

all: $(OBJECTS)
	g++ $(OBJECTS) -o $(OUTFILE)

$(OUT_DIR)%.o : %.cpp
	g++ -c $< -o $@


clean:
	rm $(OBJECTS) $(OUTFILE)



#Section to run program using winpty
run:
	winpty $(OUTFILE)
