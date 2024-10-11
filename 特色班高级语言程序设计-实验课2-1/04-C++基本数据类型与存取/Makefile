CC = g++  
CFLAGS = -Wall -Wextra -O3  
SRC = $(wildcard *.cpp)  
EXE = $(SRC:.cpp=)  
  
all: $(EXE)  

%: %.cpp  
	$(CC) $< $(CFLAGS) -o $@  
  
test:    
	echo "Testing testsize" && echo "*" | ./testsize  
	echo "Testing testdataclass" && echo "xiaoming 9 62.0 32.0 22.0 0"| ./testdataclass 
	echo "Testing testchange" && echo "9e+17" | ./testchange
	echo "Testing stringoperator" && echo "39137707 bing" && echo "crazy Thursday vivo 50"&& echo "4 10 3"  | ./stringoperator 
  
clean:  
	rm -f $(EXE)