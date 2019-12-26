OBJS = main.o matrix.o row.o

main: $(OBJS)
	g++ -o main $(OBJS)
main.o: main.cpp 
	g++ -c main.cpp
matrix.o: matrix.cpp matrix.h
	g++ -c matrix.cpp
row.o: row.cpp row.h
	g++ -c row.cpp
clean:
	rm -rf *.o