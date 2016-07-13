compile:
	clear
	gcc gen.c
	./a.out > input
	gcc iteration_matrix.c
	./a.out < input >output
	diff master output
	
