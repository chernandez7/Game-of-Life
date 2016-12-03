
CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lrt

SOURCES=main.cpp colony.cpp my_timer.cpp
OBJECTS=$(SOURCES:.cpp=.o)

EXECUTABLE=gameOfLife

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o *.out $(EXECUTABLE)
