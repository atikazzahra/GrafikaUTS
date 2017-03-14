map: map/main.cpp
	g++ map/main.cpp -lncurses -o map-game
shooter: shooter/main.cpp
	g++ shooter/main.cpp -o shooter-game
rolling: rolling/mainrolling.cpp
	g++ rolling/mainrolling.cpp -std=c++11 -lpthread -o rolling-game

all:
	g++ map/main.cpp -std=c++11 -lncurses -o map-game
	g++ shooter/main.cpp -std=c++11 -lpthread -lm -o shooter-game
	g++ rolling/mainrolling.cpp -std=c++11 -lpthread -o rolling-game
	g++ main-game.cpp getch.c byteconversion.c framebufferimage.c -o main-game
