SRC = mandelbrot.cpp
TARGET = mandelbrot
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -g

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)