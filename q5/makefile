# Source files
SRC1 = maxSubArray1.cpp
SRC2 = maxSubArray2.cpp
SRC3 = maxSubArray3.cpp

# Executable targets
BIN1 = max1
BIN2 = max2
BIN3 = max3

CXX = g++
CXXFLAGS = -pg -O1

# Default target: build all programs with profiling support
all: $(BIN1) $(BIN2) $(BIN3)

# Compile each version separately
$(BIN1): $(SRC1)
	$(CXX) $(CXXFLAGS) -o $(BIN1) $(SRC1)

$(BIN2): $(SRC2)
	$(CXX) $(CXXFLAGS) -o $(BIN2) $(SRC2)

$(BIN3): $(SRC3)
	$(CXX) $(CXXFLAGS) -o $(BIN3) $(SRC3)

# Clean generated binaries and profiling output
clean:
	rm -f $(BIN1) $(BIN2) $(BIN3) gmon.out gprof_*.txt

# Profile with N = 100
profile100:
	@echo "[ Profiling with N = 100 ]"
	rm -f gmon.out
	./$(BIN1) 42 100; gprof $(BIN1) gmon.out > gprof_$(BIN1)_100.txt; rm -f gmon.out
	./$(BIN2) 42 100; gprof $(BIN2) gmon.out > gprof_$(BIN2)_100.txt; rm -f gmon.out
	./$(BIN3) 42 100; gprof $(BIN3) gmon.out > gprof_$(BIN3)_100.txt; rm -f gmon.out

# Profile with N = 1000
profile1000:
	@echo "[ Profiling with N = 1000 ]"
	rm -f gmon.out
	./$(BIN1) 42 1000; gprof $(BIN1) gmon.out > gprof_$(BIN1)_1000.txt; rm -f gmon.out
	./$(BIN2) 42 1000; gprof $(BIN2) gmon.out > gprof_$(BIN2)_1000.txt; rm -f gmon.out
	./$(BIN3) 42 1000; gprof $(BIN3) gmon.out > gprof_$(BIN3)_1000.txt; rm -f gmon.out

# Profile with N = 10000
profile10000:
	@echo "[ Profiling with N = 10000 ]"
	rm -f gmon.out
	./$(BIN1) 42 10000; gprof $(BIN1) gmon.out > gprof_$(BIN1)_10000.txt; rm -f gmon.out
	./$(BIN2) 42 10000; gprof $(BIN2) gmon.out > gprof_$(BIN2)_10000.txt; rm -f gmon.out
	./$(BIN3) 42 10000; gprof $(BIN3) gmon.out > gprof_$(BIN3)_10000.txt; rm -f gmon.out

# Profile all three input sizes
profile_all: profile100 profile1000 profile10000