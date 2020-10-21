#main: main.c bibl.c bibl.h
#	cc main.c bibl.c -Wall -o main
#	echo "AKUKJU!"

OBJS=main.o bibl.o

main: $(OBJS)
	cc $^ -Wall -o main

#main.o: main.c 
#	cc main.c -c 

#bibl.o: bibl.c 
#	cc bibl.c -c 

%.o: %.c 
	cc $< -c 

test: main
	./main ../../L06/dane
	#./main
	#./main ../../L07/dane	

test_sortowanie: main
	./main dane_sort_1
	#./main
	#./main ../../L07/dane		