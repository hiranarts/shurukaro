CXX:=clang++
SDL_INCLUDE_DIR:=-Ilib/SDL2.framework/Headers/ 
INCLUDE_DIR:=-Iinclude/
LIB_DIR:=-Flib/
SDL_LIB_DIR:=-Flib/ -framework SDL2
SDL_DLL:= -rpath ../lib/
SRC_FILES:=src/platform.cpp
CFLAGS:=-Wall -Werror
ASAN_FLAGS:=-fsanitize=address
OBJ_DIR:=bin/

app: main.cpp $(OBJ_DIR)platform.o
	$(CXX) $(CFLAGS) $(ASAN_FLAGS) main.cpp $(OBJ_DIR)platform.o $(INCLUDE_DIR) $(SDL_LIB_DIR) $(SDL_DLL) -o bin/app
$(OBJ_DIR)platform.o: src/platform.cpp include/platform.h
	$(CXX) -c src/platform.cpp $(INCLUDE_DIR) $(LIB_DIR) -o $(OBJ_DIR)platform.o
