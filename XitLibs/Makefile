INCLUDES := -Iinclude -Iinclude/coap -Iinclude/json -Iinclude/models -Iinclude/malloc

SRC_DIR := ./
TEST_DIR := tests/
AR_N := XitLib.a
NAME := XitLib.a
CFLAGS := -std=c99 -Werror -Wall -Wextra -Wno-unused-parameter
#CFLAGS :=
TFLAGS := 
CSRC := $(wildcard src/*.c) $(wildcard src/coap/*.c) $(wildcard src/json/*.c) \
	$(wildcard src/malloc/*.c) $(wildcard src/models/*.c)
OBJS := $(CSRC:.c=.o)

.PHONY: default
default: $(NAME);

re: fclean all

tests: fclean $(EXE_N)
	./test
	
all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(AR_N) $^
	
%.o: %.c
	arm-none-eabi-gcc $(INCLUDES) $(CFLAGS) -c $< -o $@
	
parallel: 
	$(MAKE) fclean
	$(MAKE) all -j8
	$(MAKE) clean

fclean:
	rm -rf $(OBJS) tests/*.o $(AR_N)
clean:
	rm -rf $(OBJS) tests/*.o $(AR_N)