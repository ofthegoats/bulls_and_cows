CC = clang
SOURCES = $(filter-out tests.c, $(wildcard *.c))
TESTS = tests.c
OBJECTS = $(SOURCES:.c=.o)
OUTPUT = $(shell basename $(CURDIR))

$(OUTPUT) : $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.c.o :
	$(CC) -c $< -o $@

clean :
	rm -f $(OUTPUT)
	rm -f $(OBJECTS)
