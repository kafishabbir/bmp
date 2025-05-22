all:
	g++ -c -Wall -std=c++17 bmp.cpp -o bmp.o
	g++ -c -Wall -std=c++17 prog.cpp -o prog.o
	g++ prog.o bmp.o -o prog.exe
	./prog.exe


edit:
	geany -i bmp.cpp bmp.h prog.cpp
	
