CC = g++  
CFLAGS = -Wall -Wextra -O3  
SRC = $(wildcard *.cpp)  
EXE = $(SRC:.cpp=)  
  
all: $(EXE)  

%: %.cpp  
	$(CC) $< $(CFLAGS) -o $@  
  
test:    
	echo "Testing list" && echo "2"&& echo "n g i"&& echo"n k u" | ./list
	echo "Testing pointerfunction" && echo "10" && echo"5 9 6 9 8 2 1 5 6 5"| ./pointerfunction
	echo "Testing stack" && echo "0" | ./stack
	echo "Testing snack" && echo "5" | ./snack
  
clean:  
	rm -f $(EXE
