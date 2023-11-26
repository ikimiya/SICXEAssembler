assembler: main.o Math/Conversion.o src/cpp/Optable.o src/cpp/Symtable.o src/cpp/Pass1.o src/cpp/Pass2.o src/cpp/FileReader.o src/cpp/GenerateOp.o src/cpp/Libtab.o src/cpp/blockTable.o
	g++ main.o Math/Conversion.o src/cpp/Optable.o src/cpp/Symtable.o src/cpp/Pass1.o src/cpp/Pass2.o src/cpp/FileReader.o src/cpp/GenerateOp.o src/cpp/Libtab.o src/cpp/blockTable.o -o assembler

main.o: main.cpp
	g++ -c main.cpp

Optable.o: src/cpp/Optable.cpp src/h/Optable.h
	g++ -c src/cpp/Optable.cpp 

Symtable.o: src/cpp/Symtable.cpp src/h/Symtable.h
	g++ -c src/cpp/Symtable.cpp

Conversion.o: Math/Conversion.cpp Math/Conversion.h
	g++ -c Math/Conversion.cpp

FileReader.o: src/cpp/FileReader.cpp src/header/FileReader.h
	g++ -c src/cpp/FileReader.cpp

Pass1.o: src/cpp/Pass1.cpp src/header/Pass1.h
	g++ -c src/cpp/Pass1.cpp 

Pass2.o: src/cpp/Pass2.cpp src/header/Pass2.h
	g++ -c src/cpp/Pass2.cpp 

GenerateOp.o: src/cpp/GenerateOp.cpp src/header/GenerateOp.h 
	g++ -c src/cpp/GenerateOp.cpp

Libtab.o: src/cpp/Libtab.cpp src/header/Libtab.h
	g++ -c src/cpp/Libtab.cpp
blockTable.o: src/cpp/blockTable.cpp src/header/blockTable.h
	g++ -c src/cpp/blockTable.cpp

clean:
	rm -f *.o
	rm -f Math/*.o
	rm -f src/*/*.o

	rm assembler

run: assembler
	./assembler