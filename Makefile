# 编译器
CXX := g++
# 编译选项
CXXFLAGS := -std=c++11 -Wall 

# 源文件目录
SRCDIR := ./mySrc
# 头文件目录
INCDIR := ./include
# 目标文件目录
OBJDIR := ./obj
# 可执行文件名
TARGET_SER := server.out
TARGET_CLI := client.out

# 获取所有源文件
SOURCES := $(wildcard $(SRCDIR)/*.cpp)
# 生成对应的目标文件
OBJECTS := $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(patsubst %.cpp,%.o,$(SOURCES)))

# 不包含 server.o 的目标文件列表
OBJECTS_WITHOUT_SERVER := $(filter-out $(OBJDIR)/server.o, $(OBJECTS))
# 不包含 client.o 的目标文件列表
OBJECTS_WITHOUT_CLIENT := $(filter-out $(OBJDIR)/client.o, $(OBJECTS))
# 包含的头文件
INCLUDES := -I $(INCDIR)/

# 默认目标
all: $(TARGET_SER) $(TARGET_CLI)

# 生成服务器可执行文件
$(TARGET_SER): $(OBJECTS_WITHOUT_CLIENT)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

# 生成客户端可执行文件
$(TARGET_CLI): $(OBJECTS_WITHOUT_SERVER)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

# 生成目标文件
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# 清理生成的文件
clean:
	rm -f $(OBJDIR)/*.o && rm -f $(TARGET_SER) $(TARGET_CLI)
