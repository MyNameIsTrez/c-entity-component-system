# TODO: Paste 42 header here

################################################################################

NAME := libecs.a

CC := cc

SRC_DIR := ./src
OBJ_DIR := ./obj

CFLAGS := -Wall -Wextra -Werror -Wconversion -Wpedantic -Wfatal-errors

LIBFT_PATH := ../libft
LIBFT_LIB_PATH := $(LIBFT_PATH)/libft.a
LIBFT := -L$(LIBFT_PATH) -lft

LIBS := $(LIBFT) -L. -lecs

INCLUDES_HEADERS += $(LIBFT_PATH)/libft.h ./ecs.h

################################################################################

# TODO: Replace with hardcoded sources before handing in
SOURCES += $(shell find ./src -type f -name "*.c")

################################################################################

# TODO: Replace with hardcoded headers before handing in
HEADERS += $(shell find ./src -type f -name "*.h")

################################################################################

FCLEANED_FILES := $(NAME)

################################################################################

# DEBUG is set to 1 when libctester includes this file
ifdef DEBUG
CFLAGS += -DDEBUG=1
CFLAGS += -DSTATIC=
CFLAGS += -g3
endif

ifdef SAN
CFLAGS += -fsanitize=address
endif

ifdef O3
CFLAGS += -O3
endif

################################################################################

OBJECT_PATHS := $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SOURCES:.c=.o))

HEADERS += $(INCLUDES_HEADERS)

# sort removes duplicates
INCLUDES := $(addprefix -I, $(sort $(dir $(INCLUDES_HEADERS))))

# Only cleans when MAKE_DATA changes.
DATA_FILE := .make_data
MAKE_DATA := $(CFLAGS) $(SOURCES)
PRE_RULES :=
ifneq ($(shell echo "$(MAKE_DATA)"), $(shell cat "$(DATA_FILE)" 2> /dev/null))
PRE_RULES += clean
endif

################################################################################

.PHONY: all
all: $(PRE_RULES) $(NAME)

################################################################################

$(LIBFT_LIB_PATH):
	@$(MAKE) -C $(dir $(LIBFT_PATH))

################################################################################

$(NAME): $(LIBFT_LIB_PATH) $(OBJECT_PATHS)
	ar rcs $(NAME) $(OBJECT_PATHS)
	@echo "$(MAKE_DATA)" > $(DATA_FILE)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

################################################################################

.PHONY: debug
debug:
	@$(MAKE) DEBUG=1 all

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)

.PHONY: fclean
fclean: clean
	@$(MAKE) -C $(dir $(LIBFT)) fclean
	rm -f $(FCLEANED_FILES)

.PHONY: re
re: fclean all

.PHONY: example
example: all
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) ./example/main.c -o ./example.out

################################################################################
