all:
	gcc ./src/main.c ./src/ui.h ./src/smallfn.h ./src/script.h ./src/std.h -o engine -lm