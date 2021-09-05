FILES=main.cpp

all:
	g++ $(FILES) -o Build/TerminalEngine.exe

run:
	winpty ./Build/TerminalEngine.exe
