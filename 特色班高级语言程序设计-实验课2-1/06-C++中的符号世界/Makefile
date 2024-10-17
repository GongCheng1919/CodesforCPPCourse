CC = g++  
CFLAGS = -Wall -Wextra -O3  
SRC = $(wildcard *.cpp)  
EXE = $(SRC:.cpp=)  
  
all: $(EXE)  

%: %.cpp  
	$(CC) $< $(CFLAGS) -o $@  
  
test:    
	echo "Testing char and ASCII" && echo "A Z 50" | ./char and ASCII
	echo "Testing bitoperate" && echo "42 7"| ./bitoperate
	echo "Testing operate" && echo "& %" | ./operate
	echo "Testing name" && echo "23 11" | ./name
  
clean:  
	rm -f $(EXE)
