
CC=g++
CFLAGS=-c -Wall
LDFLAGS=
LDADD=-lrt

SOURCES=main.cpp colony.cpp my_timer.cpp
OBJECTS=$(SOURCES:.cpp=.o)

EXECUTABLE=gameOfLife

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LDADD)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@ $(LDADD)

clean:
	rm *.o *.out $(EXECUTABLE)
