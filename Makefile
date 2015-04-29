all:
	g++ -std=c++11 src/*.cpp -o glyphgen -lfreeimage -lfreetype -I/usr/include/freetype2/
run: 
	./glyphgen
