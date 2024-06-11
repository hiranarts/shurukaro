CXX:=clang++
SDL_INCLUDE_DIR:=-Ilib/SDL2.framework/Headers/ -Iinclude/
SDL_LIB_DIR:=-Flib/ -framework SDL2
SRC_FILES:=src/platform.cpp

app: main.o platform.o
	$(CXX) main.o platform.o -o bin/app
main.o: main.cpp
	$(CXX) -c main.cpp $(INCLUDE_DIR) -Flib/ -framework SDL2 -rpath ../lib/ -o main.o
platform.o: src/platform.cpp include/platform.h
	$(CXX) -c src/platform.cpp $(SDL_INCLUDE_DIR) -o platform.o
