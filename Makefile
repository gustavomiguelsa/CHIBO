
.PHONY: main.exe main main.o clean

main.exe: glad.o main.o
	#Windows
	i686-w64-mingw32-g++ -Wall -std=c++11 main.o glad.o -L./ -lglfw3 -L./ -lglfw3dll -lgdi32 -lopengl32 -static-libgcc -static-libstdc++ -o main.exe
	#Linux
	g++ -Wall -std=c++11 main2.o glad2.o -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor -o main -rdynamic

main.o: main.cpp glad.h glfw3.h grid.h stb_image.h window.h camera.h shader.h
	#Windows
	i686-w64-mingw32-g++ -Wall -std=c++11 -c main.cpp
	#Linux
	g++ -Wall -std=c++11 -o main2.o -c main.cpp

glad.o: glad.h glad.c
	#Windows
	i686-w64-mingw32-g++ -Wall -std=c++11 -c glad.c
	#Linux
	g++ -Wall -std=c++11 -o glad2.o -c glad.c

clean:
	rm *.o main.exe main || true


#i686-w64-mingw32-g++ hello.cc -o hello32.exe     # 32-bit
#x86_64-w64-mingw32-g++ hello.cc -o hello64.exe   # 64-bit
