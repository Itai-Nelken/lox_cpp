CXX := g++
CXXFLAGS += -Wall -Wextra -Wpedantic -Iinclude -std=c++20
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
BIN := lox++
DEBUG := 0

ifneq ($(DEBUG), 0)
	CXXFLAGS += -g
endif

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

reset:
	rm -f $(OBJ) $(BIN)
clean:
	rm -f $(OBJ)

.PHONY: all reset clean
