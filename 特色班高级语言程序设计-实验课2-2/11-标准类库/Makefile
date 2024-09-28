CC = g++
CFLAGS = -Wall -Wextra -O3
SRC = $(wildcard *.cpp)
EXE = $(SRC:.cpp=.exe)

all: $(EXE)

%.exe:%.cpp 
	$(CC) $< $(CFLAGS) -o $@

test:  
	echo "Testing SmartPointer" && echo "10 1 2 3 4 5 6 7 8 9 10" | ./SmartPointer  

clean:
	del /F /Q $(EXE)
