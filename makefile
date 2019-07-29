all:	main
main: main.o
	gcc main.o -o main -ldl -g
main.o: main.c
	gcc main.c -c
