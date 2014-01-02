CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.cpp dataconverter.cpp dataset.cpp classifier.cpp perceptron.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
