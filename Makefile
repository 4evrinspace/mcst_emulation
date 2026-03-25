all: converter.o emulator.o

clean: 
	rm -f converter.o emulator.o test_converter test_converter.o test_emulator test_emulator.o out.o in.s

converter.o : converter.cpp
	g++ -c converter.cpp

emulator.o : emulator.cpp
	g++ -c emulator.cpp

test_converter.o: test_converter.cpp
	g++ -c test_converter.cpp

test_converter: converter.o test_converter.o
	g++ test_converter.o converter.o -o test_converter
	./test_converter

test_emulator.o: test_emulator.cpp
	g++ -c test_emulator.cpp

test_emulator: converter.o emulator.o test_emulator.o
	g++ test_emulator.o converter.o emulator.o -o test_emulator
	./test_emulator


