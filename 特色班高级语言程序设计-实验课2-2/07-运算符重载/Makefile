CC = g++  
CFLAGS = -Wall -Wextra -O3  
SRC = $(wildcard *.cpp)  
EXE = $(SRC:.cpp=)   
  
all: $(EXE)  
  
%: %.cpp  
	$(CC) $< $(CFLAGS) -o $@  
  
test:  
	echo "Testing polar" && (echo "2.14 3.14 q" && echo "4.5 6.8 p" && echo -e "\n") | ./polar  
	echo "Testing complex" && (echo "1 1" && echo "2 2") | ./complex  
	echo "Testing gradient" && echo "2 2 2" | ./gradient  
  
clean:  
	rm -f $(EXE)
