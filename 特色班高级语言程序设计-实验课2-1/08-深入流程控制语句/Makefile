CC = g++  
CFLAGS = -Wall -Wextra -O3  
SRC = $(wildcard *.cpp)  
EXE = $(SRC:.cpp=)  
  
all: $(EXE)  

%: %.cpp  
	$(CC) $< $(CFLAGS) -o $@  
  
test:    
	echo "Testing Bramble'sApplesV" && echo "8"&& echo "20 40 321 67 40 40 89 15" | ./Bramble'sApplesV
	echo "Testing Bramble'sApplesVI" && echo "5"| ./Bramble'sApplesVI
	echo "Testing Bramble'sApplesVII" && echo "8 3" | ./Bramble'sApplesVII
	echo "Testing Bramble'sApplesVIII" && echo "4 3 7 7 2 5 7 8 3 1 -1" | ./Bramble'sApplesVIII
  
clean:  
	rm -f $(EXE)
