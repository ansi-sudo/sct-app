# Allow Buildroot to pass CC, CFLAGS, and LDFLAGS
all: sct-app

sct-app: main.c
$(CC) $(CFLAGS) main.c -o sct-app $(LDFLAGS) -lSDL2 -lSDL2_ttf -lSDL2_image

clean:
rm -f sct-app