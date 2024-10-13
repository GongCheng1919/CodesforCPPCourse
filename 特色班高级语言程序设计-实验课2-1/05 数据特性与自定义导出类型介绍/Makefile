CC = g++  
CFLAGS = -Wall -Wextra -O3  
SRC = $(wildcard *.cpp)  
EXE = $(SRC:.cpp=)  
  
all: $(EXE)  

%: %.cpp  
	$(CC) $< $(CFLAGS) -o $@  
  
test:    
	echo "Testing GraphicsStructure" && echo "5 2 3 4 6" | ./GraphicsStructure
  echo "Testing GraphicsStructure" && echo "-1 1 2 3 4" | ./GraphicsStructure
	echo "Testing getLogValue" && echo "5"| ./getLogValue
  echo "Testing getLogValue" && echo "-5"| ./getLogValue
	echo "Testing arraySum" && echo "1 2 3 4\n1 2 3 4 5 6 7 8" | ./arraySum
	echo "Testing MatrixAdd" && echo "2 3 4\n\n1 2 3\n4 5 6\n\n4 5 6\n7 8 9" | ./MatrixAdd
  
clean:  
	rm -f $(EXE)
