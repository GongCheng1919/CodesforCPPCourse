CC = g++
CFLAGS = -Wall -Wextra -O3
SRC = $(wildcard *.cpp)
EXE = $(SRC:.cpp=.exe)

all: $(EXE)

%.exe:%.cpp 
	$(CC) $< $(CFLAGS) -o $@

test:
	cmd /c "echo Testing Animal.exe & echo bear | Animal.exe"
	cmd /c "echo Testing Functions.exe & echo 1 2 3 | Functions.exe"
	cmd /c "echo Testing test_vitual2.exe & echo A 1 | test_vitual2.exe"
	cmd /c "echo Testing calc_shape.exe & echo Circle 3.14 | calc_shape.exe"
clean:
	del /F /Q $(EXE)