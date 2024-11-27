SOURCES = C_FILES/instructions_0.c C_FILES/instructions_1.c C_FILES/radix.c C_FILES/utils.c \
C_FILES/print.c C_FILES/parser.c C_FILES/selection_sort.c C_FILES/piles.c C_FILES/mini_sort.c \
C_FILES/actions.c C_FILES/merge_sort.c

MAIN_SRC = C_FILES/push_swap.c
BONUS_SRC = C_FILES/_bonus.c C_FILES/get_next_line.c
TESTER_SRC = C_FILES/tester.c

SOURCES_OBJ = $(SOURCES:.c=.o)
MAIN_OBJ = $(MAIN_SRC:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)
TESTER_OBJ = $(TESTER_SRC:.c=.o)

NAME = push_swap
TESTER_NAME = tester
BONUS_NAME = checker

CC = gcc

LIBPATH = libft/
LIBRARY = $(LIBPATH)libft.a

CFLAGS = -Wall -Wextra -Werror
SAN = -fsanitize=address -g

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(SOURCES_OBJ) $(MAIN_OBJ) $(LIBRARY)
	$(CC) $(CFLAGS) $(SOURCES_OBJ) $(MAIN_OBJ) $(LIBRARY) -o $(NAME)

$(TESTER_NAME): $(SOURCES_OBJ) $(TESTER_OBJ) $(LIBRARY)
	$(CC) $(CFLAGS) $(SOURCES_OBJ) $(TESTER_OBJ) $(LIBRARY) -o $(TESTER_NAME)

test: $(TESTER_NAME)
bonus: $(BONUS_NAME)

$(BONUS_NAME): $(SOURCES_OBJ) $(BONUS_OBJ) $(LIBRARY)
	$(CC) $(CFLAGS) $(SOURCES_OBJ) $(BONUS_OBJ) $(LIBRARY) -o $(BONUS_NAME)

clean:
	rm -f $(SOURCES_OBJ) $(MAIN_OBJ) $(BONUS_OBJ) $(TESTER_OBJ)

fclean: clean
	rm -f $(NAME)

debug: $(SOURCES_OBJ) $(MAIN_OBJ) $(LIBRARY)
	$(CC) $(CFLAGS) $(SAN) $(SOURCES_OBJ) $(MAIN_OBJ) $(LIBRARY) -o $(NAME)

re: fclean all

all: $(LIBRARY) $(NAME)

$(LIBRARY):
	$(MAKE) -C $(LIBPATH)
