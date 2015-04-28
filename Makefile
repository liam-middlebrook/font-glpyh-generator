all:
	g++ -std=c++11 src/*.cpp -o glyphgen -lfreeimage
run: 
	./glyphgen
