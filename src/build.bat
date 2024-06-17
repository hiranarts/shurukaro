REM This is translation object for the platform part of the code. This part should provide handlers to platform parts of the code. 
clang++ main.cpp -F../lib/ -framework SDL2 -F../lib/ -framework SDL2_mixer -rpath ../lib/ -o ../bin/platform
