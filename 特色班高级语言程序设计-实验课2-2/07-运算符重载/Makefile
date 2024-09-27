CC = g++
CFLAGS = -Wall -Wextra -O3
SRC = $(wildcard *.cpp)
EXE = $(SRC:.cpp=.exe)

all: $(EXE)

%.exe:%.cpp 
	$(CC) $< $(CFLAGS) -o $@

test:
	cmd /c "echo Testing polar.exe & ( echo 2.14 3.14 q & echo 4.5 6.8 p & echo - )| polar.exe"
	cmd /c "echo Testing complex.exe & ( echo 1 1 & echo 2 2 )| complex.exe"
	cmd /c "echo Testing gradient.exe & echo 2 2 2 | gradient.exe"

clean:
	del /F /Q $(EXE)