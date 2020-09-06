:: Démineur Classic - build-dev / MinGW-W64
windres ./src/my.rc my.o
gcc -g -std=gnu18 -O0 -Wall my.o ./src/*.c -o dist/Demineur -I ./src/include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf
if exist "my.o" (del my.o)
