CFLAGS=-DDEBUG -I../wspolne
PROG=prog11_vec

$(PROG): bibl_vec_array.c prog11_vec.c
	cc $^ -lm -o $(PROG) $(CFLAGS)

test: $(PROG)
	./$(PROG) ../dane/a.txt ../dane/x.txt w.txt
	python3 ../wspolne/plot.py 

clean:
	rm -f w.txt
	rm -f $(PROG)