all:
	clang++ main.cpp -Ilib/SDL2.framework/Headers/ -Flib/ -framework SDL2 -rpath ../lib/ -o bin/app