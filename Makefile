NAME := libecs.a

CC := cc

SRC_DIR := ./src
OBJ_DIR := ./obj

CFLAGS := -Wall -Wextra -Werror -Wconversion -Wpedantic -Wfatal-errors

INCLUDES := -I./src

################################################################################

SOURCES += $(shell find ./src -type f -name "*.c")
OBJECT_PATHS := $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SOURCES:.c=.o))

################################################################################

ifdef DEBUG
CFLAGS += -g3
endif
ifdef SAN
CFLAGS += -fsanitize=address
endif
ifdef O3
CFLAGS += -O3
endif

################################################################################

.PHONY: all
all: $(NAME)

################################################################################

$(NAME): $(OBJECT_PATHS)
	ar rcs $(NAME) $(OBJECT_PATHS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

################################################################################

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re: fclean all

################################################################################

LIBS := -L. -lecs

.PHONY: example
example: all
	$(CC) $(CFLAGS) $(INCLUDES) -c example.c -o obj/example.o
	$(CC) $(CFLAGS) $(LIBS) $(OBJECT_PATHS) $(OBJ_DIR)/example.o -o ./example
	./example
