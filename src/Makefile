.SUFFIXES: .cpp .o
CC=g++

CFLAGS = -Wall -g -pthread

INC = -I.
LIB = -lpthread

SRCS = $(shell ls *.cpp)
OBJS = $(SRCS:.cpp=.o)

TARGET = SimpleHttpServer


all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INC) -o $@ $(OBJS)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INC) -c $<

clean:
	rm -f $(OBJS) $(TARGET)

run:
	make clean
	make all
	./$(TARGET)
