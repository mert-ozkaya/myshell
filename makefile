hepsi: derle calistir

derle:
	gcc -I ./include/ -o ./lib/cmd.o -c ./src/cmd.c
	gcc -I ./include/ -o ./bin/main ./lib/cmd.o ./src/main.c
	
calistir:
	./bin/main
