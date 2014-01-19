CC=g++
CFLAGS=-c -Wall -g
LDFLAGS=
SOURCES=main.cpp dataconverter.cpp dataset.cpp classifier.cpp perceptron.cpp tester.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
