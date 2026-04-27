FLAGS = -pedantic-errors -std=c++11 -Wall -Wextra

blockblast: main.o game.o grid.o screen.o combat.o player.o chooseblocks.o window.o blocklist.o blockfunction.o blockplay.o enemyArt.o
	g++ $(FLAGS) main.o game.o grid.o screen.o combat.o player.o chooseblocks.o window.o blocklist.o blockfunction.o blockplay.o enemyArt.o -o blockblast

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

chooseblocks.o: chooseblocks.cpp chooseblocks.h blockfunction.h gamedata.h 
	g++ $(FLAGS) -c chooseblocks.cpp

window.o: window.cpp windows.h screen.h grid.h blocklist.h
	g++ $(FLAGS) -c window.cpp

blocklist.o: blocklist.cpp blocklist.h chooseblocks.h 
	g++ $(FLAGS) -c blocklist.cpp

blockfunction.o: blockfunction.cpp blockfunction.h chooseblocks.h gamedata.h blocklist.h
	g++ $(FLAGS) -c blockfunction.cpp

enemyArt.o: enemyArt.cpp enemyArt.h
	g++ $(FLAGS) -c enemyArt.cpp

blockplay.o: blockplay.cpp blockplay.h gamedata.h blockfunction.h chooseblocks.h blocklist.h
	g++ $(FLAGS) -c blockplay.cpp

clean:
	rm -f blockblast main.o game.o grid.o screen.o combat.o player.o chooseblocks.o window.o blocklist.o blockfunction.o blockplay.o enemyArt.o

.PHONY: clean