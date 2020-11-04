FICHIERS = lodepng.o image.o main.o 

FICH = src/lodepng.h src/image.h 

all: $(FICHIERS) 
	gcc -g $(FICHIERS) -o image.exe

main.o: src/main.c $(FICH)
	gcc -c -Wall src/main.c -o main.o

image.o: src/image.c $(FICH)
	gcc -c -Wall src/image.c -o image.o

lodepng.o: src/lodepng.c $(FICH)
	gcc -c -Wall src/lodepng.c -o lodepng.o


clean:
	rm image $(FICHIERS)
