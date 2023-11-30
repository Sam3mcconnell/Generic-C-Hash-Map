CC = gcc
OBJS = driver.o map.o input.o value.o
CFLAGS += -Wall -std=c99 -g
TARGETS = driver mapTest stringTest

all: $(TARGETS)

driver: driver.o map.o input.o value.o
	$(CC) $(CFLAGS) -o driver driver.o map.o input.o value.o

mapTest: mapTest.o value.o map.o
	$(CC) $(CFLAGS) -o mapTest mapTest.o value.o map.o

stringTest: stringTest.o value.o
	$(CC) $(CFLAGS) -o stringTest stringTest.o value.o

driver.o: driver.c map.h input.h value.h
	$(CC) $(CFLAGS) -c driver.c

map.o: map.c value.h
	$(CC) $(CFLAGS) -c map.c

input.o: input.c
	$(CC) $(CFLAGS) -c input.c

value.o: value.c
	$(CC) $(CFLAGS) -c value.c

clean:
	rm -f $(OBJS)
	rm -f $(TARGETS)
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.gcov