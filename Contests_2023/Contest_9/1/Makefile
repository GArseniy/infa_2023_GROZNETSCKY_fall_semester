CC = gcc
CFLAGS = -Wall -O3
LDFLAGS =
LD = gcc
EXE_NAME = printrandom

all: main linear random
	@$(LD) -o $(EXE_NAME) $(LDFLAGS) -rdynamic main.o linear.o random.o
main:
	@$(CC) main.c -c $(CFLAGS) -o main.o
linear:
	@$(CC) linear.c -c $(CFLAGS) -o linear.o
random:
	@$(CC) random.c -c $(CFLAGS) -o random.o
clean:
	@rm -rf *.o