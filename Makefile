FLAGS = -pedantic-errors -std=c++11 -Wall -Wextra

# Default target: typing `make` alone builds the full game.
blockblast: main.o game.o
	g++ $(FLAGS) main.o game.o -o blockblast

main.o: main.cpp game.h
	g++ $(FLAGS) -c main.cpp

game.o: game.cpp game.h
	g++ $(FLAGS) -c game.cpp

# When Member A pushes board.cpp/h and block.cpp/h, add:
# board.o: board.cpp board.h
# 	g++ $(FLAGS) -c board.cpp
# block.o: block.cpp block.h
# 	g++ $(FLAGS) -c block.cpp
#
# When Member B pushes player.cpp/h, combat.cpp/h, fileio.cpp/h, add similar rules.
# Then add the new .o files to BOTH the blockblast rule and the clean rule.

clean:
	rm -f blockblast main.o game.o

.PHONY: clean