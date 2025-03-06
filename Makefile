CC=gcc
CFLAGS=-Wall -Wextra -std=c99 -lm

TARGETS=image_editor

build: $(TARGETS)

image_editor: image_editor.c
	$(CC) $(CFLAGS) image_editor.c -o image_editor -lm

clean:
	rm -f $(TARGETS)


