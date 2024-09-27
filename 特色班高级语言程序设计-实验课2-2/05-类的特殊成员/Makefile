CC = g++
CFLAGS = -Wall  -Wextra -O3
SRC = $(wildcard *.cpp)
EXE = $(SRC:.cpp=.exe)

all: $(EXE)


%.exe:%.cpp 
	$(CC) $< $(CFLAGS) -o $@

test:
	cmd /c "echo Testing database.exe &( echo 3 & echo name link i & echo name zelda u & echo location hyrule i )  | database.exe"
	cmd /c "echo Testing student.exe &( echo 1 Alice & echo 2 Bob & echo 3 Charlie & echo -1 nn )| student.exe"
	cmd /c" echo Testing planet_escape.exe &( echo 6e-10 & echo 5e20 2e6 3e15 6e3 1000 & echo 2 & echo 20 200 & echo 100 1000)| planet_escape.exe"
	cmd /c "echo Testing bitoperater.exe & ( echo 15 2 > 1 4)| bitoperater.exe "

clean:
	del /F /Q $(EXE)