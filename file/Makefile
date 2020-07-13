main: main main.o faculty.o student.o professor.o
		gcc -o main main.o faculty.o student.o professor.o
main.o : main.c info.h
	gcc -c main.c
faculty.o : faculty.c info.h
	gcc -c faculty.c
student.o : student.c info.h
	gcc -c student.c
professor.o : professor.c info.h
	gcc -c professor.c
