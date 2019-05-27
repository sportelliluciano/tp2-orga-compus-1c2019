CFLAGS := -ggdb -O2
CFLAGS += -std=c99 -Wall -Wextra -Wpedantic
CC := gcc

SRCS := $(wildcard src/*.c)
OBJS := $(patsubst src/%.c,obj/%.o,$(SRCS))

EXEC := tp2

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)

obj/%.o: src/%.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(EXEC) *.o core obj

.PHONY: clean
