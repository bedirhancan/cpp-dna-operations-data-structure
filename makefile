all: compile run

compile :
	g++ -I ./include/ -o ./lib/Gen.o -c ./src/Gen.cpp
	g++ -I ./include/ -o ./lib/Kromozom.o -c ./src/Kromozom.cpp
	g++ -I ./include/ -o ./lib/Dugum.o -c ./src/Dugum.cpp
	g++ -I ./include/ -o ./lib/DNA.o -c ./src/DNA.cpp
	g++ -I ./include/ -o ./bin/Test ./lib/Kromozom.o ./lib/DNA.o ./lib/Gen.o ./lib/Dugum.o ./src/Test.cpp
run :
	./bin/Test