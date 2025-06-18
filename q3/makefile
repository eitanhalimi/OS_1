CXX = g++
CXXFLAGS = -Wall -Wextra -fPIC -std=c++11 -g
LDFLAGS = -L. -lmandelbrot
TARGET = main
LIB = libmandelbrot.so
SRC = mandelbrot.cpp
HDR = mandelbrot.hpp
MAIN = main.cpp

all: $(LIB) $(TARGET)

$(LIB): $(SRC) $(HDR)
	$(CXX) $(CXXFLAGS) -shared -o $@ $(SRC)

$(TARGET): $(MAIN) $(HDR)
	$(CXX) $(CXXFLAGS) -o $@ $(MAIN) -L. -lmandelbrot

run: all
	LD_LIBRARY_PATH=. ./main
clean:
	rm -f $(TARGET) $(LIB)