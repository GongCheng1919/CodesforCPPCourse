CC = g++  
CFLAGS = -Wall -Wextra -O3  
SRC = $(wildcard *.cpp)  
EXE = $(SRC:.cpp=)  
  
all: $(EXE)  

%: %.cpp  
	$(CC) $< $(CFLAGS) -o $@  
  
test:    
	echo "Testing Bramble'sApplesI" && echo "7 9 3 2" | ./Bramble'sApplesI
	echo "Testing Bramble'sApplesII" && echo "7 9 12 9 2"| ./Bramble'sApplesII
	echo "Testing Bramble'sApplesIII" && echo "15 1 12" | ./Bramble'sApplesIII
	echo "Testing Bramble'sApplesIV" && echo "15 3\n1 7\n2 60\n3 100" | ./Bramble'sApplesIV
  
clean:  
	rm -f $(EXE)
