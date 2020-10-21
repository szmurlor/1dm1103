# poniżej wybieramy wariant implementacji - albo domyślnie za pomocą tablicy liczby typu double, albo za pomocą listy jednokierunkowej
CFLAGS=-DDEBUG -I../wspolne 
#CFLAGS=-DDEBUG -I../wspolne -DVEC_LIST
PROG=prog11_vec


$(PROG): bibl_vec.c prog11_vec.c 
	cc $^ -lm -o $(PROG) $(CFLAGS)

test: $(PROG)
	./$(PROG) ../dane/a.txt ../dane/x.txt w.txt
	python3 ../wspolne/plot.py 

clean:
	rm -f w.txt
	rm -f $(PROG)
