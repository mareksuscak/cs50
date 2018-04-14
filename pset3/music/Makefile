CC ?= clang
CFLAGS ?= -fsanitize=integer -fsanitize=undefined -ggdb3 -O0 -std=c11 -Wall -Werror -Wextra -Wno-sign-compare -Wshadow
LDLIBS ?= -lcs50 -lm

.PHONY: all
all: notes synthesize

notes: helpers.c helpers.h notes.c wav.c wav.h
	$(CC) $(CFLAGS) -o notes helpers.c notes.c wav.c $(LDLIBS)

synthesize: synthesize.c wav.c wav.h helpers.c helpers.h
	$(CC) $(CFLAGS) -o synthesize helpers.c synthesize.c wav.c $(LDLIBS)

.PHONY: clean
clean:
	rm -f notes synthesize *.wav
