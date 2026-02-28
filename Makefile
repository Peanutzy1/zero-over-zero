CC = clang

SRC = src/main.c
OUT = build/zero-over-zero.exe

MY_CFLAGS = -std=c23 -I/C/msys64/ucrt64/include -O3 -Wall -Wextra -Werror -DPLATFORM_DESKTOP
LIBS = -L/C/msys64/ucrt64/lib -lraylib -lgdi32 -lwinmm -lopengl32 -lshell32

all:
	mkdir -p build
	$(CC) $(SRC) -o $(OUT) $(MY_CFLAGS) $(LIBS)

run: all
	./$(OUT)

clean:
	rm -rf build