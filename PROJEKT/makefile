all: app
	./app

app: main.o Application.o Board.o Bedrock.o Stone.o
	g++ -std=c++14 main.o Application.o Lava.o Bedrock.o Stone.o Board.o -o app -lsfml-graphics -lsfml-window -lsfml-system

Application.o: classes/Application.cpp
	g++ -std=c++14 -c classes/Application.cpp

Board.o: classes/Board.cpp
	g++ -std=c++14 -c classes/Board.cpp

Board.o: classes/objects/Lava.cpp
	g++ -std=c++14 -c classes/objects/Lava.cpp

main.o: main.cpp
	g++ -std=c++14 -c main.cpp

Bedrock.o: classes/objects/Bedrock.cpp
	g++ -std=c++14 -c classes/objects/Bedrock.cpp

Stone.o: classes/objects/Stone.cpp
	g++ -std=c++14 -c classes/objects/Stone.cpp

Event.o: classes/objects/Event.cpp
	g++ -std=c++14 -c classes/objects/Event.cpp


everything:
	g++ -std=c++14 -c classes/Application.cpp
	g++ -std=c++14 -c classes/Board.cpp
	g++ -std=c++14 -c classes/interface/PlayrunInterface.cpp
	g++ -std=c++14 -c classes/Event.cpp
	g++ -std=c++14 -c main.cpp
	g++ -std=c++14 -c classes/objects/Eventaware.cpp
	g++ -std=c++14 -c classes/objects/Lava.cpp
	g++ -std=c++14 -c classes/objects/Bedrock.cpp
	g++ -std=c++14 -c classes/objects/Stone.cpp
	g++ -std=c++14 -c classes/objects/Player.cpp
	g++ -std=c++14 -c classes/interface/Button.cpp
	g++ -std=c++14 main.o Application.o Event.o Button.o Eventaware.o Lava.o PlayrunInterface.o Bedrock.o Stone.o Player.o Board.o -o app -lsfml-graphics -lsfml-window -lsfml-system
	./app