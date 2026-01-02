CC = emcc
CFLAGS = -std=c23 -Iinclude -O3 -Wall -Wextra -Werror -Wpedantic -s WASM=1 -s EXPORTED_FUNCTIONS='["_init_engine"]'
SRC = src/main.c
OUT = web/engine.js

all:
	$(CC) $(SRC) -o $(OUT) $(CFLAGS)


clean:
	rm -f web/engine.js web/engine.wasm