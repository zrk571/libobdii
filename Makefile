CC=gcc
CFLAGS=
LDFLAGS=
SRC_DIR=./src/
SRC=$(wildcard $(SRC_DIR)*.c)
OBJ_DIR=./bin/
OBJ=$(SRC:.c=.o)
EXEC=libobdii.a

all: $(OBJ)
	ar -cr $(OBJ_DIR)$(EXEC) $^

%.o : %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ -c $^


clean :
	rm -rf $(SRC_DIR)*.o

mrproper : clean 
	rm -rf $(EXEC)
