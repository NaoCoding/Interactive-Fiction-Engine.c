all:
	gcc ./src/main.c ./src/SMALLFUNCTION.h ./src/GLOBALVARIABLE.h ./src/PROCESS.h ./src/SCRIPT.h ./src/std.h -o engine -lm