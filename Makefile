CC=gcc
INCLUDE := -I./
CFLAGS :=  -Wall -std=gnu99 -g -fno-common
LDFLAGS :=
LIBS :=

CSOURCES := test_coron.c main.c
CSOURCES += $(wildcard coron/*.c)

OBJECTS := $(CSOURCES:.c=.o)
EXECUTABLE := test_coron

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

clean:
	rm -rf **/*.o *.elf 
