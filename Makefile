CC=gcc
CFLAGS=-I./include
DEPS = $(wildcard include/*.h)
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
EXEC=bin/filemanager

all: $(EXEC)

$(EXEC): $(OBJ)
	@mkdir -p bin
	$(CC) $(OBJ) -o $(EXEC)

%.o: %.c $(DEPS)
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f src/*.o $(EXEC)

