FLAGS = -pedantic-errors -std=c++11 -Wall -Wextra

blockblast: main.o game.o grid.o screen.o combat.o player.o lines.o grid_window.o log_window.o status_window.o
	g++ $(FLAGS) main.o game.o grid.o screen.o combat.o player.o lines.o grid_window.o log_window.o status_window.o -o blockblast

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

lines.o: lines.cpp lines.h
	g++ $(FLAGS) -c lines.cpp

grid_window.o: grid_window.cpp windows.h screen.h grid.h
	g++ $(FLAGS) -c grid_window.cpp

log_window.o: log_window.cpp windows.h screen.h
	g++ $(FLAGS) -c log_window.cpp

status_window.o: status_window.cpp windows.h screen.h
	g++ $(FLAGS) -c status_window.cpp

clean:
	rm -f blockblast main.o game.o grid.o screen.o combat.o player.o lines.o grid_window.o log_window.o status_window.o

.PHONY: clean