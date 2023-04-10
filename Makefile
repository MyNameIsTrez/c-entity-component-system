CFLAGS := -Wall -Wextra -Werror -Wconversion -Wpedantic -Wfatal-errors

ifdef DEBUG
CFLAGS += -g3
endif
ifdef SAN
CFLAGS += -fsanitize=address
endif
ifdef O3
CFLAGS += -O3
endif

.PHONY: example
example:
	$(CC) $(CFLAGS) $(LIBS) $(OBJECT_PATHS) example.c -o ./example
	./example
