all: compile link

compile:
	g++ -c main.cpp Dijkstra.cpp Astar.cpp  -I"C:\SFML-2.5.1\include" -DSFML_STATIC
link: 
	g++ main.o Dijkstra.o Astar.o -o main -L"C:\SFML-2.5.1\lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 
clean: 
	rm -f main *.o

