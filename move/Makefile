CXX=g++
CXX_FLAGS=
SRC=$(wildcard *.cpp) $(wildcard *.c)
LIBS=-lglut -lGL -lGLU -lGLEW

make: $(SRC)
	$(CXX) -o Theodora $^ $(CXX_FLAGS) $(LIBS)