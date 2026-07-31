CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

TARGET = build/simulator
SOURCES = src/simulator.cpp src/alu/alu.cpp src/cpu/cpu.cpp src/instruction/instruction.cpp src/program/program.cpp src/register/registers.cpp

all: $(TARGET)

$(TARGET): $(SOURCES)
	mkdir -p build
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf build

.PHONY: all run clean
