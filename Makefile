CC = cc
CFLAGS = -DDUMB_TERMINAL
LDFLAGS =
LIBS = -lz

OBJS = dar.o ver.o cmd.o printf.o

EXEC =

.PHONY: all clean
.SUFFIXES: .c .o

all: dar$(EXEC)

dar$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f dar dar.exe *.o
