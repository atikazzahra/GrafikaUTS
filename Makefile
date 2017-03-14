map: map/main.cpp
	g++ map/main.cpp -lncurses -o map-game
shooter: shooter/main.cpp
	g++ shooter/main.cpp -o shooter-game
rolling: rolling/mainrolling.cpp
	g++ rolling/mainrolling.cpp -std=c++11 -lpthread -o rolling-game

all:
	g++ map/main.cpp -std=c++11 -lncurses -o map-game
	g++ map/d_overlap.cpp -std=c++11 -o overlap
	g++ shooter/main.cpp -std=c++11 -lpthread -lm -o shooter-game
	g++ rolling/mainrolling.cpp -std=c++11 -lpthread -o rolling-game
	g++ main-game.cpp getch.c byteconversion.c framebufferimage.c -o main-game

	g++ intro.cpp getch.c byteconversion.c framebufferimage.c -o intro
	g++ trans1.cpp getch.c byteconversion.c framebufferimage.c -o trans1
	g++ trans2.cpp getch.c byteconversion.c framebufferimage.c -o trans2
	g++ finish.cpp getch.c byteconversion.c framebufferimage.c -o finish
	g++ game-over.cpp getch.c byteconversion.c framebufferimage.c -o game-over
