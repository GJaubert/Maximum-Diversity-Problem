CXX = g++
#CXXFLAGS = -Wall -Wextra -pedantic -std=c++17 -g -fsanitize=address
LDFLAGS =  -fsanitize=address

SRC = ./src/main.cpp ./src/mdp.cpp ./src/element.cpp ./src/greedy.cpp ./src/grasp.cpp ./src/branch-bound.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = ./bin/main

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS)

clean:
	rm -rf $(OBJ) $(EXEC)