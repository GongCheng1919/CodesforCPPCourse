CC = g++
CFLAGS = -Wall -Wextra -O3

# 设置源文件和可执行文件的变量
SRC = Matrix.cpp
EXE = $(SRC:.cpp=.exe)

all: $(EXE)

# 生成每个可执行文件的规则
%.exe: %.cpp
	$(CC) $< $(CFLAGS) -o $@

# 测试目标
test: $(EXE)
	@test_exe=$(word 1, $(EXE)); echo "Testing $$test_exe"; printf "3 3\n" | ./$$test_exe
	@printf "\n"

clean:
	rm -f $(EXE)
