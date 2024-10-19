CC = g++  
CFLAGS = -Wall -Wextra -O3  
SRC = $(wildcard *.cpp)  
EXE = $(SRC:.cpp=)  
  
all: $(EXE)  

%: %.cpp  
	$(CC) $< $(CFLAGS) -o $@  
  
test:    
	echo "Testing enum" && echo "97" | ./enum
	echo "Testing union" && echo "9e+17"| ./union
	echo "Testing struct" && echo "3" && echo "fafa 90 90 90" && echo "lxl 95 85 90" && echo "senpai 100 80 91" | ./struct
	echo "Testing class"  && echo "5" && echo "s 1 PoVs 138 89 117" && echo "t 0 WpWoQl 3123 30363" && echo "st 1 Jq 3009 30476" && echo "s 0 Hl 126 18 50" && echo "s 1 Bx 141 30 122"  | ./class
  
clean:  
	rm -f $(EXE)
