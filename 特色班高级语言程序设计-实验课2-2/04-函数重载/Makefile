CC = g++
CFLAGS = -Wall -Wextra -O3
SRC = gemm.cpp
EXE = $(SRC:.cpp=.exe)

all: $(EXE)

%.exe:%.cpp 
	$(CC) $< $(CFLAGS) -o $@

test:
	cmd /c "echo Testing gemm.exe & echo 3 4 5 d | gemm.exe"

clean:
	del /F /Q $(EXE)