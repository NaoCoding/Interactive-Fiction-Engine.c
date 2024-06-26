
all:
	gcc ./src/main.c ./src/SMALLFUNCTION.h ./src/GLOBALVARIABLE.h ./src/PROCESS.h ./src/SCRIPT.h ./src/std.h -o engine -lm
	gcc ./src/api.c ./src/SMALLFUNCTION.h ./src/std.h -o api -lm

clear:
	-rm ./saves/*
	-rm ./output/*
	-rmdir ./saves ./output
	-rm ./api
	-rm ./engine

dev:
	-rm ./saves/*
	-rm ./output/*
	-rmdir ./saves ./output
	-rm ./api
	-rm ./engine
	gcc ./src/main.c ./src/SMALLFUNCTION.h ./src/GLOBALVARIABLE.h ./src/PROCESS.h ./src/SCRIPT.h ./src/std.h -o engine -lm
	gcc ./src/api.c ./src/SMALLFUNCTION.h ./src/std.h -o api -lm
	./engine ./example-game/

normal:
	-rm ./saves/*
	-rm ./output/*
	-rmdir ./saves ./output
	-rm ./api
	-rm ./engine
	gcc ./src/main.c ./src/SMALLFUNCTION.h ./src/GLOBALVARIABLE.h ./src/PROCESS.h ./src/SCRIPT.h ./src/std.h -o engine -lm
	gcc ./src/api.c ./src/SMALLFUNCTION.h ./src/std.h -o api -lm
	./engine ./example-game-normalgame/