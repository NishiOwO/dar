CC = cc
CFLAGS =
LDFLAGS =
LIBS = -lz

# Does your terminal ignore \x08?
# CFLAGS += -DDUMB_TERMINAL

OBJS = src/dar.o src/ver.o src/cmd.o src/io.o src/printf.o src/chunk.o src/endian.o
OBJS += src/c_info.o src/c_create.o src/c_extract.o
OBJS += src/ds.o

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
