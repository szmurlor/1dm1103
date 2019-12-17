CFLAGS=-DDEBUG
prog09: bibl.c prog10.c utils.h
	cc $^ -lm -o prog09 $(CFLAGS)

test: prog09
	./prog09 a.txt x.txt w.txt
	python3 plot.py 

clean:
	rm -f w.txt
	rm -f prog09