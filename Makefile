CC = cc
CFLAGS =
LDFLAGS =
LIBS = -lz

OBJS = zar.o ver.o cmd.o printf.o

EXEC =

.PHONY: all clean
.SUFFIXES: .c .o

all: zar$(EXEC)

zar$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f zar zar.exe *.o
