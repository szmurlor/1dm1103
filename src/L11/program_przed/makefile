CFLAGS=-DDEBUG
prog11: bibl.c prog11.c utils.h
	cc $^ -lm -o prog11 $(CFLAGS)

test: prog11
	./prog11 a.txt x.txt w.txt
	python3 plot.py 

prog11_struct: bibl_vec_struct.c prog11_vec_struct.c utils.h
	cc $^ -lm -o prog11_struct $(CFLAGS)

test_struct: prog11_struct
	./prog11_struct a.txt x.txt w.txt
	python3 plot.py 


clean:s
	rm -f w.txt
	rm -f prog11