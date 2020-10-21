#CFLAGS=-DDEBUG
prog10: bibl.c prog10.c
	cc $^ -lm -o prog10 $(CFLAGS)

test: prog10
	./prog10 a.txt x.txt wynik.txt
	python3 plot.py

clean:
	rm -f prog10
	rm -f *.o
	rm -f wynik.txt