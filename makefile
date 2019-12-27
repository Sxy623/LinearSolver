OBJS = main.o utility.o matrix.o row.o solver.o vanillaSimplexSolver.o dualSimplexSolver.o 

main: $(OBJS)
	g++ -o main $(OBJS)
main.o: main.cpp 
	g++ -c main.cpp
utility.o: utility.cpp utility.h
	g++ -c utility.cpp
matrix.o: matrix.cpp matrix.h
	g++ -c matrix.cpp
row.o: row.cpp row.h
	g++ -c row.cpp
solver.o: solver.cpp solver.h
	g++ -c solver.cpp
vanillaSimplexSolver.o: vanillaSimplexSolver.cpp vanillaSimplexSolver.h
	g++ -c vanillaSimplexSolver.cpp
dualSimplexSolver.o: dualSimplexSolver.cpp dualSimplexSolver.h
	g++ -c dualSimplexSolver.cpp
clean:
	rm -rf *.o