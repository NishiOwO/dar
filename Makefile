CC = cc
CFLAGS =
LDFLAGS =
LIBS = -lz

# Does your terminal ignore \x08?
#CFLAGS += -DDUMB_TERMINAL

# Do you have dirent.h?
CFLAGS += -DHAS_DIRENT

OBJS = src/dar.o src/ver.o src/cmd.o src/dir.o src/printf.o src/c_info.o src/c_create.o src/c_extract.o src/c_test.o

EXEC =

.PHONY: all clean
.SUFFIXES: .c .o

all: dar$(EXEC)

dar$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f dar dar.exe src/*.o
