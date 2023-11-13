CC = clang
CFLAG = -Wall -Werror

SRCS = main.c External.c FCFS.c io.c linked_list.c MM.c priority_Queue.c process.c Queue.c RR.c 

TARGET = out 

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAG) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)
