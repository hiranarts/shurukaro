clang++ -g3 -fsanitize=address -Werror main.cpp -F../lib/ -framework SDL2 -F../lib/ -framework SDL2_mixer -rpath ../lib/ -o ../bin/platform
