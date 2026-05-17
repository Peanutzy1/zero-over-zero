CC = clang

SRCS = $(wildcard src/*.c)
OUT = build/zero-over-zero

MY_CFLAGS = -std=c23 -O0 -Wall -Wextra -Wpedantic -Werror -DPLATFORM_DESKTOP
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

.PHONY: all run clean

all: $(OUT)

$(OUT): $(SRCS)
	@mkdir -p build
	$(CC) $(SRCS) -o $(OUT) $(MY_CFLAGS) $(LIBS)

run: all
	./$(OUT)

clean:
	rm -rf build