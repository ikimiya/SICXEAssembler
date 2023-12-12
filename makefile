assembler: main.o Math/Conversion.o src/cpp/Optable.o src/cpp/Symtable.o src/cpp/Pass1.o src/cpp/Pass2.o src/cpp/FileReader.o src/cpp/GenerateOp.o src/cpp/Libtab.o src/cpp/blockTable.o src/cpp/ArgTable.o src/cpp/NamTable.o src/cpp/DefTable.o src/cpp/ControlTab.o
	g++ main.o Math/Conversion.o src/cpp/Optable.o src/cpp/Symtable.o src/cpp/Pass1.o src/cpp/Pass2.o src/cpp/FileReader.o src/cpp/GenerateOp.o src/cpp/Libtab.o src/cpp/blockTable.o src/cpp/ArgTable.o src/cpp/NamTable.o src/cpp/DefTable.o src/cpp/ControlTab.o -o assembler

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

ArgTable.o: src/cpp/ArgTable.cpp src/header/ArgTable.h
	g++ -c src/cpp/ArgTable.cpp

DefTable.o: src/cpp/DefTable.cpp src/header/DefTable.h
	g++ -c src/cpp/DefTable.cpp

NamTable.o: src/cpp/NamTable.cpp src/header/NamTable.h
	g++ -c src/cpp/NamTable.cpp

ControlTab.o: src/cpp/ControlTab.cpp src/header/ControlTab.h
	g++ -c src/cpp/ControlTab.cpp

clean:
	rm -f *.o
	rm -f Math/*.o
	rm -f src/*/*.o
	rm assembler

cleanResult:
	rm -f Result/*.txt

cleanImt:
	rm -f Immediate/*.txt

cleanall:
	rm -f Immediate/*.txt
	rm -f Result/*.txt
	rm -f *.o
	rm -f Math/*.o
	rm -f src/*/*.o
	rm assembler
	
run: assembler
	./assembler