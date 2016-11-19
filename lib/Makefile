CC = gcc # C compiler
CFLAGS = -fPIC -Wall -Wextra # C flags
LDFLAGS = cr # linking flags
RM = rm -f  # rm command
AR = ar
TARGET_LIB = libfifo.a # target lib

SRCS = fifo.c # source files
OBJS = $(SRCS:.c=.o)

.PHONY: all
all: ${TARGET_LIB}

$(TARGET_LIB): $(OBJS)
	$(AR) ${LDFLAGS} $@ $^

$(SRCS:.c):%.c
	$(CC) $(CFLAGS) $<

.PHONY: clean
clean:
	${RM} ${TARGET_LIB} ${OBJS} $(SRCS:.c)

