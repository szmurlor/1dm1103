CFLAGS=-DDEBUG
prog11: bibl.c prog11.c ../wspolne/utils.h
	cc $^ -lm -o prog11 $(CFLAGS)

test: prog11
	./prog11 ../dane/a.txt ../dane/x.txt w.txt
	python3 ../wspolne/plot.py

clean:
	rm -f w.txt
	rm -f prog11