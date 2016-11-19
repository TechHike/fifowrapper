$(CC) = gcc
$(RM) = rm -f

all: test_fifo

.PHONY: clean
clean:
	$(RM) test_fifo

.PHONY: test_fifo
test_fifo: test_fifo.c
	$(CC) -o test_fifo test_fifo.c -L../lib/ -lfifo
