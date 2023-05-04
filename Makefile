FLAGS = -pedantic-errors -std=c++11

main: main.o gameplay.o graphics.o fileManipulation.o
	g++ $(FLAGS) $^ -o $@

main.o: main.cpp
	g++ $(FLAGS) -c main.cpp
	
gameplay.o: gameplay.cpp gameplay.h
	g++ $(FLAGS) -c gameplay.cpp

graphics.o: graphics.cpp graphics.h color.h
	g++ $(FLAGS) -c graphics.cpp

fileManipulation.o: fileManipulation.cpp fileManipulation.h
	g++ $(FLAGS) -c fileManipulation.cpp


clean:
	rm -f main *.o

.PHONY: clean
