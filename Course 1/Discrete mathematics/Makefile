CC = gcc
CFLAGS = -I -Wall
DEPS = main.h
OBJ = main.o lab1.o lab2.o lab3.o lab4.o lab5.o lab6.o lab7.o lab8.o lab9.o lab10.o lab11.o lab12.o lab13.o lab14.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

lab: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
