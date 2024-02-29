CC=gcc
CFLAGS=`pkg-config --cflags gtk+-3.0`
LFLAGS=`pkg-config --libs gtk+-3.0`
EXE1=p1
EXE2=p2

p1: proyecto1.c
	$(CC) $(CFLAGS) $^ -o $(EXE1) $(LFLAGS)
	./$(EXE1)
	rm $(EXE1)

p2: proyecto2.c
	$(CC) $^ -o $(EXE2)
	./$(EXE2)
	rm $(EXE2)

