CC ?= gcc
CFLAGS ?= -Wall -O2 $(shell pkg-config --cflags sdl2 SDL2_ttf SDL2_image)
LDFLAGS ?= $(shell pkg-config --libs sdl2 SDL2_ttf SDL2_image)

all: my-app

my-app: main.c
    $(CC) $(CFLAGS) main.c -o my-app $(LDFLAGS)

clean:
    rm -f my-app