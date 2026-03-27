all: assembler emulator

assembler: converter.o runner_converter.o
	g++  converter.o runner_converter.o -o assembler

emulator: converter.o emulator.o runner_emulator.o
	g++ converter.o emulator.o runner_emulator.o -o emulator

clean: 
	rm -f out *.o emulator assembler

.PHONY: clean


test_converter: converter.o test_converter.o
	g++ test_converter.o converter.o -o test_converter
	./test_converter

test_emulator.o: test_emulator.cpp
	g++ -c test_emulator.cpp

test_emulator: converter.o emulator.o test_emulator.o
	g++ test_emulator.o converter.o emulator.o -o test_emulator
	./test_emulator


%.o: %.cpp
	g++ $< -c