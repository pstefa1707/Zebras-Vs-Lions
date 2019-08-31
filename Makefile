LIBS=-lsfml-graphics -lsfml-window -lsfml-system 

all: run

run:zebras-v-lions
	@echo 'Programmed by pstefa - running now'
	./zebras-v-lions

main.o: main.cpp
	g++ -std=c++11 -c "main.cpp" -o main.o -fopenmp

Grid.o: lib/Grid.cpp
	g++ -std=c++11 -c "lib/Grid.cpp" -o Grid.o -fopenmp

Animal.o: lib/Animal.cpp
	g++ -std=c++11 -c "lib/Animal.cpp" -o Animal.o

zebras-v-lions: main.o Grid.o Animal.o
	g++ -g -Wall -o zebras-v-lions main.o Grid.o Animal.o $(LIBS) -fopenmp && clear

del-app:
	rm -f zebras-v-lions

clean: del-app
	rm -f *.o && clear
	@echo 'successfully cleaned directory'
