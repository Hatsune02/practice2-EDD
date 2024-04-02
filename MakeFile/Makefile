CXX = g++
CXXFLAGS = -std=c++17 -Wall

SRCS = backend/Menu.cpp backend/Parser.cpp backend/Reports.cpp backend/structures/AVLTree.cpp backend/structures/HashTable.cpp backend/structures/HashTableData.cpp backend/structures/Node.cpp main.cpp
OBJS = $(addprefix objects/, $(SRCS:.cpp=.o))
TARGET = output/contact-management

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS) | output
	$(CXX) $(CXXFLAGS) $^ -o $@

objects/%.o: %.cpp | objects
	$(CXX) $(CXXFLAGS) -c $^ -o $@

objects:
	mkdir -p objects/backend
	mkdir -p objects/backend/structures

output:
	mkdir -p output

clean: 
	rm -f $(OBJS) $(TARGET)
