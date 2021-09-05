FILES=main.cpp entity.cpp

all:
	g++ $(FILES) -o Build/TerminalEngine.exe

run:
	winpty ./Build/TerminalEngine.exe
