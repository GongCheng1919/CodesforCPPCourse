CC = g++
CFLAGS = -Wall -Wextra -O3

# 设置源文件和可执行文件的变量
# SRC = dynamicArray.cpp
# EXE = dynamicArray.exe
SRC = DataTime.cpp Link.cpp SaleMannager.cpp employee.cpp
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
	@test_exe=$(word 1, $(EXE)); echo "Testing $$test_exe"; printf "2022 9 1 19 57 58 2022 9 1 19 57 58" | ./$$test_exe 
	@printf "\n" 
	@test_exe=$(word 2, $(EXE)); echo "Testing $$test_exe"; printf "9\n1 2 3 4 5 6 7 8 9\n9\np\np\np\np\ni 10\ni 11\np\np\ni 12" | ./$$test_exe
	@printf "\n" 
	@test_exe=$(word 3, $(EXE)); echo "Testing $$test_exe"; printf "4\nbob Employee 5000\nmike Sales 6000 20000\nkalen Manager 7000 400000\ntom SalesManager 8000 20000 400000" | ./$$test_exe
	@printf "\n" 
	@test_exe=$(word 4, $(EXE)); echo "Testing $$test_exe"; printf "4\nbob Employee 5000\nmike Sales 6000 20000\nkalen Manager 7000 400000\ntom SalesManager 8000 20000 400000" | ./$$test_exe

clean:
	rm -f $(EXE)
