all:
	g++ TerminalGame.cpp -o Build/TerminalGame.exe

run:
	winpty ./Build/TerminalGame.exe
