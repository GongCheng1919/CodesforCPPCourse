CC = g++  
CFLAGS = -Wall -Wextra -O3  
SRC = $(wildcard *.cpp)  
EXE = $(SRC:.cpp=) 
  
all: $(EXE)  
  
%: %.cpp  
	$(CC) $< $(CFLAGS) -o $@  
  
test:  
	echo "Testing Animal" && echo "bear" | ./Animal  
	echo "Testing Functions" && echo "1 2 3" | ./Functions  
	echo "Testing test_virtual2" && echo "A 1" | ./test_virtual2  
	echo "Testing calc_shape" && echo "Circle 3.14" | ./calc_shape  
  
clean:  
	rm -f $(EXE)
