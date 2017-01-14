CC=gcc
INCLUDE := -I./
CFLAGS :=  -Wall -std=gnu99 -g -fno-common
LDFLAGS :=
LIBS :=

CSOURCES := main.c
CSOURCES += $(wildcard coron/*.c)
CSOURCES += $(wildcard tests/*.c)

OBJECTS := $(CSOURCES:.c=.o)
EXECUTABLE := test_coron

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

clean:
	rm -rf *.o **/*.o *.elf 
