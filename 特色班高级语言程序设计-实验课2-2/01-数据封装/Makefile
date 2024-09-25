CC = g++
CFLAGS = -Wall -Wextra -O3

# 设置源文件和可执行文件的变量
# SRC = dynamicArray.cpp
# EXE = dynamicArray.exe
SRC = dynamicArray.cpp studentClass.cpp # tensor.cpp tensorWithStruct.cpp volumeClass.cpp test.cpp
EXE = $(SRC:.cpp=.exe)

all: $(EXE)

# 生成每个可执行文件的规则
%.exe: %.cpp
	$(CC) $< $(CFLAGS) -o $@

# 为每个可执行文件生成测试目标
# test: $(EXE)
# 	@for exe in $(EXE); do \
# 		echo "Testing $$exe"; \
# 		./$$exe <<-EOF \
# 		10 1 2 3 4 5 6 7 8 9 10 \
# 		EOF; \
# 	done

# test:
# 	@ printf "10 1 2 3 4 5 6 7 8 9 10\n10 1 2 3 4 5 6 7 8 9 10" | ./$(EXE)
# 	@ printf "9 1 2 3 4 5 6 7 8 9 \n10 1 2 3 4 5 6 7 8 9 10" | ./$(EXE)

test:
	@test_exe=$(word 1, $(EXE)); echo "Testing $$test_exe"; printf "10 1 2 3 4 5 6 7 8 9 10\n10 1 2 3 4 5 6 7 8 9 10" | ./$$test_exe 
	@printf "\n" 
	@test_exe=$(word 2, $(EXE)); echo "Testing $$test_exe"; printf "1210517 John 67 87 92" | ./$$test_exe

clean:
	rm -f $(EXE)