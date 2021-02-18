game.exe: game_playing.o game_control.o main.o
	g++ -o game main.o game_control.o game_playing.o -lncurses
	
game_control.o: game_control.cpp game_control.h
	g++ -c game_control.cpp -lncurses
	
game_playing.o: game_playing.cpp game_playing.h
	g++ -c game_playing.cpp -lncurses
	
main.o: main.cpp game_control.h game_playing.h
	g++ -c main.cpp -lncurses

clean :
	rm game_control.o game_playing.o main.o  game.exe
