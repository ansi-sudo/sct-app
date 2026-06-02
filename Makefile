CC ?= gcc
CXX ?= g++
CFLAGS += $(shell sdl2-config --cflags)
LDFLAGS += $(shell sdl2-config --libs) -lSDL2_ttf -lSDL2_image

all: sct-app

sct-app: main.c
	$(CC) $(CFLAGS) -o sct-app main.c $(LDFLAGS)

clean:
	rm -f sct-app