all: 
	gcc `pkg-config --cflags gtk+-3.0` first.c -o first `pkg-config --libs gtk+-3.0`

test: all
	./first