CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

TARGETS = PB2add findPhone

all: $(TARGETS)

indPhone: findPhone.cpp
	$(CXX) $(CXXFLAGS) -o findPhone findPhone.cpp

PB2add: PB2add.cpp
	$(CXX) $(CXXFLAGS) -o PB2add PB2add.cpp

clean:
	rm -f $(TARGETS) *.o