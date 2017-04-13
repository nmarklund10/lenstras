# makefile
CC = g++ -std=c++11
CFLAGS  = -g -O2 -Wall -Werror
TARGET = lenstras
OUTPUT = lenstras
DEPS = -lgmp

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CC) $(CFLAGS) *.cpp *.h -o $(OUTPUT) $(DEPS)

clean:
	rm $(OUTPUT)
