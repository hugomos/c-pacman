rmdir /s /q out

mkdir out

gcc -c mapa.c -o ./out/mapa.o
gcc -c ui.c -o ./out/ui.o
gcc -c game.c -o ./out/game.o

cd out

gcc mapa.o ui.o game.o -o game.exe

game

pause