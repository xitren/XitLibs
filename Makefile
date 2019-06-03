INCLUDES := -Iinclude -Iinclude/coap -Iinclude/json -Iinclude/models \
	-Iinclude/malloc -Itests

#TOOL := gcc
TOOL := arm-none-eabi-gcc
SRC_DIR := ./
TEST_DIR := tests/
AR_N := XitLib.a
NAME := XitLib.a
CFLAGS := -std=c99 -Werror -Wall -Wextra -Os \
	-Wno-unused-parameter -Wno-pointer-to-int-cast -Wno-int-to-pointer-cast \
	-Wno-implicit-fallthrough \
	-mthumb -mcpu=cortex-m7 -mfloat-abi=hard -mfpu=fpv4-sp-d16 --specs=nosys.specs \
	-Wno-int-conversion \
	-fdata-sections -ffunction-sections
CFLAGS_SOFT := -std=c99 -Werror -Wall -Wextra -Os \
	-Wno-unused-parameter -Wno-pointer-to-int-cast -Wno-int-to-pointer-cast \
	-Wno-implicit-fallthrough \
	-mthumb -mcpu=cortex-m3 -mfloat-abi=soft --specs=nosys.specs \
	-Wno-int-conversion -DSMALL \
	-fdata-sections -ffunction-sections
#CFLAGS :=
TFLAGS := 
CSRC := $(wildcard src/*.c) $(wildcard src/coap/*.c) $(wildcard src/json/*.c) \
	$(wildcard src/malloc/*.c) $(wildcard src/models/*.c)
TSRC := $(wildcard tests/*.c)
OBJS := $(CSRC:.c=.o)
TOBJS := $(TSRC:.c=.o)
TEXES := $(TSRC:.c=.exe)

.PHONY: default
default: $(NAME);

re: fclean all

tests: fclean $(EXE_N)
	./test
	
all: $(NAME)
	
soft: 
	make parallel CFLAGS='$(CFLAGS_SOFT)'

test: parallel
	rm -rf $(TEXES)
	make $(TEXES)

$(NAME): $(OBJS)
	ar rcs $(AR_N) $^
	
%.o: %.c
	$(TOOL) $(INCLUDES) $(CFLAGS) -c $< -o $@
	
%.exe: %.o
	$(TOOL) $(INCLUDES) $(TFLAGS) $< $(AR_N) -o $@
	./$@
	
parallel: 
	$(MAKE) fclean
	$(MAKE) all -j8
	$(MAKE) clean
	
fclean:
	rm -rf $(OBJS) $(TOBJS) $(AR_N)
clean:
	rm -rf $(OBJS) $(TOBJS)