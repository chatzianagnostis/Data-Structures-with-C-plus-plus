CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
LDFLAGS = 

# Source files
SOURCES = main.cpp \
          MinHeap.cpp \
          MaxHeap.cpp \
          AVLTree.cpp \
          Graph.cpp \
          HashTable.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Executable name
TARGET = data_structures

# Default target
all: $(TARGET)

# Linking the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "Build successful! Run with './$(TARGET)'"

# Compiling source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Generate dependencies
depend: .depend

.depend: $(SOURCES)
	rm -f ./.depend
	$(CXX) $(CXXFLAGS) -MM $^ > ./.depend

-include .depend

# Clean up
clean:
	rm -f $(OBJECTS) $(TARGET) .depend

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean and rebuild
rebuild: clean all

# Show help
help:
	@echo "Available targets:"
	@echo "  all       - Build the program (default)"
	@echo "  clean     - Remove object files and executable"
	@echo "  run       - Build and run the program"
	@echo "  rebuild   - Clean and rebuild the program"
	@echo "  depend    - Generate dependencies"
	@echo "  help      - Show this help message"

.PHONY: all clean run rebuild depend help
