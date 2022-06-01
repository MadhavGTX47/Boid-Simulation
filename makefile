fishtank : fish.o viewer.o 
	g++  fish.o  -o fishtank
	g++  viewer.o -lGL -lGLU -lglut -o viewer
	

fish.o : fish.cpp 
	g++ -I/usr/include/eigen3/ -O3 -c fish.cpp

viewer.o: viewer.cpp
	g++ -I/usr/include/eigen3/  -O3 -c -lGL -lGLU -lglut viewer.cpp
clean:
	rm *.o *.ppm *.exe output sample.out fishtank viewer
	 
