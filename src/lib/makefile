## 设置编译环境
CPP := g++
BIN := libst.a
CPP_FLAGS := -Wall -g 
LIB := 

## 获取要编译的源文件，以及把源文件转换为目标文件
CPP_FILES := $(wildcard *.cpp)
OBJS := $(patsubst %.cpp, %.o, $(CPP_FILES))
D_FILES = $(patsubst %.cpp, %.d, $(CPP_FILES))

all: $(BIN)

include $(D_FILES)

## 将目标文件链接成可执行文件或动态库，或静态库
$(BIN) : $(OBJS)
	ar -r $(BIN) $(OBJS)

## 将源文件编译为目标文件
%.o: %.cpp %.d
	$(CPP) $(CPP_FLAGS) -c $< -o $@

%.d:%.cpp
	@set -e; rm -f $@; \
	$(CPP) -MM $(CPP_FLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

## 其他
clean:
	rm -rf *.o $(BIN) $(OBJS) $(D_FILES)