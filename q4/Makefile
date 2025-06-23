CXX = g++
CXXFLAGS = -Wall -g -fprofile-arcs -ftest-coverage
SRC = myDijkstra.cpp
BIN = myDijkstra

all: $(BIN)

$(BIN): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(BIN)

run: all
	./$(BIN)

coverage: all
	gcov -b -c -r $(SRC) 

clean:
	rm -f $(BIN) *.gcno *.gcda *.gcov gcov_output.txt coverage.txt

