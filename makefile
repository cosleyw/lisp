
CC := gcc
CFLAGS := -Wall -Wextra -pedantic -std=c99 -Werror -g -O2

SRC := $(wildcard src/*.c)
OBJ := $(SRC:.c=.o)

li: main.c li.a( ${OBJ} )
	${CC} $^ ${CFLAGS} -o $@

all: li
clean:
	rm -f li li.a $(OBJ)

.PHONY: all clean

