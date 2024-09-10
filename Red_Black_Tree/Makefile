# 定义编译器和编译选项
CXX = g++
CXXFLAGS = -std=c++11 -Wall -g -w

# 定义目标文件和源文件
OBJS = Red_Black_Node.o Red_Black_Tree.o Red_Black_Show.o main.o
SRCS = Red_Black_Node.cpp Red_Black_Tree.cpp Red_Black_Show.cpp main.cpp
HEADERS = Red_Black_Node.hpp Red_Black_Tree.hpp

# 定义最终生成的可执行文件名
TARGET = Executable

# 默认规则
all: $(TARGET)

# 链接目标文件生成可执行文件
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

# 生成每个目标文件的规则
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清除生成的文件
clean:
	rm -f $(OBJS) $(TARGET)

# 伪目标，避免与文件名冲突
.PHONY: all clean
