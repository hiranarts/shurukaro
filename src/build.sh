clang++ -std=c++17 -g3  -Werror main.cpp -F../lib/ -framework SDL2 -F../lib/ -framework SDL2_mixer -rpath ../lib/ -o ../bin/platform 
