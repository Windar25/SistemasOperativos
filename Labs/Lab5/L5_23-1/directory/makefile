CC=gcc
CFLAGS=-I.
DEPS = structfat.h
OBJ = fatbootsector.o
EXEC = fatbootsector

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean run

clean:
	rm -f *.o *~ core $(EXEC)

run: $(EXEC)
	./$(EXEC) $(filter-out $@,$(MAKECMDGOALS))
