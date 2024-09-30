SRCS = srcs

FILE1 = $(SRCS)/ft_putchar.c
FILE2 = $(SRCS)/ft_putstr.c
FILE3 = $(SRCS)/ft_strcmp.c
FILE4 = $(SRCS)/ft_strlen.c
FILE5 = $(SRCS)/ft_swap.c

SRCS_FILES = $(FILE1) $(FILE2) $(FILE3) $(FILE4)
OBJ_FILES = $(SRCS_FILES:srcs/%.c=srcs/%.o)

CC = cc
CFLAGS = -Iincludes/
TARGET = a.out

$(TARGET): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $(TARGET)

srcs/%.o : srcs/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(TARGET)

all: $(TARGET)

re: fclean all
