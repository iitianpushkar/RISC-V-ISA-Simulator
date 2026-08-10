CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -I.

TARGET = build/simulator
SOURCES = simulator.cpp alu/alu.cpp cpu/cpu.cpp decoder/decoder.cpp instruction/instruction.cpp memory/memory.cpp program/program.cpp register/registers.cpp

all: $(TARGET)

$(TARGET): $(SOURCES)
	mkdir -p build
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf build

.PHONY: all run clean
