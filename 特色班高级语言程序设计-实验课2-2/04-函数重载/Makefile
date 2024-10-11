CC = g++  
CFLAGS = -Wall -Wextra -O3  
SRC = $(wildcard *.cpp)  
EXE = $(SRC:.cpp=)  
  
all: $(EXE)  

%: %.cpp  
	$(CC) $< $(CFLAGS) -o $@  
  
test:    
	echo "Testing gemm" && echo "3 4 5 d" | ./gemm  
	echo "Testing Float" | ./Float  
	echo "Testing FloatX" | ./FloatX  
	echo "Testing Tensor" | ./Tensor  
  
clean:  
	rm -f $(EXE)
