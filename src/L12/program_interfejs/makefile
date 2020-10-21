CFLAGS=-DDEBUG -DWARIANT_LISTA
prog12: bibl.c prog12.c ../wspolne/utils.h
	cc $^ -lm -o prog12 $(CFLAGS)

test: prog12
	./prog12 ../dane/a.txt ../dane/x.txt w.txt
	python3 ../wspolne/plot.py

clean:
	rm -f w.txt
	rm -f prog12
