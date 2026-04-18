FLAGS = -pedantic-errors -std=c++11 -Wall -Wextra

blockblast: main.o game.o grid.o screen.o combat.o player.o
	g++ $(FLAGS) main.o game.o grid.o screen.o combat.o player.o -o blockblast

main.o: main.cpp game.h
	g++ $(FLAGS) -c main.cpp

game.o: game.cpp game.h grid.h screen.h
	g++ $(FLAGS) -c game.cpp

grid.o: grid.cpp grid.h screen.h
	g++ $(FLAGS) -c grid.cpp

screen.o: screen.cpp screen.h
	g++ $(FLAGS) -c screen.cpp

combat.o: combat.cpp combat.h
	g++ $(FLAGS) -c combat.cpp

player.o: player.cpp player.h
	g++ $(FLAGS) -c player.cpp

clean:
	rm -f blockblast main.o game.o grid.o screen.o combat.o player.o

.PHONY: clean