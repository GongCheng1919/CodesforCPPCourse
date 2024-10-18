CC = g++  
CFLAGS = -Wall -Wextra -O3  
SRC = $(wildcard *.cpp)  
EXE = $(SRC:.cpp=)  
  
all: $(EXE)  

%: %.cpp  
	$(CC) $< $(CFLAGS) -o $@  
  
test:    
	echo "Testing bignumber" && echo "10284720757613717413913  6356306993006846248183" | ./bignumber
	echo "Testing testbignumber" && echo "2147483647 2147483647"| ./testbignumber
	echo "Testing gemn" && echo "4 5 f" | ./gemn
  
clean:  
	rm -f $(EXE)
