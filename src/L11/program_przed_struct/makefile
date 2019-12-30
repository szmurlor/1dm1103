CFLAGS=-DDEBUG -I../wspolne 
PROG=prog11_struct


$(PROG): bibl_struct.c prog11_struct.c 
	cc $^ -lm -o $(PROG) $(CFLAGS)

test: $(PROG)
	./$(PROG) ../dane/a.txt ../dane/x.txt w.txt
	python3 ../wspolne/plot.py 

clean:
	rm -f w.txt
	rm -f $(PROG)
