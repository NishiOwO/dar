CC = cc
CFLAGS =
LDFLAGS =
LIBS = -lz

# Does your terminal ignore \x08?
#CFLAGS += -DDUMB_TERMINAL

OBJS = dar.o ver.o cmd.o printf.o c_info.o c_create.o c_extract.o c_test.o

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
