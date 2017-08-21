CC=g++
CFLAGS=
LDFLAGS=
SOURCES=main.cpp SearchCART.cpp Servo.cpp
EXECUTABLE=cart

all:
	$(CC) -std=c++11 `pkg-config --cflags --libs opencv` $(SOURCES) -o $(EXECUTABLE)
