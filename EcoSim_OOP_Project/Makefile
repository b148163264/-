CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET = ecosim
SOURCES = main.cpp Entity.cpp Organism.cpp Plant.cpp Animal.cpp Resource.cpp World.cpp

all:
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)
