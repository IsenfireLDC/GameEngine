# Makefile for TerminalEngine
#

OBJECTS=$(patsubst %.cpp, %.o, $(wildcard *.cpp))

all: $(OBJECTS)
	g++ $(OBJECTS) -o Build/TerminalEngine.exe

%.o : %.cpp
	g++ -c $< -o $@



#Section to run program using winpty
run:
	winpty ./Build/TerminalEngine.exe
