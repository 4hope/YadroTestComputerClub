.PHONY: all clean

CC=g++
CFLAGS=-std=c++23 -Wall -Werror -Wextra
INCLUDE=-Iinclude
EXECUTABLE=club

SRCS=$(wildcard src/*.cpp)
INCS=$(wildcard include/*.hpp)
OBJS=$(patsubst src/%.cpp,obj/%.o,$(SRCS))
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) -o $(EXECUTABLE) $(OBJS)

obj/%.o: src/%.cpp $(INCS) | obj
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
obj:
	mkdir obj
clean:
	rm -rf obj
	rm $(EXECUTABLE)
