CC = g++
CFLAGS = -Wall  -Wextra -O3
SRC = $(wildcard *.cpp)
EXE = $(SRC:.cpp=)

all: $(EXE)
%.o: %.cpp  
	$(CC) -c $< $(CFLAGS) -o $@  
%: %.o  
	$(CC) $< -o $@ 

%.exe:%.cpp 
	$(CC) $< $(CFLAGS) -o $@

test: $(EXE)  
	echo "Testing database" && (echo 3; echo name link i; echo name zelda u; echo location hyrule i) | ./database  
	echo "Testing student" && (echo 1 Alice; echo 2 Bob; echo 3 Charlie; echo -1 nn) | ./student  
	echo "Testing planet_escape" && (echo "6e-10"; echo "5e20 2e6 3e15 6e3 1000"; echo 2; echo "20 200"; echo "100 1000") | ./planet_escape  
	echo "Testing bitoperator" && (echo "15 2"; echo "1 4") | ./bitoperator

clean:  
	rm -f $(EXE)
