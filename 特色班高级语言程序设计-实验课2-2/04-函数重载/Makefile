CC = g++
CFLAGS = -Wall -Wextra -O3
SRC = gemm.cpp
EXE = $(SRC:.cpp=.exe)

all: $(EXE)

%.exe:%.cpp 
	$(CC) $< $(CFLAGS) -o $@

test:  
	echo "Testing gemm" && echo "3 4 5 d" | ./gemm  
	echo "Testing Float" | ./Float  
	echo "Testing FloatX" | ./FloatX  
	echo "Testing Tensor" | ./Tensor 

clean:
	del /F /Q $(EXE)
