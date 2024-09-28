CC = g++
CFLAGS = -Wall -Wextra -O3
SRC = $(wildcard *.cpp)
EXE = $(SRC:.cpp=.exe)

all: $(EXE)

%.exe:%.cpp 
	$(CC) $< $(CFLAGS) -o $@

test:
	cmd /c "echo Testing gemm.exe & echo 3 4 5 d | gemm.exe"
	cmd /c "echo Testing Float.exe | Float.exe"
	cmd /c "echo Testing FloatX.exe | FloatX.exe"
	cmd /c "echo Testing Tensor.exe | Tensor.exe"

clean:
	del /F /Q $(EXE)