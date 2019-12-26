main: main.o matrix.o
	g++ -o main main.o matrix.o
main.o: main.cpp 
	g++ -c main.cpp
matrix.o: matrix.cpp 
	g++ -c matrix.cpp
clean:
	rm -rf *.o