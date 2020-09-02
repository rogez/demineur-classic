:: Démineur Classic - build-release / MinGW-W64
windres ./src/my.rc my.o
gcc -mwindows -std=c17 -O3 my.o ./src/*.c -o dist/Demineur -I ./src/include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf
del my.o
